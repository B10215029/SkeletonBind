#pragma once
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:main")
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
			//mediaPlayer->Open(gcnew Uri("C:\\Users\\Delim\\Desktop\\video2.mp4"));
			//while (mediaPlayer->DownloadProgress != 1) {
			//	std::cout << "not yet" << std::endl;
			//	System::Threading::Thread::Sleep(0.5 * 1000);
			//}
			//std::cout << "ok" << std::endl;
			mediaPlayer->ScrubbingEnabled = true;
			//mediaPlayer->Play();
			//trackBar1->Maximum = mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds * FRAME_PRE_SECOND + FRAME_PRE_SECOND;
			timer1->Interval = 1.0 / FRAME_PRE_SECOND * 1000;
			timer1->Enabled = true;
			imageDataTemp = NULL;
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
				if (imageDataTemp) {
					free(imageDataTemp);
				}
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
		char* imageDataTemp;
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
private: System::Windows::Forms::Button^  button7;
private: System::Windows::Forms::Button^  button8;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
private: System::Windows::Forms::NumericUpDown^  numericUpDown8;
private: System::Windows::Forms::NumericUpDown^  numericUpDown9;
private: System::Windows::Forms::NumericUpDown^  numericUpDown10;
private: System::Windows::Forms::NumericUpDown^  numericUpDown11;
private: System::Windows::Forms::NumericUpDown^  numericUpDown12;
private: System::Windows::Forms::NumericUpDown^  numericUpDown13;
private: System::Windows::Forms::NumericUpDown^  numericUpDown14;
private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
private: System::Windows::Forms::NumericUpDown^  numericUpDown15;
private: System::Windows::Forms::Button^  button9;

















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
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown9 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown11 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown12 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown13 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown14 = (gcnew System::Windows::Forms::NumericUpDown());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->numericUpDown15 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openVideoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openCSVToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog3 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown14))->BeginInit();
			this->tableLayoutPanel6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown15))->BeginInit();
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
			this->panel1->Size = System::Drawing::Size(271, 242);
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
			this->trackBar1->Size = System::Drawing::Size(271, 20);
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
			this->statusStrip1->Size = System::Drawing::Size(1210, 22);
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
			this->panel2->Location = System::Drawing::Point(380, 33);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(271, 242);
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
			this->panel3->Location = System::Drawing::Point(657, 33);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(271, 242);
			this->panel3->TabIndex = 3;
			this->panel3->Resize += gcnew System::EventHandler(this, &MainForm::panel3_Resize);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 5;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				100)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->panel3, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->panel2, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->button4, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->button5, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->button7, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->button8, 4, 2);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel5, 4, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel6, 4, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 24);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1210, 308);
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
			this->tableLayoutPanel2->Location = System::Drawing::Point(280, 33);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 3;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(94, 242);
			this->tableLayoutPanel2->TabIndex = 4;
			// 
			// button3
			// 
			this->button3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button3->Location = System::Drawing::Point(3, 83);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(88, 74);
			this->button3->TabIndex = 0;
			this->button3->Text = L">>\r\n擷取\r\n目前\r\nFrame";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->checkBox1->Location = System::Drawing::Point(3, 3);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(88, 74);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"與影片同步";
			this->checkBox1->UseVisualStyleBackColor = true;
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
			this->tableLayoutPanel3->Size = System::Drawing::Size(277, 30);
			this->tableLayoutPanel3->TabIndex = 7;
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button1->Location = System::Drawing::Point(3, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(86, 24);
			this->button1->TabIndex = 0;
			this->button1->Text = L"播放";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button2->Location = System::Drawing::Point(95, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(86, 24);
			this->button2->TabIndex = 1;
			this->button2->Text = L"暫停";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button6
			// 
			this->button6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button6->Location = System::Drawing::Point(187, 3);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(87, 24);
			this->button6->TabIndex = 2;
			this->button6->Text = L"下一張";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// button4
			// 
			this->button4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button4->Location = System::Drawing::Point(380, 281);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(271, 24);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Reset";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button5->Location = System::Drawing::Point(657, 281);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(271, 24);
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
			this->tableLayoutPanel4->Size = System::Drawing::Size(277, 30);
			this->tableLayoutPanel4->TabIndex = 11;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 30);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Frame Number";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(141, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(133, 30);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Time";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button7
			// 
			this->button7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button7->Location = System::Drawing::Point(280, 281);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(94, 24);
			this->button7->TabIndex = 12;
			this->button7->Text = L"尋找下一筆";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::button7_MouseUp);
			// 
			// button8
			// 
			this->button8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button8->Location = System::Drawing::Point(934, 281);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(273, 24);
			this->button8->TabIndex = 13;
			this->button8->Text = L"Save Part";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MainForm::button8_Click);
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->ColumnCount = 7;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28571F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28572F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28572F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28572F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28572F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28572F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				14.28572F)));
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown1, 2, 11);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown2, 2, 9);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown3, 2, 7);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown4, 4, 7);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown5, 4, 9);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown6, 4, 11);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown7, 0, 6);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown8, 1, 4);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown9, 2, 2);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown10, 4, 2);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown11, 5, 4);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown12, 6, 6);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown13, 3, 2);
			this->tableLayoutPanel5->Controls->Add(this->numericUpDown14, 3, 0);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(934, 33);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 12;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 8.333332F)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(273, 242);
			this->tableLayoutPanel5->TabIndex = 14;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown1->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown1->Location = System::Drawing::Point(80, 223);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(33, 22);
			this->numericUpDown1->TabIndex = 0;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown2->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown2->Location = System::Drawing::Point(80, 183);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(33, 22);
			this->numericUpDown2->TabIndex = 1;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown3->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown3->Location = System::Drawing::Point(80, 143);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(33, 22);
			this->numericUpDown3->TabIndex = 2;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown4
			// 
			this->numericUpDown4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown4->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown4->Location = System::Drawing::Point(158, 143);
			this->numericUpDown4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown4->Name = L"numericUpDown4";
			this->numericUpDown4->Size = System::Drawing::Size(33, 22);
			this->numericUpDown4->TabIndex = 3;
			this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown5
			// 
			this->numericUpDown5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown5->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown5->Location = System::Drawing::Point(158, 183);
			this->numericUpDown5->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown5->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown5->Name = L"numericUpDown5";
			this->numericUpDown5->Size = System::Drawing::Size(33, 22);
			this->numericUpDown5->TabIndex = 4;
			this->numericUpDown5->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown6
			// 
			this->numericUpDown6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown6->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown6->Location = System::Drawing::Point(158, 223);
			this->numericUpDown6->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown6->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown6->Name = L"numericUpDown6";
			this->numericUpDown6->Size = System::Drawing::Size(33, 22);
			this->numericUpDown6->TabIndex = 5;
			this->numericUpDown6->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown7
			// 
			this->numericUpDown7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown7->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown7->Location = System::Drawing::Point(3, 123);
			this->numericUpDown7->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown7->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown7->Name = L"numericUpDown7";
			this->numericUpDown7->Size = System::Drawing::Size(32, 22);
			this->numericUpDown7->TabIndex = 6;
			this->numericUpDown7->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown8
			// 
			this->numericUpDown8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown8->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown8->Location = System::Drawing::Point(41, 83);
			this->numericUpDown8->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown8->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown8->Name = L"numericUpDown8";
			this->numericUpDown8->Size = System::Drawing::Size(33, 22);
			this->numericUpDown8->TabIndex = 7;
			this->numericUpDown8->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown9
			// 
			this->numericUpDown9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown9->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown9->Location = System::Drawing::Point(80, 43);
			this->numericUpDown9->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown9->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown9->Name = L"numericUpDown9";
			this->numericUpDown9->Size = System::Drawing::Size(33, 22);
			this->numericUpDown9->TabIndex = 8;
			this->numericUpDown9->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown10
			// 
			this->numericUpDown10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown10->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown10->Location = System::Drawing::Point(158, 43);
			this->numericUpDown10->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown10->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown10->Name = L"numericUpDown10";
			this->numericUpDown10->Size = System::Drawing::Size(33, 22);
			this->numericUpDown10->TabIndex = 9;
			this->numericUpDown10->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown11
			// 
			this->numericUpDown11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown11->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown11->Location = System::Drawing::Point(197, 83);
			this->numericUpDown11->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown11->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown11->Name = L"numericUpDown11";
			this->numericUpDown11->Size = System::Drawing::Size(33, 22);
			this->numericUpDown11->TabIndex = 10;
			this->numericUpDown11->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown12
			// 
			this->numericUpDown12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown12->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown12->Location = System::Drawing::Point(236, 123);
			this->numericUpDown12->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown12->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown12->Name = L"numericUpDown12";
			this->numericUpDown12->Size = System::Drawing::Size(34, 22);
			this->numericUpDown12->TabIndex = 11;
			this->numericUpDown12->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown13
			// 
			this->numericUpDown13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown13->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown13->Location = System::Drawing::Point(119, 43);
			this->numericUpDown13->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown13->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown13->Name = L"numericUpDown13";
			this->numericUpDown13->Size = System::Drawing::Size(33, 22);
			this->numericUpDown13->TabIndex = 12;
			this->numericUpDown13->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// numericUpDown14
			// 
			this->numericUpDown14->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown14->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown14->Location = System::Drawing::Point(119, 3);
			this->numericUpDown14->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown14->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown14->Name = L"numericUpDown14";
			this->numericUpDown14->Size = System::Drawing::Size(33, 22);
			this->numericUpDown14->TabIndex = 13;
			this->numericUpDown14->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 11, 0, 0, 0 });
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->ColumnCount = 2;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel6->Controls->Add(this->numericUpDown15, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->button9, 1, 0);
			this->tableLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel6->Location = System::Drawing::Point(934, 3);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 1;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 24)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(273, 24);
			this->tableLayoutPanel6->TabIndex = 17;
			// 
			// numericUpDown15
			// 
			this->numericUpDown15->Dock = System::Windows::Forms::DockStyle::Fill;
			this->numericUpDown15->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numericUpDown15->Location = System::Drawing::Point(3, 3);
			this->numericUpDown15->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999, 0, 0, 0 });
			this->numericUpDown15->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown15->Name = L"numericUpDown15";
			this->numericUpDown15->Size = System::Drawing::Size(130, 22);
			this->numericUpDown15->TabIndex = 15;
			this->numericUpDown15->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// button9
			// 
			this->button9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->button9->Location = System::Drawing::Point(139, 3);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(131, 18);
			this->button9->TabIndex = 16;
			this->button9->Text = L"Set All Value";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MainForm::button9_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1210, 24);
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
			this->openVideoToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->openVideoToolStripMenuItem->Text = L"Open Video";
			this->openVideoToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openVideoToolStripMenuItem_Click);
			// 
			// openPictureToolStripMenuItem
			// 
			this->openPictureToolStripMenuItem->Name = L"openPictureToolStripMenuItem";
			this->openPictureToolStripMenuItem->Size = System::Drawing::Size(147, 22);
			this->openPictureToolStripMenuItem->Text = L"Open Picture";
			this->openPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openPictureToolStripMenuItem_Click);
			// 
			// openCSVToolStripMenuItem
			// 
			this->openCSVToolStripMenuItem->Name = L"openCSVToolStripMenuItem";
			this->openCSVToolStripMenuItem->Size = System::Drawing::Size(147, 22);
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
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1210, 354);
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
			this->tableLayoutPanel5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown14))->EndInit();
			this->tableLayoutPanel6->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown15))->EndInit();
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
			std::cout << "not yet " << mediaPlayer->DownloadProgress << std::endl;
			System::Threading::Thread::Sleep(0.5 * 1000);
		}
		std::cout << "ok" << std::endl;
		mediaPlayer->Play();
		//if (!mediaPlayer->HasVideo) {
		//	std::cout << "not support format" << std::endl;
		//	return;
		//}
		while (!mediaPlayer->NaturalDuration.HasTimeSpan) {
			std::cout << "not yet" << std::endl;
			System::Threading::Thread::Sleep(0.5 * 1000);
		}
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
	if (!mediaPlayer->HasVideo)
		return;
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

		currentFrame = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND + 0.5;
		skeletonData->setFrame(currentFrame);
		bitmap = gcnew System::Drawing::Bitmap(rtb->PixelWidth, rtb->PixelHeight, rtb->PixelWidth * rtb->PixelHeight * 4, System::Drawing::Imaging::PixelFormat::Format32bppArgb, IntPtr(dataPtr));
	}

	if (!isTrackBarMouseDown)
		trackBar1->Value = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND + 0.5;
	label1->Text = "FN:" + System::Convert::ToString((int)(mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND + 0.5)) + "/" + System::Convert::ToString(mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds * FRAME_PRE_SECOND);
	label2->Text = "Time:" + System::Convert::ToString(mediaPlayer->Position.TotalSeconds) + "/" + System::Convert::ToString(mediaPlayer->NaturalDuration.TimeSpan.TotalSeconds);

}
private: System::Void panel2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	if (skeletonData->data == NULL)
		return;
	float x = (float)e->X / panel2->Width * 2 - 1;
	float y = (float)e->Y / panel2->Height * -2 + 1;
	for (int i = SkeletonData::Joint_Count - 1; i >= 0; i--) {
		float lengthX = fabs(skeletonData->data[SkeletonData::drawPointIndices[i] * 2 + 0] - x) * panel1->Width;
		float lengthY = fabs(skeletonData->data[SkeletonData::drawPointIndices[i] * 2 + 1] - y) * panel1->Height;
		if (lengthX < POINT_SIZE && lengthY < POINT_SIZE) {
			selectPoint = SkeletonData::drawPointIndices[i];
			selectPosition[0] = e->X;
			selectPosition[1] = e->Y;
			break;
		}
	}
}

private: System::Void panel2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (skeletonData->data == NULL)
		return;
	if (e->X < 0 || e->X > panel2->Width || e->Y < 0 || e->Y > panel2->Height)
		selectPoint = -1;
	if (selectPoint != -1) {
		float dx = (float)(e->X - selectPosition[0]) / panel2->Width * 2;
		float dy = (float)(e->Y - selectPosition[1]) / panel2->Height * -2;
		skeletonData->data[selectPoint * 2 + 0] += dx;
		skeletonData->data[selectPoint * 2 + 1] += dy;
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

	currentFrame = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND + 0.5;
	skeletonData->setFrame(currentFrame);

	array<byte>^ dataArray = gcnew array<byte>(rtb->PixelWidth * rtb->PixelHeight * rtb->Format.BitsPerPixel / 8);
	rtb->CopyPixels(dataArray, rtb->PixelWidth * 4, 0);
	pin_ptr<System::Byte> dataPtr = &dataArray[0];
	reshape(hDC2, hGLRC2, panel2->Width, panel2->Height);
	drawTexture2->setTexture(loadTextureFromArray(dataPtr, rtb->PixelWidth, rtb->PixelHeight, rtb->Format.BitsPerPixel / 8));
	display(hDC2, hGLRC2, drawTexture2, drawSkeleton2);
	display(hDC3, hGLRC3, NULL, drawSkeleton3);

	if (imageDataTemp)
		free(imageDataTemp);
	imageDataTemp = (char*)malloc(rtb->PixelWidth * rtb->PixelHeight * 4);
	memcpy(imageDataTemp, dataPtr, rtb->PixelWidth * rtb->PixelHeight * 4);
	bitmap = gcnew System::Drawing::Bitmap(rtb->PixelWidth, rtb->PixelHeight, rtb->PixelWidth * 4, System::Drawing::Imaging::PixelFormat::Format32bppArgb, IntPtr(dataPtr));
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
		toolStripStatusLabel1->Text = imageFileName;
		mediaPlayer->Open(gcnew Uri(imageFileName));
		while (mediaPlayer->DownloadProgress != 1) {
			std::cout << "not yet" << std::endl;
			System::Threading::Thread::Sleep(0.5 * 1000);
		}
		std::cout << "ok" << std::endl;
		mediaPlayer->Play();
		//if (!mediaPlayer->HasVideo) {
		//	std::cout << "not support format" << std::endl;
		//	return;
		//}
		while (!mediaPlayer->NaturalDuration.HasTimeSpan) {
			std::cout << "not yet" << std::endl;
			System::Threading::Thread::Sleep(0.5 * 1000);
		}
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
	if (openFileDialog3->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		imageFileName = openFileDialog3->FileName;
		toolStripStatusLabel1->Text = imageFileName;
		const char* chars = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(imageFileName)).ToPointer();
		skeletonData->readCSV(chars, mediaPlayer->NaturalVideoWidth, mediaPlayer->NaturalVideoHeight);
		skeletonData->setFrame(currentFrame);
	}
}
private: System::Void button7_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	int currentFrame = mediaPlayer->Position.TotalSeconds * FRAME_PRE_SECOND + 0.5;
	skeletonData->setFrame(currentFrame);
	if (e->Button == System::Windows::Forms::MouseButtons::Left)
		currentFrame = skeletonData->gotoNextFrameByTime();
	else if (e->Button == System::Windows::Forms::MouseButtons::Right)
		currentFrame = skeletonData->gotoNextFrameByData();
	mediaPlayer->Position = TimeSpan::FromSeconds(((float)currentFrame) / FRAME_PRE_SECOND);
}
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	if (bitmap == nullptr || imageFileName->Length == 0 || skeletonData->data == NULL || imageDataTemp == NULL)
		return;
	array<NumericUpDown^> ^numericUpDowns = gcnew array<NumericUpDown^>(14);
	array<String^> ^paths = gcnew array<String^>(14);
	String^ delimStr = "\\";
	array<String^>^ words = imageFileName->Split(delimStr->ToCharArray());
	String^ dirPath = String::Empty;
	for (int i = 0; i < words->Length - 1; i++)
		dirPath += words[i] + "\\";

	numericUpDowns[0] = numericUpDown1;
	numericUpDowns[1] = numericUpDown2;
	numericUpDowns[2] = numericUpDown3;
	numericUpDowns[3] = numericUpDown4;
	numericUpDowns[4] = numericUpDown5;
	numericUpDowns[5] = numericUpDown6;
	numericUpDowns[6] = numericUpDown7;
	numericUpDowns[7] = numericUpDown8;
	numericUpDowns[8] = numericUpDown9;
	numericUpDowns[9] = numericUpDown10;
	numericUpDowns[10] = numericUpDown11;
	numericUpDowns[11] = numericUpDown12;
	numericUpDowns[12] = numericUpDown13;
	numericUpDowns[13] = numericUpDown14;

	paths[0] = dirPath + gcnew System::String("Joint_AnkleRight");
	paths[1] = dirPath + gcnew System::String("Joint_KneeRight");
	paths[2] = dirPath + gcnew System::String("Joint_HipRight");
	paths[3] = dirPath + gcnew System::String("Joint_HipLeft");
	paths[4] = dirPath + gcnew System::String("Joint_KneeLeft");
	paths[5] = dirPath + gcnew System::String("Joint_AnkleLeft");
	paths[6] = dirPath + gcnew System::String("Joint_HandRight");
	paths[7] = dirPath + gcnew System::String("Joint_ElbowRight");
	paths[8] = dirPath + gcnew System::String("Joint_ShoulderRight");
	paths[9] = dirPath + gcnew System::String("Joint_ShoulderLeft");
	paths[10] = dirPath + gcnew System::String("Joint_ElbowLeft");
	paths[11] = dirPath + gcnew System::String("Joint_HandLeft");
	paths[12] = dirPath + gcnew System::String("Joint_Neck");
	paths[13] = dirPath + gcnew System::String("Joint_Head");

	//check dir
	for (int i = 0; i < numericUpDowns->Length; i++) {
		if (!System::IO::Directory::Exists(paths[i])) {
			System::IO::Directory::CreateDirectory(paths[i]);
		}
	}
	//save image
	bitmap = gcnew System::Drawing::Bitmap(bitmap->Width, bitmap->Height, bitmap->Width * 4, System::Drawing::Imaging::PixelFormat::Format32bppArgb, IntPtr(imageDataTemp));
	for (int i = 0; i < numericUpDowns->Length; i++) {
		paths[i] += "\\" + words[words->Length - 1] + "_" + currentFrame.ToString("D6") + ".png";
		int w = System::Decimal::ToInt32(numericUpDowns[i]->Value);
		int h = System::Decimal::ToInt32(numericUpDowns[i]->Value);
		int x = (1 + skeletonData->data[i * 2 + 0]) / 2 * bitmap->Width - (w / 2);
		int y = (1 - skeletonData->data[i * 2 + 1]) / 2 * bitmap->Height - (h / 2);
		if (x < 0) {
			w += x;
			x = 0;
		}
		if (y < 0) {
			h += y;
			y = 0;
		}
		if (x + w > bitmap->Width) {
			w = bitmap->Width - x;
		}
		if (y + h > bitmap->Height) {
			h = bitmap->Height - y;
		}
		if (w == 0 || h == 0) {
			break;
		}
		System::Drawing::Rectangle regionRect = System::Drawing::Rectangle(x, y, w, h);
		Bitmap^ regionBitmap = bitmap->Clone(regionRect, bitmap->PixelFormat);
		regionBitmap->Save(paths[i], System::Drawing::Imaging::ImageFormat::Png);
	}
}
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
	numericUpDown1->Value = numericUpDown15->Value;
	numericUpDown2->Value = numericUpDown15->Value;
	numericUpDown3->Value = numericUpDown15->Value;
	numericUpDown4->Value = numericUpDown15->Value;
	numericUpDown5->Value = numericUpDown15->Value;
	numericUpDown6->Value = numericUpDown15->Value;
	numericUpDown7->Value = numericUpDown15->Value;
	numericUpDown8->Value = numericUpDown15->Value;
	numericUpDown9->Value = numericUpDown15->Value;
	numericUpDown10->Value = numericUpDown15->Value;
	numericUpDown11->Value = numericUpDown15->Value;
	numericUpDown12->Value = numericUpDown15->Value;
	numericUpDown13->Value = numericUpDown15->Value;
	numericUpDown14->Value = numericUpDown15->Value;
}
};
}
