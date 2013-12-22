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
clc; clear all; cd mexhandle/objcreatedestroy;

if isunix
    disp('Unix');
    
    include = ' -I/usr/local/packages/opencv-2.4.5/include -I/usr/local/packages/opencv-2.4.5/include/opencv';
    libpath = '/usr/local/packages/opencv-2.4.5/lib/';
    
    mex -O mex_create.cpp 
    mex -O mex_destroy.cpp 
    
end


cd ..
disp('Compilation finished.');

