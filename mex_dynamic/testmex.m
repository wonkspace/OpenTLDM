[r,w] = unix('free | grep Mem');
stats = str2double(regexp(w, '[0-9]*', 'match'));
memsize = stats(1)/1e6
freemem = (stats(3)+stats(end))/1e6
input('Press return...')

mexcpp(0,10)
%mexcpp(1)

[r,w] = unix('free | grep Mem');
stats = str2double(regexp(w, '[0-9]*', 'match'));
memsize = stats(1)/1e6
freemem = (stats(3)+stats(end))/1e6

exit
