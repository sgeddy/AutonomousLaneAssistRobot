T=0.01;
Gz3=tf([0.002538 -0.002473],[1 -2.034 1.038],T)
pidtool(Gz3)
%%
KP=28.1731;
KI=103.0956;
KD=1.7305;
TF=0.014061;
Dz_PIDF3 = KP + (KI*T)*tf([1],[1 -1],T) + KD*tf([1 -1],[TF -TF+T],T)
[Gm,Pm]=margin(Dz_PIDF3*Gz3); GmdB=20*log10(Gm), Pm
Tz3=feedback(Dz_PIDF3*Gz3,1);
StepinfoTz=stepinfo(Tz3)
ssval = dcgain(Tz3);
sserror=abs(1-ssval)
step2ramp = tf([T],[1 -1],T); % Converts unit-step to unit-ramp!
ct = step(step2ramp*Tz3,60); % Generates c(t)
sserror_ramp20 = 20-ct(20/T)  % ramp error at 20 seconds