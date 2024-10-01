<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="21008000">
	<Item Name="Mein Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">Mein Computer/VI-Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">Mein Computer/VI-Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="example" Type="Folder" URL="../example">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Menufiles" Type="Folder" URL="../Menufiles">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="labbCAN_Bus_API.lvlib" Type="Library" URL="../labbCAN_Bus_API/labbCAN_Bus_API.lvlib"/>
		<Item Name="labbCAN_MotionControl_API.lvlib" Type="Library" URL="../labbCAN_MotionControl_API/labbCAN_MotionControl_API.lvlib"/>
		<Item Name="labbCAN_Pump_API.lvlib" Type="Library" URL="../labbCAN_Pump_API/labbCAN_Pump_API.lvlib"/>
		<Item Name="labbCAN_Valve_API.lvlib" Type="Library" URL="../labbCAN_Valve_API/labbCAN_Valve_API.lvlib"/>
		<Item Name="labbCAN_Controller_API.lvlib" Type="Library" URL="../labbCAN_Controller_API/labbCAN_Controller_API.lvlib"/>
		<Item Name="labbCAN_AnalogIO_API.lvlib" Type="Library" URL="../labbCAN_AnlogIO_API/labbCAN_AnalogIO_API.lvlib"/>
		<Item Name="labbCAN_DigIO_API.lvlib" Type="Library" URL="../labbCAN_DigIO_API/labbCAN_DigIO_API.lvlib"/>
		<Item Name="Abhängigkeiten" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
			</Item>
			<Item Name="labbCAN_MotionControl_API.dll" Type="Document" URL="../../../labbCAN_MotionControl_API.dll"/>
		</Item>
		<Item Name="Build-Spezifikationen" Type="Build">
			<Item Name="Pump_API_Application_Test" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{62BF138A-4609-4F14-A062-6C40EEC5591B}</Property>
				<Property Name="App_INI_GUID" Type="Str">{55999A6E-1FFB-42BC-9282-F6E95EB83937}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">1</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{719FB348-7E3B-4B0A-A171-311A586950C3}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Pump_API_Application_Test</Property>
				<Property Name="Bld_defaultLanguage" Type="Str">German</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Pump_API_Application_Test</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{7FA8C1F5-34DF-4D78-9502-A6746090703A}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Pump_API_Application_Test/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Hilfsdatei-Verzeichnis</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Pump_API_Application_Test/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{3F67D4BF-BD67-486B-BD0B-877B033D77FC}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/Mein Computer/example/Pump_API_Application_Test.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/Mein Computer/labbCAN_Bus_API.lvlib</Property>
				<Property Name="Source[2].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Library</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/Mein Computer/labbCAN_MotionControl_API.lvlib</Property>
				<Property Name="Source[3].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">Library</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/Mein Computer/labbCAN_Pump_API.lvlib</Property>
				<Property Name="Source[4].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">Library</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/Mein Computer/labbCAN_Valve_API.lvlib</Property>
				<Property Name="Source[5].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">Library</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/Mein Computer/labbCAN_Controller_API.lvlib</Property>
				<Property Name="Source[6].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">Library</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/Mein Computer/labbCAN_AnalogIO_API.lvlib</Property>
				<Property Name="Source[7].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">Library</Property>
				<Property Name="Source[8].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[8].itemID" Type="Ref">/Mein Computer/labbCAN_DigIO_API.lvlib</Property>
				<Property Name="Source[8].Library.allowMissingMembers" Type="Bool">true</Property>
				<Property Name="Source[8].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[8].type" Type="Str">Library</Property>
				<Property Name="SourceCount" Type="Int">9</Property>
				<Property Name="TgtF_companyName" Type="Str">cetoni GmbH</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Pump_API_Application_Test</Property>
				<Property Name="TgtF_internalName" Type="Str">Pump_API_Application_Test</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2019 cetoni GmbH</Property>
				<Property Name="TgtF_productName" Type="Str">Pump_API_Application_Test</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{18069487-218D-42EA-8EBC-0A4FE32CA19E}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
