% Procesado de los datos
[random_x, nada_y, e, cant] = leer_datos_float('histograma.txt');


% Creación de los gráficos
filetype='-dpng';
%mkdir('graficos');
figure;


hold on;
x = gca;
hist(random_x,30);
xlabel('Numero aleatorio','FontSize',12);
ylabel('Cantidad de apariciones','FontSize',12);
%legend('Complejidad O(n)','Tiempo de ejecucion del algoritmo','Location','northwest')
%set(get(h, 'Parent'), 'YScale', 'log');
hold off;
print('histograma', filetype);