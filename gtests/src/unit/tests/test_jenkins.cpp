// Copyright 2011 Google Inc. All Rights Reserved.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.

#include <gtest/gtest.h>
#include <cstdint>

#include "jenkins_hash.hpp"

inline char* to_char_ptr (uint8_t* uptr) {
  return reinterpret_cast<char *>(uptr);
}

inline const char* to_char_ptr (const uint8_t* uptr) {
  return reinterpret_cast<const char *>(uptr);
}

TEST(JenkinsUnitTest, TestHash64) {

  const uint64_t seed = 97;

  const uint8_t b1[] = {
      0xc7, 0x25, 0x1d, 0x5d, 0x75, 0x3a, 0x4e, 0x46, 0x22, 0x29, 0x4d, 0x6c, 0x67, 0x7a, 0xa8, 0x25,
      0x71
  };

  const uint8_t b2[] = {
      0x83, 0x8e, 0x7e, 0xf0, 0x71, 0xef, 0x9b, 0x3e, 0x4a, 0xe6, 0x12, 0x60, 0xc0, 0xa1, 0xf9, 0x94,
      0x5a, 0x85, 0x9b, 0xb1, 0xf6, 0x86, 0x97, 0xe1, 0xab, 0x87, 0xc8, 0xab, 0xc1, 0x28, 0xd1, 0x72,
      0x73, 0x0b, 0xda, 0x50, 0xe3, 0xe6, 0xf9, 0x42
  };

  const uint8_t b3[] = {
      0xad, 0xe3, 0xaa, 0xb7, 0xd2, 0xbc, 0x3a, 0xe6, 0x60, 0xe4, 0xc6, 0xc1, 0x02, 0x0a, 0x3a, 0x50,
      0x66, 0xb2, 0x26, 0x6c, 0x1d, 0x1b, 0x16, 0xb1, 0x1b, 0x51, 0x74, 0x9c, 0xa7, 0xbb, 0xad, 0x46,
      0x25, 0x54, 0xca, 0x30, 0x3a, 0x31, 0xd0, 0x34, 0x56, 0xac, 0xb1, 0xca, 0xaf, 0x7f, 0x5c, 0xf3,
      0x9e, 0x16, 0x94, 0x78, 0x84, 0xca, 0x60, 0x66, 0x27, 0x59, 0xe1, 0x99, 0xb4, 0xc4, 0xbd, 0x50,
      0x48, 0x50, 0xcb, 0xa6, 0x0b, 0xe1, 0x71, 0x31, 0x49, 0x27, 0x11, 0x9e, 0xcc, 0xcd, 0xd8, 0x19,
      0x09, 0xc6, 0xdf, 0x15, 0x64, 0x0d, 0xf7, 0x25, 0x5c, 0x48, 0x19, 0xc7, 0x6b, 0x10, 0x02, 0x7e,
      0x31, 0x54, 0x2a, 0xd8, 0x92, 0xe5, 0xc5, 0xab, 0xe9, 0x3d, 0x57, 0x99, 0x9a, 0x93, 0x4f, 0x48,
      0x3f, 0xfa, 0x73, 0x36, 0x03, 0xe1, 0xbd, 0x27, 0xe5, 0x06, 0x8a, 0x21, 0x33, 0xff, 0x91, 0x80,
      0x36, 0x4d, 0x2d, 0x04, 0xc7, 0x11, 0xcc, 0x2a, 0xc0, 0xa9, 0x17, 0x18, 0x73, 0xff, 0xd5, 0x0e,
      0x0d, 0x8b, 0x6f, 0x8b, 0xba, 0x8c, 0x37, 0x49, 0xb1, 0x31, 0x5b, 0xf4, 0x4d, 0xd7, 0x19, 0x10,
      0x40, 0x6e, 0x61, 0x41, 0xf1, 0x55, 0xaa, 0x44, 0x79, 0x13, 0x57, 0x3b, 0x72, 0xac, 0xfe, 0xce,
      0xf8, 0xd7, 0x07, 0x82, 0x05, 0xef, 0x0f, 0x53, 0x6c, 0xfe, 0x7d, 0x94, 0x48, 0xa5, 0x48, 0x42,
      0x47, 0x70, 0x29, 0xe7, 0x7e, 0x53, 0xca, 0x88, 0x89, 0x8a, 0xec, 0xe5, 0x01, 0x44, 0xf5, 0xc5,
      0xc9, 0x89, 0x6d, 0x6a, 0xf1, 0x26, 0x61, 0xae, 0x30, 0x50, 0x61, 0x68, 0x41, 0xac, 0x82, 0x40,
      0xdb, 0x12, 0x00, 0x68, 0xad, 0x34, 0x52, 0xb2, 0xbb, 0xc5, 0x74, 0xf1, 0x3e, 0x00, 0x98, 0x6e,
      0x1d, 0xc2, 0xd7, 0x7d, 0xc6, 0xc7, 0x10, 0xb2, 0xac, 0xcf, 0x8b, 0x25, 0xd9, 0x7d, 0xd5, 0x20
  };

  EXPECT_TRUE(cass::Hash64StringWithSeed(to_char_ptr(b1), sizeof(b1), seed) == 1789751740810280356ul);
  EXPECT_TRUE(cass::Hash64StringWithSeed(to_char_ptr(b2), sizeof(b2), seed) == 4001818822847464429ul);
  EXPECT_TRUE(cass::Hash64StringWithSeed(to_char_ptr(b3), sizeof(b3), seed) == 15240025333683105143ul);

}
