/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itkPrintHelper_h
#define itkPrintHelper_h

#include <iostream>
#include <iterator>
#include <vector>

#include "itkNamespace.h"

namespace itk
{

namespace print_helper
{

template <typename T>
std::ostream &
operator<<(std::ostream & os, const std::vector<T> & v)
{
  if (v.empty())
  {
    return os << "()";
  }

  os << "(";
  std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(os, ", "));
  return os << v.back() << ")";
}

} // end namespace print_helper
} // end namespace itk

#endif // itkPrintHelper_h
