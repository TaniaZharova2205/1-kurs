#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define TK 1e-3    // Время расчета
#define T_START 1e-7  // Начальный шаг
#define SMX 1e-5   // Максимальный шаг
#define SMN 1e-15  // Минимальный шаг
#define ACR 1e-3   // Точность

int    UC1dt = 0,  // Соответствие величин и индексов
    UCbdt = 1,
    ILdt = 2, 
    UC2dt = 3,    

    UL1 = 4,
    UR1 = 5,        
    URb = 6,
    URu = 7,       
    UI1 = 8,      

    IE1 = 9,       
    IC1 = 10,      
    ICb = 11,
    IC2 = 12,

    IL1 = 13,
    IR1 = 14,
    IRb = 15,      
    IRu = 16,      
    II1 = 17,

    UE1 = 18,     
    UC1 = 19,
    UCb = 20,
    UC2 = 21;    


#define V_OUT IL1  // ----------------------- Переменная, которая выводится на графике (UR1, UL1, UC1, ...)

double** m;    // Матрица Якоби
double* vector;    // Вектор невязок

const int dim = 22;   // Размерность

double* x_cur;    // Массив базисных переменных
double* x_prev; 
double* x_prevprev;

// Параметры схемы
const double I_t = 1e-12;
const double L_1 = 0.001;
const double C_1 = 1e-6;
const double C_b = 2e-12;
const double R_b = 20.0;
const double R_u = 1000000.0;
const double R_1 = 10000.0;
const double C_2 = 1e-6;
const double MFt = 0.026;
const double A = 10;
const double P = 1e-4;

//Нахождение максимального элемента для расчета точности
double maximum() { 
    double result = 0;
    for (int i = 0; i < dim; i++)
        if (result < fabs(vector[i]))
            result = fabs(vector[i]);
    return result;
}

// Функция обнуления перед новым шагом
void before_new_step() 
{
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            m[i][j] = 0;
        }
        vector[i] = 0;
    }
}

void minus_vector() 
{
    for (int i = 0; i < dim; i++) {
        vector[i] = -vector[i];
    }
}

//Функция синусоидального источника
double E_1(double t) { 
    double A = 10.0;   // Амплитуда
    double freq = 2 * M_PI / P;  // Частота (2pi/T)
    return A * sin(freq * t);
}

// Заполнение матрицы Якоби
void init_matrix(double dt) {

    double I_d_deriv = I_t / MFt * exp(x_cur[UI1] / MFt);
    
    m[UC1dt][UC1dt] = 1.0;
    m[UC1dt][UC1] = -1.0 / dt;
    
    m[UCbdt][UCbdt] = 1.0;
    m[UCbdt][UCb] = -1.0 / dt;
    
    m[ILdt][ILdt] = 1.0;
    m[ILdt][IL1] = -1.0 / dt;

    m[UC2dt][UC2dt] = 1.0;
    m[UC2dt][UC2] = -1.0 / dt;
    
    //............. 

    m[UL1][UL1] = 1.0;
    m[UL1][UC1] = -1.0;

    m[UR1][UR1] = 1.0;
    m[UR1][UE1] = -1.0;

    m[URb][URb] = 1.0;
    m[URb][UE1] = 1.0;
    m[URb][UC1] = -1.0;
    m[URb][UCb] = 1.0;
    m[URb][UC2] = -1.0;


    m[URu][URu] = 1.0;
    m[URu][UCb] = -1.0;

    m[UI1][UI1] = 1.0;
    m[UI1][UCb] = -1.0;

    //............. 

    m[IE1][IE1] = 1.0;
    m[IE1][IR1] = 1.0;
    m[IE1][IRb] = -1.0;

    m[IC1][IC1] = 1.0;
    m[IC1][IL1] = 1.0;
    m[IC1][IRb] = 1.0;

    m[ICb][ICb] = 1.0;
    m[ICb][IRb] = -1.0;
    m[ICb][IRu] = 1.0;
    m[ICb][II1] = 1.0;

    m[IC2][IC2] = 1.0;
    m[IC2][IRb] = 1.0;

    //............. 

    m[IL1][UL1] = 1.0;
    m[IL1][ILdt] = -L_1;

    m[IR1][IR1] = R_1;
    m[IR1][UR1] = -1;
  
    m[IRb][IRb] = R_b;
    m[IRb][URb] = -1;

    m[IRu][IRu] = R_u;
    m[IRu][URu] = -1;

    m[II1][II1] = 1.0;
    m[II1][UI1] = -I_d_deriv;

    //............. 

    m[UE1][UE1] = 1.0;

    m[UC1][IC1] = 1.0;
    m[UC1][UC1dt] = -C_1;

    m[UCb][ICb] = 1.0;
    m[UCb][UCbdt] = -C_b;

    m[UC2][IC2] = 1.0;
    m[UC2][UC2dt] = -C_2;

}

// Заполнение вектора невязок
void init_vector(double dt, double time){

 double I_d = I_t * (exp(x_cur[UI1] / MFt) - 1.0);
    
    vector[UC1dt] = x_cur[UC1dt] - ((x_cur[UC1] - x_prev[UC1]) / dt);
    vector[UCbdt] = x_cur[UCbdt] - ((x_cur[UCb] - x_prev[UCb]) / dt);
    vector[ILdt] = x_cur[ILdt] - ((x_cur[IL1]  - x_prev[IL1]) / dt);
    vector[UC2dt] = x_cur[UC2dt] - ((x_cur[UC2] - x_prev[UC2]) / dt);
    
    vector[UL1] = x_cur[UL1] - x_cur[UC1];
    vector[UR1] = x_cur[UR1] - x_cur[UE1];
    vector[URb] = x_cur[URb] + x_cur[UE1] - x_cur[UC1] + x_cur[UCb] - x_cur[UC2];
    vector[URu] = x_cur[URu] - x_cur[UCb];
    vector[UI1] = x_cur[UI1] - x_cur[UCb];  

    vector[IE1] = x_cur[IE1] + x_cur[IR1] - x_cur[IRb];
    vector[IC1] = x_cur[IC1] + x_cur[IL1] + x_cur[IRb];  
    vector[ICb] = x_cur[ICb] - x_cur[IRb] + x_cur[IRu] + x_cur[II1];
    vector[IC2] = x_cur[IC2] + x_cur[IRb];

    vector[IL1] = x_cur[UL1] - L_1 * x_cur[ILdt];
    vector[IR1] = x_cur[IR1] * R_1 - x_cur[UR1];
    vector[IRb] = x_cur[IRb] * R_b - x_cur[URb];
    vector[IRu] = x_cur[IRu] * R_u - x_cur[URu];
    vector[II1] = x_cur[II1] - I_d;

    vector[UE1] = x_cur[UE1] - E_1(time);
    vector[UC1] = x_cur[IC1] - C_1 * x_cur[UC1dt];
    vector[UCb] = x_cur[ICb] - C_b * x_cur[UCbdt];
    vector[UC2] = x_cur[IC2] - C_2 * x_cur[UC2dt];
}

//Метод Гаусса для решения СЛАУ
void Gauss() { 
    long int i, j, k;
    int N = dim;
    double diagonalElement;
    for (k = 0; k < N; k++) {   // Прямой ход
        diagonalElement = m[k][k];
        for (j = k; j < N; j++)
            m[k][j] /= diagonalElement;
        vector[k] /= diagonalElement;
        for (i = k + 1; i < N; i++) {
            diagonalElement = m[i][k];
            for (j = k; j < N; j++)
                m[i][j] -= m[k][j] * diagonalElement;
            vector[i] -= vector[k] * diagonalElement;
        }
    }
    for (i = N - 2; i >= 0; i--) //Обратный ход
        for (j = i + 1; j < N; j++)
            vector[i] -= m[i][j] * vector[j];
}

void gnuplot_out(){
    // Вывод графика
    FILE * gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set terminal wxt linewidth 1.5 size 900,600\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xrange [0:0.001]\n");
    fprintf(gp, "plot 'out.txt' using 1:2 with line lt rgb \"#FD1111\"  title ' '\n");
    pclose(gp);
}

int main() {
    FILE * file_out = fopen("out.txt", "w");

    double dt = T_START;      // Шаг по времени
    double dt_prev = dt;    // Предыдущий шаг по времени
    double eps_max;    // Максимальное отклонение
    double eps_min;    // Минимальное отклонение

    eps_max = 1e-3;    // Максимальное отклонение
    eps_min = 1e-6;    // Минимальное отклонение

    int counter = 0;    // Счетчик шагов по времени
    double time = 0;    // Текущее время
    double eps_cur;
    double eps;

    m = (double**) malloc(sizeof(double*) * dim);  // Матрица Якоби
    for(int i = 0; i < dim; ++i)
        m[i] = (double*) malloc(dim * sizeof(double)); 

    vector = (double * ) malloc(sizeof(double) * dim); // Вектор невязок (после итерации метода Гаусса - вектор поправок)

    x_cur = (double * ) malloc(sizeof(double) * dim); // Значения базисных переменных на текущем шаге
    x_prev = (double * ) malloc(sizeof(double) * dim); // Значения переменных на предыдущем шаге
    x_prevprev = (double * ) malloc(sizeof(double) * dim); // Значения переменных на предпредыдущем шаге

    double step_count = 0;
    while (time < TK) { //Общий цикл расчета
        int iteration = 0;  // Счетчик итераций метода Ньютона
        int flag = 1;   // Индикатор сходимости метода Ньютона

        for (int i = 0; i < dim; i++){ // Расчет приближений
            x_cur[i] = x_prevprev[i] + (dt_prev + dt) * (x_prev[i] - x_prevprev[i]) / dt_prev;
        }

        while (flag) {  // Выполнение итераций метода Ньютона
            before_new_step(); //Обнуление

            init_matrix(dt); 
            init_vector(dt, time);
            minus_vector();

            Gauss();

            for(int i=0; i<dim; i++)
                x_cur[i] += vector[i];

            iteration++;

            if (maximum() <= ACR) // Проверка точности
                flag = 0;

            if (iteration > 7 && flag == 1) { // Метод не сошелся, уменьшение шага и отбрасывание текущих результатов
                if (dt < SMN){  // Шаг слишком мал, решение не сходится
                    printf("Error: dt < dt_min (1)");
                    exit(1);
                }
                
                iteration = 0;
                dt /= 2.0;
                // printf("%.6e\n", dt);

                for(int i=0; i<dim; i++)
                    x_cur[i] = x_prev[i];
            }
        }

        // Расчет текущего приращения
        eps = 0;
        eps_cur = 0;

        for(int i=0; i<dim; i++){
            eps = fabs(0.5 * dt * dt *((x_cur[i] - x_prev[i])/dt - (x_prev[i] - x_prevprev[i])/dt_prev));
            if (eps > eps_cur) eps_cur = eps;
        }

        if (eps_cur > eps_max) { //Недостаточная точность, уменьшение шага и отбрасывание текущих результатов
            if (dt < SMN){  // Шаг слишком мал, решение не сходится
                printf("Error: dt < dt_min (2)");
                exit(1);
            }
            dt /= 2.0;

            for(int i=0; i<dim; i++)
                x_cur[i] = x_prev[i];
           
        } else { //Точность достигнута
            
            for(int i=0; i<dim; i++){
                x_prevprev[i] = x_prev[i];
                x_prev[i] = x_cur[i];
            }
            dt_prev = dt;
           
            time += dt;
            counter++;
            step_count+=dt;

                fprintf(file_out, "%.9e %.9e %.9e\n", time, x_cur[V_OUT], dt);
                printf("%d %d %.3e\n", counter, iteration, time);
            
            if ((eps_cur < eps_min) && (dt < SMX)) // Точность выше требуемой, увеличение шага
                dt *= 2.0;
        }
    }
    printf("%.6e\n", step_count/counter);

    fclose(file_out);

    gnuplot_out();

    for(int i = 0; i < dim; ++i)
        free(m[i]);
 
    free(m);
    free(vector);
    free(x_cur);
    free(x_prev);
    free(x_prevprev);

    return 0;
}
