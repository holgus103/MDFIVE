#include "GUI.h"
namespace MDFIVE{

System::Void GUI::asynchWork(){
	msclr::interop::marshal_context context;
	clock_t time, end;
	int t;
	ProgressReport^ d =
		gcnew ProgressReport(this, &GUI::progressReport);
	time = clock();
	std::string result = MD5::calculateHash(context.marshal_as<std::string>(this->path), this->cbAsm->Checked, (void (__stdcall*)(int))(Marshal::GetFunctionPointerForDelegate(d).ToPointer()));
	end = clock();
	t = end - time;
	this->showResults(gcnew System::String(result.c_str()), System::Convert::ToString(t));
}

System::Void GUI::showResults(String^ hash, String^ time){
	if (this->txHash->InvokeRequired || this->lbTime->InvokeRequired)
	{
		UpdateHash^ d =
			gcnew UpdateHash(this, &GUI::showResults);
		this->Invoke(d, gcnew array<Object^> { hash, time });
	}
	else
	{
		this->txHash->Text = hash;
		this->lbTime->Text = time;
		this->isBusy = false;
		this->pbHash->Value = 100;
	}
}

System::Void GUI::btnHash_Click(System::Object^  sender, System::EventArgs^  e) {
	if (System::String::IsNullOrWhiteSpace(this->path)){
		return;
	}
	if (this->isBusy){
		return;
	}
	this->isBusy = true;
	this->pbHash->Value = 0;
	Thread^ worker = gcnew Thread(gcnew ThreadStart(this, &GUI::asynchWork));
	worker->Start();
}

System::Void GUI::btnBrowse_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog^ fileDialog = gcnew OpenFileDialog();
	fileDialog->InitialDirectory = "C:\\";
	fileDialog->RestoreDirectory = true;
	if (fileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		this->path = fileDialog->FileName;
		this->lbPath->Text = fileDialog->FileName;
		this->txHash->Text = System::String::Empty;
	}
}

void GUI::progressReport(int val){
	if (this->pbHash->InvokeRequired){
		ProgressReport^ d =
			gcnew ProgressReport(this, &GUI::progressReport);
		this->Invoke(d, gcnew array < Object^ > { val });
	}
	else{
		this->pbHash->Value = val;
	}
}
}