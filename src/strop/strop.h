/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef STROP_STROP_H_
#define STROP_STROP_H_

#include <prim/prim.h>

#include <string>
#include <vector>

namespace strop {

std::string leftTrim(std::string _s);
std::string rightTrim(std::string _s);
std::string trim(std::string _s);

std::string toLower(std::string _s);
std::string toUpper(std::string _s);

std::vector<std::string> split(const std::string& _s, char _delim);
std::string join(const std::vector<std::string>& _v, char _delim);

std::vector<char*> toCharArrays(const std::vector<std::string>& _vec);

template <typename T>
std::string vecString(const std::vector<T>& _a, char _delim = ',',
                      s32 _precision = -1);

std::string replaceFirst(const std::string& _str, const std::string& _from,
                         const std::string& _to);
std::string replaceAll(const std::string& _str, const std::string& _from,
                       const std::string& _to);

bool startswith(const std::string& _str, const std::string& _prefix);
bool endswith(const std::string& _str, const std::string& _suffix);

std::size_t findNth(const std::string& _str, char _c, u32 _n);

}  // namespace strop

#include "strop/strop.tcc"

#endif  // STROP_STROP_H_
