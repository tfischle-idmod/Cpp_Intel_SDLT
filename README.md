# Cpp_Intel_SDLT
Using SDLT from Intel compiler with Visual Studio

Some remarks:
- Compiler version 2021.3.0
- had enable C++11 (or C++17)  (/Qstd=c++17)
- Enable Enhanced Instruction Set: Intel(R) Advanced Vector Extensions 2 (/arch:CORE-AVX2)
- Preprocessor: define __INTEL_CXX11_MODE__
- Error: _FEATURE_KNCNI is undefined. Symbol is neither defined in immintrin.h nor mentioned in http://gensoft.pasteur.fr/docs/icc/xe_2016/en/compiler_c/common/core/GUID-28ADC0C1-8E39-43E7-BB8D-24851AF00F97.htm  (Bug?) 

Commented out and set to 0 in simd_traits.h, line 54
```code
private:
    static int populate_widest_supported_lane_count() {
        int vector_register_width_in_bytes;
        #ifdef __INTEL_COMPILER
            if ((true == _may_i_use_cpu_feature(_FEATURE_AVX512F)) ||
                (/*true == _may_i_use_cpu_feature(_FEATURE_KNCNI)*/ 0)) {
                vector_register_width_in_bytes = 64;
            } else {
                if ((true == _may_i_use_cpu_feature(_FEATURE_AVX)) ||
                    (true == _may_i_use_cpu_feature(_FEATURE_AVX2))) {
                    vector_register_width_in_bytes = 32;
                } else {
                    vector_register_width_in_bytes = 16;
                }
            }
        ...
    ...
```    




