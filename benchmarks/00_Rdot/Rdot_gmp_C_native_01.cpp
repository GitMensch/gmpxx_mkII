#include <iostream>
#include <chrono>
#include <gmp.h>

#if defined USE_ORIGINAL_GMPXX
#include <gmpxx.h>
#else
#include "gmpxx_mkII.h"
#if !defined ___GMPXX_STRICT_COMPATIBILITY___
using namespace gmp;
#endif
#endif

#include "Rdot.hpp"

#define MFLOPS 1e+6

gmp_randstate_t state;

void _Rdot(int64_t n, mpf_t *dx, int64_t incx, mpf_t *dy, int64_t incy, mpf_t *ans) {
    int64_t i;
    mpf_t temp, templ;

    if (incx != 1 || incy != 1) {
        printf("Not supported, exitting\n");
        exit(-1);
    }

    mpf_set_d(*ans, 0.0);
    mpf_init(temp);
    mpf_init(templ);
    mpf_set_d(temp, 0.0);
    mpf_set_d(templ, 0.0);

    for (i = 0; i < n; i++) {
        mpf_mul(templ, dx[i], dy[i]);
        mpf_add(temp, temp, templ);
    }

    mpf_swap(*ans, temp);

    mpf_clear(temp);
    mpf_clear(templ);
}

void init_mpf_vec(mpf_t *vec, int n, int prec) {
    for (int i = 0; i < n; i++) {
        mpf_init2(vec[i], prec);
        mpf_urandomb(vec[i], state, prec);
    }
}

void clear_mpf_vec(mpf_t *vec, int n) {
    for (int i = 0; i < n; i++) {
        mpf_clear(vec[i]);
    }
}

int main(int argc, char **argv) {
    gmp_randinit_default(state);
    gmp_randseed_ui(state, 42);

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <vector size> <precision>" << std::endl;
        return 1;
    }

    int N = std::atoi(argv[1]);
    int prec = std::atoi(argv[2]);
    mpf_set_default_prec(prec);

    mpf_t *vec1 = new mpf_t[N];
    mpf_t *vec2 = new mpf_t[N];
    mpf_t _ans, dot_product;

    mpf_init2(dot_product, prec);
    mpf_init2(_ans, prec);
    init_mpf_vec(vec1, N, prec);
    init_mpf_vec(vec2, N, prec);

    mpf_class *vec1_mpf_class = new mpf_class[N];
    mpf_class *vec2_mpf_class = new mpf_class[N];
    mpf_class ans;

    for (int i = 0; i < N; i++) {
        vec1_mpf_class[i] = mpf_class(vec1[i]);
        vec2_mpf_class[i] = mpf_class(vec2[i]);
    }

    auto start = std::chrono::high_resolution_clock::now();
    _Rdot(N, vec1, 1, vec2, 1, &_ans);
    auto end = std::chrono::high_resolution_clock::now();

    ans = Rdot(N, vec1_mpf_class, 1, vec2_mpf_class, 1);

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " s" << std::endl;
    std::cout << "MFLOPS: " << (2.0 * double(N) - 1.0) / elapsed_seconds.count() / MFLOPS << std::endl;

    mpf_class _tmp;
    _tmp = abs(mpf_class(_ans) - ans);
    std::cout << "DIFF: ";
    gmp_printf("%.4Fg ", _tmp.get_mpf_t());
    if (_tmp < 1e-5)
        std::cout << "OK" << std::endl;
    else
        std::cout << "NG" << std::endl;

    clear_mpf_vec(vec1, N);
    clear_mpf_vec(vec2, N);
    mpf_clear(dot_product);
    delete[] vec1;
    delete[] vec2;

    return 0;
}
