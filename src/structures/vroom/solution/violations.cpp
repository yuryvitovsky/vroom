/*

This file is part of VROOM.

Copyright (c) 2015-2020, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include <cassert>

#include "structures/vroom/solution/violations.h"

namespace vroom {

Violations::Violations()
  : lead_time(0),
    delay(0),
    start_lead_time(std::nullopt),
    end_delay(std::nullopt) {
}

Violations::Violations(const Duration lead_time,
                       const Duration delay,
                       const Duration start_lead_time,
                       const Duration end_delay,
                       const std::unordered_set<VIOLATION>&& types)
  : lead_time(lead_time),
    delay(delay),
    start_lead_time(start_lead_time),
    end_delay(end_delay),
    types(std::move(types)) {
}

Violations& Violations::operator+=(const Violations& rhs) {
  this->lead_time += rhs.lead_time;
  this->delay += rhs.delay;

  assert(this->start_lead_time.has_value() and this->end_delay.has_value());
  if (rhs.start_lead_time.has_value()) {
    this->start_lead_time.value() += rhs.start_lead_time.value();
  }
  if (rhs.end_delay.has_value()) {
    this->end_delay.value() += rhs.end_delay.value();
  }

  for (const auto t : rhs.types) {
    this->types.insert(t);
  }

  return *this;
}

} // namespace vroom
