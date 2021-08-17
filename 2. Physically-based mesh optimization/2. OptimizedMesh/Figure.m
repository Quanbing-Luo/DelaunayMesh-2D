clear;
clf;
fid = fopen('OptimizedMesh.txt');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
M= fscanf(fid,'%*i %f %f %f\n',[3 nps]);
ps=M(1:2,:);
rr=M(3,:);

string2=fgets(fid);
nts = fscanf(fid,'%i',1);
ts = fscanf(fid,'%*i %i %i %i \n',[3 nts])+1;

string3=fgets(fid);
nes = fscanf(fid,'%i',1);
MM = fscanf(fid,'%*i %i %i %i \n',[3 nes])+1;
es=MM(1:2,:);
ids=MM(3,:);
fclose(fid);


figure (1)
pdemesh(ps,ts);

axis off equal

xs=ps(1,:);
ys=ps(2,:);
t1=ts(1,:);
t2=ts(2,:);
t3=ts(3,:);

la=hypot(xs(t2)-xs(t1), ys(t2)-ys(t1));
lb=hypot(xs(t3)-xs(t1), ys(t3)-ys(t1));
lc=hypot(xs(t3)-xs(t2), ys(t3)-ys(t2));
l=(la+lb+lc)/2;
area=sqrt(2*la.^2.*lb.^2+2*la.^2.*lc.^2+2*lb.^2.*lc.^2 ...
    - la.^4 - lb.^4 - lc.^4 )./4;
area_t=abs((xs(t2)-xs(t1)).*(ys(t3)-ys(t1))-(xs(t3)-xs(t1)).*(ys(t2)-ys(t1)))/2 ;

r=area./l;
R=(la.*lb.*lc)./(4*area);
rho=2*r./R;

figure (3)
histogram(rho,0:0.1:1,'Normalization','probability');
set(gcf,'Position',[230 250 400 400]) ;
set(gca,'Position',[0.12 0.14 0.85 0.8]);
xlim([0 1]);
xlabel('mesh quality (radius ratio)','interpreter','latex');
ylabel('Percentage','interpreter','latex');
grid on














