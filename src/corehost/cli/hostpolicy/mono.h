// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#ifndef _COREHOST_CLI_MONO_H_
#define _COREHOST_CLI_MONO_H_

#include "pal.h"
#include "trace.h"
#include <mutex>
#include <cstdint>
#include <memory>
#include <vector>
#include <functional>

class mono_property_bag_t;

class mono_t
{
public: // static
    static pal::hresult_t create(
        const pal::string_t& libmono_path,
        const char* exe_path,
        const char* app_domain_friendly_name,
        const mono_property_bag_t &properties,
        std::unique_ptr<mono_t> &inst);

public:
    using host_handle_t = void*;
    using domain_id_t = std::uint32_t;

    mono_t(host_handle_t host_handle, domain_id_t domain_id);
    ~mono_t() = default;

    pal::hresult_t execute_assembly(
        int argc,
        const char** argv,
        const char* managed_assembly_path,
        unsigned int* exit_code);

    pal::hresult_t create_delegate(
        const char* entryPointAssemblyName,
        const char* entryPointTypeName,
        const char* entryPointMethodName,
        void** delegate);

    pal::hresult_t shutdown(int* latchedExitCode);

private:
    std::mutex _shutdown_lock;
    bool _is_shutdown;
    host_handle_t _host_handle;
    domain_id_t _domain_id;
};

enum class common_property
{
    TrustedPlatformAssemblies,
    NativeDllSearchDirectories,
    PlatformResourceRoots,
    AppDomainCompatSwitch,
    AppContextBaseDirectory,
    AppContextDepsFiles,
    FxDepsFile,
    ProbingDirectories,
    FxProductVersion,
    JitPath,
    StartUpHooks,
    AppPaths,
    AppNIPaths,

    // Sentinel value - new values should be defined above
    Last
};

class mono_property_bag_t
{
public: // static
    static const pal::char_t* common_property_to_string(common_property key);

public:
    mono_property_bag_t();

    // Add a property to the property bag. If the property already exists, it is overwritten.
    // Returns true if the property was newly added, false if it already existed or could not be added.
    bool add(common_property key, const pal::char_t *value);
    bool add(const pal::char_t *key, const pal::char_t *value);

    bool try_get(common_property key, const pal::char_t **value);
    bool try_get(const pal::char_t *key, const pal::char_t **value);

    void remove(const pal::char_t *key);

    void log_properties() const;

    int count() const;

    void enumerate(std::function<void(const pal::string_t&, const pal::string_t&)> &callback) const;

private:
    std::unordered_map<pal::string_t, pal::string_t> _properties;
};

#endif // _COREHOST_CLI_MONO_H_
