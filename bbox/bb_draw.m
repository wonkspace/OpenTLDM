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
% Note: Function bb_draw has been rewritten to accept an indefinite number
% of bounded boxes as input in an array. This breaks the current definition
% of functions cam_wait, test_face_detector, tldUpdateDetector, and
% tldUpdateDetectorConservative. However, these functions are not called so
% it does not matter for the moment.

% jorgeb - ToDo - Confirm whether other breakage occurs.

function bb_draw(bboxes, varargin)
% Draw

% jorgeb
% Specify the colors to use for the bounding boxes
color_codes  = ['y' 'b' 'g' 'r'];
modulus = size(color_codes, 2);  % Returns the number of colors (columns)

for j = 1:size(bboxes,2)  % Obtain the number of columns
    if ~isempty(bboxes(j))
        bbj = bboxes(:,j);
        idx = find(bb_isdef(bbj));
        color_index = mod(j,modulus) + 1;
        varargin = {'edgecolor',color_codes(color_index)};
        for i = 1:length(idx)
            bb = bbj(:,idx(i));
            fprintf('Fixed point #%d (%c): (%f, %f) (%f, %f)\n', j, color_codes(color_index), bb(1), bb(2), bb(3), bb(4));
            if bb(3)-bb(1) > 0 && bb(4)-bb(2)>0
                rectangle('Position',[bb(1) bb(2) bb(3)-bb(1) bb(4)-bb(2)],varargin{:});
                if size(bb,1) == 5
                    cp = bb_center(bb);
                    text(cp(1),cp(2),num2str(bb(5),3),'color',color_codes(color_index));
                end
            end
        end
   end
end

fprintf('\n');
       
end