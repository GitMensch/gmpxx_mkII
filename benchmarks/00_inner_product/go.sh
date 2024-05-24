uname -a
cat /proc/cpuinfo | grep 'model name' | head -1
echo
executables=(
    "inner_product_gmp_10_naive"
    "inner_product_gmp_11_openmp"
    "inner_product_gmp_12_mpblas_orig"
    "inner_product_gmp_12_mpblas_mkII"
    "inner_product_gmp_12_mpblas_compat"
    "inner_product_gmp_12_mpblas_mkIISR"
    "inner_product_gmp_13_mpblas_openmp"
    "inner_product_gmp_13_mpblas_openmp_compat"
    "inner_product_gmp_13_mpblas_openmp_mkII"
    "inner_product_gmp_13_mpblas_openmp_mkIISR"
)
for exe in "${executables[@]}"; do
    echo "./$exe 10000000 1024"
    ./$exe 10000000 1024
    if [ -f gmon.out ]; then
        mv gmon.out "gmon_${exe}.out"
    fi
    echo
done
