// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#ifndef _MOCKMONO_H_
#define _MOCKMONO_H_

#include "pal.h"
#include "error_codes.h"

namespace mono_t
{
    using host_handle_t = void*;
    using domain_id_t = std::uint32_t;
};

// Prototype of the coreclr_initialize function from mono.dll
SHARED_API pal::hresult_t STDMETHODCALLTYPE coreclr_initialize(
    const char* exePath,
    const char* appDomainFriendlyName,
    int propertyCount,
    const char** propertyKeys,
    const char** propertyValues,
    mono_t::host_handle_t* hostHandle,
    unsigned int* domainId);

// Prototype of the coreclr_shutdown function from mono.dll
SHARED_API pal::hresult_t STDMETHODCALLTYPE coreclr_shutdown_2(
    mono_t::host_handle_t hostHandle,
    unsigned int domainId,
    int* latchedExitCode);

// Prototype of the coreclr_execute_assembly function from mono.dll
SHARED_API pal::hresult_t STDMETHODCALLTYPE coreclr_execute_assembly(
    mono_t::host_handle_t hostHandle,
    unsigned int domainId,
    int argc,
    const char** argv,
    const char* managedAssemblyPath,
    unsigned int* exitCode);

// Prototype of the coreclr_create_delegate function from mono.dll
SHARED_API pal::hresult_t STDMETHODCALLTYPE coreclr_create_delegate(
    mono_t::host_handle_t hostHandle,
    unsigned int domainId,
    const char* entryPointAssemblyName,
    const char* entryPointTypeName,
    const char* entryPointMethodName,
    void** delegate);

#endif // _MOCKMONO_H_
