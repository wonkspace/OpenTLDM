% Copyright 2011 Zdenek Kalal
%
% This file is part of TLD.
%
% TLD is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
%
% TLD is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
%
% You should have received a copy of the GNU General Public License
% along with TLD.  If not, see <http://www.gnu.org/licenses/>.

% Compiles mex files
clc; clear all; cd mex;

if ispc
    disp('PC');
    include = ' -IC:\OpenCV2.3\opencv\include\opencv\ -IC:\OpenCV2.3\build\include\ -IC:\OpenCV2.3\opencv\ -IC:\OpenCV2.3\mybuild\ -IC:\OpenCV2.3\opencv\include\ -IC:\OpenCV2.3\opencv\include\opencv\ -IC:\OpenCV2.3\opencv\modules\core\include\ -IC:\OpenCV2.3\opencv\modules\flann\include\ -IC:\OpenCV2.3\opencv\modules\imgproc\include\ -IC:\OpenCV2.3\opencv\modules\video\include\ -IC:\OpenCV2.3\opencv\modules\highgui\include\ -IC:\OpenCV2.3\opencv\modules\ml\include\ -IC:\OpenCV2.3\opencv\modules\calib3d\include\ -IC:\OpenCV2.3\opencv\modules\features2d\include\ -IC:\OpenCV2.3\opencv\modules\objdetect\include\ -IC:\OpenCV2.3\opencv\modules\legacy\include\ -IC:\OpenCV2.3\opencv\modules\contrib\include\';
    libpath = 'C:\OpenCV2.3\mybuild\lib\Release\';
    files = dir([libpath '*.lib']);
    
    lib = [];
    for i = 1:length(files),
        lib = [lib ' ' libpath files(i).name];
    end
    
    eval(['mex lk.cpp -O' include lib]);
    mex -O -c tld.cpp
    %mex -O fern.cpp tld.obj
    mex -v -g fern.cpp tld.obj
    mex -O linkagemex.cpp
    mex -O bb_overlap.cpp
    mex -O warp.cpp
    mex -O distance.cpp
end

if ismac
    disp('Mac');
    
    include = ' -I/opt/local/include/opencv/ -I/opt/local/include/'; 
    libpath = '/opt/local/lib/'; 
    
    files = dir([libpath 'libopencv*.dylib']);
    
    lib = [];
    for i = 1:length(files),
        lib = [lib ' ' libpath files(i).name];
    end
    
    eval(['mex lk.cpp -O' include lib]);
    mex -O -c tld.cpp
    mex -O fern.cpp tld.o
    mex -O linkagemex.cpp
    mex -O bb_overlap.cpp
    mex -O warp.cpp
    mex -O distance.cpp
    
end

if isunix
    disp('Unix');
    
%    include = ' -I/usr/local/include/opencv/ -I/usr/local/include/opencv2/';
%    libpath = '/usr/local/lib/';
    include = ' -I/usr/local/packages/opencv-2.4.5/include -I/usr/local/packages/opencv-2.4.5/include/opencv';
    libpath = '/usr/local/packages/opencv-2.4.5/lib/';
    
%    files = dir([libpath 'libopencv*.so']);
    files = dir([libpath 'libopencv*.so.2.4.5']);
    
    lib = [];
    for i = 1:length(files),
        lib = [lib ' ' libpath files(i).name];
    end
    
    eval(['mex lk.cpp -O' include lib]);
    mex -g -c tld.cpp
    mex -g fern.cpp tld.o
    mex -g linkagemex.cpp
    mex -g bb_overlap.cpp
    mex -g warp.cpp
    mex -g distance.cpp
    
end


cd ..
disp('Compilation finished.');

