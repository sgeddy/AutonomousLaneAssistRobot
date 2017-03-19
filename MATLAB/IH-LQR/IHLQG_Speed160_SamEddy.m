%% Problem 6:  IH-LQG (20 points): 

% For the system of Problem 3, derive an Infinite Horizon, 
% Linear Quadratic Gaussian (IH-LQG) controller for  
% Q = eye(2), and R = 0.8. 
clear all
T=0.01;
Gz=tf([0.0003315 -0.0002177],[1 -2.003 1.006], T);
[num,den]=tfdata(Gz, 'v'); [A,B,C,D]=tf2ss(num,den)
%% (a) Find the steady-state gain matrix K using MATLAB lqr.

Sys=ss(A,B,C,D,T);
Q = eye(2); R = .01; % Cost function
[K,S,e]=lqr(Sys,Q,R); K

%% (b) Find the G matrix for a Kalman state estimator assuming Rw=1, Rv=1, 
% M=eye(2), B1=[0;0], and N=20

Rw=5; Rv=10; M=eye(2); B1=[0;1200]; N=3000;
for k=1:N % Equations D5, D6, and D7
    G = M*C'*inv(C*M*C' + Rv);
    P = M - G*C*M;
    M = A*P*A' + B1*Rw*B1';
    [k,G'];
end
G

%% (c) Find Dce(z) and display in zpk format.

% Find the Dcez using Equation (9-73) for a Current Observer
syms z, Dcez = z*K*inv((z*eye(2)-A+G*C*A + B*K - G*C*B*K))*G;
[num,den]=numden(Dcez); 
num=sym2poly(num); 
den=sym2poly(den);
Dcez=tf(num,den,T);  Dcez=zpk(Dcez)

%% (d) Plot the step response.  What are the resulting Gm, Pm, 
% step-performance parameters, unit-step steady-state error, 
% and unit ramp error at 20 sec.? 

Tz = feedback(Dcez*Gz,1), step(Tz), grid
[Gm,Pm] = margin(Dcez*Gz); GmdB = 20*log10(Gm), Pm
StepinfoTz=stepinfo(Tz)
ssval = dcgain(Tz);
sserror=abs(1-ssval)
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp!
ct = step(step2ramp*Tz,60); % Generates c(t)
sserror_ramp20 = 20-ct(20/T)  % ramp error at 20 seconds