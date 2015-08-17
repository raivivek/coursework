%%
% Van der pol oscillator equations.
% Function vdp accepts three arguments namely, time, [y'; y], and mu.

%%
function zprime = vdp (t, y, mu)
% y(1) = y', y(2) = y
zprime = zeros(2,1);
zprime(1) = mu(1) * (1-y(2)^2) * y(1) - y(2)/mu(1);
zprime(2) = mu(1) * y(1);