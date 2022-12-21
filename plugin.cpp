#include <spdlog/sinks/basic_file_sink.h>

namespace logger = SKSE::log;

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) {
        SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
        return;
    }
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::info);
}

namespace PapyrusFunctions {
    void MyNativeFunctions_PrintConsole(RE::StaticFunctionTag*, std::string text) {
        RE::ConsoleLog::GetSingleton()->Print(text.c_str());
        // Also log it, just for easier testing
        logger::info("Printed to console '{}'", text);
    }
    void MyNativeFunctions_PrintLog(RE::StaticFunctionTag*, std::string text) {
        logger::info("Papyrus says '{}'", text);
    }
    std::string MyNativeFunctions_GetString(RE::StaticFunctionTag*) { return "Hello from C++"; }
    unsigned int MyNativeQuestFunctions_GetStageCount(RE::StaticFunctionTag*, RE::TESQuest* quest) {
        return quest->aliases.size();
    }
}

bool BindPapyrusFunctions(RE::BSScript::IVirtualMachine* vm) {
    vm->RegisterFunction("PrintConsole", "MyNativeFunctions", PapyrusFunctions::MyNativeFunctions_PrintConsole);
    vm->RegisterFunction("PrintLog", "MyNativeFunctions", PapyrusFunctions::MyNativeFunctions_PrintLog);
    vm->RegisterFunction("GetString", "MyNativeFunctions", PapyrusFunctions::MyNativeFunctions_GetString);
    vm->RegisterFunction("GetStageCount", "MyNativeQuestFunctions",
                         PapyrusFunctions::MyNativeQuestFunctions_GetStageCount);
    return true;
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();

    // Register a function which binds all of your Papyrus functions!
    SKSE::GetPapyrusInterface()->Register(BindPapyrusFunctions);

    return true;
}
