%Siso Lead Controller by Rutuja Chaturbhuj.

% Sisotool for TF1:  
%SS=160 Kp=23 

% Tz = tf([0.02556 -0.02105],[1 -1.994 1],0.01)
% Gz=Tz/(1-Tz)
% Gz1=zpk(Gz)
 T=0.01;
 Gz_1=23*tf([0.0003315 -0.0002177],[1 -2.003 1.006],0.01)
 Gz_1=zpk(Gz_1)
 %sisotool(Gz_1);
% 
z0 = 0.3; zp = 0.07; a0 = 100;
Kd = a0*(1-zp)/(1-z0);
Dz_lead_1 = Kd*tf([1 -z0],[1 -zp],T)
Dz_lead_1=zpk(Dz_lead_1)
%step(Dz_lead);
Tz_1=feedback(Gz_1*Dz_lead_1,1)
%step(Tz_final)

% System 2: Kprop = 15, SS=140

 Gz_2=15*tf([0.002538 -0.002473],[1 -2.034 1.038],0.01)
 Gz_2=zpk(Gz_2)
 %sisotool(Gz_1);
% 
z0 = 0.3; zp = 0.3; a0 = 21.5;
Kd = a0*(1-zp)/(1-z0);
Dz_lead_2 = Kd*tf([1 -z0],[1 -zp],T)
Dz_lead_2=zpk(Dz_lead_2)
%step(Dz_lead);
Tz_2=feedback(Gz_2*Dz_lead_2,1)
%step(Tz_final)




% SS=100 KProp=7
 Gz_3=7*tf([3.636e-05 -1.724e-05],[1 -1.998 1],0.01);
 Gz_3=zpk(Gz_3)
 %sisotool(Gz_1);
% 
z0 = 0.968; zp = 0.009; a0 = 100;
Kd = a0*(1-zp)/(1-z0);
Dz_lead_3 = Kd*tf([1 -z0],[1 -zp],T)
Dz_lead_3=zpk(Dz_lead_3)
%step(Dz_lead);
Tz_3=feedback(Gz_3*Dz_lead_3,1)
%step(Tz_final)

step(Tz_1,Tz_2,Tz_3);
stepinfo(Tz_2);


