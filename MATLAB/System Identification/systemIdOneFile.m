% Author: Alper Ender
% Description: System Identification Code for one Sampled Data Set

%% Importing Data

clear; clc; fclose('all');

fid = fopen('raw1.110.100.txt','r');

data = [];
i = 1;

while ~feof(fid)
    data1(i,1) = str2num(fgetl(fid));
    i = i+1;
end

T = 0.01;
data3 = data1;
one1 = ones([1 length(data1)])';
dataObj1 = iddata(data1,one1,T);

%% Viewing Data

one = ones([1 length(data1)])';

x = [1:length(data1)]';
stairs(x,data1)
hold on
[p,S] = polyfit(x,data1,11); y = polyval(p,x);
plot(y), grid

fclose('all')


%% Using the System Identification Toolbox

systemIdentification

%% Obtaining the Dz and Tz from the System Identification toolbox

KPROP = 100;

j = 1;
for i = [tf1 tf3 tf5]
    
    % Obtaining the Tz from the system identification toolbox
    Processesd(j).Ts = i;
    Processesd(j).Tz = c2d(Processesd(j).Ts, 0.01);
    
    D = 100;

    % Obtaining the Dz from the Ts
    Processesd(j).Gs = (Processesd(j).Ts/(1-Processesd(j).Ts))/D;
    Processesd(j).Gz = c2d(Processesd(j).Gs,0.01);
    Processesd(j).Gz = zpk(Processesd(j).Gz);
    Processesd(j).Gs
    j = j+1;
end

%% Creating an EXAMPLE PID from the Dz

T = 0.01;

% From the pidtool for ww1 = 0.9278 rad/s and Pm = 60 deg
KP = 72.8233; KI = 110.4133; KD = 4.4035; TF = 0.15403;
% KP = 2.8642; KI = 0.068872; KD = -0.3868; TF = 0.26195;

% Find Dz using Equation (8-65)
Dz_PIDF = KP + (KI*T)*tf([1],[1 -1],T) + KD*tf([1 -1],[TF -TF+T],T)
[numz, denz]=tfdata(Dz_PIDF,'v')

format long
roots(numz)

format short
%Dz_PIDF = zpk(Dz_PIDF)


% (b) Find the performance parameters for your design (as in Problem 2).

% Entire Plant
DzGz=Dz_PIDF*Gz;

% Obtaining Gain Margin and Phase Margin
[Gm, Pm] = margin(DzGz);
GmdB = 20*log10(Gm), Pm

% Closing the Loop, plotting, and obtaining characteristics 
Tz=feedback(DzGz,1);
step(Tz, 20); grid;
StepinfoTz = stepinfo(Tz)

% Obtaining the DC Value, SS Error, the Ramp20 Error
ssval = dcgain(Tz)            % DC Gain
sserror_step = abs(1-ssval)             % Steady State Error
step2ramp = tf([T],[1 -1],T);           % Converts unit-step to unit-ramp 
ct = step(step2ramp*Tz,60);   % Generates c(t)
sserror_ramp20 = 20-ct(20/T)            % error = 20 - c(20)
