#include "pointers.hpp"
#include "../hooking/hooking.hpp"
#include "../log/log.hpp"
#include "../MemoryEdit.h"
#include "../scrProgram.h"

namespace VX {

    pointers g_pointers;

    void pointers::Initialize() {
        auto start = std::chrono::steady_clock::now();

        m_script_virtual_machine = reinterpret_cast<types::script_virtual_machine*>(g_memory.scan("E8 ? ? ? ? 48 85 FF 48 89 1D", "SVM", 1, true));
        m_frame_count = reinterpret_cast<std::uint32_t*>(g_memory.scan("8B 15 ? ? ? ? 41 FF CF", "FC", 2, true));
        m_get_native_handler = reinterpret_cast<types::get_native_handler*>(g_memory.scan("48 89 5C 24 18 48 89 7C 24 20 0F", "GNH"));
        m_native_registration_table = reinterpret_cast<rage::scrNativeRegistrationTable*>(g_memory.scan("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", "NRT", 3, true));
        m_fix_vector = reinterpret_cast<types::fix_vector*>(g_memory.scan("83 79 18 00 48 8B D1 74 4A", "FV"));
        //m_set_this_thread_networked = reinterpret_cast<PVOID>(g_memory.scan("48 8B C8 FF 52 30 84 C0 74 05 48", "STHN", 8));
       // m_match_making_region = reinterpret_cast<std::uint8_t*>(g_memory.scan("48 8D 15 ? ? ? ? 48 8D 4C 24 ? 89 05 ? ? ? ? E8 ? ? ? ?", "MMR", 3, true));
       // m_streamed_scripts = g_memory.scan("44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1", "SS", 0, false);
        m_vehicle_hash_pool = reinterpret_cast<rage::hash_list*>(g_memory.scan("4C 03 05 ? ? ? ? EB 09 49 83 C2 04 EB 8B", "VHP", 3, true));
        hash_list = reinterpret_cast<rage::hash_list*>(g_memory.scan("4C 03 05 ? ? ? ? EB 09 49 83 C2 04 EB 8B", "HL", 3, true));
        //host_token = reinterpret_cast<int64_t*>(g_memory.scan("48 8B 05 ? ? ? ? 48 83 F8 FF", "HT", 3, true));
        m_GlobalPtr = reinterpret_cast<intptr_t**>(g_memory.scan("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", "GP", 3, true));
        //m_model_spawn_bypass = reinterpret_cast<PVOID>(g_memory.scan("48 8B C8 FF 52 30 84 C0 74 05 48", "MSB", 3, true));
        //m_ped_factory = reinterpret_cast<CPedFactory**>(g_memory.scan("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", "PF", 3, true));
        //set_this_thread_networked = reinterpret_cast<PVOID>(g_memory.scan("48 8B C8 FF 52 30 84 C0 74 05 48", "STTN", 3, true));
        m_GlobalBase = reinterpret_cast<std::uint64_t**>(g_memory.scan("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", "GB", 3, true));
       // add_item_to_basket = reinterpret_cast<std::uint64_t**>(g_memory.scan("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B F2 48 8D 54 24", "AITO", 3, true));
        //construct_basket = reinterpret_cast<std::uint64_t**>(g_memory.scan("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 30 48 8B F1", "CB", 3, true));
        //net_shop_mgr = reinterpret_cast<rage::netShopping::CNetworkShoppingMgr*>(g_memory.scan("48 8B 0D ? ? ? ? 41 8A D9", "NSM", 3, true));
        m_register_file = reinterpret_cast<types::file_register> (g_memory.scan("40 88 7C 24 ? E8 ? ? ? ? 0F B7 44 24 ?", "RGF", 5));
        m_handle_to_ptr = reinterpret_cast<types::handle_to_ptr>(g_memory.scan("83 F9 FF 74 31 4C 8B 0D", "htp"));
       // net_shop_mgr = reinterpret_cast<rage::netShopping::CNetworkShoppingMgr*>(g_memory.scan("48 8B 0D ? ? ? ? 41 8A D9", "NSM", 3, true));
        m_is_session_started = reinterpret_cast<bool*>(g_memory.scan("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", "ISS", 3, true));
        char* c_location = nullptr;
        auto p_worldPtr = Memory::pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
        c_location = p_worldPtr.count(1).get(0).get<char>(0);
        m_WorldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

        auto end = std::chrono::steady_clock::now();

        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        g_log.send("Memory", "Finished scanning {} signatures in {}ms", g_memory.m_sig_count, elapsed_time);
    }
    pointers* GetPointers() { return &g_pointers; }
}