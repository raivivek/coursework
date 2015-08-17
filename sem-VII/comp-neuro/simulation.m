%%
% Run simulation of Van-der-pol oscillator with values of mu = 1, 21, .. ,
% 101.
%%

for i = 1:20:101
[x, y] = ode15s(@vdp, [0, 50], [0 ; 1], [], [i]);

% generate subplots framework
subplot(2,3, 1 + round(i/20));

% phase plane plot
 plot(y(:,1), y(:,2));

% temporal plot of y' and y
% plot(x,y);
end