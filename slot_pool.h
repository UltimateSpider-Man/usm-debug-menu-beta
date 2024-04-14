#pragma once

#include "func_wrapper.h"

inline constexpr auto SLOT_POOL_INVALID_HANDLE = 0xFFFFFFFF;

template<typename T0, typename T1>
struct slot_pool {
    struct slot_t
    {
        T1 id;
        T0 field_4;
    };

    int field_0;
    int field_4;
    int field_8;
    slot_t *slots;
    int field_10;
    int MAX_SLOTS;
    int field_18[8];
    int field_38;

    slot_pool(int a2) {
        this->field_14 = a2;
        this->field_C = (int *) operator new(8 * a2);
        int v3 = this->field_14;
        uint8_t v4 = 0;
        if ((v3 - 1) & v3 || v3 == 1) {
            for (; v3; ++v4) {
                v3 >>= 1;
            }

            v3 = 1 << v4;
        }

        this->field_8 = v3;
        this->field_4 = 2 * v3;
        this->field_0 = v3 - 1;

        this->sub_64A510();
    }

    void sub_64A510() {
        this->field_10 = 0;
        this->field_38 = 0;
        if (this->field_14 > 0) {
            for (int i = 0; i < this->field_14; ++i) {
                this->field_C[2 * i] = i;
            }
        }

        for (int i = 0; i < this->field_14; ++i) {
            if (this->field_38 >= 8) {
                break;
            }

            if (!(this->field_C[2 * i] & this->field_8)) {
                this->field_18[this->field_38] = i;
                ++this->field_38;
            }
        }
    }

    T0 *get_slot_contents_ptr(const uint32_t &a2)
    {
        if ( a2 == 0 ) {
            return nullptr;
        }

        auto v3 = this->field_0 & a2;
        if ( v3 < 0 || v3 >= this->MAX_SLOTS ) {
            return nullptr;
        } else {

            auto sub_6858E6 = [](auto &self, const unsigned int &a2, int) -> T0 *
            {
                if ( a2 == self.id ) {
                    return &self.field_4;
                }

                return nullptr;
            };
            return sub_6858E6(this->slots[v3], a2, this->field_0);
        }
    }
};
