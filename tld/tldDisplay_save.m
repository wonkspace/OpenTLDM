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

global n_object_tracked;

function tld = tldDisplay(varargin)
% Plots results

% jorgeb - ToDo - Confirm that condition 'varargin{1}==0' really is needed.
% initialize the plot
if varargin{1}==0
    
    tld = varargin{2};
    
    % jorgeb - This part never executes because tldDisplay is never called
    % with 3 arguments. Might there be a case in the future?
    if nargin == 3
    %    tld.handle = varargin{3};
    %    bb_draw(tld.source.bb, tld.source.bbfixed);
   
    
    % elseif ~isfield(tld,'handle') % jorgeb - replaced with following
    elseif isempty(tld.handle)
    
        
        tld.handle = imshow(tld.img{1}.input,'initialmagnification','fit');
        % jorgeb - Changed call to bb_draw
        %bb_draw(tld.source.bb, tld.source.bbfixed1, tld.source.bbfixed2);
        %bboxes = [tld.source.bb, tld.source.bbfixed1, tld.source.bbfixed2];
        %bboxes = tld.bounding_boxes;  % jorgeb - ToDo - Fix this
        bboxes = [tld.source.bb];
        bb_draw(bboxes);
        
        
        
        %set(gcf,'MenuBar','none','ToolBar','none','color',[0 0 0]);
        %set(gca,'position',[0 0 1 1]);
           
        %img = tld.img{1}.input;
        %img = embedPex(img,tld);
        %img = embedNex(img,tld);
        %set(tld.handle,'cdata',img);
        %hold on;
        
        %set(gcf,'Position',[100 100 [640 360]]);
        %set(gcf,'Position',[100 100 2*[320 240]+1]);

        % Info
        %string = [num2str(tld.control.maxbbox) '/' num2str(tld.nGrid)];
        %text(10,200,string,'color','white');
    end
    
    
    
else
    
    % jorgeb - Replaced multiple varargin entries with one array handling
    % all objects being tracked
    %tld = varargin{2};
    %tld2 = varargin{3};
    %tld3 = varargin{4};
    %i = tld.source.idx(varargin{5});
    tldarray = varargin{2};
    n_object_tracked = size(tldarray,2);
    tld = tldarray(:,1);
    tld2 = tldarray(:,2);
    tld3 = tldarray(:,3);
    i = tld.source.idx(varargin{3});
    
    
    h = get(gca,'Children'); delete(h(1:end-1));
    if nargin == 6, text(10,10,varargin{6},'color','white'); end
    
    % Draw image
    img = tld.img{i}.input;
    [H,W] = size(img);
 %{   
    % Pex
    if tld.plot.pex == 1
        img = embedPex(img,tld);
    end
    
    % Nex
    if tld.plot.nex == 1
        img = embedNex(img,tld);
    end
    %}
%{    
    % Target
    Size = 100;
    if tld.plot.target && ~isnan(tld.bb(1,i))
        bb = bb_rescale_relative(tld.bb(:,i),4*[1 1]);
        patch = img_patch(tld.img{i}.input,bb);
        patch = imresize(patch,[Size Size]);
        img(1:Size,1:Size) = patch;
    end
    %rectangle('Position',[0 0 400 400],'edgecolor','k');
    
    % Replace
    if tld.plot.replace && ~isnan(tld.bb(1,i))
        bb = round(tld.bb(:,i));
        if bb_isin(bb,size(tld.img{i}.input))
            patch = imresize(tld.target,[bb(4)-bb(2)+1, bb(3)-bb(1)+1]);
            img(bb(2):bb(4),bb(1):bb(3)) = patch;
        end
    end
 %}
    
    % jorgeb - ToDo - Determine if this needs to change. Do for each tld?
    if ishandle(tld.handle)
        set(tld.handle,'cdata',img); hold on;
    end
%{    
    % Draw Detections
    if tld.plot.dt && ~isempty(tld.dt{i})
        % Fern detections
        %bb = tld.dt{i}.bb(:,:); if tld.plot.confidence, bb = [bb; tld.dt{i}.conf1]; end
        %bb_draw(bb,'edgecolor',0.5*[1 1 1]);
        % NN detections
        %idx = tld.dt{i}.conf1 > tld.model.thr_nn;
        %bb = tld.dt{i}.bb(:,idx); if tld.plot.confidence, bb = [bb; tld.dt{i}.conf1(idx)]; end
        %bb_draw(bb,'edgecolor','red');
        cp = bb_center(tld.dt{i}.bb);
        if ~isempty(cp)
            plot(cp(1,:),cp(2,:),'.','color',0.25*[1 1 1]);
        end
        idx = tld.dt{i}.conf1 > tld.model.thr_nn;
        cp = bb_center(tld.dt{i}.bb(:,idx));
        if ~isempty(cp)
        plot(cp(1,:),cp(2,:),'.','color','red');
        end
    end
   %} 
   
    % Draw Track
    linewidth = 2; % jorgeb disabled this conditional: if tld.valid(i) == 1, linewidth = 4; end;
    color = 'y'; %if tld.conf(i) > tld.model.thr_nn_valid, color = 'b'; end
    
    bb = tld.bb(:,i);
    bb2 = tld2.bb(:,i);
    bb3 = tld3.bb(:,i);
    % jorgeb - ToDo - Confirm we should switch on tld.plot.drawoutput. What
    % does it refer to?
    switch tld.plot.drawoutput
        
        case 1
            % jorgeb - ToDo - Confirm rescale is required only with bb
            bb = bb_rescale_relative(bb_square(bb),[1.2 1.2]);
            if tld.plot.confidence, bb = [bb; tld.conf(i)]; end
            % jorgeb - Changed call to bb_draw
            %bb_draw(bb,bb2,bb3,'linewidth',linewidth,'edgecolor',color,'curvature',[1 1]);
            bboxes = [bb bb2 bb3];
            bb_draw(bboxes,'linewidth',linewidth,'edgecolor',color,'curvature',[1 1]);
        case 2
            cp = bb_center(bb);
            % plot(cp(1),cp(2),'.r','markersize',20);
            if tld.plot.confidence, text(cp(1),cp(2),num2str(tld.conf(i))); end
            %bb_draw(bb,'linewidth',linewidth,'edgecolor',color,'curvature',[1 1]);
        case 3
            % jorgeb replaced conditional with the three statements right
            % beneath.
            %if tld.plot.confidence, bb = [bb; tld.conf(i)]; end
            bb = [bb; tld.conf(i)];
            bb2 = [bb2; tld2.conf(i)];
            bb3 = [bb3; tld3.conf(i)];
            fprintf('n_object_tracked = %d\n', n_object_tracked);

            % jorgeb - Changed call to bb_draw
            %bb_draw(bb,bb2,bb3,'linewidth',linewidth,'edgecolor',color,'curvature',[0 0]);
            bboxes = [bb bb2 bb3];
            bb_draw(bboxes,'linewidth',linewidth,'edgecolor',color,'curvature',[0 0]);
    end
    
    % Info
    
    %string = ['#' num2str(i) ', fps:' num2str(1/toc,2) ', ' num2str(tld.control.maxbbox) '/' num2str(tld.nGrid) ', Fern: ' num2str(tld.model.thr_fern,4) ', NN: ' num2str(tld.model.thr_nn,3) '/' num2str(tld.model.thr_nn_valid,3)];
    string = ['#' num2str(i) ', fps:' num2str(1/toc,3) ', ' num2str(tld.control.maxbbox) '/' num2str(tld.nGrid)];
    text(10,H-10,string,'color','white','backgroundcolor','k');
    %if tld.control.update_detector
    %    text(10,H-30,'Learning','color','white','backgroundcolor','k');
    %end
    
    if tld.trackerfailure(i)==1
        text(10,H-30,'Tracker failure','color','white','backgroundcolor','k');
    end
    
    % Draw
    if tld.plot.draw
       plot(tld.draw(1,:),tld.draw(2,:),'r','linewidth',2);    
    end
    
       if tld.plot.pts
    %       plot(tld.xFJ(1,:),tld.xFJ(2,:),'.');
       end
    
       
    if tld.plot.help
        
        k = 12;
        text(10,1*k,'n ... shows negative examples in online model (default on)');
        text(10,2*k,'p ... shows positive examples in online model (default on)');
        text(10,3*k,'i ... initialization of different target');
        text(10,4*k,'c ... show confidence score (default on)');
        text(10,5*k,'o ... show output as circle/dot/no output (default circle)');
        text(10,6*k,'d ... show detections (default on)');
        text(10,7*k,'t ... show target in top left corner (default off)');
        text(10,8*k,'r ... replace target with first patch (default off)');
        text(10,9*k,'# ... draw trajectory of target (default off)');
        text(10,10*k,'1 ... mode without learning');
        text(10,11*k,'2 ... mode with learning');
        text(10,12*k,'q ... finish application');
        text(10,13*k,'space ... save current image');
        
    end
    
    
    drawnow;
    tic;
    
    % Save
    %if tld.plot.save == 1
    %    img = getframe(1);
    %    imwrite(img.cdata,[tld.name '/' num2str(i,'%05d') '.png']);
    %end
    
end
end

function img = embedPex(img,tld)
Rescale = tld.plot.patch_rescale;
no_row = floor(tld.imgsize(1)/(Rescale*tld.model.patchsize(1)));
no_col = floor(tld.imgsize(2)/(Rescale*tld.model.patchsize(2)));
if size(tld.pex,2) > no_row*no_col
    pex = mat2img(tld.pex(:,1:no_row*no_col),no_row);
else
    pex = mat2img(tld.pex,no_row);
end
pex = uint8(imresize(255*pex,Rescale));
[pH,pW] = size(pex);
img(1:pH,end-pW+1:end) = pex;

end

function img = embedNex(img,tld)
Rescale = tld.plot.patch_rescale;
no_row = floor(tld.imgsize(1)/(Rescale*tld.model.patchsize(1)));
no_col = floor(tld.imgsize(2)/(Rescale*tld.model.patchsize(2)));
if size(tld.nex,2) > no_row*no_col
    nex = mat2img(tld.nex(:,1:no_row*no_col),no_row);
else
    nex = mat2img(tld.nex,no_row);
end
nex = uint8(imresize(255*nex,Rescale));
[pH,pW] = size(nex);
img(1:pH,1:pW)= nex;

end
