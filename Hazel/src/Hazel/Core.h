#pragma once
#include<memory>

#ifdef  HZ_PLATFORM_WINDOWS
#ifdef HZ_DYNAMIC_LINK
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif // HZ_BUILD_DLL
#else
	#define HAZEL_API
#endif
#else
	#error Hazel Only Supports Windows!
#endif //  HZ_PLATFORM_WINDOWS


#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref   = std::shared_ptr<T>;
}

//HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
//// ×ª»»³É
//{ if (!(success)) {
//	::Hazel::Log::GetCoreLogger()->error("Assertion Failed: {0}", "Could not intialize GLFW!");


