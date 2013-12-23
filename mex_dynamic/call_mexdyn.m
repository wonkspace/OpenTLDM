[r,w] = unix('free | grep Mem');
stats = str2double(regexp(w, '[0-9]*', 'match'));
memsize = stats(1)/1e6
freemem = (stats(3)+stats(end))/1e6
input('Press return...')

% Create the C++ objects in the mex file call
mexdyn(0,100)

% Destroy the C++ object in this mex file call
mexdyn(1)

[r,w] = unix('free | grep Mem');
stats = str2double(regexp(w, '[0-9]*', 'match'));
memsize = stats(1)/1e6
freemem = (stats(3)+stats(end))/1e6

exit
