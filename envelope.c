#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double gauss(double *array1, double *array2, int n, double f, double point);
double lorentz(double *array1, double *array2, int n, double f, double point);

int main(int argc, char *argv[]){
	if (argc !=8){
		printf("Remember: ./envelope name_of_file gaussian_or_lorentz num_of_points min_range max_range fwhm num_responses\n");
	} else {
		char *filename = argv[1];
		FILE *file;
		int num_of_points = atoi(argv[3]);
		int min = atoi(argv[4]);
		int max = atoi(argv[5]);
		double fwhm = atof(argv[6]);
		int num_responses = atoi(argv[7]);
		double total_points[num_of_points+1];
		double energies[num_responses];
		double responses[num_responses]; 
		int i;
		int j = strlen(filename);
		for(i=0; i<num_of_points+1; i++){
			total_points[i] = (double) min + i*(max-min)/((double) num_of_points); 
		}
		if(strcmp(argv[2], "gaussian") == 0){
			file = fopen(filename, "r");
			for(i=0; i<num_responses; i++){
				fscanf(file,"%lf%lf", &energies[i], &responses[i]);
			}
			double gaussian[num_of_points+1];
			for(i=0; i<num_of_points+1; i++){
				gaussian[i] = gauss(energies, responses, num_responses, fwhm, total_points[i]); 
			}
			fclose(file);
			filename[j-1] = 't';
			filename[j-2] = 'u';
			filename[j-3] = 'o';
			file = fopen(filename, "w");
			for(i=0; i<num_of_points+1; i++){
				fprintf(file, "%016.12lf		%015.12lf\n", total_points[i], gaussian[i]);
			}
			fclose(file);
		}
		if(strcmp(argv[2], "lorentz") == 0){
			file = fopen(filename, "r");
			for(i=0; i<num_responses; i++){
				fscanf(file,"%lf%lf", &energies[i], &responses[i]);
			}
			double lorentzian[num_of_points+1];
			for(i=0; i<num_of_points+1; i++){
				lorentzian[i] = lorentz(energies, responses, num_responses, fwhm, total_points[i]); 
			}
			fclose(file);
			filename[j-1] = 't';
			filename[j-2] = 'u';
			filename[j-3] = 'o';
			file = fopen(filename, "w");
			for(i=0; i<num_of_points+1; i++){
				fprintf(file, "%017.12lf		%015.12lf\n", total_points[i], lorentzian[i]);
			}
			fclose(file);
		}
	}
	return 0;
}

double gauss(double *array1, double *array2, int n, double f, double point){
	int i;
	double sum = 0.0;
	for(i=0; i<n; i++){
		sum += array2[i])*exp(-log(2.0)*(point-array1[i])/(f/2.0),2));
	}
	return sum;
}

double lorentz(double *array1, double *array2, int n, double f, double point){
	int i;
	double sum = 0.0;
	for(i=0; i<n; i++){
		sum += (array2[i])/(1 + pow((point-array1[i])/(f/2.0),2));
	}
	return sum;
}
