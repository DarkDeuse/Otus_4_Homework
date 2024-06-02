#pragma once

/// @file print_ip.h
/// @brief Шаблонная функция для вывода IP-адресов, без проверки на корректность

// STL
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <vector>

/// @brief  Печать целочисленного типа, где каждый байт разделен точками (как IPv4-адреса через точки)
/// @tparam T целочисленный тип
/// @param  value  целочисленное значение для вывода
template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(const T& value)
{
    constexpr auto kNumberBytesInValue  = sizeof(value);
    const auto* ptr_to_begin_byte_value = reinterpret_cast<const uint8_t*>(&value);

    for (size_t i = 0; i < kNumberBytesInValue - 1; i++)
        std::cout << static_cast<uint16_t>(ptr_to_begin_byte_value[kNumberBytesInValue - i - 1])
                  << ".";

    std::cout << static_cast<uint16_t>(ptr_to_begin_byte_value[0]) << std::endl;
}

/// @brief Печать передаваемой строки (нет проверки на корректность IPv4-адресу)
/// @tparam T строка
/// @param value строка с ip-адресом
template <typename T, std::enable_if_t<std::is_same<std::string, T>::value, bool> = true>
void print_ip(const T& value)
{
    std::cout << value << std::endl;
}

/// @brief Печать элементов контейнера, разделенных точками (нет проверки на корректность IPv4-адресу)
/// @tparam T std::vector или std::list
/// @param value контейнер
template <typename T,
          std::enable_if_t<std::is_same<T, std::vector<typename T::value_type>>::value |
                               std::is_same<T, std::list<typename T::value_type>>::value,
                           bool> = true>
void print_ip(const T& value)
{
    if (value.empty()) 
        return;

    std::for_each(value.begin(), --value.end(),
                  [](const auto& value) { std::cout << value << "."; });

    std::cout << value.back() << std::endl;
}