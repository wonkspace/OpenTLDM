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

% jorgeb - ToDo - bb_click needs tlda as an argument, not tld.
% The size of tlda will provide the number of bounding boxes.

function bounding_boxes = bb_click(tld,img,n_object_tracked)
% Create

% jorgeb - Added (~isempty(tld.handle)) to conditional below
if (isfield(tld,'handle') && (~isempty(tld.handle)))
     h = get(gca,'Children'); delete(h(1:end-1));
    set(tld.handle,'cdata',img);
else
    imshow(img);
end
text(10,10,'Select objects to track','color','red');
%bounding_boxes = zeros(4,3); % jorgeb - ToDo - Remove hardwired values


for i = 1:n_object_tracked   % jorgeb - ToDo - Remove hardwired values
    h = imrect;   % jorgeb - Create draggable rectangle interactively
    p = wait(h);  % jorgeb - Wait until data acquisition on object h is complete
    bounding_boxes(:,i) = [p(1); p(2);p(1)+p(3); p(2)+p(4)];
end