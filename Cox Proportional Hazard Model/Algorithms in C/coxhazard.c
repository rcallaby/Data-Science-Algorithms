#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA_POINTS 100

typedef struct {
    double time;     // Survival time
    int event;       // Event indicator (1 for event, 0 for censored)
    double covariate; // Single covariate
} SurvivalData;

int main() {
    int n; // Number of data points
    SurvivalData data[MAX_DATA_POINTS];

    // Read the data (in this example, we use hardcoded data)
    n = 5;
    data[0] = (SurvivalData){10.0, 1, 1.5};
    data[1] = (SurvivalData){8.0, 1, 2.0};
    data[2] = (SurvivalData){15.0, 0, 1.2};
    data[3] = (SurvivalData){12.0, 1, 3.0};
    data[4] = (SurvivalData){7.0, 0, 2.5};

    double beta = 0.5; // Coefficient for the covariate (you can adjust this)

    double risk_sum = 0.0;
    double events_sum = 0.0;

    // Calculate the hazard ratio
    for (int i = 0; i < n; i++) {
        if (data[i].event == 1) {
            risk_sum += exp(data[i].covariate * beta);
            events_sum += 1.0;
        }
    }

    double hazard_ratio = risk_sum / events_sum;

    printf("Hazard Ratio: %lf\n", hazard_ratio);

    return 0;
}