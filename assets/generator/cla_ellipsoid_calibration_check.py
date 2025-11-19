import numpy as np

# Ellipsoid coefficients from previous calculation
#coeffs = np.array([0.000018, 0.000244, 0.000047, 0.000001, -0.000002, 0.000013, 0.003023, -0.019681, 0.004662])
#coeffs = np.array([-0.000000, -0.000086, -0.000006, 0.000000, -0.000000, 0.000045, -0.000019, 0.018654, -0.004782])
coeffs = np.array([-0.000000, -0.000079, -0.000006, -0.000002, 0.000001, 0.000046, 0.000273, 0.018045, -0.005044])

def get_calibration_parameters(coeffs):
    """
    Derives hard-iron offset and soft-iron distortion matrix from ellipsoid coefficients.
    
    Coefficients are [A, B, C, D, E, F, G, H, I] from the equation:
    Ax^2 + By^2 + Cz^2 + Dxy + Exz + Fyz + Gx + Hy + Iz = 1
    
    Returns:
        hard_iron: 3x1 offset vector
        soft_iron: 3x3 distortion correction matrix
    """
    A, B, C, D, E, F, G, H, I = coeffs
    
    # 1. Construct the M matrix (symmetric 3x3) from quadratic coefficients
    M = np.array([
        [A,     D/2.0, E/2.0],
        [D/2.0, B,     F/2.0],
        [E/2.0, F/2.0, C    ]
    ])
    
    # 2. Construct the b vector from linear coefficients
    b = np.array([G, H, I])
    
    print("M matrix:")
    print(M)
    print("\nb vector:")
    print(b)
    
    # 3. Calculate Hard-Iron offset: offset = -0.5 * M_inv * b
    M_inv = np.linalg.inv(M)
    hard_iron = -0.5 * M_inv @ b
    
    print("\nM_inv matrix:")
    print(M_inv)
    print("\nHard-Iron Offset:")
    print(hard_iron)
    
    # 4. Calculate the scalar 's'
    # The equation is Ax^2 + ... + Gx + Hy + Iz = 1 (J = -1 in standard form)
    # s = 1 / ((1/4) * b^T * M_inv * b - J)
    # s = 1 / ((1/4) * b^T * M_inv * b + 1)
    b_dot_Minv_b = b.T @ M_inv @ b
    s = 1.0 / ((b_dot_Minv_b / 4.0) + 1.0)
    
    print(f"\nb^T * M_inv * b: {b_dot_Minv_b:.6f}")
    print(f"Scalar s: {s:.6f}")
    
    # 5. Calculate Soft-Iron correction matrix W from scaled M
    M_scaled = M * s
    
    print("\nM_scaled matrix:")
    print(M_scaled)
    
    # 6. Use Cholesky Decomposition: M_scaled = L * L^T, then W = L^T
    try:
        L = np.linalg.cholesky(M_scaled)
        soft_iron = L.T
        
        print("\nCholesky L matrix:")
        print(L)
        print("\nSoft-Iron Distortion Matrix W (L^T):")
        print(soft_iron)
        
    except np.linalg.LinAlgError:
        print("\nWarning: Cholesky decomposition failed. Matrix might not be positive definite.")
        print("Using eigenvalue decomposition instead...")
        
        # Alternative: Use eigenvalue decomposition
        eigenvalues, eigenvectors = np.linalg.eig(M_scaled)
        print(f"\nEigenvalues: {eigenvalues}")
        
        # W = V * sqrt(D) where M_scaled = V * D * V^T
        soft_iron = eigenvectors @ np.diag(np.sqrt(np.abs(eigenvalues)))
        
        print("\nSoft-Iron Distortion Matrix W (from eigendecomposition):")
        print(soft_iron)
    
    return hard_iron, soft_iron

# Calculate calibration parameters
hard_iron, soft_iron = get_calibration_parameters(coeffs)

print("\n" + "="*60)
print("FINAL CALIBRATION PARAMETERS")
print("="*60)
print("\nHard-Iron Offset (center of ellipsoid):")
print(f"X: {hard_iron[0]:12.6f}")
print(f"Y: {hard_iron[1]:12.6f}")
print(f"Z: {hard_iron[2]:12.6f}")

print("\nSoft-Iron Distortion Matrix W:")
for i, row in enumerate(soft_iron):
    print(f"Row {i}: [{row[0]:12.6f}, {row[1]:12.6f}, {row[2]:12.6f}]")

print("\n" + "="*60)
print("\nC Array Format - Hard-Iron Offset:")
print("{" + f"{hard_iron[0]:.6f}, {hard_iron[1]:.6f}, {hard_iron[2]:.6f}" + "}")

print("\nC Array Format - Soft-Iron Matrix:")
for row in soft_iron:
    print("    {" + f"{row[0]:.6f}, {row[1]:.6f}, {row[2]:.6f}" + "},")
print("="*60)

# Verify the calibration by checking a few sample points
print("\n\nVERIFICATION - Applying calibration to sample points:")
print("="*60)

# Take a few sample points from the original data
sample_indices = [0, 50, 100, 150, 200, 249]
hmc5883l_samples = np.array([
    [-55.0, 66.0, -143.0],   # index 0
    [-149.0, 84.0, -52.0],   # index 50
    [-271.0, 62.0, -142.0],  # index 100
    [-267.0, 90.0, -102.0],  # index 150
    [-194.0, 48.0, -248.0],  # index 200
    [-75.0, 64.0, -192.0]    # index 249
])

for i, sample in enumerate(hmc5883l_samples):
    # Apply calibration: calibrated = W * (raw - offset)
    centered = sample - hard_iron
    calibrated = soft_iron @ centered
    magnitude = np.linalg.norm(calibrated)
    
    print(f"\nSample {sample_indices[i]}:")
    print(f"  Raw:        [{sample[0]:7.1f}, {sample[1]:7.1f}, {sample[2]:7.1f}]")
    print(f"  Calibrated: [{calibrated[0]:7.3f}, {calibrated[1]:7.3f}, {calibrated[2]:7.3f}]")
    print(f"  Magnitude:  {magnitude:.3f}")