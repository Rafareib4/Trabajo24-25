#include <stdio.h>
#include <stdbool.h>
#define MAX_PATIENTS 1000

struct Patient {
    int num;
    char gender[10];
    float age;
    bool hypertension;
    bool heart_disease;
    bool ever_married;
    char work_type[20];
    char residence[20];
    float glucose;
    float bmi;
    float smoking_status;
    bool stroke;
};
