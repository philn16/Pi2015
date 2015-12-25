close all %figures
directory = '../waveforms/';
clockfile = [directory 'clock.lib'];
datafile = [directory 'data.lib'];

%Runtime options
options.PlotOrigionalDataAndCLock = 0;
options.PlotDataAndCLock = 0;
options.PlotOutData = 1;
options.DisplayHexOut = 1;

%End of Configurable vars
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figuremgr=0; %Do not make new figure if 0, make new fiurge if 1

fileID = fopen(clockfile,'r');
ORIGclock = fscanf(fileID,'%f');
fclose(fileID);

fileID = fopen(datafile,'r');
ORIGdata = fscanf(fileID,'%f');
fclose(fileID);
clear clockfile datafile directory fileID

clock = MakeBinary(ORIGclock);
data = MakeBinary(ORIGdata);

PositiveEdges = find(clock(2:numel(clock)) > clock(1:numel(clock)-1));
% NegativeEdges = find(clock(2:numel(clock)) < clock(1:numel(clock)-1));
OutData = data(PositiveEdges)';

% Plots origional clock and data voltages
if options.PlotOrigionalDataAndCLock
    if figuremgr
        figure
    end
    if(numel(ORIGclock) ~= numel(ORIGdata))
        error('Data and clokc sie are not the same');
    end
    plot(1:numel(ORIGclock) , ORIGclock , 'linewidth',  1, 'color', [1 0 0])
    hold on
    plot(1:numel(ORIGdata) , ORIGdata , 'linewidth',  1, 'color', [0 0 1])
    figuremgr = 1;
end

%Plots the binarized clock and data voltages
if options.PlotDataAndCLock
    if figuremgr
        figure
    end
    if(numel(clock) ~= numel(data))
        error('Data and clokc sie are not the same');
    end
    plot(1:numel(clock) , clock , 'linewidth',  1, 'color', [1 0 0])
    hold on
    plot(1:numel(data) , data , 'linewidth',  1, 'color', [0 0 1])
    axis([0 numel(data)+1 -0.1 1.1])
    figuremgr = 1;
end

%plots the resultant poseged out data
%8 bits and a NAK / ACK
if options.PlotOutData
    if figuremgr
        figure
    end
    %problem areas should have two points
    problems = find(OutData(2:numel(OutData)) ~= OutData(1:numel(OutData)-1))';
    clear x TempPlot;
    TempPlot(numel(OutData) + numel(problems))=0;
    x(numel(TempPlot))=0;
    k=1;
    for i=1:numel(OutData)
        TempPlot(i+k-1) = OutData(i);
        x(i+k-1) = i;
        if(k <= numel(problems) && problems(k) == i)
            TempPlot(i+k) = OutData(i);
            x(k+i) = i+1;
            k=k+1;
        end
    end
    hax=axes;
    
    plot(x,TempPlot,  'linewidth',  1.5, 'color', [0 0 1])
    axis([0 numel(OutData)+1 -0.1 1.1])
    figuremgr=1;
    
    %plots thin green line on everything
    for i=1:numel(OutData)
        line([i i],get(hax,'YLim'),'Color',[0 1 0], 'linewidth',  0.4)
    end
    
    %Plots thick line for every 9 clock cycles
    %Denotes end of read / write period
    SP= [1 : 9 : numel(OutData)]; %your point goes here
    for i=1:numel(SP)
        line([SP(i) SP(i)],get(hax,'YLim'),'Color',[1 0 0], 'linewidth',  1.2)
    end
    
    %Plots thick line for every 9 clock cycles
    %Right before Ack / nack
    SP= [9 : 9 : numel(OutData)]; %your point goes here
    for i=1:numel(SP)
        line([SP(i) SP(i)],get(hax,'YLim'),'Color',[0.6 0 0.6], 'linewidth',  1.1)
    end
    clear SP i k x TempPlot problems
end

if options.DisplayHexOut
    clear OutString
    OutString(floor(numel(OutData)/9),4)=char(0);
    for i=1:9:(numel(OutData)-9)
        OutString((i-1)/9+1 , 1:4)= [binaryVectorToHex(OutData(i:i+7)) ,' ', char(OutData(i+9)+'0')];
    end
    OutString
end