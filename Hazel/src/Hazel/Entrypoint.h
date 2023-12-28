#pragma once


#ifdef  HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argcv) {

	Hazel::Log::Init();
	HZ_WARN("111");
	int a = 3;
	HZ_CORE_INFO("222 {0}",a);
	auto app = Hazel::CreateApplication();

	app->Run();
	
	delete app;
	return 0;
}
#endif //  HZ_PLATFORM_WINDOWS


