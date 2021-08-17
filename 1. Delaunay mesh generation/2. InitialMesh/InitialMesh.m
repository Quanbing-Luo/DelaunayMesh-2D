clear;
clf;
fid = fopen('Geometry.txt');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
M1= fscanf(fid,'%*i %f %f %f\n',[3 nps]);
ps= M1(1:2,:); rs= M1(3,:);

string3=fgets(fid);
nes = fscanf(fid,'%i',1);
M3 = fscanf(fid,'%*i %i %i %i \n',[3 nes]);
es=M3(1:2,:)+1;
ids=M3(3,:);
fclose(fid);

%DT = delaunayTriangulation(ps');
DT = delaunayTriangulation(ps',es');
TF = isInterior(DT);
ts=(DT.ConnectivityList(TF,:))';

figure (1)
pdemesh(ps,ts);
hold on  

hold on
for i=1:length(rs)
rectangle('Position',[ps(1,i)-rs(i),ps(2,i)-rs(i),2*rs(i),2*rs(i)], ...
    'Curvature', [1 1], 'EdgeColor','r');
end
axis equal off

fileID = fopen('./Data/InitialMesh.txt','w');
fprintf(fileID,'Points\r\n');
np=size(ps,2);
fprintf(fileID,'%i \r\n',np);
fprintf(fileID,'%i \t %e \t %e \t %e \r\n', [1:np; ps; rs]);

fprintf(fileID,'Triangles\r\n');
nt=size(ts,2);
fprintf(fileID,'%i \r\n',nt);
fprintf(fileID,'%i \t %i \t %i \t %i \t \r\n', [1:nt ; ts-1]);

fprintf(fileID,'Edges\r\n');
ne=size(es,2);
fprintf(fileID,'%i \r\n',ne);
fprintf(fileID,'%i \t %i \t %i \t %i \r\n', [1:ne ; es-1; ids]);

fclose(fileID);



