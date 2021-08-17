clear;
clf;
fid = fopen('OptimizedNodes.txt');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
M= fscanf(fid,'%*i %f %f %f\n',[3 nps]);
ps=M(1:2,:);
rs=M(3,:);

string2=fgets(fid);
nts = fscanf(fid,'%i',1);
ts = fscanf(fid,'%*i %i %i %i \n',[3 nts])+1;

string3=fgets(fid);
nes = fscanf(fid,'%i',1);
MM = fscanf(fid,'%*i %i %i %i \n',[3 nes]);
es=MM(1:2,:)+1;
ids=MM(3,:);
fclose(fid);



figure (1)
pdemesh(ps,ts);
hold on
for i=1:length(rs)
rectangle('Position',[ps(1,i)-rs(i),ps(2,i)-rs(i),2*rs(i),2*rs(i)], ...
    'Curvature', [1 1], 'EdgeColor','r');
end

% hold on
% x_es=reshape(ps(1,es), size(es));
% y_es=reshape(ps(2,es), size(es));
% plot(x_es,y_es,'r');
axis off equal


% DT = delaunayTriangulation(ps',es');
% TF = isInterior(DT);
% ts=(DT.ConnectivityList(TF,:))';
% 
% figure (2)
% pdemesh(ps,ts);
% hold on
% for i=1:length(rs)
% rectangle('Position',[ps(1,i)-rs(i),ps(2,i)-rs(i),2*rs(i),2*rs(i)], ...
%     'Curvature', [1 1], 'EdgeColor','r');
% end
% axis off
% 
% xs=ps(1,:);ys=ps(2,:);
% t1=ts(1,:);t2=ts(2,:);t3=ts(3,:);
% la=hypot(xs(t2)-xs(t1), ys(t2)-ys(t1));
% lb=hypot(xs(t3)-xs(t1), ys(t3)-ys(t1));
% lc=hypot(xs(t3)-xs(t2), ys(t3)-ys(t2));
% rho=(lc+lb-la).*(lc+la-lb).*(la+lb-lc)./(la.*lb.*lc);
% 
% figure (3)
% histogram(rho,0:0.1:1,'Normalization','probability');
% set(gcf,'Position',[230 250 400 400]) ;
% set(gca,'Position',[0.14 0.14 0.85 0.8]);
% xlim([0 1]);
% xlabel('mesh quality (radius ratio)','interpreter','latex');
% ylabel('Percentage','interpreter','latex');
% grid on






