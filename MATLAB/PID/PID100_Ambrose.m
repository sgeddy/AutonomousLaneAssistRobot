T=0.01;
Gz1=tf([3.636e-5 -1.724e-5],[1 -1.998 1],T)
pidtool(Gz1)
%%
KP=2512.0487;
KI=6794.3394;
KD=209.756;
TF=0.016432;
%prop=KP
%int=(KI*T)*tf([1],[1 -1],T)
%diff=KD*tf([1 -1],[TF -TF+T],T)
Dz_PIDF1 = KP + (KI*T)*tf([1],[1 -1],T) + KD*tf([1 -1],[TF -TF+T],T)
[Gm,Pm]=margin(Dz_PIDF1*Gz1); GmdB=20*log10(Gm), Pm
Tz1=feedback(Dz_PIDF1*Gz1,1);
StepinfoTz=stepinfo(Tz1)
ssval = dcgain(Tz1);
sserror=abs(1-ssval)
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp!
ct = step(step2ramp*Tz1,60); % Generates c(t)
sserror_ramp20 = 20-ct(20/T)  % ramp error at 20 seconds
