/* Copyright 2016 Carnegie Mellon University, NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "storehouse/storage_backend.h"

#include <folly/Memory.h>
#include <proxygen/httpserver/RequestHandler.h>

namespace proxygen {
class ResponseHandler;
}

namespace scanner {

class VideoHandlerStats;

class VideoHandler : public proxygen::RequestHandler {
 public:
  explicit VideoHandler(
    VideoHandlerStats* stats,
    storehouse::StorageConfig* config,
    const std::string& job_name);

  void onRequest(std::unique_ptr<proxygen::HTTPMessage> message)
      noexcept override;

  void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

  void onEOM() noexcept override;

  void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;

  void requestComplete() noexcept override;

  void onError(proxygen::ProxygenError err) noexcept override;

 private:
  VideoHandlerStats* const stats_{nullptr};
  std::unique_ptr<storehouse::StorageBackend> storage_{nullptr};
  std::string job_name_;

  std::unique_ptr<proxygen::HTTPMessage> message_;
  std::unique_ptr<folly::IOBuf> body_;
};

}