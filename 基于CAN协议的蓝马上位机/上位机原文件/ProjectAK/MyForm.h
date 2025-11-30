#pragma once

#include <windows.h>
#pragma comment(lib,"LM_USB.lib")
#include "LM_USB.h"

namespace ProjectAK {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			components = gcnew System::ComponentModel::Container();
			InitializeComponent();
			deviceAddress = 0x01;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonConnect;
	private: System::Windows::Forms::Button^ buttonDisconnect;
	private: System::Windows::Forms::TextBox^ textBoxLog;
	private: System::Windows::Forms::GroupBox^ groupBoxStatus;
	private: System::Windows::Forms::TextBox^ textBoxTemperature;
	private: System::Windows::Forms::TextBox^ textBoxCurrent;
	private: System::Windows::Forms::TextBox^ textBoxVoltage;
	private: System::Windows::Forms::Label^ labelTemperature;
	private: System::Windows::Forms::Label^ labelCurrent;
	private: System::Windows::Forms::Label^ labelVoltage;
	private: System::Windows::Forms::Timer^ timerAutoRead;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>

	private: System::Windows::Forms::GroupBox^ Control;
	private: System::Windows::Forms::Button^ buttonEnable;
	private: System::Windows::Forms::TextBox^ textBoxPositionSet;
	private: System::Windows::Forms::TextBox^ textBoxSpeedSet;
	private: System::Windows::Forms::Button^ buttonSetPosition;
	private: System::Windows::Forms::Button^ buttonSetSpeed;
	private: System::Windows::Forms::TextBox^ textBoxCurrentSet;
	private: System::Windows::Forms::Button^ buttonSetCurrent;
	private: System::Windows::Forms::Button^ buttonDisable;
	private: System::Windows::Forms::Button^ SHORTEST;
	private: System::Windows::Forms::GroupBox^ situationset;
	private: System::Windows::Forms::GroupBox^ groupBoxFault;
	private: System::Windows::Forms::Label^ labelFaultCode;
	private: System::Windows::Forms::TextBox^ textBoxFaultStatus;
	private: System::Windows::Forms::Button^ buttonClearFault;

		   unsigned char deviceAddress;

		   // 通信功能函数声明
		   void ReadMotorStatus();
		   void UpdateStatusDisplay(unsigned int voltage, unsigned int current, unsigned char temperature);
		   // 故障诊断相关函数声明
		   void CheckClearFaultResponse();
		   void UpdateFaultDisplay(unsigned char faultCode);
		   String^ ParseFaultCode(unsigned char faultCode);
		   String^ GetFaultDetails(unsigned char faultCode);

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// 设计器支持所需的方法 - 不要修改
		   /// 使用代码编辑器修改此方法的内容。
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timerAutoRead = (gcnew System::Windows::Forms::Timer(this->components));
			   this->buttonConnect = (gcnew System::Windows::Forms::Button());
			   this->buttonDisconnect = (gcnew System::Windows::Forms::Button());
			   this->textBoxLog = (gcnew System::Windows::Forms::TextBox());
			   this->groupBoxStatus = (gcnew System::Windows::Forms::GroupBox());
			   this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			   this->textBoxTemperature = (gcnew System::Windows::Forms::TextBox());
			   this->textBoxCurrent = (gcnew System::Windows::Forms::TextBox());
			   this->textBoxVoltage = (gcnew System::Windows::Forms::TextBox());
			   this->labelTemperature = (gcnew System::Windows::Forms::Label());
			   this->labelCurrent = (gcnew System::Windows::Forms::Label());
			   this->labelVoltage = (gcnew System::Windows::Forms::Label());
			   this->Control = (gcnew System::Windows::Forms::GroupBox());
			   this->textBoxPositionSet = (gcnew System::Windows::Forms::TextBox());
			   this->textBoxSpeedSet = (gcnew System::Windows::Forms::TextBox());
			   this->buttonSetPosition = (gcnew System::Windows::Forms::Button());
			   this->buttonSetSpeed = (gcnew System::Windows::Forms::Button());
			   this->textBoxCurrentSet = (gcnew System::Windows::Forms::TextBox());
			   this->buttonSetCurrent = (gcnew System::Windows::Forms::Button());
			   this->buttonEnable = (gcnew System::Windows::Forms::Button());
			   this->buttonDisable = (gcnew System::Windows::Forms::Button());
			   this->SHORTEST = (gcnew System::Windows::Forms::Button());
			   this->situationset = (gcnew System::Windows::Forms::GroupBox());
			   this->groupBoxFault = (gcnew System::Windows::Forms::GroupBox());
			   this->buttonClearFault = (gcnew System::Windows::Forms::Button());
			   this->labelFaultCode = (gcnew System::Windows::Forms::Label());
			   this->textBoxFaultStatus = (gcnew System::Windows::Forms::TextBox());
			   this->groupBoxStatus->SuspendLayout();
			   this->Control->SuspendLayout();
			   this->situationset->SuspendLayout();
			   this->groupBoxFault->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // timerAutoRead
			   // 
			   this->timerAutoRead->Interval = 5000;
			   this->timerAutoRead->Tick += gcnew System::EventHandler(this, &MyForm::timerAutoRead_Tick);
			   // 
			   // buttonConnect
			   // 
			   this->buttonConnect->Location = System::Drawing::Point(7, 28);
			   this->buttonConnect->Margin = System::Windows::Forms::Padding(4);
			   this->buttonConnect->Name = L"buttonConnect";
			   this->buttonConnect->Size = System::Drawing::Size(112, 34);
			   this->buttonConnect->TabIndex = 0;
			   this->buttonConnect->Text = L"连接设备";
			   this->buttonConnect->UseVisualStyleBackColor = true;
			   this->buttonConnect->Click += gcnew System::EventHandler(this, &MyForm::buttonConnect_Click);
			   // 
			   // buttonDisconnect
			   // 
			   this->buttonDisconnect->Location = System::Drawing::Point(127, 28);
			   this->buttonDisconnect->Margin = System::Windows::Forms::Padding(4);
			   this->buttonDisconnect->Name = L"buttonDisconnect";
			   this->buttonDisconnect->Size = System::Drawing::Size(112, 34);
			   this->buttonDisconnect->TabIndex = 1;
			   this->buttonDisconnect->Text = L"释放设备";
			   this->buttonDisconnect->UseVisualStyleBackColor = true;
			   this->buttonDisconnect->Click += gcnew System::EventHandler(this, &MyForm::buttonDisconnect_Click);
			   // 
			   // textBoxLog
			   // 
			   this->textBoxLog->Location = System::Drawing::Point(35, 60);
			   this->textBoxLog->Margin = System::Windows::Forms::Padding(4);
			   this->textBoxLog->Multiline = true;
			   this->textBoxLog->Name = L"textBoxLog";
			   this->textBoxLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			   this->textBoxLog->Size = System::Drawing::Size(334, 492);
			   this->textBoxLog->TabIndex = 2;
			   this->textBoxLog->Text = L"日志记录：";
			   // 
			   // groupBoxStatus
			   // 
			   this->groupBoxStatus->Controls->Add(this->checkBox1);
			   this->groupBoxStatus->Controls->Add(this->textBoxTemperature);
			   this->groupBoxStatus->Controls->Add(this->textBoxCurrent);
			   this->groupBoxStatus->Controls->Add(this->textBoxVoltage);
			   this->groupBoxStatus->Controls->Add(this->labelTemperature);
			   this->groupBoxStatus->Controls->Add(this->labelCurrent);
			   this->groupBoxStatus->Controls->Add(this->labelVoltage);
			   this->groupBoxStatus->Location = System::Drawing::Point(393, 147);
			   this->groupBoxStatus->Margin = System::Windows::Forms::Padding(4);
			   this->groupBoxStatus->Name = L"groupBoxStatus";
			   this->groupBoxStatus->Padding = System::Windows::Forms::Padding(4);
			   this->groupBoxStatus->Size = System::Drawing::Size(300, 150);
			   this->groupBoxStatus->TabIndex = 3;
			   this->groupBoxStatus->TabStop = false;
			   this->groupBoxStatus->Text = L"电机状态";
			   // 
			   // checkBox1
			   // 
			   this->checkBox1->AutoSize = true;
			   this->checkBox1->Location = System::Drawing::Point(121, 0);
			   this->checkBox1->Name = L"checkBox1";
			   this->checkBox1->Size = System::Drawing::Size(135, 22);
			   this->checkBox1->TabIndex = 6;
			   this->checkBox1->Text = L"自动读取(5s)";
			   this->checkBox1->UseVisualStyleBackColor = true;
			   this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxAutoRead_CheckedChanged);
			   // 
			   // textBoxTemperature
			   // 
			   this->textBoxTemperature->Location = System::Drawing::Point(108, 108);
			   this->textBoxTemperature->Margin = System::Windows::Forms::Padding(4);
			   this->textBoxTemperature->Name = L"textBoxTemperature";
			   this->textBoxTemperature->ReadOnly = true;
			   this->textBoxTemperature->Size = System::Drawing::Size(148, 28);
			   this->textBoxTemperature->TabIndex = 5;
			   // 
			   // textBoxCurrent
			   // 
			   this->textBoxCurrent->Location = System::Drawing::Point(108, 72);
			   this->textBoxCurrent->Margin = System::Windows::Forms::Padding(4);
			   this->textBoxCurrent->Name = L"textBoxCurrent";
			   this->textBoxCurrent->ReadOnly = true;
			   this->textBoxCurrent->Size = System::Drawing::Size(148, 28);
			   this->textBoxCurrent->TabIndex = 4;
			   // 
			   // textBoxVoltage
			   // 
			   this->textBoxVoltage->Location = System::Drawing::Point(108, 32);
			   this->textBoxVoltage->Margin = System::Windows::Forms::Padding(4);
			   this->textBoxVoltage->Name = L"textBoxVoltage";
			   this->textBoxVoltage->ReadOnly = true;
			   this->textBoxVoltage->Size = System::Drawing::Size(148, 28);
			   this->textBoxVoltage->TabIndex = 3;
			   // 
			   // labelTemperature
			   // 
			   this->labelTemperature->AutoSize = true;
			   this->labelTemperature->Location = System::Drawing::Point(10, 112);
			   this->labelTemperature->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->labelTemperature->Name = L"labelTemperature";
			   this->labelTemperature->Size = System::Drawing::Size(98, 18);
			   this->labelTemperature->TabIndex = 2;
			   this->labelTemperature->Text = L"工作温度℃";
			   // 
			   // labelCurrent
			   // 
			   this->labelCurrent->AutoSize = true;
			   this->labelCurrent->Location = System::Drawing::Point(10, 70);
			   this->labelCurrent->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->labelCurrent->Name = L"labelCurrent";
			   this->labelCurrent->Size = System::Drawing::Size(89, 18);
			   this->labelCurrent->TabIndex = 1;
			   this->labelCurrent->Text = L"母线电流A";
			   // 
			   // labelVoltage
			   // 
			   this->labelVoltage->AutoSize = true;
			   this->labelVoltage->Location = System::Drawing::Point(10, 32);
			   this->labelVoltage->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->labelVoltage->Name = L"labelVoltage";
			   this->labelVoltage->Size = System::Drawing::Size(89, 18);
			   this->labelVoltage->TabIndex = 0;
			   this->labelVoltage->Text = L"母线电压V";
			   // 
			   // Control
			   // 
			   this->Control->Controls->Add(this->textBoxPositionSet);
			   this->Control->Controls->Add(this->textBoxSpeedSet);
			   this->Control->Controls->Add(this->buttonSetPosition);
			   this->Control->Controls->Add(this->buttonSetSpeed);
			   this->Control->Controls->Add(this->textBoxCurrentSet);
			   this->Control->Controls->Add(this->buttonSetCurrent);
			   this->Control->Location = System::Drawing::Point(393, 318);
			   this->Control->Name = L"Control";
			   this->Control->Size = System::Drawing::Size(300, 172);
			   this->Control->TabIndex = 4;
			   this->Control->TabStop = false;
			   this->Control->Text = L"电机控制";
			   // 
			   // textBoxPositionSet
			   // 
			   this->textBoxPositionSet->Location = System::Drawing::Point(170, 138);
			   this->textBoxPositionSet->Name = L"textBoxPositionSet";
			   this->textBoxPositionSet->Size = System::Drawing::Size(100, 28);
			   this->textBoxPositionSet->TabIndex = 5;
			   // 
			   // textBoxSpeedSet
			   // 
			   this->textBoxSpeedSet->Location = System::Drawing::Point(170, 89);
			   this->textBoxSpeedSet->Name = L"textBoxSpeedSet";
			   this->textBoxSpeedSet->Size = System::Drawing::Size(100, 28);
			   this->textBoxSpeedSet->TabIndex = 4;
			   // 
			   // buttonSetPosition
			   // 
			   this->buttonSetPosition->Location = System::Drawing::Point(0, 135);
			   this->buttonSetPosition->Name = L"buttonSetPosition";
			   this->buttonSetPosition->Size = System::Drawing::Size(164, 31);
			   this->buttonSetPosition->TabIndex = 3;
			   this->buttonSetPosition->Text = L"位置控制°";
			   this->buttonSetPosition->UseVisualStyleBackColor = true;
			   this->buttonSetPosition->Click += gcnew System::EventHandler(this, &MyForm::buttonSetPosition_Click);
			   // 
			   // buttonSetSpeed
			   // 
			   this->buttonSetSpeed->Location = System::Drawing::Point(0, 86);
			   this->buttonSetSpeed->Name = L"buttonSetSpeed";
			   this->buttonSetSpeed->Size = System::Drawing::Size(164, 31);
			   this->buttonSetSpeed->TabIndex = 2;
			   this->buttonSetSpeed->Text = L"速度控制RPM";
			   this->buttonSetSpeed->UseVisualStyleBackColor = true;
			   this->buttonSetSpeed->Click += gcnew System::EventHandler(this, &MyForm::buttonSetSpeed_Click);
			   // 
			   // textBoxCurrentSet
			   // 
			   this->textBoxCurrentSet->Location = System::Drawing::Point(170, 37);
			   this->textBoxCurrentSet->Name = L"textBoxCurrentSet";
			   this->textBoxCurrentSet->Size = System::Drawing::Size(100, 28);
			   this->textBoxCurrentSet->TabIndex = 1;
			   // 
			   // buttonSetCurrent
			   // 
			   this->buttonSetCurrent->Location = System::Drawing::Point(0, 37);
			   this->buttonSetCurrent->Name = L"buttonSetCurrent";
			   this->buttonSetCurrent->Size = System::Drawing::Size(164, 31);
			   this->buttonSetCurrent->TabIndex = 0;
			   this->buttonSetCurrent->Text = L"Q轴电流控制A";
			   this->buttonSetCurrent->UseVisualStyleBackColor = true;
			   this->buttonSetCurrent->Click += gcnew System::EventHandler(this, &MyForm::buttonSetCurrent_Click);
			   // 
			   // buttonEnable
			   // 
			   this->buttonEnable->Location = System::Drawing::Point(246, 28);
			   this->buttonEnable->Name = L"buttonEnable";
			   this->buttonEnable->Size = System::Drawing::Size(112, 34);
			   this->buttonEnable->TabIndex = 5;
			   this->buttonEnable->Text = L"电机使能";
			   this->buttonEnable->UseVisualStyleBackColor = true;
			   this->buttonEnable->Click += gcnew System::EventHandler(this, &MyForm::buttonEnable_Click);
			   // 
			   // buttonDisable
			   // 
			   this->buttonDisable->Location = System::Drawing::Point(365, 29);
			   this->buttonDisable->Name = L"buttonDisable";
			   this->buttonDisable->Size = System::Drawing::Size(112, 34);
			   this->buttonDisable->TabIndex = 6;
			   this->buttonDisable->Text = L"电机失能";
			   this->buttonDisable->UseVisualStyleBackColor = true;
			   this->buttonDisable->Click += gcnew System::EventHandler(this, &MyForm::buttonDisable_Click);
			   // 
			   // SHORTEST
			   // 
			   this->SHORTEST->Location = System::Drawing::Point(483, 29);
			   this->SHORTEST->Name = L"SHORTEST";
			   this->SHORTEST->Size = System::Drawing::Size(148, 33);
			   this->SHORTEST->TabIndex = 7;
			   this->SHORTEST->Text = L"最短距离回原点";
			   this->SHORTEST->UseVisualStyleBackColor = true;
			   this->SHORTEST->Click += gcnew System::EventHandler(this, &MyForm::SHORTEST_Click);
			   // 
			   // situationset
			   // 
			   this->situationset->Controls->Add(this->buttonConnect);
			   this->situationset->Controls->Add(this->SHORTEST);
			   this->situationset->Controls->Add(this->buttonDisconnect);
			   this->situationset->Controls->Add(this->buttonDisable);
			   this->situationset->Controls->Add(this->buttonEnable);
			   this->situationset->Location = System::Drawing::Point(393, 60);
			   this->situationset->Name = L"situationset";
			   this->situationset->Size = System::Drawing::Size(636, 80);
			   this->situationset->TabIndex = 8;
			   this->situationset->TabStop = false;
			   this->situationset->Text = L"状态设置";
			   // 
			   // groupBoxFault
			   // 
			   this->groupBoxFault->Controls->Add(this->buttonClearFault);
			   this->groupBoxFault->Controls->Add(this->labelFaultCode);
			   this->groupBoxFault->Controls->Add(this->textBoxFaultStatus);
			   this->groupBoxFault->Location = System::Drawing::Point(727, 148);
			   this->groupBoxFault->Name = L"groupBoxFault";
			   this->groupBoxFault->Size = System::Drawing::Size(297, 205);
			   this->groupBoxFault->TabIndex = 9;
			   this->groupBoxFault->TabStop = false;
			   this->groupBoxFault->Text = L"故障诊断";
			   this->groupBoxFault->Enter += gcnew System::EventHandler(this, &MyForm::groupBoxFault_Enter);
			   // 
			   // buttonClearFault
			   // 
			   this->buttonClearFault->Location = System::Drawing::Point(176, 31);
			   this->buttonClearFault->Name = L"buttonClearFault";
			   this->buttonClearFault->Size = System::Drawing::Size(106, 30);
			   this->buttonClearFault->TabIndex = 2;
			   this->buttonClearFault->Text = L"清除故障";
			   this->buttonClearFault->UseVisualStyleBackColor = true;
			   this->buttonClearFault->Click += gcnew System::EventHandler(this, &MyForm::buttonClearFault_Click);
			   // 
			   // labelFaultCode
			   // 
			   this->labelFaultCode->AutoSize = true;
			   this->labelFaultCode->Location = System::Drawing::Point(173, 74);
			   this->labelFaultCode->Name = L"labelFaultCode";
			   this->labelFaultCode->Size = System::Drawing::Size(62, 18);
			   this->labelFaultCode->TabIndex = 1;
			   this->labelFaultCode->Text = L"故障：";
			   this->labelFaultCode->Click += gcnew System::EventHandler(this, &MyForm::labelFaultCode_Click);
			   // 
			   // textBoxFaultStatus
			   // 
			   this->textBoxFaultStatus->Location = System::Drawing::Point(6, 34);
			   this->textBoxFaultStatus->Multiline = true;
			   this->textBoxFaultStatus->Name = L"textBoxFaultStatus";
			   this->textBoxFaultStatus->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			   this->textBoxFaultStatus->Size = System::Drawing::Size(167, 165);
			   this->textBoxFaultStatus->TabIndex = 0;
			   this->textBoxFaultStatus->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxFaultStatus_TextChanged);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1058, 574);
			   this->Controls->Add(this->groupBoxFault);
			   this->Controls->Add(this->situationset);
			   this->Controls->Add(this->Control);
			   this->Controls->Add(this->groupBoxStatus);
			   this->Controls->Add(this->textBoxLog);
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->Name = L"MyForm";
			   this->Text = L"电机状态监控";
			   this->groupBoxStatus->ResumeLayout(false);
			   this->groupBoxStatus->PerformLayout();
			   this->Control->ResumeLayout(false);
			   this->Control->PerformLayout();
			   this->situationset->ResumeLayout(false);
			   this->groupBoxFault->ResumeLayout(false);
			   this->groupBoxFault->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private:
		// 事件处理函数声明
		System::Void buttonConnect_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonDisconnect_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonEnable_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonDisable_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonSetCurrent_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonSetSpeed_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonSetPosition_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void SHORTEST_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void timerAutoRead_Tick(System::Object^ sender, System::EventArgs^ e);
		System::Void checkBoxAutoRead_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonClearFault_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void textBoxFaultStatus_TextChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void groupBoxFault_Enter(System::Object^ sender, System::EventArgs^ e);
		System::Void labelFaultCode_Click(System::Object^ sender, System::EventArgs^ e);
};
}