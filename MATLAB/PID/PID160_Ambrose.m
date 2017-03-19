T=0.01;
Gz4=tf([0.0003315 -0.0002177],[1 -2.003 1.006],T)
pidtool(Gz4)
%%
KP=42.0247;
KI=68.102;
KD=6.1697;
TF=0.013659;
Dz_PIDF4 = KP + (KI*T)*tf([1],[1 -1],T) + KD*tf([1 -1],[TF -TF+T],T)
[Gm,Pm]=margin(Dz_PIDF4*Gz4); GmdB=20*log10(Gm), Pm
Tz4=feedback(Dz_PIDF4*Gz4,1);
StepinfoTz=stepinfo(Tz4)
ssval = dcgain(Tz4);
sserror=abs(1-ssval)
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp!
ct = step(step2ramp*Tz4,60); % Generates c(t)
sserror_ramp20 = 20-ct(20/T)  % ramp error at 20 seconds