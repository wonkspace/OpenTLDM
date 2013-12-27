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


function [bb,conf] = tldExample(opt,n_object_tracked)


global tld; % holds results and temporal variables


% INITIALIZATION ----------------------------------------------------------

opt.source = tldInitSource(opt.source); % select data source, camera/directory

figure(2); set(2,'KeyPressFcn', @handleKey); % open figure for display of results
finish = 0; function handleKey(~,~), finish = 1; end % by pressing any key, the process will exit

while 1
    source = tldInitFirstFrame(tld,opt.source,opt.model.min_win,n_object_tracked); % get initial bounding box, return 'empty' if bounding box is too small
    if ~isempty(source), opt.source = source; break; end % check size
end

% jorgeb - Number of objects being tracked
%n_object_tracked = size(source.bounding_boxes, 2);
%fprintf('No. tracked: %d\n',n_object_tracked);
%fields = initialize_fields(fields, n_object_tracked);      % jorgeb
%initialize_fields(n_object_tracked);                        % jorgeb

%for i = 1:n_object_tracked
%    opt.id = i-1;
    % jorgeb - ToDo - Replace conditional to handle arbitrary number of
    % objects
%    if i == 1
        %opt.source.bb = source.bb;
%        opt.source.bb = source.bounding_boxes(:,1);
%    elseif i == 2
        %opt.source.bb = source.bbfixed1;
%        opt.source.bb = source.bounding_boxes(:,2);
%    elseif i == 3
        %opt.source.bb = source.bbfixed2;
%        opt.source.bb = source.bounding_boxes(:,3);
%    end
%    tld = tldInit(opt,[]); % train initial detector and initialize the 'tld' structure
%
%    tlda(1,i) = tld;
%end

for i = 1:n_object_tracked
    opt.id = i-1;
    opt.source.bb = source.bounding_boxes(:,i);
    tld = tldInit(opt,[],n_object_tracked); % train initial detector and initialize the 'tld' structure

    tlda(1,i) = tld;
end

tld = tlda(1,1); % jorgeb - Remove once the switch to tlda is completed?

% jorgeb - Question - Note only tld is used here. Is this fine because all 
% objects are on the same display? Is this even necessary for handling
% multiple objects?
tld = tldDisplay(0,tld,n_object_tracked); % initialize display
tlda(1,1) = tld;     % jorgeb - Is this right and needed?

fprintf('tlda(1,1).bb = (%f, %f) (%f, %f)\n', tlda(1,1).bb(1), tlda(1,1).bb(2), tlda(1,1).bb(3), tlda(1,1).bb(4));
fprintf('tlda(1,2).bb = (%f, %f) (%f, %f)\n', tlda(1,2).bb(1), tlda(1,2).bb(2), tlda(1,2).bb(3), tlda(1,2).bb(4));
fprintf('tlda(1,3).bb = (%f, %f) (%f, %f)\n', tlda(1,3).bb(1), tlda(1,3).bb(2), tlda(1,3).bb(3), tlda(1,3).bb(4));

% RUN-TIME ----------------------------------------------------------------

for i = 2:length(tlda(1,1).source.idx) % for every frame
    % jorgeb - Process each tracked object
    for j = 1:n_object_tracked
        tlda(1,j) = tldProcessFrame(tlda(1,j), i); % process frame i
    end
    
    % jorgeb - Need to change this to allow tracking any number of objects
    %tldDisplay(1,tlda(1,1),tlda(1,2),tlda(1,3),i); % display results on frame i
    tldDisplay(1,tlda,i); % display results on frame i

    if finish % finish if any key was pressed
        if tlda(1,1).source.camera
            stoppreview(tlda(1,1).source.vid);
            closepreview(tlda(1,1).source.vid);
             close(1);
        end
        close(2);
        bb = tlda(1,1).bb; conf = tlda(1,1).conf; % return results
        return;
    end
    
    if tlda(1,1).plot.save == 1
        img = getframe;
        imwrite(img.cdata,[tlda(1,1).output num2str(i,'%05d') '.png']);
    end

end

bb = tlda(1,1).bb; conf = tlda(1,1).conf; % return results  % jorgeb - ToDo - Alright to just return the first tld?

end
