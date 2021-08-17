clear;
clf;
fid = fopen('Mesh.txt');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
M= fscanf(fid,'%*i %f %f %f\n',[3 nps]);
ps=M(1:2,:);
rs=M(3,:);

string2=fgets(fid);
nts = fscanf(fid,'%i',1);
ts = fscanf(fid,'%*i %i %i %i \n',[3 nts])+1;

fclose(fid);

figure (1)
pdemesh(ps,ts);

hold on
for i=1:length(rs)
rectangle('Position',[ps(1,i)-rs(i),ps(2,i)-rs(i),2*rs(i),2*rs(i)], ...
    'Curvature', [1 1], 'EdgeColor','r');
end
axis off



