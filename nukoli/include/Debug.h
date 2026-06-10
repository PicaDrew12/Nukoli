#pragma once
#include<iostream>

namespace Debug {
    void Log();

    template <typename T, typename... Args>
    void Log(T first, Args... rest) {
        std::cout << "\033[37m" << first;
        Log(rest...);
    }
    void Warn();

    template <typename T, typename... Args>
    void Warn(T first, Args... rest) {
        std::cout << "\033[33m" << first;
        Warn(rest...);
    }

    void Error();

    template <typename T, typename... Args>
    void Error(T first, Args... rest) {
        std::cout << "\033[31m" << first;
        Error(rest...);
    }
}