#include "MyForm.h"

namespace ProjectAK {

	// 连接设备按钮事件
	System::Void MyForm::buttonConnect_Click(System::Object^ sender, System::EventArgs^ e) {
		unsigned int ret;
		unsigned char RXF[4], RXM[4];
		RXF[0] = 0; RXF[1] = 0; RXF[2] = 0; RXF[3] = 0;
		RXM[0] = 0; RXM[1] = 0; RXM[2] = 0; RXM[3] = 0;

		textBoxLog->AppendText("正在初始化CAN...\r\n");

		// 尝试不同的波特率
		ret = Init_can(5, 1, 1000, 2, 0, RXF, RXM); // 1MHz

		if (ret == 0) {
			textBoxLog->AppendText("CAN初始化成功\r\n");
			// 然后读取状态
			ReadMotorStatus();
			UpdateFaultDisplay(0);
		}
		else {
			textBoxLog->AppendText("CAN初始化失败，错误码: " + ret + "\r\n");

			// 显示错误含义
			switch (ret) 
			{
			case 1: textBoxLog->AppendText("错误: 设备已连接\r\n"); break;
			case 2: textBoxLog->AppendText("错误: 检测到串口但无设备应答\r\n"); break;
			case 3: textBoxLog->AppendText("错误: 无可用串口\r\n"); break;
			default: textBoxLog->AppendText("错误: 未知错误\r\n"); break;
			}
		}
	}
	// 清除故障按钮事件
	System::Void MyForm::buttonClearFault_Click(System::Object^ sender, System::EventArgs^ e) {
		unsigned int ret;
		unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };

		// 发送清除故障命令 (0xAF)
		unsigned char clearFaultData[8] = { 0xAF, 0, 0, 0, 0, 0, 0, 0 };

		ret = Can_send(IDbuff, clearFaultData, 0, 1);
		if (ret == 0) {
			textBoxLog->AppendText("清除故障命令发送成功\r\n");

			// 等待并接收应答
			System::Threading::Thread::Sleep(100);
			CheckClearFaultResponse();
		}
		else {
			textBoxLog->AppendText("清除故障命令发送失败: " + ret + "\r\n");
		}
	}

	// 检查清除故障应答
	void MyForm::CheckClearFaultResponse() {
		unsigned int ret;
		unsigned char FreamType, Bytes;
		int attempts = 0;

		while (attempts < 50) {
			unsigned char recvID[4] = { 0 };
			unsigned char recvData[8] = { 0 };
			ret = Can_receive(recvID, recvData, &FreamType, &Bytes);

			if (ret == 1) {
				// 检查是否是0xAF命令的应答
				if (recvData[0] == 0xAF && Bytes >= 2) {
					unsigned char faultCode = recvData[1];
					UpdateFaultDisplay(faultCode);

					if (faultCode == 0) {
						textBoxLog->AppendText("故障清除成功，系统恢复正常\r\n");
					}
					else {
						textBoxLog->AppendText("故障清除失败，仍有故障存在\r\n");
					}
					return;
				}
			}
			else if (ret == 0) {
				System::Threading::Thread::Sleep(1);
			}
			attempts++;
		}
		textBoxLog->AppendText("清除故障应答超时\r\n");
	}

	// 更新故障显示
	void MyForm::UpdateFaultDisplay(unsigned char faultCode) {
		// 解析故障码
		String^ faultDescription = ParseFaultCode(faultCode);
		String^ faultDetails = GetFaultDetails(faultCode);

		// 更新故障码显示
		labelFaultCode->Text = "故障码: 0x" + faultCode.ToString("X2");

		// 更新故障状态显示
		textBoxFaultStatus->Text = faultDescription + "\r\n" + faultDetails;

		// 根据故障状态设置文本颜色
		if (faultCode == 0) {
			textBoxFaultStatus->ForeColor = Drawing::Color::Green;
			labelFaultCode->ForeColor = Drawing::Color::Green;
		}
		else {
			textBoxFaultStatus->ForeColor = Drawing::Color::Red;
			labelFaultCode->ForeColor = Drawing::Color::Red;
		}
	}

	// 解析故障码
	// 或者使用更简单的方法，直接构建字符串：
	String^ MyForm::ParseFaultCode(unsigned char faultCode) {
		if (faultCode == 0) {
			return "系统正常";
		}

		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

		// 解析各个故障位
		if ((faultCode & 0x01) != 0) sb->Append("电压故障、");
		if ((faultCode & 0x02) != 0) sb->Append("电流故障、");
		if ((faultCode & 0x04) != 0) sb->Append("温度故障、");
		if ((faultCode & 0x08) != 0) sb->Append("编码器故障、");
		if ((faultCode & 0x40) != 0) sb->Append("硬件故障、");
		if ((faultCode & 0x80) != 0) sb->Append("软件故障、");

		// 移除最后一个顿号
		if (sb->Length > 0) {
			sb->Remove(sb->Length - 1, 1);
		}

		return sb->ToString();
	}

	// 获取故障详细信息
	String^ MyForm::GetFaultDetails(unsigned char faultCode) {
		if (faultCode == 0) {
			return "所有系统参数正常，无故障状态";
		}

		String^ details = "故障详情:\r\n";

		if ((faultCode & 0x01) != 0)
			details += "• 电压故障: 母线电压异常，可能过压或欠压\r\n";
		if ((faultCode & 0x02) != 0)
			details += "• 电流故障: 母线电流异常，可能过流\r\n";
		if ((faultCode & 0x04) != 0)
			details += "• 温度故障: 电机或驱动器温度过高\r\n";
		if ((faultCode & 0x08) != 0)
			details += "• 编码器故障: 编码器信号异常或丢失\r\n";
		if ((faultCode & 0x40) != 0)
			details += "• 硬件故障: 驱动器硬件电路异常\r\n";
		if ((faultCode & 0x80) != 0)
			details += "• 软件故障: 系统软件运行异常\r\n";

		details += "\r\n建议: 检查相关参数并尝试清除故障";
		return details;
	}
	// 释放设备按钮事件
	System::Void MyForm::buttonDisconnect_Click(System::Object^ sender, System::EventArgs^ e) {
		unsigned int ret;
		ret = Quit_can();
		textBoxLog->AppendText("释放设备连接\r\n");
	}
	// 定时器触发事件 - 自动读取状态
	System::Void MyForm::timerAutoRead_Tick(System::Object^ sender, System::EventArgs^ e) {
		ReadMotorStatus();
	}

	// 复选框状态改变事件
	System::Void MyForm::checkBoxAutoRead_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox1->Checked) {
			timerAutoRead->Start();
		}
		else {
			timerAutoRead->Stop();
		}
	}
	// 读取电机状态函数
	void MyForm::ReadMotorStatus() {
		unsigned int ret;
		unsigned char IDbuff[4] = { 0 };
		unsigned char Databuff[8] = { 0 };
		unsigned char FreamType;
		unsigned char Bytes;
		IDbuff[0] = 0x00;
		IDbuff[1] = 0x01;
		IDbuff[2] = 0x00;
		IDbuff[3] = 0x00;

		// 发送数据：只有命令码0xAE
		unsigned char sendData[8] = { 0xAE, 0, 0, 0, 0, 0, 0, 0 };

		// 发送0xAE命令
		ret = Can_send(IDbuff, sendData, 0, 1); // 帧类型0=标准数据帧，DLC=1

		if (ret != 0)
		{
			textBoxLog->AppendText("发送0xAE命令失败，错误码: " + ret + "\r\n");
			return;
		}
		System::Threading::Thread::Sleep(100); // 等待100ms

		// 等待并接收应答
		int attempts = 0;
		while (attempts < 100) { // 尝试50次，避免死循环
			unsigned char recvID[4] = { 0 };
			unsigned char recvData[8] = { 0 };
			ret = Can_receive(recvID, recvData, &FreamType, &Bytes);
			if (ret == 1)
			{
				/* 成功收到一帧数据
				 重组接收到的ID*/
				unsigned int recvStdID = (recvID[1] << 8) | recvID[0];
				recvStdID &= 0x7FF; // 确保是11位
				// 解析数据：电压[1-2]、电流[3-4]、温度[5]
				unsigned int voltage = (recvData[2] << 8) | recvData[1]; // 小端
				unsigned int current = (recvData[4] << 8) | recvData[3]; // 小端
				unsigned char temperature = recvData[5];
				unsigned char faultCode = recvData[7]; // 根据协议，故障码在Data[7]
				UpdateFaultDisplay(faultCode);
				// 更新UI显示
				UpdateStatusDisplay(voltage, current, temperature);
				return;
			}
			else if (ret == 0) {
				// 没有数据，稍作延迟
				System::Threading::Thread::Sleep(1);
			}
			else {
				textBoxLog->AppendText("接收数据出错，错误码: " + ret + "\r\n");
				break;
			}
			attempts++;
		}

		textBoxLog->AppendText("读取状态超时\r\n");
	}

	// 电机使能
	System::Void MyForm::buttonEnable_Click(System::Object^ sender, System::EventArgs^ e) {
		unsigned int ret;
		unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };

		// Q轴电流控制命令 (0xC0)，电流设为0A
		unsigned char currentData[8] = { 0xC0, 0x00, 0x00, 0x00, 0x00, 0, 0, 0 };

		ret = Can_send(IDbuff, currentData, 0, 5);
		if (ret == 0) {
			textBoxLog->AppendText("电机使能成功\r\n");
		}
		else {
			textBoxLog->AppendText("电机使能失败: " + ret + "\r\n");
		}
	}

	// 电机失能
	System::Void MyForm::buttonDisable_Click(System::Object^ sender, System::EventArgs^ e) {
		unsigned int ret;
		unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };

		// 关闭电机输出命令 (0xCF)
		unsigned char disableData[8] = { 0xCF, 0, 0, 0, 0, 0, 0, 0 };

		ret = Can_send(IDbuff, disableData, 0, 1);
		if (ret == 0) {
			textBoxLog->AppendText("电机失能成功\r\n");
		}
		else {
			textBoxLog->AppendText("电机失能失败: " + ret + "\r\n");
		}
	}

	// 设置电流控制
	System::Void MyForm::buttonSetCurrent_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		try {
			double current = Double::Parse(textBoxCurrentSet->Text); // 单位：A
			int currentValue = (int)(current * 1000); // 转换为0.001A单位

			unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };
			unsigned char currentData[8] = { 0xC0,
											(currentValue & 0xFF),
											((currentValue >> 8) & 0xFF),
											((currentValue >> 16) & 0xFF),
											((currentValue >> 24) & 0xFF), 0, 0, 0 };

			unsigned int ret = Can_send(IDbuff, currentData, 0, 5);
			if (ret == 0) {
				textBoxLog->AppendText("电流设置成功: " + current + "A\r\n");
			}
			else {
				textBoxLog->AppendText("电流设置失败: " + ret + "\r\n");
			}
		}
		catch (Exception^ ex) {
			textBoxLog->AppendText("电流值格式错误\r\n");
		}
	}

	// 设置速度控制
	System::Void MyForm::buttonSetSpeed_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			double speed = Double::Parse(textBoxSpeedSet->Text); // 单位：RPM
			int speedValue = (int)(speed * 100); // 转换为0.01RPM单位

			unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };
			unsigned char speedData[8] = { 0xC1,
										  (speedValue & 0xFF),
										  ((speedValue >> 8) & 0xFF),
										  ((speedValue >> 16) & 0xFF),
										  ((speedValue >> 24) & 0xFF), 0, 0, 0 };

			unsigned int ret = Can_send(IDbuff, speedData, 0, 5);
			if (ret == 0) {
				textBoxLog->AppendText("速度设置成功: " + speed + "RPM\r\n");
			}
			else {
				textBoxLog->AppendText("速度设置失败: " + ret + "\r\n");
			}
		}
		catch (Exception^ ex) {
			textBoxLog->AppendText("速度值格式错误\r\n");
		}
	}

	// 设置位置控制
	System::Void MyForm::buttonSetPosition_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			double position = Double::Parse(textBoxPositionSet->Text); // 单位：度
			int positionValue = (int)(position * 16384 / 360); // 转换为Count单位

			unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };
			unsigned char positionData[8] = { 0xC2,
											 (positionValue & 0xFF),
											 ((positionValue >> 8) & 0xFF),
											 ((positionValue >> 16) & 0xFF),
											 ((positionValue >> 24) & 0xFF), 0, 0, 0 };

			unsigned int ret = Can_send(IDbuff, positionData, 0, 5);
			if (ret == 0) {
				textBoxLog->AppendText("位置设置成功: " + position + "度\r\n");
			}
			else {
				textBoxLog->AppendText("位置设置失败: " + ret + "\r\n");
			}
		}
		catch (Exception^ ex) 
		{
			textBoxLog->AppendText("位置值格式错误\r\n");
		}
	}
	System::Void MyForm::SHORTEST_Click(System::Object^ sender, System::EventArgs^ e)
	{
		unsigned int ret;
		unsigned char IDbuff[4] = { 0x00, 0x01, 0x00, 0x00 };

		// 最短距离回原点命令 (0xC4)
		unsigned char homeData[8] = { 0xC4, 0, 0, 0, 0, 0, 0, 0 };

		ret = Can_send(IDbuff, homeData, 0, 1);
		if (ret == 0) {
			textBoxLog->AppendText("回原点命令发送成功\r\n");
		}
		else {
			textBoxLog->AppendText("回原点命令发送失败: " + ret + "\r\n");
		}
	}

	// 更新状态显示
	void MyForm::UpdateStatusDisplay(unsigned int voltage, unsigned int current, unsigned char temperature) {
		// 单位换算
		double voltage_val = voltage * 0.01; // 单位 0.01V -> V
		double current_val = current * 0.01; // 单位 0.01A -> A
		double temp_val = temperature;       // 单位 ℃

		// 更新UI控件
		textBoxVoltage->Text = voltage_val.ToString("F2");
		textBoxCurrent->Text = current_val.ToString("F2");
		textBoxTemperature->Text = temp_val.ToString("F0");
	}
	System::Void MyForm::textBoxFaultStatus_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		// 留空，不需要特殊处理
	}

	System::Void MyForm::groupBoxFault_Enter(System::Object^ sender, System::EventArgs^ e) {
		// 留空，不需要特殊处理
	}

	System::Void MyForm::labelFaultCode_Click(System::Object^ sender, System::EventArgs^ e) {
		// 留空，不需要特殊处理
	}
}