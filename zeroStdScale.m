function scaledData = zeroStdScale(data)

maxData = max(data);
minData = min(data);
if maxData < 0 || minData > 0
    error("expected positive and negative values")
end

if maxData >= minData
    absmax = maxData;
else
    absmax = abs(minData);
end

if absmax ~= 0 
    scaledData = data / absmax;
else
    scaledData = data;
end
