#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define DEBUG

typedef struct test {
    int i;
    int j;
    int cost;
} test_t;

/* сравнение двух целых для сортировки */
int comp (const void *a, const void *b) {

    test_t *test_a = (test_t *)a;
    test_t *test_b = (test_t *)b;

    return (test_a->cost - test_b->cost);
}

#define INF -999

int potentials(int **input_array, int **plan, int m, int n, int *supply, int *demand) {

    int u[m];
    int v[n];

    for (int i = 0; i < m; i++) {
        u[i] = INF;
    }

    for (int i = 0; i < n; i++) {
        v[i] = INF;
    }

    u[0] = 0;
    
    for (int i = 0; i < m; i++) {
        
        // заполним u если есть v
        for (int j = 0; j < n; j++) {
            if (plan[i][j] != 0) {
                if (v[j] != INF && u[i] == INF) {
                    u[i] = input_array[i][j] - v[j];
                }
            }
        }

        // заполним v если есть u
        for (int j = 0; j < n; j++) {
            if (plan[i][j] != 0 && u[i] != INF) {
                v[j] = input_array[i][j] - u[i];
            }
        }


    }

    // вывод u, v
    #ifdef DEBUG
        
        printf("plan with potentials\n");
        printf("s\\d\t");
        for (int i = 0; i < n; i++) {
            printf("%d\t", demand[i]);
        }
        printf("u\n");
        for (int i = 0; i < n+1; i++) {
            printf("---\t");
        }
        printf("---\n");

        for (int i = 0; i < m; i++) {
            printf("%2d|\t", supply[i]);
            for (int j = 0; j < n; j++) {
                char str[5];
                if (plan[i][j] != 0) {
                    sprintf(str, "%d", plan[i][j]);
                } else {
                    sprintf(str, "%c", '-');
                }
                printf("%s(%d)\t", str, input_array[i][j]);
            }
            printf("%d\n", u[i]);
        }        

        printf("v:|\t");
        for (int i = 0; i < n; i++) {
            printf("%d\t", v[i]);
        }

        printf("\n\nu: ");

        for (int i = 0; i < m; i++) {
            printf("%d ", u[i]);
        }
        printf("\nv: ");

        for (int i = 0; i < n; i++) {
            printf("%d ", v[i]);
        }
        printf("\n");
    #endif

// exit(1);

    // рассчитываем delta
    int delta[m][n];
    int opt_flag = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            delta[i][j] = 0;
            // если клетки пустые считаем delta и проверяем есть ли положительная delta
            if (plan[i][j] == 0) {
                delta[i][j] = u[i] + v[j] - input_array[i][j];
                if (delta[i][j] > 0) {
                    opt_flag = 1;
                }
            }
        }
    }

    // вывод delta
    #ifdef DEBUG
        printf("\ndefects\n");

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d\t", delta[i][j]);
            }
            printf("\n");
        }


        if (opt_flag == 1) {
            printf("plan not optimal, continue!\n");
            int res = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (plan[i][j] != 0) {
                        res = res + plan[i][j] * input_array[i][j];
                    }
                }
            }
            printf("Z = %d\n", res);
        } else {
            printf("plan optimal, done!\n");
            return 1;
        }
    #endif

    // Если план не оптимален построим цикл перевозок
        int max = INT_MIN;
        int max_i;
        int max_j;
        for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (plan[i][j] == 0 && max < delta[i][j]) {
                        max = delta[i][j];
                        max_i = i;
                        max_j = j;
                    }
                }
        }

        printf("max %d, [%d %d]\n", max, max_i, max_j);

        int min = INT_MAX;
        // схема прямоугольник
        for (int i = 0; i < m; i++) {

            if (delta[i][max_j] == 0) {
                for (int j = 0; j < n; j++) {
                    if (delta[max_i][j] == 0) {
                        if (delta[i][j] == 0) {
                            printf("- %d %d\n- %d %d\n+ %d %d\n+ %d %d\n", i, max_j, max_i, j, i, j, max_i, max_j); // прямоугольник
                            // добавим к началу цикла (max_i, max_j) перевозку +
                            // минимальная перевозка в цикле из отрицательных:
                            min = plan[i][max_j] < plan[max_i][j] ? plan[i][max_j] : plan[max_i][j];

                            // if (plan[i][max_j] == 0) {
                            //     min = plan[max_i][j];
                            // } else if (plan[max_i][j] == 0) {
                            //     min = plan[i][max_j];
                            // }

                            printf("min = %d\n", min);
                            
                            plan[i][max_j] -= min;
                            plan[max_i][j] -= min;
                            plan[i][j]  += min;
                            plan[max_i][max_j] += min;

                            break;
                        }
                    }
                }
            }
        }

        if (min == INT_MAX || min == 0) {
            printf("only rectangle search\n");
            exit(1);
        }


        // #ifdef DEBUG
        //     printf("\n");
        //     for (int i = 0; i < m+1; i++) {
        //         for (int j = 0; j < n+1; j++) {
        //             printf("%d\t", plan[i][j]);
        //         }
        //         printf("\n");
        //     }
        // #endif

}

int planMatrix(int **input_array, int *supply, int *demand, int n, int m) {

    test_t test[m*n];

    int k = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            test[k].i = i;
            test[k].j = j;
            test[k].cost = input_array[i][j];
            k++;
        }
    }

    // построить путь для метода наименьшей цены
    qsort(test, m*n, sizeof(test_t), comp);
    
    // тест вывод пути
    // for (int i = 0; i < m*n; i++) {
    //     printf("%d %d %d\n", test[i].cost, test[i].i, test[i].j);
    // }


    int **plan = (int **)malloc((m + 1)*sizeof(int *));
    for (int i = 0; i < m + 1; i++) {
        plan[i] = (int *)malloc((n + 1)*sizeof(int));
    }

    for (int i = 0; i < m+1; i++) {
            for (int j = 0; j < n+1; j++) {
                plan[i][j] = 0;
            }
    }
    
    for (int i = 0; i < m; i++) {
        plan[i][n] = supply[i];
    }

    for (int j = 0; j < n; j++) {
        plan[m][j] = demand[j];
    }

    #ifdef DEBUG    
        // printf("input plan\n");

        // printf("s\\d\t");
        // for (int i = 0; i < n; i++) {
        //     printf("%d\t", demand[i]);
        // }
        // printf("\n");
        // for (int i = 0; i < n+1; i++) {
        //     printf("---\t");
        // }
        // printf("\n");

        // for (int i = 0; i < m; i++) {
        //     printf("%2d|\t", supply[i]);
        //     for (int j = 0; j < n; j++) {
        //         printf("%d\t", plan[i][j]);
        //     }
        //     printf("\n");        
        // }
    #endif

    for (k = 0; k < m*n; k++) {
        int i = test[k].i;
        int j = test[k].j;
        // если есть потребность, восполняем из запасов
        // запасы - plan[i][n];
        // потребность - plan[m][j];
        if (plan[m][j] != 0) {
            if (plan[i][n] - plan[m][j] > 0) {
                plan[i][j] = plan[i][n] - (plan[i][n] - plan[m][j]);
                plan[i][n] -= plan[i][j];
                plan[m][j] -= plan[i][j];
            } else {
                plan[i][j] = plan[i][n];
                plan[i][n] -= plan[i][n];
                plan[m][j] -= plan[i][j];
            }
            
        }
    }

    #ifdef DEBUG
        printf("\ninput plan\n");
        printf("s\\d\t");
        for (int i = 0; i < n; i++) {
            printf("%d\t", demand[i]);
        }
        printf("\n");
        for (int i = 0; i < n+1; i++) {
            printf("---\t");
        }
        printf("\n");

        for (int i = 0; i < m; i++) {
            printf("%2d|\t", supply[i]);
            for (int j = 0; j < n; j++) {
                printf("%d\t", plan[i][j]);
            }
            printf("\n");
        }        

        printf("\n");
    #endif
            
    int deg = 0;
    for (int i = 0; i < m+1; i++) {
        for (int j = 0; j < n+1; j++) {
            // занятые клетки
            if (plan[i][j] != 0) {
                deg++;
            }
        }
    }
    // вырожденная матрица или нет
    if (m + n - 1 == deg) {
        // не вырожден план
        // printf("continue..\n");
    } else {
        // вырожденный план
        printf("m + n - 1 != not empty\n");
            int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (plan[i][j] != 0) {
                    res = res + plan[i][j] * input_array[i][j];
                }
            }
        }
        printf("Z = %d\n", res);

        // exit(1);
    }

    
    // *************************** оптимальность плана методом потенциалов ***************************
    int optimal = 0;
    do {

        if (potentials(input_array, plan, m, n, supply, demand) == 1) {
            printf("done\n");
            optimal = 1;
        }
    } while(!optimal);
    

    // *************************** Ответ ***************************
        printf("s\\d\t");
        for (int i = 0; i < n; i++) {
            printf("%d\t", demand[i]);
        }
        printf("\n");
        for (int i = 0; i < n+1; i++) {
            printf("---\t");
        }
        printf("\n");

        for (int i = 0; i < m; i++) {
            printf("%2d|\t", supply[i]);
            for (int j = 0; j < n; j++) {
                printf("%d\t", plan[i][j]);
            }
            printf("\n");
        }        

        printf("\n");
    

    int res = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (plan[i][j] != 0) {
                res = res + plan[i][j] * input_array[i][j];
            }
        }
    }



    for (int i = 0; i < m + 1; i++) {
        free(plan[i]);
    }
    free(plan);

    return res;


}


int main(int argc, char *argv[]) {

    int m, n;
    int **input;
    int *supply, *demand; // запасы, потребности

    FILE *file = fopen("input8.txt", "r");
    if (file == NULL) {
        printf("error reading file!\n");
        exit(1);
    }
	
    fscanf(file, "%d %d", &m, &n);


    input = (int **)malloc((m-1)*sizeof(int *));
    supply = (int *)malloc((m-1)*sizeof(int *));
    demand = (int *)malloc((n-1)*sizeof(int *));

	
    for (int i = 0; i < m - 1; i++) {

        input[i] = (int *)malloc((n-1)*sizeof(int *));
        for (int j = 0; j < n; j++) {

            // Входные данные, если последний столбец, то запасы
            if (j < n - 1)
                fscanf(file, "%d", &input[i][j]);
            else 
                fscanf(file, "%d", &supply[i]);
        }
    }

    // Последняя m строка с потребностями
    for (int i = 0; i < n-1; i++) {
        fscanf(file, "%d", &demand[i]);
    }

    fclose(file);

    printf("\ns\\d\t");
    for (int i = 0; i < n - 1; i++) {
        printf("%d\t", demand[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("---\t");
    }
    printf("\n");

    // Вывод входных данных
    for (int i = 0; i < m - 1; i++) {
        printf("%2d|\t", supply[i]);        
        for (int j = 0; j < n - 1; j++) {
            printf("%d\t", input[i][j]);
        }
        printf("\n");
    }

    printf("\n");


    int supply_sum = 0, demand_sum = 0;
    for (int i = 0; i < m - 1; i++) {
        supply_sum += supply[i];
    }
    for (int j = 0; j < n - 1; j++) {
        demand_sum += demand[j];
    }

    if (supply_sum == demand_sum) {
        printf("closed transportation problem\n");
    } else {
        printf("open transportation problem supplies %d demands %d\n", supply_sum, demand_sum);
        exit(1);
    }

    int total_cost = planMatrix(input, supply, demand, n-1, m-1);
    printf("Z = %d\n", total_cost);

    for (int i = 0; i < m - 1; i++) {
        free(input[i]);
    }
    free(input);
    free(demand);
    free(supply);

	return 0;
}