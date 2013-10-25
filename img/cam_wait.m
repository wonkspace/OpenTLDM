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

% jorgeb
% Note: Function bb_draw has been redefined. Its call must be changed here
% for this function to execute properly.

function img = cam_wait(T,BB)
% Runs cam for T sec. and returns the last frame.

global vid;
tic;
while toc < T
    img = img_alloc(getsnapshot(vid));
    imshow(img.in);
    if exist('BB','var')
        bb_draw(BB,'EdgeColor','y','LineWidth',3); 
        %title(toc); 
        drawnow;
    end
end
