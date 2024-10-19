#pragma once
#include "../manager.hpp"
#include "../hooking.hpp"
#include "../../queue.h"
namespace VX {
	std::int64_t hooks::script_virtual_machine(void* stack, std::int64_t** globals, std::int64_t* program, std::int64_t* thread_context) {
		static std::uint32_t hook_frame_count;
		if (hook_frame_count != *GetPointers()->m_frame_count) {
			handle_fibers();
			g_queue.create_scripts();
			hook_frame_count = *GetPointers()->m_frame_count;
		}
		return GetHooking()->m_script_virtual_machine.get_original<decltype(&script_virtual_machine)>()(stack, globals, program, thread_context);
	}
}