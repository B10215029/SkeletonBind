#include "MainForm.h"

[System::STAThreadAttribute]
int main(array<System::String^>^ args) {
	//System::Windows::Forms::Application::EnableVisualStyles();
	//System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	SkeletonBind::MainForm form;
	System::Windows::Forms::Application::Run(%form);
}