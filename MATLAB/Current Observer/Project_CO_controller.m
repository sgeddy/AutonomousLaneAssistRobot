%a)
digits(8), T=0.01;
syms z;

gz160=tf([.02556 -.02105], [1 -2.02 1.021], T);
gz140=tf([.002538 -.002473], [1 -2.034 1.038], T);
gz120=tf([-.0001002 9.706e-05],[1 -1.998 1], T);
gz100=tf([3.636e-05 -1],[1 -1.998 1], T);
%----------------------------------------------------------------
[Ad,Bd,Cd,Dd]=ssdata(gz160);
P=[8 8;8 7];
A=inv(P)*Ad*P; B=inv(P)*Bd; C=Cd*P; D=Dd;
r=pole(gz160);
a=0.9; b=0.85;
P=[a*r(1) b*r(2)]; 
K=acker(A,B,P)


%b)
Perr=.5*P;
G=acker(A',(C*A)',Perr)' ;%Note the transposes
% Merge the state equations (Eqn 9-74)
Areg=[A -B*K;G*C*A A-G*C*A-B*K];
% Check the results	
eig(Areg);
%c)
% Find the Dcez using Equation (9-73) for a Current Observer
syms z, Dcez = z*K*inv((z*eye(2)-A+G*C*A + B*K - G*C*B*K))*G

[num,den]=numden(Dcez); 
num=sym2poly(num); 
den=sym2poly(den);
Dcez160=tf(num,den,T)
Dcez160=zpk(Dcez160);

%d)
Tz160 = feedback(Dcez160*gz160,1); 
hold on
step(Tz160), grid
Margins = allmargin(Dcez160*gz160);
Gm = Margins.GainMargin; GmdB = 20*log10(Gm);
Pm = Margins.PhaseMargin;
StepinfoTz=stepinfo(Tz160)
ssval = dcgain(Tz160);
sserror=abs(1-ssval);
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp! 
ct = step(step2ramp*Tz160,60); % Generates c(t) 
sserror_ramp = 20-ct(20/T);

%--------------------------------------------------------------
[Ad,Bd,Cd,Dd]=ssdata(gz140);
P=[8 8;8 7];
A=inv(P)*Ad*P; B=inv(P)*Bd; C=Cd*P; D=Dd;
r=pole(gz140);
a=0.9; b=0.85;
P=[a*r(1) b*r(2)]; 
K=acker(A,B,P);


%b)
Perr=.5*P;
G=acker(A',(C*A)',Perr)'; %Note the transposes
% Merge the state equations (Eqn 9-74)
Areg=[A -B*K;G*C*A A-G*C*A-B*K];
% Check the results	
eig(Areg);
%c)
% Find the Dcez using Equation (9-73) for a Current Observer
syms z, Dcez = z*K*inv((z*eye(2)-A+G*C*A + B*K - G*C*B*K))*G;

[num,den]=numden(Dcez); 
num=sym2poly(num); 
den=sym2poly(den);
Dcez140=tf(num,den,T) 
Dcez140=zpk(Dcez140);

%d)
Tz140 = feedback(Dcez140*gz140,1);
hold on
step(Tz140), grid
Margins = allmargin(Dcez140*gz140);
Gm = Margins.GainMargin; GmdB = 20*log10(Gm);
Pm = Margins.PhaseMargin;
StepinfoTz=stepinfo(Tz140);
ssval = dcgain(Tz140);
sserror=abs(1-ssval);
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp! 
ct = step(step2ramp*Tz140,60); % Generates c(t) 
sserror_ramp = 20-ct(20/T);

%------------------------------------------------------------------
[Ad,Bd,Cd,Dd]=ssdata(gz120);
P=[8 8;8 7];
A=inv(P)*Ad*P; B=inv(P)*Bd; C=Cd*P; D=Dd;
r=pole(gz120);
a=0.9; b=0.85;
P=[a*r(1) b*r(2)]; 
K=acker(A,B,P);


%b)
Perr=.5*P;
G=acker(A',(C*A)',Perr)' ;%Note the transposes
% Merge the state equations (Eqn 9-74)
Areg=[A -B*K;G*C*A A-G*C*A-B*K];
% Check the results	
eig(Areg);
%c)
% Find the Dcez using Equation (9-73) for a Current Observer
syms z, Dcez = z*K*inv((z*eye(2)-A+G*C*A + B*K - G*C*B*K))*G;

[num,den]=numden(Dcez); 
num=sym2poly(num); 
den=sym2poly(den);
Dcez120=tf(num,den,T) 
Dcez120=zpk(Dcez120);

%d)
Tz120 = feedback(Dcez120*gz120,1); 
step(Tz120), grid
Margins = allmargin(Dcez120*gz120);
Gm = Margins.GainMargin; GmdB = 20*log10(Gm);
Pm = Margins.PhaseMargin;
StepinfoTz=stepinfo(Tz120);
ssval = dcgain(Tz120);
sserror=abs(1-ssval);
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp! 
ct = step(step2ramp*Tz120,60); % Generates c(t) 
sserror_ramp = 20-ct(20/T);
%------------------------------------------------------

[Ad,Bd,Cd,Dd]=ssdata(gz100);
P=[8 8;8 7];
A=inv(P)*Ad*P; B=inv(P)*Bd; C=Cd*P; D=Dd;
r=pole(gz100);
a=0.9; b=0.85;
P=[a*r(1) b*r(2)]; 
K=acker(A,B,P);


%b)
Perr=.5*P;
G=acker(A',(C*A)',Perr)' ;%Note the transposes
% Merge the state equations (Eqn 9-74)
Areg=[A -B*K;G*C*A A-G*C*A-B*K];
% Check the results	
eig(Areg);
%c)
% Find the Dcez using Equation (9-73) for a Current Observer
syms z, Dcez = z*K*inv((z*eye(2)-A+G*C*A + B*K - G*C*B*K))*G;

[num,den]=numden(Dcez); 
num=sym2poly(num); 
den=sym2poly(den);
Dcez100=tf(num,den,T) 
Dcez100=zpk(Dcez100);

%d)
Tz100 = feedback(Dcez100*gz100,1); 
step(Tz100), grid
legend('Tz160','Tz140','Tz120','Tz100')
Margins = allmargin(Dcez100*gz100);
Gm = Margins.GainMargin; GmdB = 20*log10(Gm);
Pm = Margins.PhaseMargin;
StepinfoTz=stepinfo(Tz100);
ssval = dcgain(Tz100);
sserror=abs(1-ssval);
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp! 
ct = step(step2ramp*Tz100,60); % Generates c(t) 
sserror_ramp = 20-ct(20/T);