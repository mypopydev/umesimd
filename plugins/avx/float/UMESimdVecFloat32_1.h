// The MIT License (MIT)
//
// Copyright (c) 2015 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's 
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//

#ifndef UME_SIMD_VEC_FLOAT32_1_H_
#define UME_SIMD_VEC_FLOAT32_1_H_

#include <type_traits>
#include <immintrin.h>

#include "../../../UMESimdInterface.h"

namespace UME {
namespace SIMD {

    template<>
    class SIMDVec_f<float, 1> final :
        public SIMDVecFloatInterface<
        SIMDVec_f<float, 1>,
        SIMDVec_u<uint32_t, 1>,
        SIMDVec_i<int32_t, 1>,
        float,
        1,
        uint32_t,
        SIMDVecMask<1>,
        SIMDVecSwizzle<1 >>
    {
    private:
        float mVec;

        typedef SIMDVec_u<uint32_t, 1>    VEC_UINT_TYPE;
        typedef SIMDVec_i<int32_t, 1>     VEC_INT_TYPE;
        typedef SIMDVec_f<float, 1>       HALF_LEN_VEC_TYPE;
    public:

        constexpr static uint32_t alignment() {
            return 4;
        }
        // ZERO-CONSTR - Zero element constructor 
        inline SIMDVec_f() {}
        // SET-CONSTR  - One element constructor
        // FULL-CONSTR - constructor with VEC_LEN scalar element 
        inline explicit SIMDVec_f(float f) {
            mVec = f;
        }
        // UTOF
        inline explicit SIMDVec_f(VEC_UINT_TYPE const & vecUint) {
            mVec = float(vecUint[0]);
        }
        // FTOU
        inline VEC_UINT_TYPE ftou() const {
            return VEC_UINT_TYPE(uint32_t(mVec));
        }
        // ITOF
        inline explicit SIMDVec_f(VEC_INT_TYPE const & vecInt) {
            mVec = float(vecInt[0]);
        }
        // FTOI
        inline VEC_INT_TYPE ftoi() const {
            return VEC_UINT_TYPE(int32_t(mVec));
        }
        // LOAD-CONSTR - Construct by loading from memory
        inline explicit SIMDVec_f(float const *p) {
            mVec = p[0];
        }

        // EXTRACT
        inline float extract(uint32_t index) const {
            return mVec;
        }
        // EXTRACT
        inline float operator[] (uint32_t index) const {
            return mVec;
        }
        // Override Mask Access operators
        inline IntermediateMask<SIMDVec_f, SIMDVecMask<1>> operator[] (SIMDVecMask<1> const & mask) {
            return IntermediateMask<SIMDVec_f, SIMDVecMask<1>>(mask, static_cast<SIMDVec_f &>(*this));
        }
        // INSERT
        inline SIMDVec_f & insert(uint32_t index, float value) {
            mVec = value;
            return *this;
        }
        // ****************************************************************************************
        // Overloading Interface functions starts here!
        // ****************************************************************************************
        //(Initialization)
        // ASSIGNV     - Assignment with another vector
        inline SIMDVec_f & assign(SIMDVec_f const & b) {
            mVec = b.mVec;
            return *this;
        }
        // MASSIGNV    - Masked assignment with another vector
        inline SIMDVec_f & assign(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            if (mask.mMask == true) mVec = b.mVec;
            return *this;
        }
        // ASSIGNS     - Assignment with scalar
        inline SIMDVec_f & assign(float b) {
            mVec = b;
            return *this;
        }
        // MASSIGNS    - Masked assign with scalar
        inline SIMDVec_f & assign(SIMDVecMask<1> const & mask, float b) {
            if (mask.mMask == true) mVec = b;
            return *this;
        }
        //(Memory access)
        // LOAD    - Load from memory (either aligned or unaligned) to vector 
        inline SIMDVec_f & load(float const * p) {
            mVec = p[0];
            return *this;
        }
        // MLOAD   - Masked load from memory (either aligned or unaligned) to
        //        vector
        inline SIMDVec_f & load(SIMDVecMask<1> const & mask, float const * p) {
            if (mask.mMask == true) mVec = p[0];
            return *this;
        }
        // LOADA   - Load from aligned memory to vector
        inline SIMDVec_f & loada(float const * p) {
            mVec = p[0];
            return *this;
        }
        // MLOADA  - Masked load from aligned memory to vector
        inline SIMDVec_f & loada(SIMDVecMask<1> const & mask, float const * p) {
            if (mask.mMask == true) mVec = p[0];
            return *this;
        }
        // STORE   - Store vector content into memory (either aligned or unaligned)
        inline float* store(float * p) const {
            p[0] = mVec;
            return p;
        }
        // MSTORE  - Masked store vector content into memory (either aligned or
        //        unaligned)
        inline float* store(SIMDVecMask<1> const & mask, float * p) const {
            if (mask.mMask == true) p[0] = mVec;
            return p;
        }
        // STOREA  - Store vector content into aligned memory
        inline float* storea(float * p) const {
            p[0] = mVec;
            return p;
        }
        // MSTOREA - Masked store vector content into aligned memory
        inline float* storea(SIMDVecMask<1> const & mask, float * p) const {
            if (mask.mMask == true) p[0] = mVec;
            return p;
        }
        //(Addition operations)
        // ADDV     - Add with vector 
        inline SIMDVec_f add(SIMDVec_f const & b) const {
            float t0 = mVec + b.mVec;
            return SIMDVec_f(t0);
        }
        inline SIMDVec_f operator+ (SIMDVec_f const & b) const {
            return add(b);
        }
        // MADDV    - Masked add with vector
        inline SIMDVec_f add(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = mask.mMask ? mVec + b.mVec : mVec;
            return SIMDVec_f(t0);
        }
        // ADDS     - Add with scalar
        inline SIMDVec_f add(float a) const {
            float t0 = mVec + a;
            return SIMDVec_f(t0);
        }
        // MADDS    - Masked add with scalar
        inline SIMDVec_f add(SIMDVecMask<1> const & mask, float b) const {
            float t0 = mask.mMask ? mVec + b : mVec;
            return SIMDVec_f(t0);
        }
        // ADDVA    - Add with vector and assign
        inline SIMDVec_f & adda(SIMDVec_f const & b) {
            mVec += b.mVec;
            return *this;
        }
        // MADDVA   - Masked add with vector and assign
        inline SIMDVec_f & adda(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            mVec = mask.mMask ? mVec + b.mVec : mVec;
            return *this;
        }
        // ADDSA    - Add with scalar and assign
        inline SIMDVec_f & adda(float a) {
            mVec += a;
            return *this;
        }
        // MADDSA   - Masked add with scalar and assign
        inline SIMDVec_f & adda(SIMDVecMask<1> const & mask, float b) {
            mVec = mask.mMask ? mVec + b : mVec;
            return *this;
        }
        // SADDV    - Saturated add with vector
        // MSADDV   - Masked saturated add with vector
        // SADDS    - Saturated add with scalar
        // MSADDS   - Masked saturated add with scalar
        // SADDVA   - Saturated add with vector and assign
        // MSADDVA  - Masked saturated add with vector and assign
        // SADDSA   - Satureated add with scalar and assign
        // MSADDSA  - Masked staturated add with vector and assign
        // POSTINC  - Postfix increment
        inline SIMDVec_f postinc() {
            float t0 = mVec++;
            return SIMDVec_f(t0);
        }
        // MPOSTINC - Masked postfix increment
        inline SIMDVec_f postinc(SIMDVecMask<1> const & mask) {
            float t0 = (mask.mMask == true) ? mVec++ : mVec;
            return SIMDVec_f(t0);
        }
        // PREFINC  - Prefix increment
        inline SIMDVec_f & prefinc() {
            ++mVec;
            return *this;
        }
        // MPREFINC - Masked prefix increment
        inline SIMDVec_f & prefinc(SIMDVecMask<1> const & mask) {
            if (mask.mMask == true) ++mVec;
            return *this;
        }
        //(Subtraction operations)
        // SUBV       - Sub with vector
        inline SIMDVec_f sub(SIMDVec_f const & b) const {
            float t0 = mVec - b.mVec;
            return SIMDVec_f(t0);
        }
        // MSUBV      - Masked sub with vector
        inline SIMDVec_f sub(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = (mask.mMask == true) ? (mVec - b.mVec) : mVec;
            return SIMDVec_f(t0);
        }
        // SUBS       - Sub with scalar
        inline SIMDVec_f sub(float b) const {
            float t0 = mVec - b;
            return SIMDVec_f(t0);
        }
        // MSUBS      - Masked subtraction with scalar
        inline SIMDVec_f sub(SIMDVecMask<1> const & mask, float b) const {
            float t0 = (mask.mMask == true) ? (mVec - b) : mVec;
            return SIMDVec_f(t0);
        }
        // SUBVA      - Sub with vector and assign
        inline SIMDVec_f & suba(SIMDVec_f const & b) {
            mVec = mVec - b.mVec;
            return *this;
        }
        // MSUBVA     - Masked sub with vector and assign
        inline SIMDVec_f & suba(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            if (mask.mMask == true) mVec = mVec - b.mVec;
            return *this;
        }
        // SUBSA      - Sub with scalar and assign
        inline SIMDVec_f & suba(const float b) {
            mVec = mVec - b;
            return *this;
        }
        // MSUBSA     - Masked sub with scalar and assign
        inline SIMDVec_f & suba(SIMDVecMask<1> const & mask, const float b) {
            if (mask.mMask == true) mVec = mVec - b;
            return *this;
        }
        // SSUBV      - Saturated sub with vector
        // MSSUBV     - Masked saturated sub with vector
        // SSUBS      - Saturated sub with scalar
        // MSSUBS     - Masked saturated sub with scalar
        // SSUBVA     - Saturated sub with vector and assign
        // MSSUBVA    - Masked saturated sub with vector and assign
        // SSUBSA     - Saturated sub with scalar and assign
        // MSSUBSA    - Masked saturated sub with scalar and assign
        // SUBFROMV   - Sub from vector
        inline SIMDVec_f subfrom(SIMDVec_f const & a) const {
            float t0 = a.mVec - mVec;
            return SIMDVec_f(t0);
        }
        // MSUBFROMV  - Masked sub from vector
        inline SIMDVec_f subfrom(SIMDVecMask<1> const & mask, SIMDVec_f const & a) const {
            float t0 = (mask.mMask == true) ? (a.mVec - mVec) : a[0];
            return SIMDVec_f(t0);
        }
        // SUBFROMS   - Sub from scalar (promoted to vector)
        inline SIMDVec_f subfrom(float a) const {
            float t0 = a - mVec;
            return SIMDVec_f(t0);
        }
        // MSUBFROMS  - Masked sub from scalar (promoted to vector)
        inline SIMDVec_f subfrom(SIMDVecMask<1> const & mask, float a) const {
            float t0 = (mask.mMask == true) ? (a - mVec) : a;
            return SIMDVec_f(t0);
        }
        // SUBFROMVA  - Sub from vector and assign
        inline SIMDVec_f & subfroma(SIMDVec_f const & a) {
            mVec = a.mVec - mVec;
            return *this;
        }
        // MSUBFROMVA - Masked sub from vector and assign
        inline SIMDVec_f & subfroma(SIMDVecMask<1> const & mask, SIMDVec_f const & a) {
            mVec = (mask.mMask == true) ? (a.mVec - mVec) : a.mVec;
            return *this;
        }
        // SUBFROMSA  - Sub from scalar (promoted to vector) and assign
        inline SIMDVec_f & subfroma(float a) {
            mVec = a - mVec;
            return *this;
        }
        // MSUBFROMSA - Masked sub from scalar (promoted to vector) and assign
        inline SIMDVec_f & subfroma(SIMDVecMask<1> const & mask, float a) {
            mVec = (mask.mMask == true) ? (a - mVec) : a;
            return *this;
        }
        // POSTDEC    - Postfix decrement
        inline SIMDVec_f postdec() {
            float t0 = mVec--;
            return SIMDVec_f(t0);
        }
        // MPOSTDEC   - Masked postfix decrement
        inline SIMDVec_f postdec(SIMDVecMask<1> const & mask) {
            float t0 = (mask.mMask == true) ? mVec-- : mVec;
            return SIMDVec_f(t0);
        }
        // PREFDEC    - Prefix decrement
        inline SIMDVec_f & prefdec() {
            --mVec;
            return *this;
        }
        // MPREFDEC   - Masked prefix decrement
        inline SIMDVec_f & prefdec(SIMDVecMask<1> const & mask) {
            if (mask.mMask == true) --mVec;
            return *this;
        }
        //(Multiplication operations)
        // MULV   - Multiplication with vector
        inline SIMDVec_f mul(SIMDVec_f const & b) const {
            float t0 = mVec * b.mVec;
            return SIMDVec_f(t0);
        }
        // MMULV  - Masked multiplication with vector
        inline SIMDVec_f mul(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = mask.mMask ? mVec * b.mVec : mVec;
            return SIMDVec_f(t0);
        }
        // MULS   - Multiplication with scalar
        inline SIMDVec_f mul(float b) const {
            float t0 = mVec * b;
            return SIMDVec_f(t0);
        }
        // MMULS  - Masked multiplication with scalar
        inline SIMDVec_f mul(SIMDVecMask<1> const & mask, float b) const {
            float t0 = mask.mMask ? mVec * b : mVec;
            return SIMDVec_f(t0);
        }
        // MULVA  - Multiplication with vector and assign
        inline SIMDVec_f & mula(SIMDVec_f const & b) {
            mVec *= b.mVec;
            return *this;
        }
        // MMULVA - Masked multiplication with vector and assign
        inline SIMDVec_f & mula(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            if (mask.mMask == true) mVec *= b.mVec;
            return *this;
        }
        // MULSA  - Multiplication with scalar and assign
        inline SIMDVec_f & mula(float b) {
            mVec *= b;
            return *this;
        }
        // MMULSA - Masked multiplication with scalar and assign
        inline SIMDVec_f & mula(SIMDVecMask<1> const & mask, float b) {
            if (mask.mMask == true) mVec *= b;
            return *this;
        }

        //(Division operations)
        // DIVV   - Division with vector
        inline SIMDVec_f div(SIMDVec_f const & b) const {
            float t0 = mVec / b.mVec;
            return SIMDVec_f(t0);
        }
        // MDIVV  - Masked division with vector
        inline SIMDVec_f div(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = mask.mMask ? mVec / b.mVec : mVec;
            return SIMDVec_f(t0);
        }
        // DIVS   - Division with scalar
        inline SIMDVec_f div(float b) const {
            float t0 = mVec / b;
            return SIMDVec_f(t0);
        }
        // MDIVS  - Masked division with scalar
        inline SIMDVec_f div(SIMDVecMask<1> const & mask, float b) const {
            float t0 = mask.mMask ? mVec / b : mVec;
            return SIMDVec_f(t0);
        }
        // DIVVA  - Division with vector and assign
        inline SIMDVec_f & diva(SIMDVec_f const & b) {
            mVec /= b.mVec;
            return *this;
        }
        // MDIVVA - Masked division with vector and assign
        inline SIMDVec_f & diva(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            if (mask.mMask == true) mVec /= b.mVec;
            return *this;
        }
        // DIVSA  - Division with scalar and assign
        inline SIMDVec_f & diva(float b) {
            mVec /= b;
            return *this;
        }
        // MDIVSA - Masked division with scalar and assign
        inline SIMDVec_f & diva(SIMDVecMask<1> const & mask, float b) {
            if (mask.mMask == true) mVec /= b;
            return *this;
        }
        // RCP    - Reciprocal
        inline SIMDVec_f rcp() const {
            float t0 = 1.0f / mVec;
            return SIMDVec_f(t0);
        }
        // MRCP   - Masked reciprocal
        inline SIMDVec_f rcp(SIMDVecMask<1> const & mask) const {
            float t0 = mask.mMask ? 1.0f / mVec : mVec;
            return SIMDVec_f(t0);
        }
        // RCPS   - Reciprocal with scalar numerator
        inline SIMDVec_f rcp(float b) const {
            float t0 = b / mVec;
            return SIMDVec_f(t0);
        }
        // MRCPS  - Masked reciprocal with scalar
        inline SIMDVec_f rcp(SIMDVecMask<1> const & mask, float b) const {
            float t0 = mask.mMask ? b / mVec : mVec;
            return SIMDVec_f(t0);
        }
        // RCPA   - Reciprocal and assign
        inline SIMDVec_f & rcpa() {
            mVec = 1.0f / mVec;
            return *this;
        }
        // MRCPA  - Masked reciprocal and assign
        inline SIMDVec_f & rcpa(SIMDVecMask<1> const & mask) {
            if (mask.mMask == true) mVec = 1.0f / mVec;
            return *this;
        }
        // RCPSA  - Reciprocal with scalar and assign
        inline SIMDVec_f & rcpa(float b) {
            mVec = b / mVec;
            return *this;
        }
        // MRCPSA - Masked reciprocal with scalar and assign
        inline SIMDVec_f & rcpa(SIMDVecMask<1> const & mask, float b) {
            if (mask.mMask == true) mVec = b / mVec;
            return *this;
        }

        //(Comparison operations)
        // CMPEQV - Element-wise 'equal' with vector
        inline SIMDVecMask<1> cmpeq(SIMDVec_f const & b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec == b.mVec;
            return mask;
        }
        // CMPEQS - Element-wise 'equal' with scalar
        inline SIMDVecMask<1> cmpeq(float b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec == b;
            return mask;
        }
        // CMPNEV - Element-wise 'not equal' with vector
        inline SIMDVecMask<1> cmpne(SIMDVec_f const & b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec != b.mVec;
            return mask;
        }
        // CMPNES - Element-wise 'not equal' with scalar
        inline SIMDVecMask<1> cmpne(float b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec != b;
            return mask;
        }
        // CMPGTV - Element-wise 'greater than' with vector
        inline SIMDVecMask<1> cmpgt(SIMDVec_f const & b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec > b.mVec;
            return mask;
        }
        // CMPGTS - Element-wise 'greater than' with scalar
        inline SIMDVecMask<1> cmpgt(float b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec > b;
            return mask;
        }
        // CMPLTV - Element-wise 'less than' with vector
        inline SIMDVecMask<1> cmplt(SIMDVec_f const & b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec < b.mVec;
            return mask;
        }
        // CMPLTS - Element-wise 'less than' with scalar
        inline SIMDVecMask<1> cmplt(float b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec < b;
            return mask;
        }
        // CMPGEV - Element-wise 'greater than or equal' with vector
        inline SIMDVecMask<1> cmpge(SIMDVec_f const & b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec >= b.mVec;
            return mask;
        }
        // CMPGES - Element-wise 'greater than or equal' with scalar
        inline SIMDVecMask<1> cmpge(float b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec >= b;
            return mask;
        }
        // CMPLEV - Element-wise 'less than or equal' with vector
        inline SIMDVecMask<1> cmple(SIMDVec_f const & b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec <= b.mVec;
            return mask;
        }
        // CMPLES - Element-wise 'less than or equal' with scalar
        inline SIMDVecMask<1> cmple(float b) const {
            SIMDVecMask<1> mask;
            mask.mMask = mVec <= b;
            return mask;
        }
        // CMPEX  - Check if vectors are exact (returns scalar 'bool')
        inline bool cmpex(SIMDVec_f const & b) const {
            return (b.mVec == mVec);
        }

        // (Pack/Unpack operations - not available for SIMD1)

        //(Blend/Swizzle operations)
        // BLENDV   - Blend (mix) two vectors
        inline SIMDVec_f blend(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = (mask.mMask == true) ? mVec : b.mVec;
            return SIMDVec_f(t0);
        }
        // BLENDS   - Blend (mix) vector with scalar (promoted to vector)
        //         assign
        inline SIMDVec_f blend(SIMDVecMask<1> const & mask, float b) const {
            float t0 = (mask.mMask == true) ? mVec : b;
            return SIMDVec_f(t0);
        }
        // SWIZZLE  - Swizzle (reorder/permute) vector elements
        // SWIZZLEA - Swizzle (reorder/permute) vector elements and assign

        //(Reduction to scalar operations)
        // HADD  - Add elements of a vector (horizontal add)
        inline float hadd() const {
            return mVec;
        }
        // MHADD - Masked add elements of a vector (horizontal add)
        inline float hadd(SIMDVecMask<1> const & mask) const {
            float t0 = 0.0f;
            if (mask.mMask == true) t0 += mVec;
            return t0;
        }
        // HMUL  - Multiply elements of a vector (horizontal mul)
        inline float hmul() const {
            return mVec;
        }
        // MHMUL - Masked multiply elements of a vector (horizontal mul)
        inline float hmul(SIMDVecMask<1> const & mask) const {
            float t0 = 1.0f;
            if (mask.mMask == true) t0 *= mVec;
            return t0;
        }

        //(Fused arithmetics)
        // FMULADDV  - Fused multiply and add (A*B + C) with vectors
        inline SIMDVec_f fmuladd(SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = mVec * b.mVec + c.mVec;
            return SIMDVec_f(t0);
        }
        // MFMULADDV - Masked fused multiply and add (A*B + C) with vectors
        inline SIMDVec_f fmuladd(SIMDVecMask<1> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = (mask.mMask == true) ? (mVec * b.mVec + c.mVec) : mVec;
            return SIMDVec_f(t0);
        }
        // FMULSUBV  - Fused multiply and sub (A*B - C) with vectors
        inline SIMDVec_f fmulsub(SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = mVec * b.mVec - c.mVec;
            return SIMDVec_f(t0);
        }
        // MFMULSUBV - Masked fused multiply and sub (A*B - C) with vectors
        inline SIMDVec_f fmulsub(SIMDVecMask<1> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = (mask.mMask == true) ? (mVec * b.mVec - c.mVec) : mVec;
            return SIMDVec_f(t0);
        }
        // FADDMULV  - Fused add and multiply ((A + B)*C) with vectors
        inline SIMDVec_f faddmul(SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = (mVec + b.mVec) * c.mVec;
            return SIMDVec_f(t0);
        }
        // MFADDMULV - Masked fused add and multiply ((A + B)*C) with vectors
        inline SIMDVec_f faddmul(SIMDVecMask<1> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = (mask.mMask == true) ? ((mVec + b.mVec) * c.mVec) : mVec;
            return SIMDVec_f(t0);
        }
        // FSUBMULV  - Fused sub and multiply ((A - B)*C) with vectors
        inline SIMDVec_f fsubmul(SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = (mVec - b.mVec) * c.mVec;
            return SIMDVec_f(t0);
        }
        // MFSUBMULV - Masked fused sub and multiply ((A - B)*C) with vectors
        inline SIMDVec_f fsubmul(SIMDVecMask<1> const & mask, SIMDVec_f const & b, SIMDVec_f const & c) const {
            float t0 = (mask.mMask == true) ? ((mVec - b.mVec) * c.mVec) : mVec;
            return SIMDVec_f(t0);
        }

        // (Mathematical operations)
        // MAXV   - Max with vector
        inline SIMDVec_f max(SIMDVec_f const & b) const {
            float t0 = mVec > b.mVec ? mVec : b.mVec;
            return SIMDVec_f(t0);
        }
        // MMAXV  - Masked max with vector
        inline SIMDVec_f max(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec > b.mVec) ? mVec : b.mVec;
            }
            return SIMDVec_f(t0);
        }
        // MAXS   - Max with scalar
        inline SIMDVec_f max(float b) const {
            float t0 = mVec > b ? mVec : b;
            return SIMDVec_f(t0);
        }
        // MMAXS  - Masked max with scalar
        inline SIMDVec_f max(SIMDVecMask<1> const & mask, float b) const {
            float t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec > b) ? mVec : b;
            }
            return SIMDVec_f(t0);
        }
        // MAXVA  - Max with vector and assign
        inline SIMDVec_f & maxa(SIMDVec_f const & b) {
            if (mVec < b.mVec) mVec = b.mVec;
            return *this;
        }
        // MMAXVA - Masked max with vector and assign
        inline SIMDVec_f & maxa(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            if ((mask.mMask == true) && (mVec < b.mVec)) mVec = b.mVec;
            return *this;
        }
        // MAXSA  - Max with scalar (promoted to vector) and assign
        inline SIMDVec_f & maxa(float b) {
            if (mVec < b) mVec = b;
            return *this;
        }
        // MMAXSA - Masked max with scalar (promoted to vector) and assign
        inline SIMDVec_f & maxa(SIMDVecMask<1> const & mask, float b) {
            if ((mask.mMask == true) && (mVec < b)) mVec = b;
            return *this;
        }
        // MINV   - Min with vector
        inline SIMDVec_f min(SIMDVec_f const & b) const {
            float t0 = mVec < b.mVec ? mVec : b.mVec;
            return SIMDVec_f(t0);
        }
        // MMINV  - Masked min with vector
        inline SIMDVec_f min(SIMDVecMask<1> const & mask, SIMDVec_f const & b) const {
            float t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec < b.mVec) ? mVec : b.mVec;
            }
            return SIMDVec_f(t0);
        }
        // MINS   - Min with scalar (promoted to vector)
        inline SIMDVec_f min(float b) const {
            float t0 = mVec < b ? mVec : b;
            return SIMDVec_f(t0);
        }
        // MMINS  - Masked min with scalar (promoted to vector)
        inline SIMDVec_f min(SIMDVecMask<1> const & mask, float b) const {
            float t0 = mVec;
            if (mask.mMask == true) {
                t0 = (mVec < b) ? mVec : b;
            }
            return SIMDVec_f(t0);
        }
        // MINVA  - Min with vector and assign
        inline SIMDVec_f & mina(SIMDVec_f const & b) {
            if (mVec > b.mVec) mVec = b.mVec;
            return *this;
        }
        // MMINVA - Masked min with vector and assign
        inline SIMDVec_f & mina(SIMDVecMask<1> const & mask, SIMDVec_f const & b) {
            if ((mask.mMask == true) && (mVec > b.mVec)) mVec = b.mVec;
            return *this;
        }
        // MINSA  - Min with scalar (promoted to vector) and assign
        inline SIMDVec_f & mina(float b) {
            if (mVec > b) mVec = b;
            return *this;
        }
        // MMINSA - Masked min with scalar (promoted to vector) and assign
        inline SIMDVec_f & mina(SIMDVecMask<1> const & mask, float b) {
            if ((mask.mMask == true) && (mVec > b)) mVec = b;
            return *this;
        }
        // HMAX   - Max of elements of a vector (horizontal max)
        inline float hmax() const {
            return mVec;
        }
        // MHMAX  - Masked max of elements of a vector (horizontal max)
        inline float hmax(SIMDVecMask<1> const & mask) const {
            float t0 = std::numeric_limits<float>::min();
            if (mask.mMask == true) t0 = mVec;
            return t0;
        }
        // IMAX   - Index of max element of a vector
        inline uint32_t imax() const {
            return 0;
        }
        // MIMAX  - Masked index of max element of a vector
        inline uint32_t mimax(SIMDVecMask<1> const & mask) const {
            return 0;
        }
        // HMIN   - Min of elements of a vector (horizontal min)
        inline float hmin() const {
            return mVec;
        }
        // MHMIN  - Masked min of elements of a vector (horizontal min)
        inline float mhmin(SIMDVecMask<1> const & mask) const {
            float t0 = std::numeric_limits<float>::max();
            if (mask.mMask == true) t0 = mVec;
            return t0;
        }
        // IMIN   - Index of min element of a vector
        inline uint32_t imin() const {
            return 0;
        }
        // MIMIN  - Masked index of min element of a vector
        inline uint32_t mimin(SIMDVecMask<1> const & mask) const {
            return 0;
        }

        // (Gather/Scatter operations)
        // GATHERS   - Gather from memory using indices from array
        inline SIMDVec_f & gather(float * baseAddr, uint64_t * indices) {
            mVec = baseAddr[indices[0]];
            return *this;
        }
        // MGATHERS  - Masked gather from memory using indices from array
        inline SIMDVec_f & gather(SIMDVecMask<1> const & mask, float * baseAddr, uint64_t * indices) {
            if (mask.mMask == true) mVec = baseAddr[indices[0]];
            return *this;
        }
        // GATHERV   - Gather from memory using indices from vector
        inline SIMDVec_f & gather(float * baseAddr, VEC_UINT_TYPE const & indices) {
            mVec = baseAddr[indices[0]];
            return *this;
        }
        // MGATHERV  - Masked gather from memory using indices from vector
        inline SIMDVec_f & gather(SIMDVecMask<1> const & mask, float * baseAddr, VEC_UINT_TYPE const & indices) {
            if (mask.mMask == true) mVec = baseAddr[indices[0]];
            return *this;
        }
        // SCATTERS  - Scatter to memory using indices from array
        inline float * scatter(float * baseAddr, uint64_t * indices) const {
            baseAddr[indices[0]] = mVec;
            return baseAddr;
        }
        // MSCATTERS - Masked scatter to memory using indices from array
        inline float * scatter(SIMDVecMask<1> const & mask, float * baseAddr, uint64_t * indices) const {
            if (mask.mMask == true) baseAddr[indices[0]] = mVec;
            return baseAddr;
        }
        // SCATTERV  - Scatter to memory using indices from vector
        inline float * scatter(float * baseAddr, VEC_UINT_TYPE const & indices) const {
            baseAddr[indices[0]] = mVec;
            return baseAddr;
        }
        // MSCATTERV - Masked scatter to memory using indices from vector
        inline float * scatter(SIMDVecMask<1> const & mask, float * baseAddr, VEC_UINT_TYPE const & indices) const {
            if (mask.mMask == true)  baseAddr[indices[0]] = mVec;
            return baseAddr;
        }
        // NEG   - Negate signed values
        inline SIMDVec_f neg() const {
            return SIMDVec_f(-mVec);
        }
        // MNEG  - Masked negate signed values
        inline SIMDVec_f neg(SIMDVecMask<1> const & mask) const {
            float t0 = (mask.mMask == true) ? -mVec : mVec;
            return SIMDVec_f(t0);
        }
        // NEGA  - Negate signed values and assign
        inline SIMDVec_f & nega() {
            mVec = -mVec;
            return *this;
        }
        // MNEGA - Masked negate signed values and assign
        inline SIMDVec_f & nega(SIMDVecMask<1> const & mask) {
            if (mask.mMask == true) mVec = -mVec;
            return *this;
        }

        // (Mathematical functions)
        // ABS   - Absolute value
        inline SIMDVec_f abs() const {
            float t0 = (mVec > 0.0f) ? mVec : -mVec;
            return SIMDVec_f(t0);
        }
        // MABS  - Masked absolute value
        inline SIMDVec_f abs(SIMDVecMask<1> const & mask) const {
            float t0 = ((mask.mMask == true) && (mVec < 0.0f)) ? -mVec : mVec;
            return SIMDVec_f(t0);
        }
        // ABSA  - Absolute value and assign
        inline SIMDVec_f & absa() {
            if (mVec < 0.0f) mVec = -mVec;
            return *this;
        }
        // MABSA - Masked absolute value and assign
        inline SIMDVec_f & absa(SIMDVecMask<1> const & mask) {
            if ((mask.mMask == true) && (mVec < 0.0f)) mVec = -mVec;
            return *this;
        }

        // 5) Operations available for floating point SIMD types:

        // (Comparison operations)
        // CMPEQRV - Compare 'Equal within range' with margins from vector
        // CMPEQRS - Compare 'Equal within range' with scalar margin

        // (Mathematical functions)
        // SQR       - Square of vector values
        // MSQR      - Masked square of vector values
        // SQRA      - Square of vector values and assign
        // MSQRA     - Masked square of vector values and assign
        // SQRT      - Square root of vector values
        // MSQRT     - Masked square root of vector values 
        // SQRTA     - Square root of vector values and assign
        // MSQRTA    - Masked square root of vector values and assign
        // POWV      - Power (exponents in vector)
        // MPOWV     - Masked power (exponents in vector)
        // POWS      - Power (exponent in scalar)
        // MPOWS     - Masked power (exponent in scalar) 
        // ROUND     - Round to nearest integer
        // MROUND    - Masked round to nearest integer
        // TRUNC     - Truncate to integer (returns Signed integer vector)
        inline SIMDVec_i<int32_t, 1> trunc() {
            int32_t t0 = (int32_t)mVec;
            return SIMDVec_i<int32_t, 1>(t0);
        }
        // MTRUNC    - Masked truncate to integer (returns Signed integer vector)
        inline SIMDVec_i<int32_t, 1> trunc(SIMDVecMask<1> const & mask) {
            int32_t t0 = mask.mMask ? (int32_t)mVec : 0;
            return SIMDVec_i<int32_t, 1>(t0);
        }
        // FLOOR     - Floor
        // MFLOOR    - Masked floor
        // CEIL      - Ceil
        // MCEIL     - Masked ceil
        // ISFIN     - Is finite
        // ISINF     - Is infinite (INF)
        // ISAN      - Is a number
        // ISNAN     - Is 'Not a Number (NaN)'
        // ISSUB     - Is subnormal
        // ISZERO    - Is zero
        // ISZEROSUB - Is zero or subnormal
        // SIN       - Sine
        // MSIN      - Masked sine
        // COS       - Cosine
        // MCOS      - Masked cosine
        // TAN       - Tangent
        // MTAN      - Masked tangent
        // CTAN      - Cotangent
        // MCTAN     - Masked cotangent
    };
}
}

#endif