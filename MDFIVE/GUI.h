#pragma once
#include <MD5.h>
#include <msclr/marshal_cppstd.h>
#include <time.h>
#include <process.h>

namespace MDFIVE {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnHash;
	protected:

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Label^  lbPath;
	private: System::Windows::Forms::Button^  btnBrowse;
	private: System::Windows::Forms::CheckBox^  cbAsm;
	private: System::String^ path;
	private: System::Windows::Forms::TextBox^  txHash;
	private: delegate void UpdateHash(String^ hash, String^ time);
	private: delegate void ProgressReport(int val);
	private: boolean isBusy;
	private: System::Windows::Forms::Label^  lbTime;
	private: System::Windows::Forms::ProgressBar^  pbHash;




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(GUI::typeid));
			this->btnHash = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->lbPath = (gcnew System::Windows::Forms::Label());
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->cbAsm = (gcnew System::Windows::Forms::CheckBox());
			this->txHash = (gcnew System::Windows::Forms::TextBox());
			this->lbTime = (gcnew System::Windows::Forms::Label());
			this->pbHash = (gcnew System::Windows::Forms::ProgressBar());
			this->SuspendLayout();
			// 
			// btnHash
			// 
			this->btnHash->Location = System::Drawing::Point(182, 182);
			this->btnHash->Name = L"btnHash";
			this->btnHash->Size = System::Drawing::Size(75, 23);
			this->btnHash->TabIndex = 0;
			this->btnHash->Text = L"Hash";
			this->btnHash->UseVisualStyleBackColor = true;
			this->btnHash->Click += gcnew System::EventHandler(this, &GUI::btnHash_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// lbPath
			// 
			this->lbPath->AutoSize = true;
			this->lbPath->Location = System::Drawing::Point(29, 22);
			this->lbPath->Name = L"lbPath";
			this->lbPath->Size = System::Drawing::Size(23, 13);
			this->lbPath->TabIndex = 2;
			this->lbPath->Text = L"File";
			// 
			// btnBrowse
			// 
			this->btnBrowse->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->btnBrowse->Location = System::Drawing::Point(182, 59);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(75, 23);
			this->btnBrowse->TabIndex = 3;
			this->btnBrowse->Text = L"Browse";
			this->btnBrowse->UseVisualStyleBackColor = true;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &GUI::btnBrowse_Click);
			// 
			// cbAsm
			// 
			this->cbAsm->AutoSize = true;
			this->cbAsm->Location = System::Drawing::Point(32, 167);
			this->cbAsm->Name = L"cbAsm";
			this->cbAsm->Size = System::Drawing::Size(69, 17);
			this->cbAsm->TabIndex = 4;
			this->cbAsm->Text = L"use ASM";
			this->cbAsm->UseVisualStyleBackColor = true;
			// 
			// txHash
			// 
			this->txHash->Location = System::Drawing::Point(32, 141);
			this->txHash->Name = L"txHash";
			this->txHash->Size = System::Drawing::Size(224, 20);
			this->txHash->TabIndex = 5;
			// 
			// lbTime
			// 
			this->lbTime->AutoSize = true;
			this->lbTime->Location = System::Drawing::Point(29, 69);
			this->lbTime->Name = L"lbTime";
			this->lbTime->Size = System::Drawing::Size(10, 13);
			this->lbTime->TabIndex = 6;
			this->lbTime->Text = L"-";
			// 
			// pbHash
			// 
			this->pbHash->Location = System::Drawing::Point(32, 112);
			this->pbHash->Name = L"pbHash";
			this->pbHash->Size = System::Drawing::Size(224, 23);
			this->pbHash->TabIndex = 7;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->pbHash);
			this->Controls->Add(this->lbTime);
			this->Controls->Add(this->txHash);
			this->Controls->Add(this->cbAsm);
			this->Controls->Add(this->btnBrowse);
			this->Controls->Add(this->lbPath);
			this->Controls->Add(this->btnHash);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"GUI";
			this->Text = L"MDFIVE";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {	}
	private: System::Void btnBrowse_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnHash_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void showResults(String^ hash, String^ time);
	private: System::Void asynchWork();
	private: void GUI::progressReport(int val);
};
}
