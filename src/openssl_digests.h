#ifndef OPENSSL_DIGESTS
#define OPENSSL_DIGESTS

// DISCLAIMER: Posted Feb 24, 2021 at 20:04 in StackOverflow by WhozCraig

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdint>

#include <openssl/evp.h>
#include <openssl/sha.h>


namespace OpenSSL {

struct Delete {
    void operator()(EVP_MD_CTX *p) const {
        EVP_MD_CTX_free(p);
    }
};
template<typename T> using Ptr = std::unique_ptr<T, Delete>;

class Digests {
  protected:
    using EVP_MD_CTX_ptr = OpenSSL::Ptr<EVP_MD_CTX>;

  public:
    Digests() {
        OpenSSL_add_all_digests();
        OpenSSL_add_all_algorithms();
    }

    // generic MD digest runner
    std::string generateDigest(const void *src, size_t slen, const EVP_MD* digest) {
        unsigned int mdlen = EVP_MD_size(digest);
        std::vector<uint8_t> md(mdlen);

        EVP_MD_CTX_ptr ctx(EVP_MD_CTX_new());
        EVP_DigestInit(ctx.get(), digest);
        EVP_DigestUpdate(ctx.get(), src, slen);
        EVP_DigestFinal(ctx.get(), md.data(), &mdlen);

        // build output string
        static const char halpha[] = "0123456789abcdef";
        std::string result;
        result.reserve(mdlen * 2);
        for( auto b : md ) {
            result.push_back(halpha[(b >> 4) & 0xF]);
            result.push_back(halpha[b & 0xF]);
        }
        return result;
    }

    std::string sha1(const void *src, std::size_t slen) {
        return generateDigest(src, slen, EVP_sha1());
    }

    std::string sha256(const void *src, std::size_t slen) {
        return generateDigest(src, slen, EVP_sha256());
    }

    std::string sha1(const std::string &src) {
        return sha1(src.c_str(), src.size());
    }

    std::string sha256(const std::string &src) {
        return sha256(src.c_str(), src.size());
    }
};

}

#endif

