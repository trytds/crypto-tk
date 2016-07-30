//
// libsse_crypto - An abstraction layer for high level cryptographic features.
// Copyright (C) 2015-2016 Raphael Bost
//
// This file is part of libsse_crypto.
//
// libsse_crypto is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// libsse_crypto is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with libsse_crypto.  If not, see <http://www.gnu.org/licenses/>.
//


#pragma once

#define USE_AESNI (!defined( NO_AESNI ) && defined (__AES__))

#include <cstdint>

namespace sse
{
    
    namespace crypto
    {
        
        extern uint64_t tick_counter;
    }
}

#if USE_AESNI

#include <array>

#include <emmintrin.h>
#include <wmmintrin.h>
#include <tmmintrin.h>


namespace sse
{
    
    namespace crypto
    {
        constexpr uint8_t kNround = 10;
        constexpr uint8_t kBlockSize = 16;


        typedef std::array<uint8_t, kBlockSize> aes_key_type;
        typedef std::array<uint8_t, (kNround+1)*kBlockSize> aes_subkeys_type;

        aes_subkeys_type aesni_derive_subkeys(const uint8_t* key);
        inline aes_subkeys_type aesni_derive_subkeys(const aes_key_type& key)
        {
            return aesni_derive_subkeys(key.data());
        }
        

        void aesni_encrypt(const uint8_t* in, const aes_subkeys_type &subkeys, uint8_t *out);

        void aesni_encrypt2(const uint8_t* in, const aes_subkeys_type &subkeys, uint8_t *out);
        
        
        void pipeline_encrypt1(const uint8_t* in, const uint8_t* key, uint8_t *out);
        void pipeline_encrypt2(const uint8_t* in, const uint8_t* key, uint8_t *out);
        void pipeline_encrypt2_bad(const uint8_t* in, const uint8_t* key, uint8_t *out);

    }
}

#endif