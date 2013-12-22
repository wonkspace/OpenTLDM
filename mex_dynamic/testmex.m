[r,w] = unix('free | grep Mem');
stats = str2double(regexp(w, '[0-9]*', 'match'));
memsize = stats(1)/1e6
freemem = (stats(3)+stats(end))/1e6
input('Press return...')
for i=0:1000
	mexcpp(i,floor(rand*10),floor(rand*10))
end
[r,w] = unix('free | grep Mem');
stats = str2double(regexp(w, '[0-9]*', 'match'));
memsize = stats(1)/1e6
freemem = (stats(3)+stats(end))/1e6

exit
