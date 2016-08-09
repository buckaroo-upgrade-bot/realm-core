/*************************************************************************
 *
 * Copyright 2016 Realm Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **************************************************************************/

#ifndef REALM_DESCRIPTOR_FWD_HPP
#define REALM_DESCRIPTOR_FWD_HPP

#include <memory>

namespace realm {

class Descriptor;
using DescriptorRef = std::shared_ptr<Descriptor>;
using ConstDescriptorRef = std::shared_ptr<const Descriptor>;

} // namespace realm

#endif // REALM_DESCRIPTOR_FWD_HPP
