// SPDX-License-Identifier: GPL-3.0-only
#pragma once

#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <concepts>

template<std::integral T = unsigned>
class localid {

public:
    localid();
    localid(T value);
    localid(const localid&) = default;
    localid(std::string encoded);
    std::string to_string() const;
    bool is_valid() const noexcept;
    template<std::integral TT>
    friend std::ostream& operator << (std::ostream& os, const localid<TT>& h);
    friend auto operator<=>(const localid&, const localid&) = default;
    operator T() const;

private:
    T value;
    bool valid = true;
    static std::string_view dict;
};

template<std::integral T>
localid<T>::operator T() const {
    return value;
}

template<std::integral T> std::string_view localid<T>::dict = "0123456789ABCDEFGHJKLMNPQRTUVWXY";

thread_local std::random_device rd;
thread_local std::mt19937_64 eng(rd());

template<std::integral T>
localid<T>::localid() {
    thread_local std::uniform_int_distribution<T> distr;
    value = distr(eng);
}

template<std::integral T>
localid<T>::localid(T value) : value(value) {}

template<std::integral T>
localid<T>::localid(std::string encod) {
    T reconst = 0;
    for (char c : encod)
    {
        reconst *= dict.size();
        auto loc = std::find(dict.begin(), dict.end(), c);
        if (loc == dict.end()) {
            value = 0;
            valid = false;
            return;
        }
        reconst += std::distance(dict.begin(), loc);
    }
    value = reconst;
}

template<std::integral TT>
std::ostream& operator << (std::ostream& os, const localid<TT>& h)
{
    os << h.to_string();
    return os;
}

template<std::integral T>
bool localid<T>::is_valid() const noexcept {
    return valid;
}

#include <type_traits>

template<std::integral T>
std::string localid<T>::to_string() const
{
    std::string encod;

    using unsigned_t = std::make_unsigned_t<T>;
    auto unsigned_value = static_cast<unsigned_t>(value);

    while (unsigned_value != 0) {
        encod += dict[unsigned_value % dict.size()];
        unsigned_value /= dict.size();
    }
    std::reverse(encod.begin(), encod.end());

    return encod;
}

namespace std {
    template<std::integral T>
    struct hash<localid<T>> {
        std::size_t operator()(const localid<T>& id) const noexcept { return hash<T>()(static_cast<T>(id)); }
    };
}