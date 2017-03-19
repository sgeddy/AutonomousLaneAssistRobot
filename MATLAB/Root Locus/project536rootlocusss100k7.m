% project536 root locus ss100


clc;
clear all;
clf;
T=0.01;
Gz=tf([0.00003636 -0.00001724],[1 -1.998 1],T);
[num,den] = tfdata(Gz,'v');
poles = roots(den)
zeros = roots(num)

 Kd =46200; 
 z1 = poles(1);  
 z2 = poles(2);  
 p1=1;
 p2=0.8;
 Dz = Kd*tf([1 -(z1+z2) (z1*z2)],[1 -(p1+p2) p1*p2],T);   

 DzGz = Dz*Gz;
 figure(1);
 rlocus(Gz,DzGz);
% rlocus(Gz);
grid; 
% axis([0 1.5 -1.2 1.2])




[Gm,Pm]=margin(Dz*Gz); GmdB=20*log10(Gm), Pm
Tz=feedback(Dz*Gz,1);
figure(2), step(Tz), grid
StepinfoTz=stepinfo(Tz)
ssval = dcgain(Tz);
sserror=abs(1-ssval)
step2ramp = tf([T],[1 -1],T); 
ct = step(step2ramp*Tz,60); 
sserror_ramp20 = 20-ct(20/T)  
axis([0 30 -1.2 1.2])
Tz