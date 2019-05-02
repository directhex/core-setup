# Licensed to the .NET Foundation under one or more agreements.
# The .NET Foundation licenses this file to you under the MIT license.
# See the LICENSE file in the project root for more information.

cmake_minimum_required (VERSION 2.6)
project(mockmono)

set(DOTNET_PROJECT_NAME "mockmono")

set(SOURCES
    ./mockmono.cpp
)

if(WIN32)
    list(APPEND SOURCES
        mockmono.def)
endif()

include(../testlib.cmake)

install(TARGETS mockmono DESTINATION corehost_test)
install_symbols(mockmono corehost_test)
