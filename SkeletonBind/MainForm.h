#pragma once

namespace SkeletonBind {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm 的摘要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AllowDrop = true;
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(260, 237);
			this->panel1->TabIndex = 0;
			this->panel1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragDrop);
			this->panel1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragEnter);
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseDown);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseMove);
			this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseUp);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->panel1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void panel1_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		//System::Diagnostics::Debug::WriteLine(((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0]);
		//panel1->BackgroundImage = System::Drawing::Image::FromFile(((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0]);
		//System::Diagnostics::Debug::WriteLine(panel1->BackgroundImage->PixelFormat);
		System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0]);
		//System::Diagnostics::Debug::WriteLine(bitmap->PixelFormat);
		Rectangle rect = Rectangle(0, 0, bitmap->Width, bitmap->Height);
		System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bitmap->PixelFormat);
		unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();
		if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb) {
			int p = 0;
			for (int y = 0; y < bitmap->Height; y++) {
				for (int x = 0; x < bitmap->Width; x++) {
					int c = data[p + 0] + data[p + 1] + data[p + 2];
					c /= 3;
					data[p + 0] = c;
					data[p + 1] = c;
					data[p + 2] = c;
					p += 3;
				}
			}
		}
		else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format32bppArgb) {
			int p = 0;
			for (int y = 0; y < bitmap->Height; y++) {
				for (int x = 0; x < bitmap->Width; x++) {
					int c = data[p + 0] + data[p + 1] + data[p + 2];
					c /= 3;
					data[p + 0] = c;
					data[p + 1] = c;
					data[p + 2] = c;
					//data[p + 3] = 0;
					p += 4;
				}
			}
		}
		bitmap->UnlockBits(bitmapData);
		panel1->BackgroundImage = bitmap;
	}
	private: System::Void panel1_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;
		else
			e->Effect = DragDropEffects::None;
	}
	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		//System::Diagnostics::Debug::WriteLine("MouseDown");
	}
	private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		//System::Diagnostics::Debug::WriteLine("MouseUp");
	}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		//System::Diagnostics::Debug::WriteLine("MouseMove");
	}
	};
}
