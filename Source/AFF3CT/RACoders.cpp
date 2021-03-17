// Copyright (c) 2021 Nicholas Corgan
// SPDX-License-Identifier: GPL-3.0-or-later

#include "AFF3CTDynamic/EntryPoints.hpp"
#include "CoderBase.hpp"
#include "TypeTraits.hpp"
#include "Utility.hpp"

#include <Pothos/Exception.hpp>
#include <Pothos/Framework.hpp>

#include <cassert>
#include <string>

//
// Helper class
//

template <typename B, typename Q>
struct RAHelper
{
    using EncoderParamType = aff3ct::factory::Encoder_RA::parameters;
    using DecoderParamType = aff3ct::factory::Decoder_RA::parameters;

    static void initCoderParams(
        std::unique_ptr<aff3ct::factory::Encoder::parameters>& rEncoderParamsUPtr,
        std::unique_ptr<aff3ct::factory::Decoder::parameters>& rDecoderParamsUPtr,
        std::unique_ptr<aff3ct::factory::Interleaver_core::parameters>& rInterleaverCoreParamsUPtr)
    {
        rEncoderParamsUPtr.reset(new EncoderParamType);
        rDecoderParamsUPtr.reset(new DecoderParamType);
        rInterleaverCoreParamsUPtr.reset(new aff3ct::factory::Interleaver_core::parameters);
    }

    static void resetCodec(
        const std::unique_ptr<aff3ct::factory::Encoder::parameters>& encoderParamsUPtr,
        const std::unique_ptr<aff3ct::factory::Decoder::parameters>& decoderParamsUPtr,
        const std::unique_ptr<aff3ct::factory::Interleaver_core::parameters>& interleaverCoreParamsUPtr,
        std::unique_ptr<aff3ct::module::Codec<B,Q>>& rCodecUPtr)
    {
        assert(encoderParamsUPtr);
        assert(decoderParamsUPtr);
        assert(interleaverCoreParamsUPtr);

        // TODO
        /*
        rCodecUPtr = AFF3CTDynamic::makeRACodec<B,Q>(
                         *safeDynamicCast<EncoderParamType>(encoderParamsUPtr),
                         *safeDynamicCast<DecoderParamType>(decoderParamsUPtr));
        assert(rCodecUPtr);
        */
    }
};

/*

//
// Encoder
//

template <typename B, typename Q>
class BCHEncoder: public AFF3CTEncoder<B,Q>
{
public:
    BCHEncoder(): AFF3CTEncoder<B,Q>()
    {
        BCHHelper<B,Q>::initCoderParams(this->_encoderParamsUPtr, this->_decoderParamsUPtr);
    }

    virtual ~BCHEncoder() = default;

protected:
    void _resetCodec() override
    {
        assert(!this->isActive());

        this->_encoderPtr = nullptr;
        BCHHelper<B,Q>::resetCodec(
            this->_encoderParamsUPtr,
            this->_decoderParamsUPtr,
            this->_codecUPtr);

        this->_encoderPtr = this->_codecUPtr->get_encoder().get();
        assert(this->_encoderPtr);
    }
};

//
// Decoder
//

template <typename B, typename Q, bool siho>
class BCHDecoder: public AFF3CTDecoder<B,Q>
{
public:
    using Class = BCHDecoder<B,Q,siho>;
    using DecoderParamType = typename BCHHelper<B,Q>::DecoderParamType;

    BCHDecoder():
        AFF3CTDecoder<B,Q>(siho ? AFF3CTDecoderType::SIHO : AFF3CTDecoderType::HIHO)
    {
        BCHHelper<B,Q>::initCoderParams(this->_encoderParamsUPtr, this->_decoderParamsUPtr);

        this->registerCall(this, POTHOS_FCN_TUPLE(Class, correctionPower));
        this->registerCall(this, POTHOS_FCN_TUPLE(Class, setCorrectionPower));
    }

    virtual ~BCHDecoder() = default;

    size_t correctionPower() const
    {
        assert(this->_decoderParamsUPtr);

        return size_t(safeDynamicCast<DecoderParamType>(this->_decoderParamsUPtr)->t);
    }

    void setCorrectionPower(size_t correctionPower)
    {
        assert(this->_decoderParamsUPtr);
        this->_throwIfBlockIsActive();

        safeDynamicCast<DecoderParamType>(this->_decoderParamsUPtr)->t = int(correctionPower);
        this->_resetCodec();
    }

protected:
    void _resetCodec() override
    {
        assert(!this->isActive());

        this->_decoderSIHOSPtr.reset();
        this->_decoderHIHOSPtr.reset();
        BCHHelper<B,Q>::resetCodec(
            this->_encoderParamsUPtr,
            this->_decoderParamsUPtr,
            this->_codecUPtr);

        if(siho) this->_decoderSIHOSPtr = this->_codecAsCodecSIHO()->get_decoder_siho();
        else     this->_decoderHIHOSPtr = this->_codecAsCodecHIHO()->get_decoder_hiho();
    }
};

//
// Registration
//

static Pothos::Block* makeBCHEncoderBlock(const Pothos::DType& dtype)
{
#define IfTypeThenEncoder(T) \
    if(doesDTypeMatch<T>(dtype)) return new BCHEncoder<B, AFF3CTTypeTraits<B>::Q>();

    IfTypeThenEncoder(B_8)
    IfTypeThenEncoder(B_16)
    IfTypeThenEncoder(B_32)
    IfTypeThenEncoder(B_64)

    throw Pothos::InvalidArgumentException("BCHEncoder: invalid type "+dtype.toString());
}

static Pothos::Block* makeBCHDecoderBlock(const Pothos::DType& dtype, const std::string& mode)
{
#define IfTypeThenDecoder(T) \
    if(doesDTypeMatch<T>(dtype) && (mode == "SIHO")) return new BCHDecoder<B, AFF3CTTypeTraits<B>::Q, true>(); \
    if(doesDTypeMatch<T>(dtype) && (mode == "HIHO")) return new BCHDecoder<B, AFF3CTTypeTraits<B>::Q, false>();

    IfTypeThenDecoder(B_8)
    IfTypeThenDecoder(B_16)
    IfTypeThenDecoder(B_32)
    IfTypeThenDecoder(B_64)

    throw Pothos::InvalidArgumentException("BCHDecoder: invalid type "+dtype.toString() + ", mode "+mode);
}

static Pothos::BlockRegistry registerBCHEncoder(
    "/fec/bch_encoder",
    &makeBCHEncoderBlock);

static Pothos::BlockRegistry registerBCHDecoder(
    "/fec/bch_decoder",
    &makeBCHDecoderBlock);

*/
