#pragma once

#include "variable.h"
#include "func_wrapper.h"
#include "mstring.h"

#include <optional>


struct os_developer_options
{
    enum strings_t {
        SOUND_LIST = 0,
        SCENE_NAME = 1,
        HERO_NAME = 2,
        GAME_TITLE = 3,
        GAME_LONG_TITLE = 4,
        SAVE_GAME_DESC = 5,
        VIDEO_MODE = 6,
        GFX_DEVICE = 7,
        FORCE_DEBUG_MISSION = 8,
        FORCE_LANGUAGE = 9,
        SKU = 10,
        CONSOLE_EXEC = 11,
        HERO_START_DISTRICT = 12,
        DEBUG_ENTITY_NAME = 13,
    };

    bool m_flags[150];
    mString m_strings[14];
    int m_ints[76];

    std::optional<mString> get_string(strings_t a2)
    {
        if (a2 < strings_t::SOUND_LIST || a2 > strings_t::DEBUG_ENTITY_NAME) {
            return {};
        } else {
            auto a3 = this->m_strings[a2];
            return a3;
        }
    }

    int get_int(const mString &a2)
    {
        return this->m_ints[this->get_int_from_name(a2)];
    }

    int get_int2(const mString &a2)
    {
        return this->m_ints[this->get_int_from_name(a2)];
    }

    void set_int(const mString &a2, int a3)
    {
        this->m_ints[this->get_int_from_name(a2)] = a3;
    }

    void set_flag(const mString &a2, bool a3)
    {
        this->m_flags[this->get_flag_from_name(a2)] = a3;
    }

    static inline Var<const char *[76]> int_names { 0x00936940 };

    static inline Var<int[76]> int_defaults{0x00936A70};

    int get_int_from_name(const mString &a1) {

        auto func = [&a1](auto &v2) {
            return (_strcmpi(v2, a1.c_str()) == 0);
        };

        auto it = std::find_if(std::begin(int_names()),
                                std::end(int_names()),
                                func);

        if (it == std::end(int_names())) {
            printf("Nonexistent int %s", a1.c_str());
        }

        return std::distance(std::begin(int_names()), it);
    }


    mString* get_hero_name()
    {
        if constexpr (1) {
            static Var<int> dword_96A4AC { 0x0096A4AC };

            static Var<mString> result { 0x0096A49C };


            void(__fastcall * sub_868B40)(void*, void*) = (decltype(sub_868B40))0x00868B40;

            if (!(dword_96A4AC() & 1)) {
                dword_96A4AC() |= 1u;

                result() = mString { "HERO" };
            }

            result() = this->m_strings[2];
            return (&result());
        } else {
            return (mString*)CDECL_CALL(0x005C3150, this);
        }
    }


    static inline Var<const char *[150]> flag_names { 0x00936420 };

    static inline Var<BOOL[150]> flag_defaults{0x00936678};

    int get_flag_from_name(const mString &a1) {
        const char **v2 = flag_names();
        do {
            if (_strcmpi(*v2, a1.guts) == 0) {
                break;
            }

            ++v2;
        } while (v2 != (const char **) flag_defaults());

        int v3 = v2 - flag_names();
        if (v3 == 150) {
            printf("Nonexistent option flag %s", a1.c_str());
        }

        return v3;
    }

    bool get_flag(int a2)
    {
        return this->m_flags[a2];
    }

    bool get_flag(const mString &a2)
    {
        return this->m_flags[this->get_flag_from_name(a2)];
    }

    static inline Var<os_developer_options *> instance{0x0096858C};
};

Var<int[76]> int_defaults{0x00936A70};

Var<const char *[76]> int_names { 0x00936940 };

Var<BOOL[150]> flag_defaults{0x00936678};

Var<const char *[150]> flag_names { 0x00936420 };



