// Nettoyage
xdel(winsid());
clear;

// Configuration
lw = 2;
fs = 4;

// Répertoire detravail
wd = cd;

// Données US
xUS   = [1 2 3 20 22 25 28 31 34]*1e-3;
yUSex = [65 65 65 74 84 93 104 113 123]*1e-3;
yUSth = xUS/25.4 * (5/512)*1e3;

// Tracé courbe US
cf1 = figure(1);
cf1.figure_name = 'US';
cf1.background  = 8;
plot(xUS*1e3, yUSex*1e3,'-' ,'LineWidth',lw,'Color',[0 0 1]);
plot(xUS*1e3, yUSth*1e3,'-' ,'LineWidth',lw,'Color',[1 0 0]);
ca1  = get('current_axes');
//ca1.data_bounds = [0 50 50 150];
ca1.font_size   = fs;
xlabel('$x (mm)$');  xL = get(ca1,'x_label');
xL.font_style = 8;
xL.font_size  = fs+1;
ylabel('$U (mV)$');  yL = get(ca1,'y_label');
yL.font_style = 8;
yL.font_size  = fs+1;
xgrid;
legend('Expérience','Théorie',2);

// Données IR
xIR   = [1 2 4 5 6 8 10 12 15 20 25]*1e-3;
yIRex = [2.7 3 2.3 1.9 1.67 1.32 1.1 0.94 0.77 0.57 0.45];
yIRth = 3*exp(-10*(xIR-50e-3));

// Tracé courbe IR
cf2 = figure(2);
cf2.figure_name = 'IR';
cf2.background  = 8;
plot(xIR*1e3, yIRex, '-' ,'LineWidth',lw,'Color',[0 0 1]);
plot(xIR*1e3, yIRth, '-' ,'LineWidth',lw,'Color',[1 0 0]);
ca2  = get('current_axes');
//ca2.data_bounds = [0 50 50 150];
ca2.font_size   = fs;
xlabel('$x (mm)$');  xL = get(ca2,'x_label');
xL.font_style = 8;
xL.font_size  = fs+1;
ylabel('$U (V)$');  yL = get(ca2,'y_label');
yL.font_style = 8;
yL.font_size  = fs+1;
xgrid;
legend('Expérience','Théorie',1);
