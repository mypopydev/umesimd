#ifndef UME_SIMD_PLUGIN_NATIVE_AVX512
#define UME_SIMD_PLUGIN_NATIVE_AVX512


#include <type_traits>

#include "UMESimdInterface.h"

#include "UMESimdPluginScalarEmulation.h"

#include <immintrin.h>
namespace UME
{
namespace SIMD
{   

    // forward declarations of simd types classes;
    template<typename SCALAR_TYPE, uint32_t VEC_LEN>       class SIMDVecAVX512Mask;
    template<typename SCALAR_UINT_TYPE, uint32_t VEC_LEN>  class SIMDVecAVX512_u;
    template<typename SCALAR_INT_TYPE, uint32_t VEC_LEN>   class SIMDVecAVX512_i;
    template<typename SCALAR_FLOAT_TYPE, uint32_t VEC_LEN> class SIMDVecAVX512_f;

    // ********************************************************************************************
    // MASK VECTORS
    // ********************************************************************************************
    template<typename MASK_BASE_TYPE, uint32_t VEC_LEN>
    struct SIMDVecAVX512Mask_traits {};

    template<>
    struct SIMDVecAVX512Mask_traits<bool, 1> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 2> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 4> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 8> { 
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 16> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 32> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 64> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    template<>
    struct SIMDVecAVX512Mask_traits<bool, 128> {
        static bool TRUE() {return true;};
        static bool FALSE() {return false;};
    };
    
    // MASK_BASE_TYPE is the type of element that will represent single entry in
    //                mask register. This can be for examle a 'bool' or 'unsigned int' or 'float'
    //                The actual representation depends on how the underlying instruction
    //                set handles the masks/mask registers. For scalar emulation the mask vetor should
    //                be represented using a boolean values. Bool in C++ has one disadventage: it is possible
    //                for the compiler to implicitly cast it to integer. To forbid this casting operations from
    //                happening the default type has to be wrapped into a class. 
    template<typename MASK_BASE_TYPE, uint32_t VEC_LEN>
    class SIMDVecAVX512Mask final : public SIMDMaskBaseInterface< SIMDVecAVX512Mask<MASK_BASE_TYPE, VEC_LEN>,
                                                               MASK_BASE_TYPE,
                                                               VEC_LEN>
    {   
        typedef ScalarTypeWrapper<MASK_BASE_TYPE> MASK_SCALAR_TYPE; // Wrapp-up MASK_BASE_TYPE (int, float, bool) with a class
        typedef SIMDVecAVX512Mask_traits<MASK_BASE_TYPE, VEC_LEN> MASK_TRAITS;
    private:
        MASK_SCALAR_TYPE mMask[VEC_LEN]; // each entry represents single mask element. For real SIMD vectors, mMask will be of mask intrinsic type.
    public:
        SIMDVecAVX512Mask() {
            UME_EMULATION_WARNING();
            for(int i = 0; i < VEC_LEN; i++)
            {
                mMask[i] = MASK_SCALAR_TYPE(MASK_TRAITS::FALSE()); // Iniitialize MASK with FALSE value. False value depends on mask representation.
            }
        }

        // Regardless of the mask representation, the interface should only allow initialization using 
        // standard bool or using equivalent mask
        SIMDVecAVX512Mask( bool m ) {
            UME_EMULATION_WARNING();
            for(int i = 0; i < VEC_LEN; i++)
            {
                mMask[i] = MASK_SCALAR_TYPE(m);
            }
        }
        
        // TODO: this should be handled using variadic templates, but unfortunatelly Visual Studio does not support this feature...
        SIMDVecAVX512Mask( bool m0, bool m1 )
        {
            mMask[0] = MASK_SCALAR_TYPE(m0); 
            mMask[1] = MASK_SCALAR_TYPE(m1);
        }

        SIMDVecAVX512Mask( bool m0, bool m1, bool m2, bool m3 )
        {
            mMask[0] = MASK_SCALAR_TYPE(m0); 
            mMask[1] = MASK_SCALAR_TYPE(m1); 
            mMask[2] = MASK_SCALAR_TYPE(m2); 
            mMask[3] = MASK_SCALAR_TYPE(m3);
        };

        SIMDVecAVX512Mask( bool m0, bool m1, bool m2, bool m3,
                                bool m4, bool m5, bool m6, bool m7 )
        {
            mMask[0] = MASK_SCALAR_TYPE(m0); mMask[1] = MASK_SCALAR_TYPE(m1);
            mMask[2] = MASK_SCALAR_TYPE(m2); mMask[3] = MASK_SCALAR_TYPE(m3);
            mMask[4] = MASK_SCALAR_TYPE(m4); mMask[5] = MASK_SCALAR_TYPE(m5);
            mMask[6] = MASK_SCALAR_TYPE(m6); mMask[7] = MASK_SCALAR_TYPE(m7);
        }

        SIMDVecAVX512Mask( bool m0,  bool m1,  bool m2,  bool m3,
                                bool m4,  bool m5,  bool m6,  bool m7,
                                bool m8,  bool m9,  bool m10, bool m11,
                                bool m12, bool m13, bool m14, bool m15 )
        {
            mMask[0] = MASK_SCALAR_TYPE(m0);  mMask[1] = MASK_SCALAR_TYPE(m1);
            mMask[2] = MASK_SCALAR_TYPE(m2);  mMask[3] = MASK_SCALAR_TYPE(m3);
            mMask[4] = MASK_SCALAR_TYPE(m4);  mMask[5] = MASK_SCALAR_TYPE(m5);
            mMask[6] = MASK_SCALAR_TYPE(m6);  mMask[7] = MASK_SCALAR_TYPE(m7);
            mMask[8] = MASK_SCALAR_TYPE(m8);  mMask[9] = MASK_SCALAR_TYPE(m9);
            mMask[10] = MASK_SCALAR_TYPE(m10); mMask[11] = MASK_SCALAR_TYPE(m11);
            mMask[12] = MASK_SCALAR_TYPE(m12); mMask[13] = MASK_SCALAR_TYPE(m13);
            mMask[14] = MASK_SCALAR_TYPE(m14); mMask[15] = MASK_SCALAR_TYPE(m15);
        }

        SIMDVecAVX512Mask( bool m0,  bool m1,  bool m2,  bool m3,
                                bool m4,  bool m5,  bool m6,  bool m7,
                                bool m8,  bool m9,  bool m10, bool m11,
                                bool m12, bool m13, bool m14, bool m15,
                                bool m16, bool m17, bool m18, bool m19,
                                bool m20, bool m21, bool m22, bool m23,
                                bool m24, bool m25, bool m26, bool m27,
                                bool m28, bool m29, bool m30, bool m31)
        {
            mMask[0] = MASK_SCALAR_TYPE(m0);   mMask[1] = MASK_SCALAR_TYPE(m1);
            mMask[2] = MASK_SCALAR_TYPE(m2);   mMask[3] = MASK_SCALAR_TYPE(m3);
            mMask[4] = MASK_SCALAR_TYPE(m4);   mMask[5] = MASK_SCALAR_TYPE(m5);
            mMask[6] = MASK_SCALAR_TYPE(m6);   mMask[7] = MASK_SCALAR_TYPE(m7);
            mMask[8] = MASK_SCALAR_TYPE(m8);   mMask[9] = MASK_SCALAR_TYPE(m9);
            mMask[10] = MASK_SCALAR_TYPE(m10); mMask[11] = MASK_SCALAR_TYPE(m11);
            mMask[12] = MASK_SCALAR_TYPE(m12); mMask[13] = MASK_SCALAR_TYPE(m13);
            mMask[14] = MASK_SCALAR_TYPE(m14); mMask[15] = MASK_SCALAR_TYPE(m15);
            mMask[16] = MASK_SCALAR_TYPE(m16); mMask[17] = MASK_SCALAR_TYPE(m17);
            mMask[18] = MASK_SCALAR_TYPE(m18); mMask[19] = MASK_SCALAR_TYPE(m19);
            mMask[20] = MASK_SCALAR_TYPE(m20); mMask[21] = MASK_SCALAR_TYPE(m21);
            mMask[22] = MASK_SCALAR_TYPE(m22); mMask[23] = MASK_SCALAR_TYPE(m23);
            mMask[24] = MASK_SCALAR_TYPE(m24); mMask[25] = MASK_SCALAR_TYPE(m25);
            mMask[26] = MASK_SCALAR_TYPE(m26); mMask[27] = MASK_SCALAR_TYPE(m27);
            mMask[28] = MASK_SCALAR_TYPE(m28); mMask[29] = MASK_SCALAR_TYPE(m29);
            mMask[30] = MASK_SCALAR_TYPE(m30); mMask[31] = MASK_SCALAR_TYPE(m31);
        }

        // A non-modifying element-wise access operator
        inline MASK_SCALAR_TYPE operator[] (uint32_t index) const { return MASK_SCALAR_TYPE(mMask[index]); }

        inline MASK_BASE_TYPE extract(uint32_t index)
        {
            return mMask[index];
        }

        // Element-wise modification operator
        inline void insert(uint32_t index, bool x) { 
            mMask[index] = MASK_SCALAR_TYPE(x);
        }

        SIMDVecAVX512Mask(SIMDVecAVX512Mask const & mask) {
            UME_EMULATION_WARNING();
            for(int i = 0; i < VEC_LEN; i++)
            {
                mMask[i] = mask.mMask[i];
            }
        }
    };
    
    // ********************************************************************************************
    // MASK VECTOR SPECIALIZATION
    // ********************************************************************************************
    template<>
    class SIMDVecAVX512Mask<uint32_t, 8> : public SIMDMaskBaseInterface< 
                                                               SIMDVecAVX512Mask<uint32_t, 8>,
                                                               uint32_t,
                                                               8>
    {   
        static const uint32_t TRUE() { return 0xFFFFFFFF; };
        static const uint32_t FALSE() { return 0x00000000; };

        // This function returns internal representation of boolean value based on bool input
        static inline uint32_t toMaskBool(bool m) { if (m == true) return TRUE(); else return FALSE(); }
        // This function returns a boolean value based on internal representation
        static inline bool toBool(uint32_t m) { if( (m & 0x80000000) != 0) return true; else return false; }

        friend class SIMDVecAVX512_u<uint32_t, 8>;
        friend class SIMDVecAVX512_i<int32_t, 8>;
        friend class SIMDVecAVX512_f<float, 8>;
        friend class SIMDVecAVX512_f<double, 8>;
    private:
        __m256i mMask;

        SIMDVecAVX512Mask(__m256i const & x) { mMask = x; };
    public:
        SIMDVecAVX512Mask() {
            mMask = _mm256_set1_epi32(FALSE());
        }

        // Regardless of the mask representation, the interface should only allow initialization using 
        // standard bool or using equivalent mask
        SIMDVecAVX512Mask( bool m ) {
            mMask = _mm256_set1_epi32(toMaskBool(m));
        }
        
        SIMDVecAVX512Mask( bool m0, bool m1, bool m2, bool m3, bool m4, bool m5, bool m6, bool m7 ) {
            mMask = _mm256_setr_epi32(toMaskBool(m0), toMaskBool(m1), 
                                      toMaskBool(m2), toMaskBool(m3),
                                      toMaskBool(m4), toMaskBool(m5), 
                                      toMaskBool(m6), toMaskBool(m7));
        }
        
        SIMDVecAVX512Mask(SIMDVecAVX512Mask const & mask) {
            UME_EMULATION_WARNING();
            this->mMask = mask.mMask;
        }

        inline bool extract(uint32_t index) const {
            UME_PERFORMANCE_UNOPTIMAL_WARNING() 
            alignas(32) uint32_t raw[8];
            _mm256_store_si256((__m256i*)raw, mMask);
            return raw[index] == TRUE();
        }
        
        // A non-modifying element-wise access operator
        inline bool operator[] (uint32_t index) const { 
            return extract(index);
        }

        // Element-wise modification operator
        inline void insert(uint32_t index, bool x) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING() 
            alignas(32) static uint32_t raw[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
            _mm256_store_si256((__m256i*)raw, mMask);
            raw[index] = toMaskBool(x);
            mMask = _mm256_load_si256((__m256i*)raw);
        }

        inline SIMDVecAVX512Mask<uint32_t, 8> & operator= (SIMDVecAVX512Mask<uint32_t, 8> const & x) {
            //mMask = x.mMask;
            mMask = _mm256_load_si256(&x.mMask);
            return *this;
        }
    };
    
    // Mask vectors. Mask vectors with bool base type will resolve into scalar emulation.
    typedef SIMDVecAVX512Mask<bool, 1>     SIMDMask1;
    typedef SIMDVecAVX512Mask<bool, 2>     SIMDMask2;
    typedef SIMDVecAVX512Mask<bool, 4>     SIMDMask4;
    typedef SIMDVecAVX512Mask<uint32_t, 8> SIMDMask8;
    typedef SIMDVecAVX512Mask<bool, 16>    SIMDMask16;
    typedef SIMDVecAVX512Mask<bool, 32>    SIMDMask32;
    typedef SIMDVecAVX512Mask<bool, 64>    SIMDMask64;
    typedef SIMDVecAVX512Mask<bool, 128>   SIMDMask128;    


    // ********************************************************************************************
    // UNSIGNED INTEGER VECTORS
    // ********************************************************************************************
    template<typename VEC_TYPE, uint32_t VEC_LEN>
    struct SIMDVecAVX512_u_traits{
        // Generic trait class not containing type definition so that only correct explicit
        // type definitions are compiled correctly
    };

    // 64b vectors
    template<>
    struct SIMDVecAVX512_u_traits<uint8_t, 8>{
        typedef int8_t    SCALAR_INT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint16_t, 4>{
        typedef int16_t   SCALAR_INT_TYPE;
        typedef SIMDMask4 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint32_t, 2>{
        typedef int32_t   SCALAR_INT_TYPE;
        typedef SIMDMask2 MASK_TYPE;
    };

    // 128b vectors
    template<>
    struct SIMDVecAVX512_u_traits<uint8_t, 16>{
        typedef int8_t     SCALAR_INT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint16_t, 8>{
        typedef int16_t   SCALAR_INT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint32_t, 4>{
        typedef int32_t   SCALAR_INT_TYPE;
        typedef SIMDMask4 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint64_t, 2>{
        typedef int64_t   SCALAR_INT_TYPE;
        typedef SIMDMask2 MASK_TYPE;
    };

    // 256b vectors
    template<>
    struct SIMDVecAVX512_u_traits<uint8_t, 32>{
        typedef int8_t   SCALAR_INT_TYPE;
        typedef SIMDMask32 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_u_traits<uint16_t, 16>{
        typedef int16_t   SCALAR_INT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint32_t, 8>{
        typedef int32_t   SCALAR_INT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_u_traits<uint64_t, 4>{
        typedef int64_t   SCALAR_INT_TYPE;
        typedef SIMDMask4 MASK_TYPE;
    };

    // 512b vectors
    template<>
    struct SIMDVecAVX512_u_traits<uint8_t, 64>{
        typedef int8_t   SCALAR_INT_TYPE;
        typedef SIMDMask64 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_u_traits<uint16_t, 32>{
        typedef int16_t   SCALAR_INT_TYPE;
        typedef SIMDMask32 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint32_t, 16>{
        typedef int32_t   SCALAR_INT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_u_traits<uint64_t, 8>{
        typedef int64_t   SCALAR_INT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };
    
    // 1024b vectors
    template<>
    struct SIMDVecAVX512_u_traits<uint8_t, 128>{
        typedef int8_t   SCALAR_INT_TYPE;
        typedef SIMDMask128 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_u_traits<uint16_t, 64>{
        typedef int16_t   SCALAR_INT_TYPE;
        typedef SIMDMask64 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_u_traits<uint32_t, 32>{
        typedef int32_t   SCALAR_INT_TYPE;
        typedef SIMDMask32 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_u_traits<uint64_t, 16>{
        typedef int64_t   SCALAR_INT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };

    template<typename SCALAR_UINT_TYPE, uint32_t VEC_LEN>
    class SIMDVecAVX512_u final : public SIMDVecUnsignedInterface< 
        SIMDVecAVX512_u<SCALAR_UINT_TYPE, VEC_LEN>, // DERIVED_VEC_TYPE
        SIMDVecAVX512_u<SCALAR_UINT_TYPE, VEC_LEN>, // DERIVED_VEC_UINT_TYPE
        SCALAR_UINT_TYPE,                        // SCALAR_TYPE
        SCALAR_UINT_TYPE,                        // SCALAR_UINT_TYPE
        VEC_LEN,
        typename SIMDVecAVX512_u_traits<SCALAR_UINT_TYPE, VEC_LEN>::MASK_TYPE>
    {
    public:
        typedef SIMDVecEmuRegister<SCALAR_UINT_TYPE, VEC_LEN>                                   VEC_EMU_REG;
            
        typedef typename SIMDVecAVX512_u_traits<SCALAR_UINT_TYPE, VEC_LEN>::SCALAR_INT_TYPE  SCALAR_INT_TYPE;
        
        // Conversion operators require access to private members.
        friend class SIMDVecAVX512_i<SCALAR_INT_TYPE, VEC_LEN>;

    private:
        // This is the only data member and it is a low level representation of vector register.
        VEC_EMU_REG mVec; 

    public:
        inline SIMDVecAVX512_u() : mVec() {};

        inline explicit SIMDVecAVX512_u(SCALAR_UINT_TYPE i) : mVec(i) {};

        inline SIMDVecAVX512_u(SCALAR_UINT_TYPE i0, SCALAR_UINT_TYPE i1, SCALAR_UINT_TYPE i2, SCALAR_UINT_TYPE i3) {
            mVec.insert(0, i0);  mVec.insert(1, i1);  mVec.insert(2, i2);  mVec.insert(3, i3);
        }

        inline SIMDVecAVX512_u(SCALAR_UINT_TYPE i0, SCALAR_UINT_TYPE i1, SCALAR_UINT_TYPE i2, SCALAR_UINT_TYPE i3, SCALAR_UINT_TYPE i4, SCALAR_UINT_TYPE i5, SCALAR_UINT_TYPE i6, SCALAR_UINT_TYPE i7) 
        {
            mVec.insert(0, i0);  mVec.insert(1, i1);  mVec.insert(2, i2);  mVec.insert(3, i3);
            mVec.insert(4, i4);  mVec.insert(5, i5);  mVec.insert(6, i6);  mVec.insert(7, i7);
        }

        inline SIMDVecAVX512_u(SCALAR_UINT_TYPE i0, SCALAR_UINT_TYPE i1, SCALAR_UINT_TYPE i2, SCALAR_UINT_TYPE i3, SCALAR_UINT_TYPE i4, SCALAR_UINT_TYPE i5, SCALAR_UINT_TYPE i6, SCALAR_UINT_TYPE i7,
                            SCALAR_UINT_TYPE i8, SCALAR_UINT_TYPE i9, SCALAR_UINT_TYPE i10, SCALAR_UINT_TYPE i11, SCALAR_UINT_TYPE i12, SCALAR_UINT_TYPE i13, SCALAR_UINT_TYPE i14, SCALAR_UINT_TYPE i15)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);    mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);    mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);    mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);  mVec.insert(14, i14);  mVec.insert(15, i15); 
        }

        inline SIMDVecAVX512_u(SCALAR_UINT_TYPE i0, SCALAR_UINT_TYPE i1, SCALAR_UINT_TYPE i2, SCALAR_UINT_TYPE i3, SCALAR_UINT_TYPE i4, SCALAR_UINT_TYPE i5, SCALAR_UINT_TYPE i6, SCALAR_UINT_TYPE i7,
                            SCALAR_UINT_TYPE i8, SCALAR_UINT_TYPE i9, SCALAR_UINT_TYPE i10, SCALAR_UINT_TYPE i11, SCALAR_UINT_TYPE i12, SCALAR_UINT_TYPE i13, SCALAR_UINT_TYPE i14, SCALAR_UINT_TYPE i15,
                            SCALAR_UINT_TYPE i16, SCALAR_UINT_TYPE i17, SCALAR_UINT_TYPE i18, SCALAR_UINT_TYPE i19, SCALAR_UINT_TYPE i20, SCALAR_UINT_TYPE i21, SCALAR_UINT_TYPE i22, SCALAR_UINT_TYPE i23,
                            SCALAR_UINT_TYPE i24, SCALAR_UINT_TYPE i25, SCALAR_UINT_TYPE i26, SCALAR_UINT_TYPE i27, SCALAR_UINT_TYPE i28, SCALAR_UINT_TYPE i29, SCALAR_UINT_TYPE i30, SCALAR_UINT_TYPE i31)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);    mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);    mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);    mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);  mVec.insert(14, i14);  mVec.insert(15, i15);     
            mVec.insert(16, i16);  mVec.insert(17, i17);  mVec.insert(18, i18);  mVec.insert(19, i19);
            mVec.insert(20, i20);  mVec.insert(21, i21);  mVec.insert(22, i22);  mVec.insert(23, i23);
            mVec.insert(24, i24);  mVec.insert(25, i25);  mVec.insert(26, i26);  mVec.insert(27, i27);
            mVec.insert(28, i28);  mVec.insert(29, i29);  mVec.insert(30, i30);  mVec.insert(31, i31);
        }
            
        // Override Access operators
        inline SCALAR_UINT_TYPE operator[] (uint32_t index) const {
            return mVec[index];
        }
                
        // insert[] (scalar)
        inline SIMDVecAVX512_u & insert(uint32_t index, SCALAR_UINT_TYPE value) {
            mVec.insert(index, value);
            return *this;
        }

        inline  operator SIMDVecAVX512_i<SCALAR_INT_TYPE, VEC_LEN>() const {
            SIMDVecAVX512_i<SCALAR_INT_TYPE, VEC_LEN> retval;
            for(uint32_t i = 0; i < VEC_LEN; i++) {
                retval.insert(i, (SCALAR_INT_TYPE)mVec[i]);
            }
            return retval;
        }
    };

                        
    // ********************************************************************************************
    // UNSIGNED INTEGER VECTORS specialization
    // ********************************************************************************************
    template<>
    class SIMDVecAVX512_u<uint32_t, 8> : public SIMDVecUnsignedInterface< 
        SIMDVecAVX512_u<uint32_t, 8>, 
        SIMDVecAVX512_u<uint32_t, 8>,
        uint32_t,
        uint32_t, 
        8,
        SIMDMask8>
    {
    public:            
        // Conversion operators require access to private members.
        friend class SIMDVecAVX512_i<int32_t, 8>;

    private:
        __m256i mVec;

        inline SIMDVecAVX512_u(__m256i & x) { this->mVec = x; }
    public:
        inline SIMDVecAVX512_u() { 
            mVec = _mm256_setzero_si256();
        }

        inline explicit SIMDVecAVX512_u(uint32_t i) {
            mVec = _mm256_set1_epi32(i);
        }

        inline SIMDVecAVX512_u(uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3, 
                            uint32_t i4, uint32_t i5, uint32_t i6, uint32_t i7) 
        {
            mVec = _mm256_setr_epi32(i0, i1, i2, i3, i4, i5, i6, i7);
        }

        inline uint32_t extract (uint32_t index) const {
            UME_PERFORMANCE_UNOPTIMAL_WARNING(); // This routine can be optimized
            alignas(32) uint32_t raw[8];
            _mm256_store_si256 ((__m256i*)raw, mVec);
            return raw[index];
        }            

        // Override Access operators
        inline uint32_t operator[] (uint32_t index) const {
            return extract(index);
        }
                
        // insert[] (scalar)
        inline SIMDVecAVX512_u & insert (uint32_t index, uint32_t value) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8];
            _mm256_store_si256 ((__m256i*)raw, mVec);
            raw[index] = value;
            mVec = _mm256_load_si256((__m256i*)raw);
            return *this;
        }
        // STOREA
        inline uint32_t * storea (uint32_t * addrAligned) {
            _mm256_store_si256((__m256i*)addrAligned, mVec);
            return addrAligned;
        }

        // ADDS
        inline SIMDVecAVX512_u add (uint32_t b) {
            __m128i b_vec = _mm_set1_epi32(b);
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i r_low = _mm_add_epi32(a_low, b_vec);
            __m128i r_high = _mm_add_epi32(a_high, b_vec);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;            
        }
        // ADDVA
        inline SIMDVecAVX512_u adda (SIMDVecAVX512_u const & b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm256_extractf128_si256 (b.mVec, 0);
            __m128i b_high = _mm256_extractf128_si256 (b.mVec, 1);
            __m128i r_low = _mm_add_epi32(a_low, b_low);
            __m128i r_high = _mm_add_epi32(a_high, b_high);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;            
        }
        // MADDVA
        inline SIMDVecAVX512_u & adda (SIMDMask8 const & mask, SIMDVecAVX512_u const & b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm256_extractf128_si256 (b.mVec, 0);
            __m128i b_high = _mm256_extractf128_si256 (b.mVec, 1);
            __m128i r_low = _mm_add_epi32(a_low, b_low);
            __m128i r_high = _mm_add_epi32(a_high, b_high);
            __m128i m_low = _mm256_extractf128_si256 (mask.mMask, 0);
            __m128i m_high = _mm256_extractf128_si256 (mask.mMask, 1);
            r_low = _mm_blendv_epi8(a_low, r_low, m_low);
            r_high = _mm_blendv_epi8(a_high, r_high, m_high);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;            
        }
        // ADDSA 
        inline SIMDVecAVX512_u & adda (uint32_t b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_vec = _mm_set1_epi32(b);
            __m128i r_low = _mm_add_epi32(a_low, b_vec);
            __m128i r_high = _mm_add_epi32(a_high, b_vec);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;
        }
        // MADDSA
        inline SIMDVecAVX512_u & adda (SIMDMask8 const & mask, uint32_t b) {
            __m128i b_vec = _mm_set1_epi32(b);
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i r_low = _mm_add_epi32(a_low, b_vec);
            __m128i r_high = _mm_add_epi32(a_high, b_vec);
            __m128i m_low = _mm256_extractf128_si256 (mask.mMask, 0);
            __m128i m_high = _mm256_extractf128_si256 (mask.mMask, 1);
            r_low = _mm_blendv_epi8(a_low, r_low, m_low);
            r_high = _mm_blendv_epi8(a_high, r_high, m_high);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;            
        }
        // MULV
        inline SIMDVecAVX512_u mul (SIMDVecAVX512_u const & b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm256_extractf128_si256 (b.mVec, 0);
            __m128i b_high = _mm256_extractf128_si256 (b.mVec, 1);
            __m128i r_low = _mm_mullo_epi32(a_low, b_low);
            __m128i r_high = _mm_mullo_epi32(a_high, b_high);
            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256(ret, r_low, 0);
            ret = _mm256_insertf128_si256(ret, r_high, 1);
            return SIMDVecAVX512_u(ret);
        }
        // MMULV
        inline SIMDVecAVX512_u mul (SIMDMask8 const & mask, SIMDVecAVX512_u const & b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm256_extractf128_si256 (b.mVec, 0);
            __m128i b_high = _mm256_extractf128_si256 (b.mVec, 1);
            __m128i r_low = _mm_mullo_epi32(a_low, b_low);
            __m128i r_high = _mm_mullo_epi32(a_high, b_high);
            __m128i m_low = _mm256_extractf128_si256 (mask.mMask, 0);            
            __m128i m_high = _mm256_extractf128_si256 (mask.mMask, 1);            
            r_low = _mm_blendv_epi8(a_low, r_low, m_low);
            r_high = _mm_blendv_epi8(a_high, r_high, m_high);
            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256(ret, r_low, 0);
            ret = _mm256_insertf128_si256(ret, r_high, 1);
            return SIMDVecAVX512_u(ret);
        }
        // MULS
        inline SIMDVecAVX512_u mul (uint32_t b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_vec = _mm_set1_epi32(b);
            __m128i r_low = _mm_mullo_epi32(a_low, b_vec);
            __m128i r_high = _mm_mullo_epi32(a_high, b_vec);
            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256(ret, r_low, 0);
            ret = _mm256_insertf128_si256(ret, r_high, 1);
            return SIMDVecAVX512_u(ret);
        }
        // MMULS
        inline SIMDVecAVX512_u mul (SIMDMask8 const & mask, uint32_t b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_vec = _mm_set1_epi32(b);
            __m128i r_low = _mm_mullo_epi32(a_low, b_vec);
            __m128i r_high = _mm_mullo_epi32(a_high, b_vec);
            __m128i m_low = _mm256_extractf128_si256 (mask.mMask, 0);            
            __m128i m_high = _mm256_extractf128_si256 (mask.mMask, 1);       
            r_low = _mm_blendv_epi8(a_low, r_low, m_low);
            r_high = _mm_blendv_epi8(a_high, r_high, m_high);
            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256(ret, r_low, 0);
            ret = _mm256_insertf128_si256(ret, r_high, 1);
            return SIMDVecAVX512_u(ret);
        }
        // CMPEQV
        inline SIMDMask8 cmpeq (SIMDVecAVX512_u const & b) {
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm256_extractf128_si256 (b.mVec, 0);
            __m128i b_high = _mm256_extractf128_si256 (b.mVec, 1);
            
            __m128i r_low = _mm_cmpeq_epi32(a_low, b_low);
            __m128i r_high = _mm_cmpeq_epi32(a_high, b_high);

            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256 (ret, r_low, 0);
            ret = _mm256_insertf128_si256 (ret, r_high, 1);
            return SIMDMask8(ret);
        }
        // MCMPEQ
        inline SIMDMask8 cmpeq (uint32_t b) {
            __m128i b_vec = _mm_set1_epi32(b);
            __m128i a_low = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);

            __m128i r_low = _mm_cmpeq_epi32(a_low, b_vec);
            __m128i r_high = _mm_cmpeq_epi32(a_high, b_vec);

            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256 (ret, r_low, 0);
            ret = _mm256_insertf128_si256 (ret, r_high, 1);
            return SIMDMask8(ret);
        }

        // GATHERS
        SIMDVecAVX512_u & gather ( uint32_t* baseAddr, uint64_t* indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8] = { baseAddr[indices[0]], baseAddr[indices[1]], baseAddr[indices[2]], baseAddr[indices[3]],
                                            baseAddr[indices[4]], baseAddr[indices[5]], baseAddr[indices[6]], baseAddr[indices[7]]};
            mVec = _mm256_load_si256((__m256i*)raw);
            return *this;
        }   
        // MGATHERS
        SIMDVecAVX512_u & gather (SIMDMask8 const & mask, uint32_t* baseAddr, uint64_t* indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8] = { baseAddr[indices[0]], baseAddr[indices[1]], baseAddr[indices[2]], baseAddr[indices[3]],
                                            baseAddr[indices[4]], baseAddr[indices[5]], baseAddr[indices[6]], baseAddr[indices[7]]};
            __m128i a_low  = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm_load_si128((__m128i*)&raw[0]);
            __m128i b_high = _mm_load_si128((__m128i*)&raw[4]);
            __m128i m_low = _mm256_extractf128_si256 (mask.mMask, 0);
            __m128i m_high = _mm256_extractf128_si256 (mask.mMask, 1);
            __m128i r_low = _mm_blendv_epi8(a_low, b_low, m_low);
            __m128i r_high = _mm_blendv_epi8(a_high, b_high, m_high);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;
        }
        // GATHERV
        SIMDVecAVX512_u & gather (uint32_t* baseAddr, SIMDVecAVX512_u const & indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t rawInd[8];
            alignas(32) uint32_t raw[8]; 
            
            _mm256_store_si256((__m256i*) rawInd, indices.mVec);
            for(int i = 0; i < 8; i++) { raw[i] = baseAddr[rawInd[i]]; }
            mVec = _mm256_load_si256((__m256i*)raw);
            return *this;
        }
        // MGATHERV
        SIMDVecAVX512_u & gather (SIMDMask8 const & mask, uint32_t* baseAddr, SIMDVecAVX512_u const & indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t rawInd[8];
            alignas(32) uint32_t raw[8]; 
            
            _mm256_store_si256((__m256i*) rawInd, indices.mVec);
            for(int i = 0; i < 8; i++) { raw[i] = baseAddr[rawInd[i]]; }
            __m128i a_low  = _mm256_extractf128_si256 (mVec, 0);
            __m128i a_high = _mm256_extractf128_si256 (mVec, 1);
            __m128i b_low = _mm_load_si128((__m128i*)&raw[0]);
            __m128i b_high = _mm_load_si128((__m128i*)&raw[4]);
            __m128i m_low = _mm256_extractf128_si256 (mask.mMask, 0);
            __m128i m_high = _mm256_extractf128_si256 (mask.mMask, 1);
            __m128i r_low = _mm_blendv_epi8(a_low, b_low, m_low);
            __m128i r_high = _mm_blendv_epi8(a_high, b_high, m_high);
            mVec = _mm256_insertf128_si256(mVec, r_low, 0);
            mVec = _mm256_insertf128_si256(mVec, r_high, 1);
            return *this;
        }
        // SCATTERS
        uint32_t* scatter (uint32_t* baseAddr, uint64_t* indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8];
            _mm256_store_si256((__m256i*) raw, mVec);
            for(int i = 0; i < 8; i++) { baseAddr[indices[i]] = raw[i]; };
            return baseAddr;
        }
        // MSCATTERS
        uint32_t* scatter (SIMDMask8 const & mask, uint32_t* baseAddr, uint64_t* indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8];
            alignas(32) uint32_t rawMask[8];
            _mm256_store_si256((__m256i*) raw, mVec);
            _mm256_store_si256((__m256i*) rawMask, mask.mMask);
            for(int i = 0; i < 8; i++) { if(rawMask[i] == SIMDMask8::TRUE()) baseAddr[indices[i]] = raw[i]; };
            return baseAddr;
        }
        // SCATTERV
        uint32_t* scatter (uint32_t* baseAddr, SIMDVecAVX512_u const & indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8];
            alignas(32) uint32_t rawIndices[8];
            _mm256_store_si256((__m256i*) raw, mVec);
            _mm256_store_si256((__m256i*) rawIndices, indices.mVec);
            for(int i = 0; i < 8; i++) { baseAddr[rawIndices[i]] = raw[i]; };
            return baseAddr;
        }
        // MSCATTERV
        uint32_t* scatter (SIMDMask8 const & mask, uint32_t* baseAddr, SIMDVecAVX512_u const & indices) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            alignas(32) uint32_t raw[8];
            alignas(32) uint32_t rawIndices[8];
            alignas(32) uint32_t rawMask[8];
            _mm256_store_si256((__m256i*) raw, mVec);
            _mm256_store_si256((__m256i*) rawIndices, indices.mVec);
            _mm256_store_si256((__m256i*) rawMask, mask.mMask);
            for(int i = 0; i < 8; i++) { 
                if(rawMask[i] == SIMDMask8::TRUE())
                    baseAddr[rawIndices[i]] = raw[i]; 
            };
            return baseAddr;
        }
        
        inline  operator SIMDVecAVX512_i<int32_t, 8> const ();
    };
                        
    // ********************************************************************************************
    // SIGNED INTEGER VECTORS
    // ********************************************************************************************
    template<typename SCALAR_INT_TYPE, uint32_t VEC_LEN>
    struct SIMDVecAVX512_i_traits{
        // Generic trait class not containing type definition so that only correct explicit
        // type definitions are compiled correctly
    };

    // 64b vectors
    template<>
    struct SIMDVecAVX512_i_traits<int8_t, 8> {
        typedef SIMDVecAVX512_u<uint8_t, 8> VEC_UINT;
        typedef uint8_t SCALAR_UINT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int16_t, 4>{
        typedef SIMDVecAVX512_u<uint16_t, 4> VEC_UINT;
        typedef uint16_t  SCALAR_UINT_TYPE;
        typedef SIMDMask4 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_i_traits<int32_t, 2>{
        typedef SIMDVecAVX512_u<uint32_t, 2> VEC_UINT;
        typedef uint32_t SCALAR_UINT_TYPE;
        typedef SIMDMask2 MASK_TYPE;
    };

    // 128b vectors
    template<>
    struct SIMDVecAVX512_i_traits<int8_t, 16>{
        typedef SIMDVecAVX512_u<uint8_t, 16> VEC_UINT;
        typedef uint8_t SCALAR_UINT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_i_traits<int16_t, 8>{
        typedef SIMDVecAVX512_u<uint16_t, 8> VEC_UINT;
        typedef uint16_t SCALAR_UINT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };
            
    template<>
    struct SIMDVecAVX512_i_traits<int32_t, 4>{
        typedef SIMDVecAVX512_u<uint32_t, 4> VEC_UINT;
        typedef uint32_t SCALAR_UINT_TYPE;
        typedef SIMDMask4 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_i_traits<int64_t, 2>{
        typedef SIMDVecAVX512_u<uint64_t, 2> VEC_UINT;
        typedef uint64_t SCALAR_UINT_TYPE;
        typedef SIMDMask2 MASK_TYPE;
    };

    // 256b vectors
    template<>
    struct SIMDVecAVX512_i_traits<int8_t, 32>{
        typedef SIMDVecAVX512_u<uint8_t, 32> VEC_UINT;
        typedef uint8_t SCALAR_UINT_TYPE;
        typedef SIMDMask32 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int16_t, 16>{
        typedef SIMDVecAVX512_u<uint16_t, 16> VEC_UINT;
        typedef uint16_t SCALAR_UINT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int32_t, 8>{
        typedef SIMDVecAVX512_u<uint32_t, 8> VEC_UINT;
        typedef uint32_t SCALAR_UINT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_i_traits<int64_t, 4>{
        typedef SIMDVecAVX512_u<uint64_t, 4> VEC_UINT;
        typedef uint64_t SCALAR_UINT_TYPE;
        typedef SIMDMask4 MASK_TYPE;
    };

    // 512b vectors
    template<>
    struct SIMDVecAVX512_i_traits<int8_t, 64>{
        typedef SIMDVecAVX512_u<uint8_t, 64> VEC_UINT;
        typedef uint8_t SCALAR_UINT_TYPE;
        typedef SIMDMask64 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int16_t, 32>{
        typedef SIMDVecAVX512_u<uint16_t, 32> VEC_UINT;
        typedef uint16_t SCALAR_UINT_TYPE;
        typedef SIMDMask32 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int32_t, 16>{
        typedef SIMDVecAVX512_u<uint32_t, 16> VEC_UINT;
        typedef uint32_t SCALAR_UINT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_i_traits<int64_t, 8>{
        typedef SIMDVecAVX512_u<uint64_t, 8> VEC_UINT;
        typedef uint64_t SCALAR_UINT_TYPE;
        typedef SIMDMask8 MASK_TYPE;
    };

    // 1024b vectors
    template<>
    struct SIMDVecAVX512_i_traits<int8_t, 128>{
        typedef SIMDVecAVX512_u<uint8_t, 128> VEC_UINT;
        typedef uint8_t SCALAR_UINT_TYPE;
        typedef SIMDMask128 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int16_t, 64>{
        typedef SIMDVecAVX512_u<uint16_t, 64> VEC_UINT;
        typedef uint16_t SCALAR_UINT_TYPE;
        typedef SIMDMask64 MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_i_traits<int32_t, 32>{
        typedef SIMDVecAVX512_u<uint32_t, 32> VEC_UINT;
        typedef uint32_t SCALAR_UINT_TYPE;
        typedef SIMDMask32 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_i_traits<int64_t, 16>{
        typedef SIMDVecAVX512_u<uint64_t, 16> VEC_UINT;
        typedef uint64_t SCALAR_UINT_TYPE;
        typedef SIMDMask16 MASK_TYPE;
    };

    template<typename SCALAR_INT_TYPE, uint32_t VEC_LEN>
    class SIMDVecAVX512_i final : public SIMDVecSignedInterface< SIMDVecAVX512_i<SCALAR_INT_TYPE, VEC_LEN>, 
                                                 typename SIMDVecAVX512_i_traits<SCALAR_INT_TYPE, VEC_LEN>::VEC_UINT,
                                                 SCALAR_INT_TYPE, 
                                                 VEC_LEN,
                                                 typename SIMDVecAVX512_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_UINT_TYPE,
                                                 typename SIMDVecAVX512_i_traits<SCALAR_INT_TYPE, VEC_LEN>::MASK_TYPE>
    {
    public:
        typedef SIMDVecEmuRegister<SCALAR_INT_TYPE, VEC_LEN>                            VEC_EMU_REG;
            
        typedef typename SIMDVecAVX512_i_traits<SCALAR_INT_TYPE, VEC_LEN>::SCALAR_UINT_TYPE     SCALAR_UINT_TYPE;
        typedef typename SIMDVecAVX512_i_traits<SCALAR_INT_TYPE, VEC_LEN>::VEC_UINT             VEC_UINT;
        
        friend class SIMDVecScalarEmu_u<SCALAR_UINT_TYPE, VEC_LEN>;
    private:
        VEC_EMU_REG mVec;

    public:
        inline SIMDVecAVX512_i() : mVec() {};

        inline explicit SIMDVecAVX512_i(SCALAR_INT_TYPE i) : mVec(i) {};

        inline SIMDVecAVX512_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1, SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3) {
            mVec.insert(0, i0);  mVec.insert(1, i1);  mVec.insert(2, i2);  mVec.insert(3, i3);
        }

        inline SIMDVecAVX512_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1, SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3, SCALAR_INT_TYPE i4, SCALAR_INT_TYPE i5, SCALAR_INT_TYPE i6, SCALAR_INT_TYPE i7) 
        {
            mVec.insert(0, i0);  mVec.insert(1, i1);  mVec.insert(2, i2);  mVec.insert(3, i3);
            mVec.insert(4, i4);  mVec.insert(5, i5);  mVec.insert(6, i6);  mVec.insert(7, i7);
        }

        inline SIMDVecAVX512_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1, SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3, SCALAR_INT_TYPE i4, SCALAR_INT_TYPE i5, SCALAR_INT_TYPE i6, SCALAR_INT_TYPE i7,
                            SCALAR_INT_TYPE i8, SCALAR_INT_TYPE i9, SCALAR_INT_TYPE i10, SCALAR_INT_TYPE i11, SCALAR_INT_TYPE i12, SCALAR_INT_TYPE i13, SCALAR_INT_TYPE i14, SCALAR_INT_TYPE i15)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);    mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);    mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);    mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);  mVec.insert(14, i14);  mVec.insert(15, i15); 
        }

        inline SIMDVecAVX512_i(SCALAR_INT_TYPE i0, SCALAR_INT_TYPE i1, SCALAR_INT_TYPE i2, SCALAR_INT_TYPE i3, SCALAR_INT_TYPE i4, SCALAR_INT_TYPE i5, SCALAR_INT_TYPE i6, SCALAR_INT_TYPE i7,
                            SCALAR_INT_TYPE i8, SCALAR_INT_TYPE i9, SCALAR_INT_TYPE i10, SCALAR_INT_TYPE i11, SCALAR_INT_TYPE i12, SCALAR_INT_TYPE i13, SCALAR_INT_TYPE i14, SCALAR_INT_TYPE i15,
                            SCALAR_INT_TYPE i16, SCALAR_INT_TYPE i17, SCALAR_INT_TYPE i18, SCALAR_INT_TYPE i19, SCALAR_INT_TYPE i20, SCALAR_INT_TYPE i21, SCALAR_INT_TYPE i22, SCALAR_INT_TYPE i23,
                            SCALAR_INT_TYPE i24, SCALAR_INT_TYPE i25, SCALAR_INT_TYPE i26, SCALAR_INT_TYPE i27, SCALAR_INT_TYPE i28, SCALAR_INT_TYPE i29, SCALAR_INT_TYPE i30, SCALAR_INT_TYPE i31)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);    mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);    mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);    mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);  mVec.insert(14, i14);  mVec.insert(15, i15);     
            mVec.insert(16, i16);  mVec.insert(17, i17);  mVec.insert(18, i18);  mVec.insert(19, i19);
            mVec.insert(20, i20);  mVec.insert(21, i21);  mVec.insert(22, i22);  mVec.insert(23, i23);
            mVec.insert(24, i24);  mVec.insert(25, i25);  mVec.insert(26, i26);  mVec.insert(27, i27);
            mVec.insert(28, i28);  mVec.insert(29, i29);  mVec.insert(30, i30);  mVec.insert(31, i31);
        }
            
        // Override Access operators
        inline SCALAR_INT_TYPE operator[] (uint32_t index) const {
            return mVec[index];
        }
                
        // insert[] (scalar)
        inline SIMDVecAVX512_i & insert(uint32_t index, SCALAR_INT_TYPE value) {
            mVec.insert(index, value);
            return *this;
        }

        inline  operator SIMDVecAVX512_u<SCALAR_UINT_TYPE, VEC_LEN>() const {
            SIMDVecAVX512_u<SCALAR_UINT_TYPE, VEC_LEN> retval;
            for(uint32_t i = 0; i < VEC_LEN; i++) {
                retval.insert(i, (SCALAR_UINT_TYPE)mVec[i]);
            }
            return retval;
        }
    };
    // ********************************************************************************************
    // SIGNED INTEGER VECTOR specializations
    // ********************************************************************************************

    template<>
    class SIMDVecAVX512_i<int32_t, 8>: public SIMDVecSignedInterface< SIMDVecAVX512_i<int32_t, 8>, 
                                                 SIMDVecAVX512_u<uint32_t, 8>,
                                                 int32_t, 
                                                 8,
                                                 uint32_t,
                                                 SIMDMask8>
    {
        friend class SIMDVecAVX512_u<uint32_t, 8>;
        friend class SIMDVecAVX512_f<float, 8>;
        friend class SIMDVecAVX512_f<double, 8>;

    private:
        __m256i mVec;

        inline explicit SIMDVecAVX512_i(__m256i & x) {
            this->mVec = x;
        }
    public:
        inline SIMDVecAVX512_i() {};

        inline explicit SIMDVecAVX512_i(int32_t i) {
            mVec = _mm256_set1_epi32(i);
        }

        inline SIMDVecAVX512_i(int32_t i0, int32_t i1, int32_t i2, int32_t i3, 
                            int32_t i4, int32_t i5, int32_t i6, int32_t i7) 
        {
            mVec = _mm256_setr_epi32(i0, i1, i2, i3, i4, i5, i6, i7);
        }

        inline int32_t extract(uint32_t index) const {
            UME_PERFORMANCE_UNOPTIMAL_WARNING();
            //return _mm256_extract_epi32(mVec, index); // TODO: this can be implemented in ICC
            alignas(32) int32_t raw[8];
            _mm256_store_si256((__m256i *)raw, mVec);
            return raw[index];
        }
            
        // Override Access operators
        inline int32_t operator[] (uint32_t index) const {
            return extract(index);
        }
                
        // insert[] (scalar)
        inline SIMDVecAVX512_i & insert(uint32_t index, int32_t value) {
            UME_PERFORMANCE_UNOPTIMAL_WARNING()
            alignas(32) int32_t raw[8];
            _mm256_store_si256((__m256i *)raw, mVec);
            raw[index] = value;
            mVec = _mm256_load_si256((__m256i *)raw);
            return *this;
        }

        inline  operator SIMDVecAVX512_u<uint32_t, 8> const ();

        // ABS
        SIMDVecAVX512_i abs () {
            __m128i a_low  = _mm256_extractf128_si256(mVec, 0);
            __m128i a_high = _mm256_extractf128_si256(mVec, 1);
            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256(ret, _mm_abs_epi32(a_low), 0);
            ret = _mm256_insertf128_si256(ret, _mm_abs_epi32(a_high), 1);
            return SIMDVecAVX512_i(ret);
        }
        // MABS
        SIMDVecAVX512_i abs (SIMDMask8 const & mask) {
            __m128i a_low  = _mm256_extractf128_si256(mVec, 0);
            __m128i a_high = _mm256_extractf128_si256(mVec, 1);
            __m128i m_low  = _mm256_extractf128_si256(mask.mMask, 0);
            __m128i m_high = _mm256_extractf128_si256(mask.mMask, 1);
            
            __m128i r_low = _mm_blendv_epi8(a_low, _mm_abs_epi32(a_low), m_low);
            __m128i r_high = _mm_blendv_epi8(a_high, _mm_abs_epi32(a_high), m_high);
            __m256i ret = _mm256_setzero_si256();
            ret = _mm256_insertf128_si256(ret, r_low, 0);
            ret = _mm256_insertf128_si256(ret, r_high, 1);
            return SIMDVecAVX512_i(ret);
        }
    };

    inline SIMDVecAVX512_i<int32_t, 8>::operator const SIMDVecAVX512_u<uint32_t, 8>() {
        return SIMDVecAVX512_u<uint32_t, 8>(this->mVec);
    }

    inline SIMDVecAVX512_u<uint32_t, 8>::operator const SIMDVecAVX512_i<int32_t, 8>() {
        return SIMDVecAVX512_i<int32_t, 8>(this->mVec);
    }

    // ********************************************************************************************
    // FLOATING POINT VECTORS
    // ********************************************************************************************

    template<typename SCALAR_FLOAT_TYPE, uint32_t VEC_LEN>
    struct SIMDVecAVX512_f_traits{
        // Generic trait class not containing type definition so that only correct explicit
        // type definitions are compiled correctly
    };

    // 64b vectors
    template<>
    struct SIMDVecAVX512_f_traits<float, 2>{
        typedef SIMDVecAVX512_u<uint32_t, 2> VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int32_t, 2>  VEC_INT_TYPE;
        typedef int32_t                      SCALAR_INT_TYPE;
        typedef uint32_t                     SCALAR_UINT_TYPE;
        typedef float*                       SCALAR_TYPE_PTR;
        typedef SIMDMask2                    MASK_TYPE;
    };
    
    // 128b vectors
    template<>
    struct SIMDVecAVX512_f_traits<float, 4>{
        typedef SIMDVecAVX512_u<uint32_t, 4>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int32_t, 4>  VEC_INT_TYPE;
        typedef int32_t                   SCALAR_INT_TYPE;
        typedef uint32_t                  SCALAR_UINT_TYPE;
        typedef float*                    SCALAR_TYPE_PTR;
        typedef SIMDMask4                 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_f_traits<double, 2>{
        typedef SIMDVecAVX512_u<uint64_t, 2>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int64_t, 2>  VEC_INT_TYPE;
        typedef int64_t                   SCALAR_INT_TYPE;
        typedef uint64_t                  SCALAR_UINT_TYPE;
        typedef double*                   SCALAR_TYPE_PTR;
        typedef SIMDMask2                 MASK_TYPE;
    };

    // 256b vectors
    template<>
    struct SIMDVecAVX512_f_traits<float, 8>{
        typedef SIMDVecAVX512_u<uint32_t, 8>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int32_t, 8>  VEC_INT_TYPE;
        typedef int32_t                   SCALAR_INT_TYPE;
        typedef uint32_t                  SCALAR_UINT_TYPE;
        typedef float*                    SCALAR_TYPE_PTR;
        typedef SIMDMask8                 MASK_TYPE;
    };

    template<>
    struct SIMDVecAVX512_f_traits<double, 4>{
        typedef SIMDVecAVX512_u<uint64_t, 4>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int64_t, 4>  VEC_INT_TYPE;
        typedef int64_t                   SCALAR_INT_TYPE;
        typedef uint64_t                  SCALAR_UINT_TYPE;
        typedef double*                   SCALAR_TYPE_PTR;
        typedef SIMDMask4                 MASK_TYPE;
    };
    
    // 512b vectors
    template<>
    struct SIMDVecAVX512_f_traits<float, 16>{
        typedef SIMDVecAVX512_u<uint32_t, 16>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int32_t, 16> VEC_INT_TYPE;
        typedef int32_t                   SCALAR_INT_TYPE;
        typedef uint32_t                  SCALAR_UINT_TYPE;
        typedef float*                    SCALAR_TYPE_PTR;
        typedef SIMDMask16                MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_f_traits<double, 8>{
        typedef SIMDVecAVX512_u<uint64_t, 8>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int64_t, 8>  VEC_INT_TYPE;
        typedef int64_t                   SCALAR_INT_TYPE;
        typedef uint64_t                  SCALAR_UINT_TYPE;
        typedef double*                   SCALAR_TYPE_PTR;
        typedef SIMDMask8                 MASK_TYPE;
    };

    // 1024b vectors
    template<>
    struct SIMDVecAVX512_f_traits<float, 32>{
        typedef SIMDVecAVX512_u<uint32_t,32>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int32_t, 32>  VEC_INT_TYPE;
        typedef int32_t                       SCALAR_INT_TYPE;
        typedef uint32_t                      SCALAR_UINT_TYPE;
        typedef float*                        SCALAR_TYPE_PTR;
        typedef SIMDMask32                    MASK_TYPE;
    };
    
    template<>
    struct SIMDVecAVX512_f_traits<double, 16>{
        typedef SIMDVecAVX512_u<uint64_t, 16>  VEC_UINT_TYPE;
        typedef SIMDVecAVX512_i<int64_t, 16>   VEC_INT_TYPE;
        typedef int64_t                       SCALAR_INT_TYPE;
        typedef uint64_t                      SCALAR_UINT_TYPE;
        typedef double*                       SCALAR_TYPE_PTR;
        typedef SIMDMask16                     MASK_TYPE;
    };


    template<typename SCALAR_FLOAT_TYPE, uint32_t VEC_LEN>
    class SIMDVecAVX512_f final : public SIMDVecFloatInterface< SIMDVecAVX512_f<SCALAR_FLOAT_TYPE, VEC_LEN>, 
                                                 typename SIMDVecAVX512_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::VEC_UINT_TYPE,
                                                 typename SIMDVecAVX512_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::VEC_INT_TYPE,
                                                 SCALAR_FLOAT_TYPE, 
                                                 VEC_LEN,
                                                 typename SIMDVecAVX512_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::SCALAR_UINT_TYPE,
                                                 typename SIMDVecAVX512_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::MASK_TYPE>
    {
    public:
        typedef SIMDVecEmuRegister<SCALAR_FLOAT_TYPE, VEC_LEN>                            VEC_EMU_REG;
        typedef typename SIMDVecAVX512_f_traits<SCALAR_FLOAT_TYPE, VEC_LEN>::MASK_TYPE       MASK_TYPE;
        
        typedef SIMDVecAVX512_f VEC_TYPE;
    private:
        VEC_EMU_REG mVec;

    public:
        inline SIMDVecAVX512_f() : mVec() {};

        inline explicit SIMDVecAVX512_f(SCALAR_FLOAT_TYPE i) : mVec(i) {};

        inline SIMDVecAVX512_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1, SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3) {
            mVec.insert(0, i0);  mVec.insert(1, i1);  mVec.insert(2, i2);  mVec.insert(3, i3);
        }

        inline SIMDVecAVX512_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1, SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3, SCALAR_FLOAT_TYPE i4, SCALAR_FLOAT_TYPE i5, SCALAR_FLOAT_TYPE i6, SCALAR_FLOAT_TYPE i7) 
        {
            mVec.insert(0, i0);  mVec.insert(1, i1);  mVec.insert(2, i2);  mVec.insert(3, i3);
            mVec.insert(4, i4);  mVec.insert(5, i5);  mVec.insert(6, i6);  mVec.insert(7, i7);
        }

        inline SIMDVecAVX512_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1, SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3, SCALAR_FLOAT_TYPE i4, SCALAR_FLOAT_TYPE i5, SCALAR_FLOAT_TYPE i6, SCALAR_FLOAT_TYPE i7,
                            SCALAR_FLOAT_TYPE i8, SCALAR_FLOAT_TYPE i9, SCALAR_FLOAT_TYPE i10, SCALAR_FLOAT_TYPE i11, SCALAR_FLOAT_TYPE i12, SCALAR_FLOAT_TYPE i13, SCALAR_FLOAT_TYPE i14, SCALAR_FLOAT_TYPE i15)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);    mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);    mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);    mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);  mVec.insert(14, i14);  mVec.insert(15, i15); 
        }

        inline SIMDVecAVX512_f(SCALAR_FLOAT_TYPE i0, SCALAR_FLOAT_TYPE i1, SCALAR_FLOAT_TYPE i2, SCALAR_FLOAT_TYPE i3, SCALAR_FLOAT_TYPE i4, SCALAR_FLOAT_TYPE i5, SCALAR_FLOAT_TYPE i6, SCALAR_FLOAT_TYPE i7,
                            SCALAR_FLOAT_TYPE i8, SCALAR_FLOAT_TYPE i9, SCALAR_FLOAT_TYPE i10, SCALAR_FLOAT_TYPE i11, SCALAR_FLOAT_TYPE i12, SCALAR_FLOAT_TYPE i13, SCALAR_FLOAT_TYPE i14, SCALAR_FLOAT_TYPE i15,
                            SCALAR_FLOAT_TYPE i16, SCALAR_FLOAT_TYPE i17, SCALAR_FLOAT_TYPE i18, SCALAR_FLOAT_TYPE i19, SCALAR_FLOAT_TYPE i20, SCALAR_FLOAT_TYPE i21, SCALAR_FLOAT_TYPE i22, SCALAR_FLOAT_TYPE i23,
                            SCALAR_FLOAT_TYPE i24, SCALAR_FLOAT_TYPE i25, SCALAR_FLOAT_TYPE i26, SCALAR_FLOAT_TYPE i27, SCALAR_FLOAT_TYPE i28, SCALAR_FLOAT_TYPE i29, SCALAR_FLOAT_TYPE i30, SCALAR_FLOAT_TYPE i31)
        {
            mVec.insert(0, i0);    mVec.insert(1, i1);    mVec.insert(2, i2);    mVec.insert(3, i3);
            mVec.insert(4, i4);    mVec.insert(5, i5);    mVec.insert(6, i6);    mVec.insert(7, i7);
            mVec.insert(8, i8);    mVec.insert(9, i9);    mVec.insert(10, i10);  mVec.insert(11, i11);
            mVec.insert(12, i12);  mVec.insert(13, i13);  mVec.insert(14, i14);  mVec.insert(15, i15);     
            mVec.insert(16, i16);  mVec.insert(17, i17);  mVec.insert(18, i18);  mVec.insert(19, i19);
            mVec.insert(20, i20);  mVec.insert(21, i21);  mVec.insert(22, i22);  mVec.insert(23, i23);
            mVec.insert(24, i24);  mVec.insert(25, i25);  mVec.insert(26, i26);  mVec.insert(27, i27);
            mVec.insert(28, i28);  mVec.insert(29, i29);  mVec.insert(30, i30);  mVec.insert(31, i31);
        }
            
        // Override Access operators
        inline SCALAR_FLOAT_TYPE operator[] (uint32_t index) const {
            return mVec[index];
        }
                
        // insert[] (scalar)
        inline SIMDVecAVX512_f & insert(uint32_t index, SCALAR_FLOAT_TYPE value) {
            mVec.insert(index, value);
            return *this;
        }

    };

    // ********************************************************************************************
    // FLOATING POINT VECTOR specializations
    // ********************************************************************************************

    template<>
    class SIMDVecAVX512_f<float, 8> : public SIMDVecFloatInterface< SIMDVecAVX512_f<float, 8>, 
                                                 SIMDVecAVX512_u<uint32_t, 8>,
                                                 SIMDVecAVX512_i<int32_t, 8>,
                                                 float, 
                                                 8,
                                                 uint32_t,
                                                 SIMDMask8>
    {
    private:
        __m256 mVec;

        inline SIMDVecAVX512_f(__m256 & x) {
            this->mVec = x;
        }

    public:
        inline SIMDVecAVX512_f() {
        }

        inline explicit SIMDVecAVX512_f(float f) {
            mVec = _mm256_set1_ps(f);
        }

        inline SIMDVecAVX512_f(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7) {
 	    mVec = _mm256_set_ps(f0, f1, f2, f3, f4, f5, f6, f7);
        }

        // Override Access operators
        inline float operator[] (uint32_t index) const {
	    alignas(32) float raw[8];
	    _mm256_store_ps(raw, mVec);
	    return raw[index];
        }
                
        // insert[] (scalar)
        inline SIMDVecAVX512_f & insert(uint32_t index, float value) {
	    alignas(32) float raw[8];
	    _mm256_store_ps(raw, mVec);
	    raw[index] = value;
            mVec = _mm256_load_ps(raw);
            return *this;
        }
    };

    // 64b uint vectors
    typedef SIMDVecAVX512_u<uint8_t,  8>   SIMD8_8u;
    typedef SIMDVecAVX512_u<uint16_t, 4>   SIMD4_16u;
    typedef SIMDVecAVX512_u<uint32_t, 2>   SIMD2_32u; 

    // 128b uint vectors
    typedef SIMDVecAVX512_u<uint8_t,  16>  SIMD16_8u;
    typedef SIMDVecAVX512_u<uint16_t, 8>   SIMD8_16u;
    typedef SIMDVecAVX512_u<uint32_t, 4>   SIMD4_32u;
    typedef SIMDVecAVX512_u<uint64_t, 2>   SIMD2_64u;
    
    // 256b uint vectors
    typedef SIMDVecAVX512_u<uint8_t,  32>  SIMD32_8u;
    typedef SIMDVecAVX512_u<uint16_t, 16>  SIMD16_16u;
    typedef SIMDVecAVX512_u<uint32_t, 8>   SIMD8_32u;
    typedef SIMDVecAVX512_u<uint64_t, 4>   SIMD4_64u;
    
    // 512b uint vectors
    typedef SIMDVecAVX512_u<uint8_t,  64>  SIMD64_8u;
    typedef SIMDVecAVX512_u<uint16_t, 32>  SIMD32_16u;
    typedef SIMDVecAVX512_u<uint32_t, 16>  SIMD16_32u;
    typedef SIMDVecAVX512_u<uint64_t, 8>   SIMD8_64u;
    
    // 1024b uint vectors
    typedef SIMDVecAVX512_u<uint8_t,  128> SIMD128_8u;
    typedef SIMDVecAVX512_u<uint16_t, 64>  SIMD64_16u;
    typedef SIMDVecAVX512_u<uint32_t, 32>  SIMD32_32u;
    typedef SIMDVecAVX512_u<uint64_t, 16>  SIMD16_64u;


    // 64b int vectors
    typedef SIMDVecAVX512_i<int8_t,   8>   SIMD8_8i; 
    typedef SIMDVecAVX512_i<int16_t,  4>   SIMD4_16i;
    typedef SIMDVecAVX512_i<int32_t,  2>   SIMD2_32i;
    
    // 128b int vectors
    typedef SIMDVecAVX512_i<int8_t,   16>  SIMD16_8i; 
    typedef SIMDVecAVX512_i<int16_t,  8>   SIMD8_16i;
    typedef SIMDVecAVX512_i<int32_t,  4>   SIMD4_32i;
    typedef SIMDVecAVX512_i<int64_t,  2>   SIMD2_64i;

    // 256b int vectors
    typedef SIMDVecAVX512_i<int8_t,   32>  SIMD32_8i;
    typedef SIMDVecAVX512_i<int16_t,  16>  SIMD16_16i;
    typedef SIMDVecAVX512_i<int32_t,  8>   SIMD8_32i;
    typedef SIMDVecAVX512_i<int64_t,  4>   SIMD4_64i;
    
    // 512b int vectors
    typedef SIMDVecAVX512_i<int8_t,   64>  SIMD64_8i;
    typedef SIMDVecAVX512_i<int16_t,  32>  SIMD32_16i;
    typedef SIMDVecAVX512_i<int32_t,  16>  SIMD16_32i;
    typedef SIMDVecAVX512_i<int64_t,  8>   SIMD8_64i;

    // 1024b int vectors
    typedef SIMDVecAVX512_i<int8_t,   128> SIMD128_8i;
    typedef SIMDVecAVX512_i<int16_t,  64>  SIMD64_16i;
    typedef SIMDVecAVX512_i<int32_t,  32>  SIMD32_32i;
    typedef SIMDVecAVX512_i<int64_t,  16>  SIMD16_64i;


    // 64b float vectors
    typedef SIMDVecAVX512_f<float, 2>      SIMD2_32f;

    // 128b float vectors
    typedef SIMDVecAVX512_f<float,  4>     SIMD4_32f;
    typedef SIMDVecAVX512_f<double, 2>     SIMD2_64f;

    // 256b float vectors
    typedef SIMDVecAVX512_f<float,  8>     SIMD8_32f;
    typedef SIMDVecAVX512_f<double, 4>     SIMD4_64f;

    // 512b float vectors
    typedef SIMDVecAVX512_f<float,  16>    SIMD16_32f;
    typedef SIMDVecAVX512_f<double, 8>     SIMD8_64f;

    // 1024b float vectors
    typedef SIMDVecAVX512_f<float, 32>     SIMD32_32f;
    typedef SIMDVecAVX512_f<double, 16>    SIMD16_64f;
} // SIMD
} // UME

#endif // UME_SIMD_PLUGIN_NATIVE_AVX512
