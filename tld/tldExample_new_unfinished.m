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

function [bb,conf] = tldExample(opt)

global tld; % holds results and temporal variables
%global tld2;
%global tld3;
% jorgeb - Note reference to tld in other/init_workspace.m
global num_tracked; % jorgeb - Total number of objects tracked

% INITIALIZATION ----------------------------------------------------------

opt.source = tldInitSource(opt.source); % select data source, camera/directory

figure(2); set(2,'KeyPressFcn', @handleKey); % open figure for display of results
finish = 0; function handleKey(~,~), finish = 1; end % by pressing any key, the process will exit

while 1
    source = tldInitFirstFrame(tld,opt.source,opt.model.min_win); % get initial bounding box, return 'empty' if bounding box is too small
    if ~isempty(source), opt.source = source; break; end % check size
end

% fprintf('bb2: (%f, %f) (%f, %f)\n', source.bbfixed(1), source.bbfixed(2), source.bbfixed(3), source.bbfixed(4));

% tld2.source.bb = source.bbfixed;

%num_tracked = 0;
%opt.id = 0;
%tld = tldInit(opt,[]); % train initial detector and initialize the 'tld' structure
%num_tracked = num_tracked + 1;
%opt2 = opt;
%opt2.id = 1;
%opt2.source.bb = source.bbfixed1;
%tld2 = tldInit(opt2, []);
%num_tracked = num_tracked + 1;
%opt3 = opt;
%opt3.id = 2;
%opt3.source.bb = source.bbfixed2;
%tld3 = tldInit(opt3, []);
%num_tracked = num_tracked + 1;

num_tracked = 0;
for i = 1:3  % jorgeb - ToDo - Remove hardwired value
    opt.id = i-1;
    tld = tldInit(opt,[]); % train initial detector and initialize the 'tld' structure
    % jorgeb - To resolve 'struct to double' conversion problem I made
    % tlda non-global. Confirm this is alright.
    tld.handle = ''; % jorgeb - add all fields to tld right up front
    tld.xFj = '';    % jorgeb - add all fields to tld right up front
    tlda(1,i) = tld;
    num_tracked = num_tracked + 1;
end

tld = tlda(1,1); % jorgeb - Remove once the switch to tlda is completed?

% jorgeb - Question - Note only tld is used here. Is this fine because all 
% objects are on the same display?
%tld = tldDisplay(0,tld); % initialize display
tld = tldDisplay(0,tld); % initialize display  % jorgeb - Replace tld
tlda(1,1) = tld;     % jorgeb - tlda and tldarray have different structs?

%fprintf('tld.bb = (%f, %f) (%f, %f)\n', tld.bb(1), tld.bb(2), tld.bb(3), tld.bb(4));
%fprintf('tld2.bb = (%f, %f) (%f, %f)\n', tld2.bb(1), tld2.bb(2), tld2.bb(3), tld2.bb(4));
fprintf('tlda(1,1).bb = (%f, %f) (%f, %f)\n', tlda(1,1).bb(1), tlda(1,1).bb(2), tlda(1,1).bb(3), tlda(1,1).bb(4));
fprintf('tlda(1,2).bb = (%f, %f) (%f, %f)\n', tlda(1,2).bb(1), tlda(1,2).bb(2), tlda(1,2).bb(3), tlda(1,2).bb(4));
fprintf('tlda(1,3).bb = (%f, %f) (%f, %f)\n', tlda(1,3).bb(1), tlda(1,3).bb(2), tlda(1,3).bb(3), tlda(1,3).bb(4));
%tld2 = tldDisplay(0, tld2, tld.handle);

% RUN-TIME ----------------------------------------------------------------

%for i = 2:length(tld.source.idx) % for every frame
for i = 2:length(tlda(1,1).source.idx) % for every frame
 %   fprintf('\nFixed point: (%f, %f) (%f, %f)\n', tld2.source.bb(1), tld2.source.bb(2), tld2.source.bb(3), tld2.source.bb(4));

    % jorgeb - ToDo - Replace the tlds with tlda elements?

    %tld = tldProcessFrame(tld, i); % process frame i
    %tld2 = tldProcessFrame(tld2,i);
    %tld3 = tldProcessFrame(tld3,i);
    tld = tldProcessFrame(tld, i); % process frame i
    tlda(1,1) = tld;
    tlda(1,2) = tldProcessFrame(tlda(1,2), i);
    tlda(1,3) = tldProcessFrame(tlda(1,3), i);
    
    % jorgeb - ToDo - Replace individual tlds with tlda
    %tldDisplay(1,tld,tld2,tld3,i); % display results on frame i
    tldDisplay(1,tlda(1,1),tlda(1,2),tlda(1,3),i); % display results on frame i
%    hold on;
   % tld2 = tldDisplay(1,tld2,i);
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
   %{
    idx = find(bb_isdef(tld.bb));
    bb = (tld.bb(:,i));
    bb = bb(:,idx(1));
    fprintf('Robot: (%f, %f) (%f, %f)\n', bb(1), bb(2), bb(3), bb(4));
    
    idx = find(bb_isdef(tld2.bb));
    bb = (tld2.bb(:,i));
    bb = bb(:,idx(1));
    fprintf('Fixed point1: (%f, %f) (%f, %f)\n', bb(1), bb(2), bb(3), bb(4));
    
    idx = find(bb_isdef(tld3.bb));
    bb = (tld3.bb(:,i));
    bb = bb(:,idx(1));
    fprintf('Fixed point2: (%f, %f) (%f, %f)\n\n', bb(1), bb(2), bb(3), bb(4));
    %}
        
    
end

bb = tlda(1,1).bb; conf = tlda(1,1).conf; % return results  % jorgeb - ToDo - Alright to just return the first tld?

end
