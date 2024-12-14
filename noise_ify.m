function noisyData = noise_ify(data)

range = mean(abs(data));
threshold = 0.25;



% Add uniform noise
noisyData = data + (2*threshold*range) * rand(size(data)) -(threshold * range);