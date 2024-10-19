#include "invoker.hpp"
#include "../log/log.hpp"
namespace VX {
	invoker g_invoker;
	native_call_context::native_call_context() {
		m_return_value = &m_return_stack[0];
		m_args = &m_arg_stack[0];
	}
	bool invoker::cache_handler() {
		for (const rage::scrNativeMapping& mapping : g_crossmap) {
		   rage::scrNativeHandler handler = GetPointers()->m_get_native_handler(GetPointers()->m_native_registration_table, mapping.second);
		   m_cache.emplace(mapping.first, handler);	
		}
		g_log.send("Invoker", "Natives cached");
		return true;
	}

	void invoker::begin_call() {
		m_call_context.reset();
	}

	void invoker::end_call(rage::scrNativeHash hash) {
		if (auto it = m_cache.find(hash); it != m_cache.end()) {
			rage::scrNativeHandler handler = it->second;
			handler(&m_call_context);
			GetPointers()->m_fix_vector(&m_call_context);
		}
		else {
			g_log.send("invoker", "failed to find {} in crossmap", hash);
		}
	}
	invoker* GetInvoker() { return &g_invoker; }
}