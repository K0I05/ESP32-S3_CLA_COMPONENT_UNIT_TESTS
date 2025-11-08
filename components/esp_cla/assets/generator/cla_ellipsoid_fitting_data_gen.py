#
# The MIT License (MIT)
#
# Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#!/usr/bin/env python
import numpy as np

def generate_ellipsoid_data(num_samples, center, radii, rotation_angles, noise_level=0.01):
    """
    Generates sample points on a rotated and translated ellipsoid.
    """
    # Generate points on a unit sphere
    u = np.random.uniform(0, 2 * np.pi, num_samples)
    v = np.random.uniform(0, np.pi, num_samples)
    x = np.cos(u) * np.sin(v)
    y = np.sin(u) * np.sin(v)
    z = np.cos(v)

    # Scale to ellipsoid radii
    points = np.vstack((x * radii[0], y * radii[1], z * radii[2]))

    # Rotation matrices
    rx, ry, rz = rotation_angles
    Rx = np.array([[1, 0, 0], [0, np.cos(rx), -np.sin(rx)], [0, np.sin(rx), np.cos(rx)]])
    Ry = np.array([[np.cos(ry), 0, np.sin(ry)], [0, 1, 0], [-np.sin(ry), 0, np.cos(ry)]])
    Rz = np.array([[np.cos(rz), -np.sin(rz), 0], [np.sin(rz), np.cos(rz), 0], [0, 0, 1]])
    R = Rz @ Ry @ Rx

    # Rotate and translate
    rotated_points = R @ points
    translated_points = rotated_points + np.array(center).reshape(3, 1)

    # Add noise
    noise = np.random.normal(0, noise_level, translated_points.shape)
    noisy_points = translated_points + noise

    return noisy_points.T

def get_ellipsoid_coeffs(center, radii, rotation_angles):
    """
    Calculates the coefficients of the general quadratic form of an ellipsoid.
    """
    # Rotation matrix
    rx, ry, rz = rotation_angles
    Rx = np.array([[1, 0, 0], [0, np.cos(rx), -np.sin(rx)], [0, np.sin(rx), np.cos(rx)]])
    Ry = np.array([[np.cos(ry), 0, np.sin(ry)], [0, 1, 0], [-np.sin(ry), 0, np.cos(ry)]])
    Rz = np.array([[np.cos(rz), -np.sin(rz), 0], [np.sin(rz), np.cos(rz), 0], [0, 0, 1]])
    R = Rz @ Ry @ Rx

    # Diagonal matrix of squared semi-axes
    D = np.diag([1/radii[0]**2, 1/radii[1]**2, 1/radii[2]**2])

    # Matrix of the quadratic form
    M = R @ D @ R.T

    # Coefficients
    A, B, C = M[0, 0], M[1, 1], M[2, 2]
    D_coeff, E_coeff, F_coeff = M[0, 1], M[0, 2], M[1, 2]

    # Linear term coefficients
    c_vec = np.array(center)
    G = -A * c_vec[0] - D_coeff * c_vec[1] - E_coeff * c_vec[2]
    H = -D_coeff * c_vec[0] - B * c_vec[1] - F_coeff * c_vec[2]
    I = -E_coeff * c_vec[0] - F_coeff * c_vec[1] - C * c_vec[2]

    # The equation is of the form:
    # Ax^2 + By^2 + Cz^2 + 2Dxy + 2Exz + 2Fyz + 2Gx + 2Hy + 2Iz + J = 0
    # where J = c_vec.T * M * c_vec - 1
    # We want to solve for Ax^2 + ... = 1, which is equivalent to
    # (A/-J)x^2 + ... = 1
    J_calc = c_vec.T @ M @ c_vec
    
    # The equation is x'Mx - 2c'Mx + c'Mc = 1
    # Ax^2+...+2Dxy+...+2Gx+...+c'Mc-1=0
    # We want Ax^2+...+2Gx=1, so we need to scale by 1/(1-(c'Mc))
    scale = 1.0 / (1.0 - J_calc)

    # The C code solves for [A, B, C, D, E, F, G, H, I] in the equation
    # Ax^2 + By^2 + Cz^2 + D(xy) + E(xz) + F(yz) + Gx + Hy + Iz = 1
    # The python script calculates coefficients for
    # Ax^2 + By^2 + Cz^2 + 2Dxy + 2Exz + 2Fyz + 2Gx + 2Hy + 2Iz = 1-J_calc
    # So we need to scale all coefficients by 1/(1-J_calc)

    return [c * scale for c in [A, B, C, 2*D_coeff, 2*E_coeff, 2*F_coeff, 2*G, 2*H, 2*I]]

def write_header_file(filename, test_cases):
    with open(filename, "w", encoding="utf-8") as f:
        f.write("/*                  MIT License (MIT)                       */\n")
        f.write("/*           AUTO GENERATED CODE - DO NOT MODIFY            */\n")
        f.write("/* Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com) */\n\n")
        f.write("#ifndef __CLA_ELLIPSOID_FITTING_DATA_H__\n")
        f.write("#define __CLA_ELLIPSOID_FITTING_DATA_H__\n\n")
        f.write("#include <stdint.h>\n\n")
        f.write("#ifdef __cplusplus\n")
        f.write('extern "C" {\n')
        f.write("#endif\n\n")
        f.write("/**\n * public constant definitions\n */\n\n")
        f.write(f"static const uint8_t cla_ellipsoid_fitting_cases = {len(test_cases)};\n\n")

        samples_str = "static const double cla_ellipsoid_fitting_samples[{}][250][3] = {{\n".format(len(test_cases))
        coeffs_str = "static const double cla_ellipsoid_fitting_coeffs[{}][9] = {{\n".format(len(test_cases))

        for i, case in enumerate(test_cases):
            samples_str += "    {\n"
            for sample in case['samples']:
                samples_str += "        {{{:f}, {:f}, {:f}}},\n".format(sample[0], sample[1], sample[2])
            samples_str += "    },\n"

            coeffs_str += "    {{".format(i)
            coeffs_str += ", ".join(["{:.4f}".format(c) for c in case['coeffs']])
            coeffs_str += "},\n"

        samples_str += "};\n\n"
        coeffs_str += "};\n\n"

        f.write(samples_str)
        f.write(coeffs_str)

        f.write("#ifdef __cplusplus\n")
        f.write("}\n")
        f.write("#endif\n\n")
        f.write("#endif  // __CLA_ELLIPSOID_FITTING_DATA_H__\n")

if __name__ == "__main__":
    # Test Case 1: From existing data
    case1_coeffs = [0.4444, 1.0, 1.7778, 0.0, 0.0, 0.0, -0.6667, -0.3333, -0.4444]
    # For this example, we can't perfectly regenerate the original noisy samples,
    # so we'll generate new ones based on the coefficients.
    # This is complex, so we'll define a new simple ellipsoid for demonstration.

    # Test Case 2: A new generated ellipsoid
    center2 = [1.0, 2.0, 3.0]
    radii2 = [4.0, 5.0, 6.0]
    rotation2 = [np.pi/6, np.pi/4, np.pi/3] # 30, 45, 60 degrees
    samples2 = generate_ellipsoid_data(250, center2, radii2, rotation2, noise_level=0.05)
    coeffs2 = get_ellipsoid_coeffs(center2, radii2, rotation2)

    test_cases = [
        # We will generate two new test cases as regenerating the first one is non-trivial
        {
            'samples': generate_ellipsoid_data(250, [0.5, -0.2, 0.8], [1.5, 0.75, 2.0], [0.1, 0.2, 0.3]),
            'coeffs': get_ellipsoid_coeffs([0.5, -0.2, 0.8], [1.5, 0.75, 2.0], [0.1, 0.2, 0.3])
        },
        {
            'samples': samples2,
            'coeffs': coeffs2
        }
    ]

    output_filename = "../data/cla_ellipsoid_fitting_data.h"
    write_header_file(output_filename, test_cases)
    print(f"Generated {output_filename} with {len(test_cases)} test cases.")
