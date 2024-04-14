#pragma once

#include "float.hpp"
#include "string_hash.h"

#include <cstdint>

struct sound_instance {
    void stop();
};

struct sound_instance_slot {
    int field_0[20];
    int field_50;
};

struct sound_instance_id {
    uint32_t field_0;

    sound_instance_id() = default;

    sound_instance_id(uint32_t a1) : field_0(a1) {}

    sound_instance *get_sound_instance_ptr();
};

[[nodiscard]] extern sound_instance_id sub_60B960(string_hash a2, Float a3, Float a4);

extern Var<sound_instance_slot *> s_sound_instance_slots;
