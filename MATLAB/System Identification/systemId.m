%%

% Author: Alper Ender
% Description: System Identification code for multiple sampled data sets

%% Importing Raw Data from multiple files

clear; clc; fclose('all');

for i = 1:3
    
    str = sprintf('raw%d.80.100.txt',i);

    fid = fopen(str,'r');

    j = 1;

    while ~feof(fid)
        data(i).raw(j) = str2num(fgetl(fid));
        j = j+1;
    end
    
    fclose(fid);

end

T = 0.01;

data1 = data(1).raw';
data2 = data(2).raw';
data3 = data(3).raw';

one1 = ones([1 length(data1)])';
one2 = ones([1 length(data2)])';
one3 = ones([1 length(data3)])';

dataObj1 = iddata(data1,one1,T);
dataObj2 = iddata(data2,one2,T);
dataObj3 = iddata(data3,one3,T);


%% Viewing Data

plotval = data3;

one = ones([1 length(plotval)])';

x = 1:length(plotval);
stairs(x,plotval)
hold on
[p,S] = polyfit(x,plotval,11); y = polyval(p,x);
plot(y), grid

fclose('all')


%% Using the System Identification toolbox

systemIdentification

%% Obtaining the Ts from the toolbox

Ts = tf1
Tz = c2d(Ts, 0.01)

%% Obtaining the Dz from the Ts from the toolbox

D = 23;

Gs = (Ts/(1-Ts))/D
Gz = c2d(Gs,0.01)
Gz = zpk(Gz)
