clear;
clf;
fid = fopen('OptimizedNodes.txt');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
M= fscanf(fid,'%*i %f %f %f\n',[3 nps]);
ps=M(1:2,:);
rr=M(3,:);

string2=fgets(fid);
nts = fscanf(fid,'%i',1);
tss = fscanf(fid,'%*i %i %i %i \n',[3 nts])+1;

string3=fgets(fid);
nes = fscanf(fid,'%i',1);
MM = fscanf(fid,'%*i %i %i %i \n',[3 nes])+1;
es=MM(1:2,:);
ids=MM(3,:);
fclose(fid);

%DT = delaunayTriangulation(ps');
DT = delaunayTriangulation(ps',es');
TF = isInterior(DT);
ts=(DT.ConnectivityList(TF,:))';
%ts=(DT.ConnectivityList)';


figure (1)
pdemesh(ps,ts);

axis off

xs=ps(1,:);ys=ps(2,:);
t1=ts(1,:);t2=ts(2,:);t3=ts(3,:);
la=hypot(xs(t2)-xs(t1), ys(t2)-ys(t1));
lb=hypot(xs(t3)-xs(t1), ys(t3)-ys(t1));
lc=hypot(xs(t3)-xs(t2), ys(t3)-ys(t2));
rho=(lc+lb-la).*(lc+la-lb).*(la+lb-lc)./(la.*lb.*lc);

figure (3)
histogram(rho,0:0.1:1,'Normalization','probability');
set(gcf,'Position',[230 250 400 400]) ;
set(gca,'Position',[0.12 0.14 0.85 0.8]);
xlim([0 1]);
xlabel('mesh quality (radius ratio)','interpreter','latex');
ylabel('Percentage','interpreter','latex');
grid on


fileID = fopen('./Data/OptimizedMesh.txt','w');
fprintf(fileID,'Points\r\n');
np=size(ps,2);
fprintf(fileID,'%i \r\n',np);
fprintf(fileID,'%i \t %e \t %e \t %e \r\n', [1:np;ps;rr]);

fprintf(fileID,'Triangles\r\n');
nt=size(ts,2);
fprintf(fileID,'%i \r\n',nt);
fprintf(fileID,'%i \t %i \t %i \t %i \t \r\n', [1:nt ; ts-1]);

fprintf(fileID,'Edges\r\n');
ne=size(es,2);
fprintf(fileID,'%i \r\n',ne);
fprintf(fileID,'%i \t %i \t %i \t %i \r\n', [1:ne ; es-1; ids]);

fclose(fileID);

