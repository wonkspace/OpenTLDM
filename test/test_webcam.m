% jorgeb - Replaced the following videoinput line with the next one
%          based on output from imaqhwinfo, which provided the adaptor
%          name 'linuxvideo', and imaqhwinfo('linuxvideo',1), which
%          provided the format name 'YUYV_640x480'.
%obj    = videoinput('winvideo', 1, 'RGB24_320x240'); 
obj = videoinput('linuxvideo', 1,'YUYV_640x480');

vidRes = get(obj, 'VideoResolution'); 
nBands = get(obj, 'NumberOfBands'); 
hImage = image( zeros(vidRes(2), vidRes(1), nBands) ); 
preview(obj, hImage); 
