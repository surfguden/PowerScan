<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="23008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Property Name="SMProvider.SMVersion" Type="Int">201310</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="TEC LabVIEW Control Software v0.14" Type="Folder">
			<Item Name="Source" Type="Folder">
				<Item Name="LV Source" Type="Folder">
					<Item Name="[meerstetter engineering TE Cooling]" Type="Folder">
						<Item Name="Error Handling" Type="Folder">
							<Item Name="meTEC_Check for Communication Error.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Error Handling/meTEC_Check for Communication Error.vi"/>
							<Item Name="meTEC_Check for Device Error.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Error Handling/meTEC_Check for Device Error.vi"/>
							<Item Name="meTEC_Create Error Cluster (Monitoring Loop).vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Error Handling/meTEC_Create Error Cluster (Monitoring Loop).vi"/>
							<Item Name="meTEC_Create Error Cluster.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Error Handling/meTEC_Create Error Cluster.vi"/>
							<Item Name="meTEC_Error Test_Read_ID 100_Device Type.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Error Handling/meTEC_Error Test_Read_ID 100_Device Type.vi"/>
							<Item Name="meTEC_Re-Init after Error (Monitoring Loop).vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Error Handling/meTEC_Re-Init after Error (Monitoring Loop).vi"/>
						</Item>
						<Item Name="Serial Communication" Type="Folder">
							<Item Name="meTEC_Decompose Serial Message.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Serial Communication/meTEC_Decompose Serial Message.vi"/>
							<Item Name="meTEC_Determine List of COM Ports.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Serial Communication/meTEC_Determine List of COM Ports.vi"/>
							<Item Name="meTEC_Find TECs.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Serial Communication/meTEC_Find TECs.vi"/>
							<Item Name="meTEC_Open Session.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Serial Communication/meTEC_Open Session.vi"/>
							<Item Name="meTEC_Send &amp; Read Serial Message.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Serial Communication/meTEC_Send &amp; Read Serial Message.vi"/>
						</Item>
						<Item Name="TEC Commands" Type="Folder">
							<Item Name="meTEC_Limit Read_ID 3000_Object Target Temperature.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Limit Read_ID 3000_Object Target Temperature.vi"/>
							<Item Name="meTEC_Limit Read_ID 50001_Live Set Current.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Limit Read_ID 50001_Live Set Current.vi"/>
							<Item Name="meTEC_Limit Read_ID 50002_Live Set Voltage.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Limit Read_ID 50002_Live Set Voltage.vi"/>
							<Item Name="meTEC_Read_Firmware Indentification String.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_Firmware Indentification String.vi"/>
							<Item Name="meTEC_Read_ID 100_Device Type.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 100_Device Type.vi"/>
							<Item Name="meTEC_Read_ID 101_Hardware Version.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 101_Hardware Version.vi"/>
							<Item Name="meTEC_Read_ID 102_Serial Number.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 102_Serial Number.vi"/>
							<Item Name="meTEC_Read_ID 103_Firmware Version.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 103_Firmware Version.vi"/>
							<Item Name="meTEC_Read_ID 104_Device Status.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 104_Device Status.vi"/>
							<Item Name="meTEC_Read_ID 105_Error Number.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 105_Error Number.vi"/>
							<Item Name="meTEC_Read_ID 106_Error Instance.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 106_Error Instance.vi"/>
							<Item Name="meTEC_Read_ID 107_Error Parameter.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 107_Error Parameter.vi"/>
							<Item Name="meTEC_Read_ID 1000_Object Temperature.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 1000_Object Temperature.vi"/>
							<Item Name="meTEC_Read_ID 1001_Sink Temperature.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 1001_Sink Temperature.vi"/>
							<Item Name="meTEC_Read_ID 1020_Actual Output Current.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 1020_Actual Output Current.vi"/>
							<Item Name="meTEC_Read_ID 1021_Actual Output Voltage.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 1021_Actual Output Voltage.vi"/>
							<Item Name="meTEC_Read_ID 1200_Temperature Stability Detection.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 1200_Temperature Stability Detection.vi"/>
							<Item Name="meTEC_Read_ID 2030_Current Limitation.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 2030_Current Limitation.vi"/>
							<Item Name="meTEC_Read_ID 2031_Voltage Limitation.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 2031_Voltage Limitation.vi"/>
							<Item Name="meTEC_Read_ID 2051_Device Address.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 2051_Device Address.vi"/>
							<Item Name="meTEC_Read_ID 4010_Object Temperature_Lower Error Threshold.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 4010_Object Temperature_Lower Error Threshold.vi"/>
							<Item Name="meTEC_Read_ID 4011_Object Temperature_Upper Error Threshold.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Read_ID 4011_Object Temperature_Upper Error Threshold.vi"/>
							<Item Name="meTEC_Reset Device.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Reset Device.vi"/>
							<Item Name="meTEC_Set_ID 2000_Input Selection.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 2000_Input Selection.vi"/>
							<Item Name="meTEC_Set_ID 3000_Object Target Temperature.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 3000_Object Target Temperature.vi"/>
							<Item Name="meTEC_Set_ID 50000_Live Enable.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 50000_Live Enable.vi"/>
							<Item Name="meTEC_Set_ID 50001_Live Set Current.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 50001_Live Set Current.vi"/>
							<Item Name="meTEC_Set_ID 50002_Live Set Voltage.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 50002_Live Set Voltage.vi"/>
							<Item Name="meTEC_Set_ID 50011_Object Target Temperature Source Selection.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 50011_Object Target Temperature Source Selection.vi"/>
							<Item Name="meTEC_Set_ID 50012_Object Target Temperature.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TEC Commands/meTEC_Set_ID 50012_Object Target Temperature.vi"/>
						</Item>
						<Item Name="TypeDefs" Type="Folder">
							<Item Name="meTEC_Configuration.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TypeDefs/meTEC_Configuration.ctl"/>
							<Item Name="meTEC_ID 104_Device Status.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TypeDefs/meTEC_ID 104_Device Status.ctl"/>
							<Item Name="meTEC_ID 1200_Temperature is Stable.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TypeDefs/meTEC_ID 1200_Temperature is Stable.ctl"/>
							<Item Name="meTEC_ID 2000_Input Selection.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TypeDefs/meTEC_ID 2000_Input Selection.ctl"/>
							<Item Name="meTEC_ID 50000_Live Enable.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TypeDefs/meTEC_ID 50000_Live Enable.ctl"/>
							<Item Name="meTEC_ID 50011_Object Target Temperature Source Selection.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/TypeDefs/meTEC_ID 50011_Object Target Temperature Source Selection.ctl"/>
						</Item>
						<Item Name="Utilities" Type="Folder">
							<Item Name="Calculate Checksum (CRC-16).vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Utilities/Calculate Checksum (CRC-16).vi"/>
							<Item Name="Convert String (Hex to Normal).vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/[meerstetter engineering TE Cooling]/Utilities/Convert String (Hex to Normal).vi"/>
						</Item>
					</Item>
					<Item Name="Error Handling" Type="Folder">
						<Item Name="Clear All Errors.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Error Handling/Clear All Errors.vi"/>
						<Item Name="Clear Specified Error.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Error Handling/Clear Specified Error.vi"/>
						<Item Name="Error_Decompose Source String.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Error Handling/Error_Decompose Source String.vi"/>
						<Item Name="Error_Log to File (Simple).vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Error Handling/Error_Log to File (Simple).vi"/>
						<Item Name="Error_Log to File.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Error Handling/Error_Log to File.vi"/>
					</Item>
					<Item Name="Initialization &amp; Shutdown" Type="Folder">
						<Item Name="Initialize System.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Initialization &amp; Shutdown/Initialize System.vi"/>
						<Item Name="Initialize_FP_Channel Setup.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Initialization &amp; Shutdown/Initialize_FP_Channel Setup.vi"/>
						<Item Name="Initialize_FP_Input Ranges CH1.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Initialization &amp; Shutdown/Initialize_FP_Input Ranges CH1.vi"/>
						<Item Name="Initialize_FP_Input Ranges CH2.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Initialization &amp; Shutdown/Initialize_FP_Input Ranges CH2.vi"/>
						<Item Name="Shutdown System.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Initialization &amp; Shutdown/Shutdown System.vi"/>
					</Item>
					<Item Name="Type Definitions" Type="Folder">
						<Item Name="Main Loop Queue Data.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Type Definitions/Main Loop Queue Data.ctl"/>
						<Item Name="Main Loop States.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Type Definitions/Main Loop States.ctl"/>
					</Item>
					<Item Name="Utilities" Type="Folder">
						<Item Name="Charts &amp; Graphs" Type="Folder">
							<Item Name="Chart_Create evenly-spaced dataset.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Charts &amp; Graphs/Chart_Create evenly-spaced dataset.vi"/>
						</Item>
						<Item Name="Queue" Type="Folder">
							<Item Name="Dequeue Main Queue &amp; Enqueue Warn&amp;Error.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Queue/Dequeue Main Queue &amp; Enqueue Warn&amp;Error.vi"/>
							<Item Name="Error Queue - Enqueue Element.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Queue/Error Queue - Enqueue Element.vi"/>
							<Item Name="Multiple Element Enqueue - Main Loop.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Queue/Multiple Element Enqueue - Main Loop.vi"/>
						</Item>
						<Item Name="Boolean Crossing.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Boolean Crossing.vi"/>
						<Item Name="Get + Format Date + Time.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Get + Format Date + Time.vi"/>
						<Item Name="Timestamp.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Timestamp.vi"/>
						<Item Name="Wait n mSec.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Utilities/Wait n mSec.vi"/>
					</Item>
					<Item Name="Variables" Type="Folder">
						<Item Name="FGVs" Type="Folder">
							<Item Name="Type Defs" Type="Folder">
								<Item Name="FGV_Front Panel References.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/FGVs/Type Defs/FGV_Front Panel References.ctl"/>
								<Item Name="FGV_Operations.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/FGVs/Type Defs/FGV_Operations.ctl"/>
								<Item Name="FGV_TE Controller.ctl" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/FGVs/Type Defs/FGV_TE Controller.ctl"/>
							</Item>
							<Item Name="FGV_TE Controller.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/FGVs/FGV_TE Controller.vi"/>
						</Item>
						<Item Name="Globals" Type="Folder">
							<Item Name="Global_Initialized.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/Globals/Global_Initialized.vi"/>
							<Item Name="Global_Quit.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/Globals/Global_Quit.vi"/>
							<Item Name="Global_TEC Monitor Loop_Status.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/LV Source/Variables/Globals/Global_TEC Monitor Loop_Status.vi"/>
						</Item>
					</Item>
				</Item>
				<Item Name="meTEC Control Software.vi" Type="VI" URL="../TEC LabVIEW Control Software v0.14/Source/meTEC Control Software.vi"/>
			</Item>
			<Item Name="meTEC Control Software.aliases" Type="Document" URL="../TEC LabVIEW Control Software v0.14/meTEC Control Software.aliases"/>
			<Item Name="meTEC Control Software.lvlps" Type="Document" URL="../TEC LabVIEW Control Software v0.14/meTEC Control Software.lvlps"/>
			<Item Name="meTEC Control Software.lvproj" Type="Document" URL="../TEC LabVIEW Control Software v0.14/meTEC Control Software.lvproj"/>
			<Item Name="TEC LabVIEW Control Software Notes 5200F.pdf" Type="Document" URL="../TEC LabVIEW Control Software v0.14/TEC LabVIEW Control Software Notes 5200F.pdf"/>
		</Item>
		<Item Name="Application.lvclass" Type="LVClass" URL="../Application_class/Application.lvclass"/>
		<Item Name="AD2andExtAWG.lvclass" Type="LVClass" URL="../AD2andExtAWG_class/AD2andExtAWG.lvclass"/>
		<Item Name="InstrumentBase.lvclass" Type="LVClass" URL="../InstrumentBase_class/AD2_SDK_class/InstrumentBase.lvclass"/>
		<Item Name="tdmstest.vi" Type="VI" URL="../tdmstest.vi"/>
		<Item Name="AFGTest.vi" Type="VI" URL="../AFGTest.vi"/>
		<Item Name="AD2_SDK.lvclass" Type="LVClass" URL="../AD2_SDK_class/AD2_SDK.lvclass"/>
		<Item Name="AD2_MSO_SDK.lvclass" Type="LVClass" URL="../AD2_MSO_SDK_class/AD2_MSO_SDK.lvclass"/>
		<Item Name="AFG3022B.lvclass" Type="LVClass" URL="../AFG3022B_class/AFG3022B.lvclass"/>
		<Item Name="AD2_WFG_SDK.lvclass" Type="LVClass" URL="../AD2_WFG_SDK_class/AD2_WFG_SDK.lvclass"/>
		<Item Name="TDMSLogger.lvclass" Type="LVClass" URL="../TDMSLogger_class/TDMSLogger.lvclass"/>
		<Item Name="mcctest.vi" Type="VI" URL="../mcctest.vi"/>
		<Item Name="MTec.lvclass" Type="LVClass" URL="../MTec_class/MTec.lvclass"/>
		<Item Name="MTecSim.lvclass" Type="LVClass" URL="../MTecSim_class/MTecSim.lvclass"/>
		<Item Name="Hamamatsu.lvclass" Type="LVClass" URL="../Hamamatsu_class/Hamamatsu.lvclass"/>
		<Item Name="cameratest.vi" Type="VI" URL="../cameratest.vi"/>
		<Item Name="Main3.vi" Type="VI" URL="../Main3.vi"/>
		<Item Name="Experiment.lvclass" Type="LVClass" URL="../Experiment_class/Experiment.lvclass"/>
		<Item Name="MTEC_Async.lvclass" Type="LVClass" URL="../MTEC_Async_class/MTEC_Async.lvclass"/>
		<Item Name="MTtecAsyncTest.vi" Type="VI" URL="../MTtecAsyncTest.vi"/>
		<Item Name="mtect_regular_test.vi" Type="VI" URL="../mtect_regular_test.vi"/>
		<Item Name="array test.vi" Type="VI" URL="../../../test/array test.vi"/>
		<Item Name="Control 1.ctl" Type="VI" URL="../Application_class/Control 1.ctl"/>
		<Item Name="CetoniPump.lvclass" Type="LVClass" URL="../CetoniPump_class/CetoniPump.lvclass"/>
		<Item Name="TDMSLogger_PowerScan.lvclass" Type="LVClass" URL="../TDMSLogger_PowerScan_class/TDMSLogger_PowerScan.lvclass"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="DU64_U32SubtractWithBorrow.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/TSOps.llb/DU64_U32SubtractWithBorrow.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="I128 Timestamp.ctl" Type="VI" URL="/&lt;vilib&gt;/Waveform/TSOps.llb/I128 Timestamp.ctl"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_MABase.lvlib" Type="Library" URL="/&lt;vilib&gt;/measure/NI_MABase.lvlib"/>
				<Item Name="NI_MAPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/measure/NI_MAPro.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Timestamp Subtract.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/TSOps.llb/Timestamp Subtract.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="VISA Lock Async.vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Lock Async.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Check for Equality.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/WDTOps.llb/Check for Equality.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="LVMinMaxIncTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVMinMaxIncTypeDef.ctl"/>
				<Item Name="IMAQ Image.ctl" Type="VI" URL="/&lt;vilib&gt;/vision/Image Controls.llb/IMAQ Image.ctl"/>
				<Item Name="Image Type" Type="VI" URL="/&lt;vilib&gt;/vision/Image Controls.llb/Image Type"/>
				<Item Name="IMAQ ArrayToImage" Type="VI" URL="/&lt;vilib&gt;/vision/Basics.llb/IMAQ ArrayToImage"/>
				<Item Name="IMAQ Dispose" Type="VI" URL="/&lt;vilib&gt;/vision/Basics.llb/IMAQ Dispose"/>
				<Item Name="IMAQ Create" Type="VI" URL="/&lt;vilib&gt;/vision/Basics.llb/IMAQ Create"/>
				<Item Name="IMAQ WindDraw" Type="VI" URL="/&lt;vilib&gt;/vision/Display.llb/IMAQ WindDraw"/>
				<Item Name="IMAQ WindZoom 2" Type="VI" URL="/&lt;vilib&gt;/vision/Display.llb/IMAQ WindZoom 2"/>
				<Item Name="FormatTime String.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/FormatTime String.vi"/>
				<Item Name="subElapsedTime.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/subElapsedTime.vi"/>
				<Item Name="Trim Whitespace One-Sided.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace One-Sided.vi"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="NI_LVConfig.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/config.llb/NI_LVConfig.lvlib"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="8.6CompatibleGlobalVar.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/config.llb/8.6CompatibleGlobalVar.vi"/>
				<Item Name="IMAQ Write TIFF File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write TIFF File 2"/>
				<Item Name="IMAQ Write PNG File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write PNG File 2"/>
				<Item Name="IMAQ Write JPEG2000 File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write JPEG2000 File 2"/>
				<Item Name="IMAQ Write JPEG File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write JPEG File 2"/>
				<Item Name="IMAQ Write Image And Vision Info File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write Image And Vision Info File 2"/>
				<Item Name="IMAQ Write BMP File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write BMP File 2"/>
				<Item Name="IMAQ Write File 2" Type="VI" URL="/&lt;vilib&gt;/vision/Files.llb/IMAQ Write File 2"/>
			</Item>
			<Item Name="user.lib" Type="Folder">
				<Item Name="tm_getframe16_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_getframe16_40.vi"/>
				<Item Name="tm_initialize_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_initialize_40.vi"/>
				<Item Name="tm_deinitialize_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_deinitialize_40.vi"/>
				<Item Name="tm_closecamera_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_closecamera_40.vi"/>
				<Item Name="tm_opencamera_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_opencamera_40.vi"/>
				<Item Name="tm_preparecapture_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_preparecapture_40.vi"/>
				<Item Name="tm_inputtriggersource_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/trigger/tm_inputtriggersource_40.vi"/>
				<Item Name="tm_startcapture_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_startcapture_40.vi"/>
				<Item Name="tm_waitnextframe_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_waitnextframe_40.vi"/>
				<Item Name="tm_unpreparecapture_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_unpreparecapture_40.vi"/>
				<Item Name="tm_stopcapture_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_stopcapture_40.vi"/>
				<Item Name="tm_setparameter_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_setparameter_40.vi"/>
				<Item Name="tm_inputtriggeractive_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/trigger/tm_inputtriggeractive_40.vi"/>
				<Item Name="tm_getcaptureinfo_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_getcaptureinfo_40.vi"/>
				<Item Name="tm_getarea_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_getarea_40.vi"/>
				<Item Name="tm_setarea_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_setarea_40.vi"/>
				<Item Name="tm_setoutputtrigger_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/trigger/tm_setoutputtrigger_40.vi"/>
				<Item Name="tm_getparameter_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_getparameter_40.vi"/>
				<Item Name="tm_firetrigger_40.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/trigger/tm_firetrigger_40.vi"/>
				<Item Name="tm_errorreport.vi" Type="VI" URL="/&lt;userlib&gt;/Hamamatsu Video Capture/tm_errorreport.vi"/>
			</Item>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="Olasdwf.lvlib" Type="Library" URL="../Olasdwf/Olasdwf.lvlib"/>
			<Item Name="nivision.dll" Type="Document" URL="nivision.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="nivissvc.dll" Type="Document" URL="nivissvc.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="tmcamcon.dll" Type="Document" URL="tmcamcon.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="Tektronix AFG 3000 Series.lvlib" Type="Library" URL="../Tektronix AFG 3000 Series/Tektronix AFG 3000 Series.lvlib"/>
			<Item Name="labbCAN_Bus_API.lvlib" Type="Library" URL="../CETONI_SDK/lib/labview/labbCAN_Bus_API/labbCAN_Bus_API.lvlib"/>
			<Item Name="labbCAN_Pump_API.lvlib" Type="Library" URL="../CETONI_SDK/lib/labview/labbCAN_Pump_API/labbCAN_Pump_API.lvlib"/>
			<Item Name="labbCAN_Valve_API.lvlib" Type="Library" URL="../CETONI_SDK/lib/labview/labbCAN_Valve_API/labbCAN_Valve_API.lvlib"/>
			<Item Name="dwf.dll" Type="Document" URL="/../Windows/System32/dwf.dll"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Main Application" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{51D186D8-2FD9-4F4B-8F36-40D68E57FFBC}</Property>
				<Property Name="App_INI_GUID" Type="Str">{F8BAE070-8383-465E-800B-3DF9D752A65B}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">1</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{96FCFFEE-92FF-41D7-8A5C-2E1B7D4F08B1}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Main Application</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Main Application</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{9236DFC5-A1BE-45C5-93F4-A12737594CB8}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Main.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Main Application/Main.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Main Application/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{04B475E1-04C7-4A89-80BE-B47BDBB71E4D}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Main3.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Main Application</Property>
				<Property Name="TgtF_internalName" Type="Str">Main Application</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">Main Application</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{8D31CF1E-BFEE-4FAB-AC90-991853A95B09}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Main.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
