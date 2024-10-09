fileName = "C:\Users\olaja\Downloads\1e8to1e9MHz_step1kHz_noTcontrol.tdms";
info = tdmsinfo(fileName);
synced_channels=info.ChannelList.ChannelName(info.ChannelList.ChannelGroupName=="Untitled")
all_data=tdmsread(fileName, ChannelGroupName='Untitled', ChannelName=synced_channels)
%% We dont it as cell:
all_data=all_data{1}

%% calculate elapsed time
all_data.ElapsedTime=all_data.meTECTime(:)-all_data.meTECTime(1)
%%
%remove data with function generator off:
all_data=all_data(all_data.WFGEnabled==1,:)

%remove special characters from header in table.... arghh
for i=1:numel(all_data.Properties.VariableNames)
    str=all_data.Properties.VariableNames{i}
    str(~ismember(str,['A':'Z' 'a':'z' '0':'9'])) = ''
    all_data.Properties.VariableNames{i}=str
end

%%
unique_set_powers=unique(all_data.SetPower)
figure
for i=unique_set_powers'%dont forget the '....
    i
    hold on
    plot(all_data.SetFreqCh1(all_data.SetPower==i),all_data.meTECCH1ObjectTemperatureC(all_data.SetPower==i), 'DisplayName',"T Ch1 (piezo), @"+i +"W")
    plot(all_data.SetFreqCh1(all_data.SetPower==i),all_data.meTECCH2ObjectTemperatureC(all_data.SetPower==i), 'DisplayName',"T Ch2 (CU-film) @"+i +"W")
    xlabel("Frequency(Hz)")
    ylabel("Temperature (C)")
    legend
    axis padded
end
axis padded

%% Plot average Temperature for every power (3 points, hehe)
mean_temp_ch1=[]
mean_temp_ch2=[]
for i=unique_set_powers' %dont forget the '....
    mean_temp_ch1=[mean_temp_ch1 mean(all_data.meTECCH1ObjectTemperatureC(all_data.SetPower==i))]
    mean_temp_ch2=[mean_temp_ch2 mean(all_data.meTECCH2ObjectTemperatureC(all_data.SetPower==i))]
end
    tiledlayout("flow")
    nexttile
    plot(unique_set_powers,mean_temp_ch1,"og")
    hold on
    plot(unique_set_powers,mean_temp_ch2,"or")
    legend("ch1", "ch2", 'Location',"best")
    xlabel("set power (W)")
    ylabel("mean temperature (T)")
    axis padded
    title("Average Temperature Vs Power")


    nexttile
    plot(all_data.MeasuredPower,all_data.meTECCH1ObjectTemperatureC,'DisplayName',"T Ch1 (piezo)","LineStyle", "none", "marker", "x", "color", "red" )
    hold on
    plot(all_data.MeasuredPower,all_data.meTECCH2ObjectTemperatureC,'DisplayName',"T Ch2 (cu film)","LineStyle", "none", "marker", "x", "color", "green" )
    xlabel("measured power")
    ylabel("measured Temperature")
    legend('Location',"best")
    axis padded
    title("Temperature vs Measured Power")

    nexttile
    for i=unique_set_powers'
        plot(all_data.Ch2Amp(all_data.SetPower==i)./5,all_data.meTECCH1ObjectTemperatureC(all_data.SetPower==i), 'DisplayName', i +"W","marker", "o","LineStyle", "none")
        hold on
    end
    legend('Location',"best")
    xlabel("measured current")
    ylabel("measured Temperature")
    axis padded
    title("Temperature vs Measured Current")

    nexttile
    hold on
    plot(all_data.ElapsedTime, all_data.meTECCH1ObjectTemperatureC)
    plot(all_data.ElapsedTime, all_data.meTECCH2ObjectTemperatureC)
    yyaxis right
    plot(all_data.ElapsedTime, all_data.CetoniFillLevel)
    title("Temperature Vs Elapsed Time, and syringe level")
    legend(["Temperature CH1" "Temperature CH2" "Syringe Fill Level"],'Location',"best")

