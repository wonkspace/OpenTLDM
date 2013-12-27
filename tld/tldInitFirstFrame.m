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

% jorgeb - ToDo - tldInitFirstFrame needs to be passed tldarray, not tld.
function source = tldInitFirstFrame(tld,source,min_win,n_object_tracked)

% load the first frame into memory
source.im0  = img_get(source,source.idx(1));

% set the initial bounding box: 
% - from file
if source.camera == 0 && exist([source.input '/init.txt'],'file')
    bb = dlmread([source.input '/init.txt']);
    source.bb = bb(:);
    
    % check
    if isempty(source.bb) || min(bb_size(source.bb)) < min_win
        exit('Error: bounding box is incorrectly defined or too small');
    end
% - by mouse    
else
    % jorgeb - Modified call to bb_click. ToDo - Replace bbfixedX variables
    %[source.bb, source.bbfixed1, source.bbfixed2] = bb_click(tld,source.im0.input);
    bounding_boxes = bb_click(tld,source.im0.input,n_object_tracked);
    source.bb = bounding_boxes(:,1);
    %source.bbfixed1 = bounding_boxes(:,2);
    %source.bbfixed2 = bounding_boxes(:,3);
    source.bounding_boxes = bounding_boxes;
 %   tld2.source.bb = source.bbfixed;
    
    % check
    if isempty(source.bb) || min(bb_size(source.bb)) < min_win
       disp('ERROR: Bounding box too small');
       source = [];
    end
end


