clear;
clf;
fid = fopen('Geometry.txt');
string1=fgets(fid);
n_ps = fscanf(fid,'%i',1);
Mp= fscanf(fid,'%*i %f %f %f\n',[3 n_ps]);
ps= Mp(1:2,:); rs= Mp(3,:);

string3=fgets(fid);
n_es = fscanf(fid,'%i',1);
es = fscanf(fid,'%*i %i %i %*i \n',[2 n_es])+1;
fclose(fid);

x_es=reshape(ps(1,es), size(es));
y_es=reshape(ps(2,es), size(es));
%y_es=ps(2,es);

figure (1)
plot(x_es,y_es,'r');
hold on
plot(x_es,y_es,'.k');

hold on
for i=1:length(rs)
rectangle('Position',[ps(1,i)-rs(i),ps(2,i)-rs(i),2*rs(i),2*rs(i)], ...
    'Curvature', [1 1], 'EdgeColor','r');
end


axis equal off


