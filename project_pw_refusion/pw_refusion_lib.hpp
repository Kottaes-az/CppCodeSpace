#pragma once
#pragma optimize(2)
#include <cryptopp/aes.h>
#include <cryptopp/base64.h>
#include <cryptopp/default.h>
#include <cryptopp/osrng.h>
#include <fast_io.h>
#define PWR_CRYPTION_MODE CBC_Mode
namespace fau {
    namespace crypt {
        // basic_string based on unsigned char(0 ~255).
        using byte_string = std::basic_string<CryptoPP::byte>;

        namespace Base64 {
            static byte_string stringEncryption(const byte_string &);
            static byte_string stringDecryption(const byte_string &);
        } // namespace Base64
        namespace AES {
            static std::string stringEncryption(const std::string &,
                                                const byte_string &,
                                                const byte_string &);
            static std::string stringDecryption(const std::string &,
                                                const byte_string &,
                                                const byte_string &);
            void GenerateKey();
            void SetKey(CryptoPP::byte *, CryptoPP::byte *, const size_t &);
        } // namespace AES

    } // namespace crypt
} // namespace fau
static fau::crypt::byte_string
fau::crypt::Base64::stringEncryption(const byte_string &bysPlain) {
    byte_string bysEncoded;
    CryptoPP::Base64Encoder encrB64;
    encrB64.Put(bysPlain.c_str(), bysPlain.size());
    // cause CryptoPP::byte(aka unsigned char)'s size was 1,
    // so omitted '* sizeof(CryptoPP:byte)'.
    encrB64.MessageEnd();

    CryptoPP::lword wordTemp = encrB64.MaxRetrievable();
    if (wordTemp) {
        bysEncoded.resize(wordTemp);
        encrB64.Get((CryptoPP::byte *)bysEncoded.c_str(), bysEncoded.size());
    }
    return bysEncoded;
}
static fau::crypt::byte_string
fau::crypt::Base64::stringDecryption(const byte_string &bysCipher) {
    byte_string bysDecoded;
    CryptoPP::Base64Decoder decrB64;
    decrB64.Put(bysCipher.c_str(), bysCipher.size());
    decrB64.MessageEnd();

    CryptoPP::lword wordTemp = decrB64.MaxRetrievable();
    if (wordTemp && wordTemp <= SIZE_MAX) {
        bysDecoded.resize(wordTemp);
        decrB64.Get((CryptoPP::byte *)bysDecoded.c_str(), bysDecoded.size());
    }
    return bysDecoded;
}

static std::string
fau::crypt::AES::stringEncryption(const std::string &strPlain,
                                  const byte_string &key,
                                  const byte_string &iv) {
    std::string strCipher;
    try {
        CryptoPP::PWR_CRYPTION_MODE<CryptoPP::AES>::Encryption encrAES;
        encrAES.SetKeyWithIV((CryptoPP::byte *)key.c_str(), key.size(),
                             (CryptoPP::byte *)iv.c_str());

        // The StreamTransformationFilter removes
        //  padding as required.
        CryptoPP::StringSource strsrcEncrAES(
            strPlain, true,
            new CryptoPP::StreamTransformationFilter(
                encrAES,
                new CryptoPP::StringSink(
                    strCipher)) // StreamTransformationFilter
        );                      // StringSource
    } catch (const CryptoPP::Exception &excptEncr) {
        print(excptEncr.what(), '\n');
    }

    std::string strEcdToB64;
    CryptoPP::StringSource strsrcEncrB64(
        strCipher, true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(strEcdToB64))); // StringSource
    return strEcdToB64;
}
static std::string
fau::crypt::AES::stringDecryption(const std::string &strCipher,
                                  const byte_string &key,
                                  const byte_string &iv) {
    std::string strDcdFromB64;
    CryptoPP::StringSource strsrcDecrB64(
        strCipher, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink(strDcdFromB64)));

    std::string strPlain;
    try {
        CryptoPP::PWR_CRYPTION_MODE<CryptoPP::AES>::Decryption decrAES;
        decrAES.SetKeyWithIV((CryptoPP::byte *)key.c_str(), key.size(),
                             (CryptoPP::byte *)iv.c_str());

        CryptoPP::StringSource strsrcDecrAES(
            strDcdFromB64, true,
            new CryptoPP::StreamTransformationFilter(
                decrAES,
                new CryptoPP::StringSink(
                    strPlain)) // StreamTransformationFilter
        );                     // StringSource
    } catch (const CryptoPP::Exception &excptDecr) {
        print(excptDecr.what(), '\n');
    }

    return strPlain;
}
#undef PWR_CRYPTION_MODE