#pragma once
#include "logger/logger.hpp"
#include <signal.h>
#include <random>
/**
 * Friendly name for a pure virtual routine.
 */
#define PURE = 0

#define RELEASE_ASSERT(X) \
    {                     \
        if (!(X))         \
        {                 \
            abort();      \
        }                 \
    }

#ifndef NDEBUG
#define ASSERT(X) RELEASE_ASSERT(X)
#else
#define ASSERT(X)
#endif

/**
 * Indicate a panic situation and exit.
 */
#define PANIC(X) abort();
