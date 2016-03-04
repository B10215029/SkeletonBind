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
			imageFileName = "";
			currentFrame = 0;
			drawTexture1 = new DrawTexture();
			drawTexture2 = new DrawTexture();
			drawSkeleton2 = new DrawSkeleton();
			drawSkeleton3 = new DrawSkeleton();
			skeletonData = new SkeletonData();
			selectPoint = -1;
			selectPosition = new int[2];
			isTrackBarMouseDown = false;

			hDC1 = GetDC((HWND)(panel1->Handle.ToInt32()));
			hGLRC1 = initializeOpenGLContext(hDC1);
			drawTexture1->initialize();
			reshape(hDC1, hGLRC1, panel1->Width, panel1->Height);
			display(hDC1, hGLRC1, drawTexture1, NULL);

			hDC2 = GetDC((HWND)(panel2->Handle.ToInt32()));
			hGLRC2 = initializeOpenGLContext(hDC2);
			drawTexture2->initialize();
			drawSkeleton2->initialize();
			reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
			display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);

			hDC3 = GetDC((HWND)(panel3->Handle.ToInt32()));
			hGLRC3 = initializeOpenGLContext(hDC3);
			drawSkeleton3->initialize();
			reshape(hDC3, hGLRC3, panel3->Width, panel3->Height);
			display(hDC3, hGLRC3, NULL, drawSkeleton3);

			mediaPlayer = gcnew System::Windows::Media::MediaPlayer();
			mediaPlayer->Open(gcnew Uri("C:\\Users\\Delim\\Desktop\\video2.mp4"));
			while (mediaPlayer->DownloadProgress != 1) {
				std::cout << "not yet" << std::endl;
				System::Threading::Thread::Sleep(0.5 * 1000);
			}
			std::cout << "ok" << std::endl;
			mediaPlayer->ScrubbingEnabled = true;
			mediaPlayer->Play();
			trackBar1->Maximum = mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds * FRAME_PRE_SECOND + FRAME_PRE_SECOND;
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
				if (hGLRC1) {
					wglDeleteContext(hGLRC1);
				}
				if (hGLRC2) {
					wglDeleteContext(hGLRC2);
				}
				if (hGLRC3) {
					wglDeleteContext(hGLRC3);
				}
				delete drawTexture1;
				delete drawTexture2;
				delete drawSkeleton2;
				delete drawSkeleton3;
				delete skeletonData;
				delete components;
				components = nullptr;
			}
		}
		HGLRC initializeOpenGLContext(HDC hDC);
		void reshape(HDC hDC, HGLRC hGLRC, int width, int height);
		void display(HDC hDC, HGLRC hGLRC, DrawTexture* drawTexture, DrawSkeleton* drawSkeleton);
		void saveImage();
	protected:
		HDC hDC1;
		HDC hDC2;
		HDC hDC3;
		HGLRC hGLRC1;
		HGLRC hGLRC2;
		HGLRC hGLRC3;
		DrawTexture* drawTexture1;
		DrawTexture* drawTexture2;
		DrawSkeleton* drawSkeleton2;
		DrawSkeleton* drawSkeleton3;
		SkeletonData* skeletonData;
		bool isTrackBarMouseDown;
		int currentFrame;
		int selectPoint;
		int* selectPosition;
		System::String^ imageFileName;
		System::Drawing::Bitmap^ bitmap;
		System::Windows::Media::MediaPlayer^ mediaPlayer;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3; 
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;





	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;



	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog3;
private: System::Windows::Forms::TrackBar^  trackBar1;
private: System::Windows::Forms::Button^  button6;
private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  openVideoToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  openPictureToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  openCSVToolStripMenuItem;
private: System::Windows::Forms::CheckBox^  checkBox1;



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
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openVideoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openCSVToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog3 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AllowDrop = true;
			this->panel1->Controls->Add(this->trackBar1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(3, 33);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(254, 242);
			this->panel1->TabIndex = 0;
			this->panel1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragDrop);
			this->panel1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragEnter);
			this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseDown);
			this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseMove);
			this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseUp);
			this->panel1->Resize += gcnew System::EventHandler(this, &MainForm::panel1_Resize);
			// 
			// trackBar1
			// 
			this->trackBar1->AutoSize = false;
			this->trackBar1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->trackBar1->Location = System::Drawing::Point(0, 222);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(254, 20);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
			this->trackBar1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::trackBar1_MouseDown);
			this->trackBar1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::trackBar1_MouseUp);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 332);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(861, 22);
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
			// panel2
			// 
			this->panel2->AllowDrop = true;
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(343, 33);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(254, 242);
			this->panel2->TabIndex = 2;
			this->panel2->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel2_DragDrop);
			this->panel2->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel2_DragEnter);
			this->panel2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel2_MouseDown);
			this->panel2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel2_MouseMove);
			this->panel2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel2_MouseUp);
			this->panel2->Resize += gcnew System::EventHandler(this, &MainForm::panel2_Resize);
			// 
			// panel3
			// 
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(603, 33);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(255, 242);
			this->panel3->TabIndex = 3;
			this->panel3->Resize += gcnew System::EventHandler(this, &MainForm::panel3_Resize);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 4;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				80)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->panel3, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->panel2, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->button4, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->button5, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 24);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(861, 308);
			this->tableLayoutPanel1->TabIndex = 4;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel2->Controls->Add(this->button3, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->checkBox1, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(263, 33);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 3;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(74, 242);
			this->tableLayoutPanel2->TabIndex = 4;
			// 
			// button3
			// 
			this->button3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button3->Location = System::Drawing::Point(3, 83);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(68, 74);
			this->button3->TabIndex = 0;
			this->button3->Text = L">>\r\n擷取\r\n目前\r\nFrame";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 3;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel3->Controls->Add(this->button1, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->button2, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->button6, 2, 0);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(0, 278);
			this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(260, 30);
			this->tableLayoutPanel3->TabIndex = 7;
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(80, 24);
			this->button1->TabIndex = 0;
			this->button1->Text = L"播放";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button2->Location = System::Drawing::Point(89, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(80, 24);
			this->button2->TabIndex = 1;
			this->button2->Text = L"暫停";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button6
			// 
			this->button6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button6->Location = System::Drawing::Point(175, 3);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(82, 24);
			this->button6->TabIndex = 2;
			this->button6->Text = L"下一張";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// button4
			// 
			this->button4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button4->Location = System::Drawing::Point(343, 281);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(254, 24);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Reset";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button5->Location = System::Drawing::Point(603, 281);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(255, 24);
			this->button5->TabIndex = 10;
			this->button5->Text = L"Save";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->label2, 1, 0);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel4->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(260, 30);
			this->tableLayoutPanel4->TabIndex = 11;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 30);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Frame Number";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(133, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(124, 30);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Time";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(861, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openVideoToolStripMenuItem,
					this->openPictureToolStripMenuItem, this->openCSVToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openVideoToolStripMenuItem
			// 
			this->openVideoToolStripMenuItem->Name = L"openVideoToolStripMenuItem";
			this->openVideoToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openVideoToolStripMenuItem->Text = L"Open Video";
			this->openVideoToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openVideoToolStripMenuItem_Click);
			// 
			// openPictureToolStripMenuItem
			// 
			this->openPictureToolStripMenuItem->Name = L"openPictureToolStripMenuItem";
			this->openPictureToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openPictureToolStripMenuItem->Text = L"Open Picture";
			this->openPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openPictureToolStripMenuItem_Click);
			// 
			// openCSVToolStripMenuItem
			// 
			this->openCSVToolStripMenuItem->Name = L"openCSVToolStripMenuItem";
			this->openCSVToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openCSVToolStripMenuItem->Text = L"Open CSV";
			this->openCSVToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openCSVToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			// 
			// openFileDialog3
			// 
			this->openFileDialog3->FileName = L"openFileDialog3";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->checkBox1->Location = System::Drawing::Point(3, 3);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(68, 74);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"自動撥放載入的CSV檔和圖片";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(861, 354);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"SkeletonBind";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void panel1_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		imageFileName = ((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0];
		toolStripStatusLabel1->Text = imageFileName;
		mediaPlayer->Open(gcnew Uri(imageFileName));
		while (mediaPlayer->DownloadProgress != 1) {
			std::cout << "not yet" << std::endl;
			System::Threading::Thread::Sleep(0.5 * 1000);
		}
		std::cout << "ok" << std::endl;
		mediaPlayer->Play();
		trackBar1->Maximum = mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds * FRAME_PRE_SECOND + FRAME_PRE_SECOND;
	}
	private: System::Void panel1_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;
		else
			e->Effect = DragDropEffects::None;
	}
	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	}
	private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		//System::Diagnostics::Debug::WriteLine(e->Location);
	}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	}
	private: System::Void MainForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		System::Diagnostics::Debug::WriteLine(e->KeyCode);
		//if (e->KeyCode == Keys::Space && bitmap != nullptr) {
		//	const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(imageFileName)).ToPointer();
		//	std::string str = chars;
		//	str = str + ".csv";
		//	Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
		//	skeletonData->saveCSV(str.c_str(), bitmap->Width, bitmap->Height);
		//	saveImage();
		//	toolStripStatusLabel1->Text = "save file";
		//}
	}
	private: System::Void panel1_Resize(System::Object^  sender, System::EventArgs^  e) {
		reshape(hDC1, hGLRC1, panel1->Width, panel1->Height);
		display(hDC1, hGLRC1, drawTexture1, NULL);
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
	reshape(hDC1, hGLRC1, panel1->Width, panel1->Height);
	drawTexture1->setTexture(loadTextureFromArray(dataPtr, rtb->PixelWidth, rtb->PixelHeight, rtb->Format.BitsPerPixel / 8));
	display(hDC1, hGLRC1, drawTexture1, NULL);

	if (checkBox1->Checked) {
		reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
		drawTexture2->setTexture(loadTextureFromArray(dataPtr, rtb->PixelWidth, rtb->PixelHeight, rtb->Format.BitsPerPixel / 8));
		display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
		display(hDC3, hGLRC3, NULL, drawSkeleton3);

		currentFrame = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND;
		bitmap = gcnew System::Drawing::Bitmap(rtb->PixelWidth, rtb->PixelHeight, rtb->PixelWidth * rtb->PixelHeight * 4, System::Drawing::Imaging::PixelFormat::Format32bppArgb, IntPtr(dataPtr));
	}

	if (!isTrackBarMouseDown)
		trackBar1->Value = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND;
	label1->Text = "FN:" + System::Convert::ToString((int)(mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND)) + "/" + System::Convert::ToString(mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds * FRAME_PRE_SECOND);
	label2->Text = "Time:" + System::Convert::ToString(mediaPlayer->Position.TotalSeconds) + "/" + System::Convert::ToString(mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds);

}
private: System::Void panel2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	float x = (float)e->X / panel2->Width * 2 - 1;
	float y = (float)e->Y / panel2->Height * -2 + 1;
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

private: System::Void panel2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->X < 0 || e->X > panel2->Width || e->Y < 0 || e->Y > panel2->Height)
		selectPoint = -1;
	if (selectPoint != -1) {
		float dx = (float)(e->X - selectPosition[0]) / panel2->Width * 2;
		float dy = (float)(e->Y - selectPosition[1]) / panel2->Height * -2;
		skeletonData->data[selectPoint][0] += dx;
		skeletonData->data[selectPoint][1] += dy;
		selectPosition[0] = e->X;
		selectPosition[1] = e->Y;
		display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
		display(hDC3, hGLRC3, NULL, drawSkeleton3);
	}
}
private: System::Void panel2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	selectPoint = -1;
}
private: System::Void panel2_Resize(System::Object^  sender, System::EventArgs^  e) {
	reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
}
private: System::Void panel3_Resize(System::Object^  sender, System::EventArgs^  e) {
	reshape(hDC3, hGLRC3, panel3->Width, panel3->Height);
	display(hDC3, hGLRC3, NULL, drawSkeleton3);
}
private: System::Void panel2_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	imageFileName = ((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0];
	toolStripStatusLabel1->Text = imageFileName;
	bitmap = gcnew System::Drawing::Bitmap(imageFileName);
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height);
	System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, bitmap->PixelFormat);
	unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();
	reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
	if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb) {
		drawTexture2->setTexture(loadTextureFromArray(data, bitmap->Width, bitmap->Height, 3));
	}
	else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format32bppArgb) {
		drawTexture2->setTexture(loadTextureFromArray(data, bitmap->Width, bitmap->Height, 4));
	}
	bitmap->UnlockBits(bitmapData);
	skeletonData->initialize();
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
	display(hDC3, hGLRC3, NULL, drawSkeleton3);
}
private: System::Void panel2_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	if (e->Data->GetDataPresent(DataFormats::FileDrop))
		e->Effect = DragDropEffects::Copy;
	else
		e->Effect = DragDropEffects::None;
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	//mediaPlayer->Play();
	if (mediaPlayer->SpeedRatio == 0) {
		mediaPlayer->SpeedRatio = 1;
		System::Threading::Thread::Sleep(0.2 * 1000);
	}
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	//mediaPlayer->Pause();
	mediaPlayer->SpeedRatio = 0;
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Media::Imaging::RenderTargetBitmap^ rtb = gcnew System::Windows::Media::Imaging::RenderTargetBitmap(mediaPlayer->NaturalVideoWidth, mediaPlayer->NaturalVideoHeight, 96, 96, System::Windows::Media::PixelFormats::Pbgra32);
	System::Windows::Media::DrawingVisual^ dv = gcnew System::Windows::Media::DrawingVisual();
	System::Windows::Media::DrawingContext^ dc;
	System::Windows::Rect rect(System::Windows::Point(0, 0), System::Windows::Size(mediaPlayer->NaturalVideoWidth, mediaPlayer->NaturalVideoHeight));

	dc = dv->RenderOpen();
	dc->DrawVideo(mediaPlayer, rect);
	dc->Close();
	rtb->Render(dv);

	currentFrame = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND;

	array<byte>^ dataArray = gcnew array<byte>(rtb->PixelWidth * rtb->PixelHeight * rtb->Format.BitsPerPixel / 8);
	rtb->CopyPixels(dataArray, rtb->PixelWidth * 4, 0);
	pin_ptr<System::Byte> dataPtr = &dataArray[0];
	reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
	drawTexture2->setTexture(loadTextureFromArray(dataPtr, rtb->PixelWidth, rtb->PixelHeight, rtb->Format.BitsPerPixel / 8));
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
	display(hDC3, hGLRC3, NULL, drawSkeleton3);

	System::IO::MemoryStream^ memoryStream = gcnew System::IO::MemoryStream();
	System::Windows::Media::Imaging::PngBitmapEncoder^ coder = gcnew System::Windows::Media::Imaging::PngBitmapEncoder();
	coder->Interlace = System::Windows::Media::Imaging::PngInterlaceOption::Off;
	coder->Frames->Add(System::Windows::Media::Imaging::BitmapFrame::Create(rtb));
	coder->Save(memoryStream);
	bitmap = gcnew System::Drawing::Bitmap(memoryStream);
	memoryStream->Close();
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	skeletonData->initialize();
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
	display(hDC3, hGLRC3, NULL, drawSkeleton3);
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (bitmap != nullptr && imageFileName->Length != 0) {
		const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(imageFileName)).ToPointer();
		std::string str = chars;
		str = str + ".csv";
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
		skeletonData->saveCSV(str.c_str(), bitmap->Width, bitmap->Height);
		saveImage();
		toolStripStatusLabel1->Text = "save file";
		// TODO
	}
}
private: System::Void trackBar1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	isTrackBarMouseDown = true;
}
private: System::Void trackBar1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	isTrackBarMouseDown = false;
	mediaPlayer->Position = TimeSpan::FromSeconds(trackBar1->Value / FRAME_PRE_SECOND);
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	mediaPlayer->Position = mediaPlayer->Position.Add(TimeSpan::FromSeconds(1.0 / FRAME_PRE_SECOND));
}
private: System::Void openVideoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		imageFileName = openFileDialog1->FileName;
		mediaPlayer->Open(gcnew Uri(openFileDialog1->FileName));
		while (mediaPlayer->DownloadProgress != 1) {
			std::cout << "not yet" << std::endl;
			System::Threading::Thread::Sleep(0.5 * 1000);
		}
		std::cout << "ok" << std::endl;
		mediaPlayer->Play();
		trackBar1->Maximum = mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds * FRAME_PRE_SECOND + FRAME_PRE_SECOND;
	}
}
private: System::Void openPictureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		imageFileName = openFileDialog2->FileName;
		toolStripStatusLabel1->Text = imageFileName;
		bitmap = gcnew System::Drawing::Bitmap(imageFileName);
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height);
		System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, bitmap->PixelFormat);
		unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();
		reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
		if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb) {
			drawTexture2->setTexture(loadTextureFromArray(data, bitmap->Width, bitmap->Height, 3));
		}
		else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format32bppArgb) {
			drawTexture2->setTexture(loadTextureFromArray(data, bitmap->Width, bitmap->Height, 4));
		}
		bitmap->UnlockBits(bitmapData);
		skeletonData->initialize();
		display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
		display(hDC3, hGLRC3, NULL, drawSkeleton3);
	}
}
private: System::Void openCSVToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	// TODO
}
};
}
