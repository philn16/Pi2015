function [ signal ] = MakeBinary( signal )
signal = signal - min(signal);
NominalHigh = 0.6; % anything equal or above this max ratio is seen as a 1
maximum = max(signal);
signal = (signal > maximum * NominalHigh);
end

