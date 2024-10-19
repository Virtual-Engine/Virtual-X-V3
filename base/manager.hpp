#pragma once
#include "fiber.hpp"
#include "log/log.hpp"

namespace VX {
	inline std::recursive_mutex m_Mutex;
	inline std::vector<fiber*> g_fibers;
	inline bool m_once;
	inline void add_fiber(fiber* script) {
		std::lock_guard Lock(m_Mutex);
		g_log.send("Fibers", std::format("Create: {}", script->m_name).c_str());
		g_fibers.push_back(std::move(script));
	}

	inline void handle_fibers() {
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
		if (!ensure_main_fiber) {
			return;
		}
		for (auto const& script : g_fibers) {
			if (script->m_disabled)
				return;
			script->tick();
		}
	}
}
