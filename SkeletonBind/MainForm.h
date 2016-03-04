#pragma once
#include <Windows.h>
#include "DrawTexture.h"
#include "DrawSkeleton.h"
#include "SkeletonData.h"
#include "ShaderUtility.h"
#include <math.h>
#include <iostream>
#include <fstream>

#define FRAME_PRE_SECOND 29

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
			//FreeConsole();
			//HWND handleWindow = FindWindowA("ConsoleWindowClass", NULL);
			//ShowWindow(handleWindow, SW_HIDE);

			InitializeComponent();
			hGLRC = NULL;
			hDC = GetDC((HWND)(this->panel1->Handle.ToInt32()));
			drawTexture = new DrawTexture();
			drawSkeleton = new DrawSkeleton();
			skeletonData = new SkeletonData();
			selectPoint = -1;
			selectPosition = new int[2];
			imageFileName = "";
			initializeOpenGLContext();
			reshape(this->panel1->Width, this->panel1->Height);
			display();


			mediaPlayer = gcnew System::Windows::Media::MediaPlayer();
			mediaPlayer->Open(gcnew Uri("C:\\Users\\Delim\\Desktop\\video.mp4"));
			while (mediaPlayer->DownloadProgress != 1) {
				std::cout << "not yet" << std::endl;
				System::Threading::Thread::Sleep(0.5 * 1000);
			}
			std::cout << "ok" << std::endl;
			mediaPlayer->ScrubbingEnabled = true;
			mediaPlayer->Play();
			timer1->Interval = 1.0 / FRAME_PRE_SECOND * 1000;
			timer1->Enabled = true;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				mediaPlayer->Close();
				if (hGLRC) {
					wglMakeCurrent(NULL, NULL);
					wglDeleteContext(hGLRC);
				}
				delete drawTexture;
				delete drawSkeleton;
				delete skeletonData;
				delete components;
				components = nullptr;
			}
		}
		bool initializeOpenGLContext();
		void reshape(int width, int height);
		void display();
		void saveImage();
	private: System::Windows::Forms::Panel^  panel1;
	protected:
		HDC hDC;
		HGLRC hGLRC;
		DrawTexture* drawTexture;
		DrawSkeleton* drawSkeleton;
		SkeletonData* skeletonData;
		int selectPoint;
		int* selectPosition;
		System::Drawing::Bitmap^ bitmap;
		System::String^ imageFileName;
		System::Windows::Media::MediaPlayer^ mediaPlayer;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AllowDrop = true;
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(260, 224);
			this->panel1->TabIndex = 0;
			this->panel1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragDrop);
			this->panel1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragEnter);
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseDown);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseMove);
			this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseUp);
			this->panel1->Resize += gcnew System::EventHandler(this, &MainForm::panel1_Resize);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 239);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(284, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			// 
			// timer1
			// 
			this->timer1->Interval = 30;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->panel1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void panel1_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		imageFileName = ((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0];
		toolStripStatusLabel1->Text = imageFileName;
		bitmap = gcnew System::Drawing::Bitmap(imageFileName);
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height);
		System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, bitmap->PixelFormat);
		unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();
		if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb) {
			drawTexture->setTexture(loadTextureFromArray(data, bitmap->Width, bitmap->Height, 3));
		}
		else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format32bppArgb) {
			drawTexture->setTexture(loadTextureFromArray(data, bitmap->Width, bitmap->Height, 4));
		}
		bitmap->UnlockBits(bitmapData);
		skeletonData->initialize();
		display();
	}
	private: System::Void panel1_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;
		else
			e->Effect = DragDropEffects::None;
	}
	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		float x = (float)e->X / panel1->Width * 2 - 1;
		float y = (float)e->Y / panel1->Height * -2 + 1;
		for (int i = SkeletonData::Joint_Count - 1; i >= 0; i--) {
			float lengthX = fabs(skeletonData->data[SkeletonData::drawPointIndices[i]][0] - x) * panel1->Width;
			float lengthY = fabs(skeletonData->data[SkeletonData::drawPointIndices[i]][1] - y) * panel1->Height;
			if (lengthX < POINT_SIZE && lengthY < POINT_SIZE) {
				selectPoint = SkeletonData::drawPointIndices[i];
				selectPosition[0] = e->X;
				selectPosition[1] = e->Y;
				break;
			}
		}
	}
	private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		//System::Diagnostics::Debug::WriteLine(e->Location);
		selectPoint = -1;
	}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->X < 0 || e->X > panel1->Width || e->Y < 0 || e->Y > panel1->Height)
			selectPoint = -1;
		if (selectPoint != -1) {
			float dx = (float)(e->X - selectPosition[0]) / panel1->Width * 2;
			float dy = (float)(e->Y - selectPosition[1]) / panel1->Height * -2;
			skeletonData->data[selectPoint][0] += dx;
			skeletonData->data[selectPoint][1] += dy;
			selectPosition[0] = e->X;
			selectPosition[1] = e->Y;
			display();
		}
	}
	private: System::Void MainForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		System::Diagnostics::Debug::WriteLine(e->KeyCode);
		if (e->KeyCode == Keys::Space && bitmap != nullptr) {
			const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(imageFileName)).ToPointer();
			std::string str = chars;
			str = str + ".csv";
			Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
			skeletonData->saveCSV(str.c_str(), bitmap->Width, bitmap->Height);
			saveImage();
			toolStripStatusLabel1->Text = "save file";
		}
	}
	private: System::Void panel1_Resize(System::Object^  sender, System::EventArgs^  e) {
		reshape(panel1->Width, panel1->Height);
		display();
	}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Media::Imaging::RenderTargetBitmap^ rtb = gcnew System::Windows::Media::Imaging::RenderTargetBitmap(mediaPlayer->NaturalVideoWidth, mediaPlayer->NaturalVideoHeight, 96, 96, System::Windows::Media::PixelFormats::Pbgra32);
	System::Windows::Media::DrawingVisual^ dv = gcnew System::Windows::Media::DrawingVisual();
	System::Windows::Media::DrawingContext^ dc;
	System::Windows::Rect rect(System::Windows::Point(0, 0), System::Windows::Size(mediaPlayer->NaturalVideoWidth, mediaPlayer->NaturalVideoHeight));

	dc = dv->RenderOpen();
	dc->DrawVideo(mediaPlayer, rect);
	dc->Close();
	rtb->Render(dv);
	
	array<byte>^ dataArray = gcnew array<byte>(rtb->PixelWidth * rtb->PixelHeight * rtb->Format.BitsPerPixel / 8);
	rtb->CopyPixels(dataArray, rtb->PixelWidth * 4, 0);
	pin_ptr<System::Byte> dataPtr = &dataArray[0];
	drawTexture->setTexture(loadTextureFromArray(dataPtr, rtb->PixelWidth, rtb->PixelHeight, rtb->Format.BitsPerPixel / 8));
	display();
}
};
}
