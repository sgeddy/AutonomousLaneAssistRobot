syms z
T = 0.01;
N = 4; %Number of transfer functions

%TF for setspeed 160
num160 = [0.0003315 -0.0002177];
den160 = [1 -2.003 1.006];
Gz160 = tf(num160,den160,T);
%Gz160 = SIz;
% num160 = [-0.0009748 0.001136];
% den160 = [1 -2.002 1.005];

%TF for setspeed 140
num140 = [0.002538 -0.002473];
den140 = [1 -2.034 1.038];
Gz140 = tf(num140,den140,T);

%TF for setspeed 120
num120 = [-0.0001002 0.00009706];
den120 = [1 -1.998 1];
Gz120 = tf(num120,den120,T);

%TF for setspeed 100
num100 = [0.00003636 -0.00001724];
den100 = [1 -1.998 1];
Gz100 = tf(num100,den100,T);

Gz = [Gz160 Gz140 Gz120 Gz100];

A160 = 0.85; %Real pole location 0.96034
B160 = 0.05225; %Imaginary pole location 0.05225
desDen160 = [A160+j*B160 A160-j*B160]; %Preferred poles
[A,B,C,D] = tf2ss(num160,den160); %Getting State space of our plant
K160 = acker(A,B,desDen160); %Ackermans formula to get K
desDen160PO=0.1.*desDen160;
G160 = acker(A',C',desDen160PO)'; %Prediction observer
Dz160=K160*inv(z*eye(2)-A+B*K160+G160*C)*G160;
[num160PO, den160PO] = nicer(Dz160,z);
Dz160 = tf(num160PO,den160PO,0.01)
DzGz160 = Dz160*Gz160;
Tz160 = feedback(DzGz160,1);
 figure(1)
 step(Tz160)
%  figure(2)
% rlocus(DzGz160)

% for i=1:N
%     
% end
