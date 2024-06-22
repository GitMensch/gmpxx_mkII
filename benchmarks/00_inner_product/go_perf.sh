uname -a
cat /proc/cpuinfo | grep 'model name' | head -1
echo

FLAMEGRAPH_DIR="/home/docker/FlameGraph"

executables=(
    "inner_product_gmp_10_naive"
    "inner_product_gmp_11_openmp"
    "inner_product_gmp_12_0_mpblas_orig"
    "inner_product_gmp_12_0_mpblas_mkII"
    "inner_product_gmp_12_0_mpblas_mkIISR"
    "inner_product_gmp_12_1_mpblas_orig"
    "inner_product_gmp_12_1_mpblas_mkII"
    "inner_product_gmp_12_1_mpblas_mkIISR"
    "inner_product_gmp_12_2_mpblas_orig"
    "inner_product_gmp_12_2_mpblas_mkII"
    "inner_product_gmp_12_2_mpblas_mkIISR"
    "inner_product_gmp_13_0_mpblas_openmp_orig"
    "inner_product_gmp_13_0_mpblas_openmp_mkII"
    "inner_product_gmp_13_0_mpblas_openmp_mkIISR"
    "inner_product_gmp_13_1_mpblas_openmp_orig"
    "inner_product_gmp_13_1_mpblas_openmp_mkII"
    "inner_product_gmp_13_1_mpblas_openmp_mkIISR"
)

args="500000000 512"
for exe in "${executables[@]}"; do
    echo "Profiling $exe"
    sudo perf record -o perf.data_${exe} -g -- ./$exe $args 
    sudo perf script -i perf.data_${exe} > out_${exe}.perf
    cat out_${exe}.perf | $FLAMEGRAPH_DIR/stackcollapse-perf.pl | $FLAMEGRAPH_DIR/flamegraph.pl > flamegraph_${exe}.svg
    echo "Flamegraph for $exe generated."
    echo
done
