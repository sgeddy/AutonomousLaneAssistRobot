T=0.01;
Gz2=tf([-0.0001002 9.706e-5],[1 -1.998 1],T)
pidtool(Gz2)
%%
KP=-476.2742;
KI=-1908.5395;
KD=-25.7463;
TF=0.017256;
Dz_PIDF2 = KP + (KI*T)*tf([1],[1 -1],T) + KD*tf([1 -1],[TF -TF+T],T)
[Gm,Pm]=margin(Dz_PIDF2*Gz2); GmdB=20*log10(Gm), Pm
Tz2=feedback(Dz_PIDF2*Gz2,1);
StepinfoTz=stepinfo(Tz2)
ssval = dcgain(Tz2);
sserror=abs(1-ssval)
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp!
ct = step(step2ramp*Tz2,60); % Generates c(t)
sserror_ramp20 = 20-ct(20/T)  % ramp error at 20 seconds