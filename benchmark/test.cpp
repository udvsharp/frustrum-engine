#include <benchmark/benchmark.h>
#include <vector>

const int kRows = 10000;
const int kCols = 10000;

// Initialize a 2D array with some values
int16_t matrix[kRows][kCols];

// Benchmark for row-major traversal
static void BM_RowMajor(benchmark::State& state) {
    for (auto _ : state) {
        int sum = 0;
        for (int i = 0; i < kRows; ++i) {
            for (int j = 0; j < kCols; ++j) {
                benchmark::DoNotOptimize(sum += matrix[i][j]);
            }
        }
        benchmark::ClobberMemory();  // Ensure sum isn't optimized out
    }
}
BENCHMARK(BM_RowMajor);

// Benchmark for column-major traversal
static void BM_ColMajor(benchmark::State& state) {
    for (auto _ : state) {
        int sum = 0;
        for (int j = 0; j < kCols; ++j) {
            for (int i = 0; i < kRows; ++i) {
                benchmark::DoNotOptimize(sum += matrix[i][j]);
            }
        }
        benchmark::ClobberMemory();  // Ensure sum isn't optimized out
    }
}
BENCHMARK(BM_ColMajor);

BENCHMARK_MAIN();
