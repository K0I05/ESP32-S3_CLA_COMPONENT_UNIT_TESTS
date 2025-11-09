import numpy as np
import os

def format_c_array(arr, name, dtype="double"):
    """Formats a numpy array into a C-style array string."""
    if arr.ndim == 1:
        return f"static const {dtype} {name}[{len(arr)}] = {{ {', '.join(map(str, arr))} }};"
    elif arr.ndim == 2:
        rows = ["    { " + ", ".join(map(str, row)) + " }" for row in arr]
        return f"static const {dtype} {name}[{arr.shape[0]}][{arr.shape[1]}] = {{\n" + ",\n".join(rows) + "\n};"
    elif arr.ndim == 3:
        cases = []
        for case in arr:
            rows = ["        { " + ", ".join(map(str, row)) + " }" for row in case]
            cases.append("    {\n" + ",\n".join(rows) + "\n    }")
        return f"static const {dtype} {name}[{arr.shape[0]}][{arr.shape[1]}][{arr.shape[2]}] = {{\n" + ",\n".join(cases) + "\n};"
    return ""

def generate_calibration_test_data(num_samples=250, filename="cla_ellipsoid_calibration_data.h"):
    """
    Generates test data for validating ellipsoid calibration parameter extraction.
    """
    np.random.seed(42)

    num_test_cases = 5
    all_raw_points = []
    all_hard_iron_offsets = []
    all_soft_iron_matrices = []

    # Generate Ideal Spherical Data once, as it's the same for all cases
    ideal_points = []
    phi = np.linspace(0, np.pi, int(np.sqrt(num_samples)))
    theta = np.linspace(0, 2 * np.pi, int(np.sqrt(num_samples)))
    for p in phi:
        for t in theta:
            x = np.sin(p) * np.cos(t)
            y = np.sin(p) * np.sin(t)
            z = np.cos(p)
            ideal_points.append([x, y, z])
    ideal_points = np.array(ideal_points)
    # Ensure we have exactly num_samples
    if len(ideal_points) < num_samples:
        extra_points = np.random.rand(num_samples - len(ideal_points), 3) * 2 - 1
        extra_points /= np.linalg.norm(extra_points, axis=1)[:, np.newaxis]
        ideal_points = np.vstack([ideal_points, extra_points])
    
    ideal_points = ideal_points[:num_samples]

    for i in range(num_test_cases):
        # 1. Define unique Ground Truth Calibration Parameters for each case
        # Hard-iron offset (bias)
        hard_iron_offset = np.random.uniform(-50, 50, 3)

        # Soft-iron distortion matrix (upper triangular, to match the C algorithm's output)
        soft_iron_matrix = np.array([
            [np.random.uniform(0.8, 1.5), np.random.uniform(-0.3, 0.3), np.random.uniform(-0.3, 0.3)],
            [0.0, np.random.uniform(0.8, 1.5), np.random.uniform(-0.3, 0.3)],
            [0.0, 0.0, np.random.uniform(0.8, 1.5)]
        ])

        # 3. Generate "Raw" Distorted Data by inverting the calibration process
        # raw = (W_inv * ideal) + offset
        try:
            soft_iron_inv = np.linalg.inv(soft_iron_matrix)
        except np.linalg.LinAlgError:
            print(f"Error: The soft-iron matrix for case {i} is singular and cannot be inverted.")
            continue

        raw_points = np.dot(soft_iron_inv, ideal_points.T).T + hard_iron_offset

        all_raw_points.append(raw_points)
        all_hard_iron_offsets.append(hard_iron_offset)
        all_soft_iron_matrices.append(soft_iron_matrix)

    # 4. Prepare data for C header file
    raw_points_3d = np.array(all_raw_points)
    hard_iron_2d = np.array(all_hard_iron_offsets)
    soft_iron_3d = np.array(all_soft_iron_matrices)

    # 5. Generate C header file content
    header_content = f"""/*
 *
 *                MIT License (MIT) 
 *
 *        AUTO GENERATED CODE - DO NOT MODIFY
 *
 * Copyright (c) 2025 Eric Gionet (gionet.c.eric@gmail.com)
 *
 */
#ifndef __CLA_ELLIPSOID_CALIBRATION_TEST_DATA_H__
#define __CLA_ELLIPSOID_CALIBRATION_TEST_DATA_H__

#include <stdint.h>

static const uint8_t cla_ellipsoid_calibration_cases = {num_test_cases};
static const uint16_t cla_ellipsoid_calibration_samples = {num_samples};

{format_c_array(raw_points_3d, 'cla_ellipsoid_calibration_a_samples')}

{format_c_array(hard_iron_2d, 'cla_ellipsoid_calibration_hard_iron_x_offsets')}

{format_c_array(soft_iron_3d, 'cla_ellipsoid_calibration_soft_iron_x_distortions')}

#endif // __CLA_ELLIPSOID_CALIBRATION_TEST_DATA_H__
"""

    # Write to file
    with open(filename, "w", encoding="utf-8") as f:
        f.write(header_content)
    print(f"Generated test data file: {filename}")


if __name__ == "__main__":
    # Get the directory of the script
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Define the output path relative to the script
    output_filename = os.path.join(script_dir, "../data/cla_ellipsoid_calibration_data.h")
    
    generate_calibration_test_data(filename=output_filename)
