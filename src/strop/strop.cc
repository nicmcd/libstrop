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
#include "strop/strop.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>

// modified from:
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring  NOLINT

namespace strop {

// trim from start
std::string leftTrim(std::string _s) {
  _s.erase(_s.begin(),
           std::find_if(_s.begin(), _s.end(),
                        std::not1(std::ptr_fun<int, int>(std::isspace))));
  return _s;
}

// trim from end
std::string rightTrim(std::string _s) {
  _s.erase(std::find_if(
      _s.rbegin(),
      _s.rend(),
      std::not1(std::ptr_fun<int, int>(std::isspace))).base(), _s.end());
  return _s;
}

// trim from both ends
std::string trim(std::string _s) {
  return leftTrim(rightTrim(_s));
}

// converts to uppercase
std::string toLower(std::string _s) {
  std::transform(_s.begin(), _s.end(), _s.begin(), ::tolower);
  return _s;
}

// converts to lowercase
std::string toUpper(std::string _s) {
  std::transform(_s.begin(), _s.end(), _s.begin(), ::toupper);
  return _s;
}

// split a string into tokens via a delimiter
std::vector<std::string> split(const std::string& _s, char _delim) {
  std::vector<std::string> tokens;
  std::stringstream ss(_s);
  std::string item;
  while (std::getline(ss, item, _delim)) {
    tokens.push_back(item);
  }
  return tokens;
}

}  // namespace strop
