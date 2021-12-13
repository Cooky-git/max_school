#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5

int statistic_target = 50; 		//number of buckets

float	*ft_equiwidth_freq(int *array_lower, int *array_upper, int *array_lower_tri, int *array_upper_tri)
{
	int		i;
	int		j;
	float	hist_length;
	float	lowest_bound;
	float	lower_bucket_bound;
	float	upper_bucket_bound;
	float	bucket_length;
	float	*bucket;
	float	increment;

	hist_length = array_upper_tri[ARRAY_LENGTH - 1] - array_lower_tri[0];
	bucket_length = hist_length / statistic_target;
	lowest_bound = array_lower_tri[0];
	lower_bucket_bound = lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;

	bucket = malloc(sizeof(float) * statistic_target + 1);
	if (!bucket)
		return NULL;
	bucket[statistic_target] = '\0';

	for (i = 0; i < statistic_target; i++)
	{
		for(j = 0; j < ARRAY_LENGTH; j++)
		{

			if((array_lower[j] > lower_bucket_bound) && (array_lower[j] < upper_bucket_bound))
			{
				printf("\ncoucou1\n");
				increment = (upper_bucket_bound - array_lower[j]) / bucket_length;
				bucket[i] += increment;
			}
			else if((array_lower[j] <= lower_bucket_bound) && (array_upper[j] >= upper_bucket_bound))
			{
				printf("\ncoucou2\n");
				bucket[i] += 1 ;
			}
			else if((array_upper[j] < upper_bucket_bound) && (array_upper[j] > lower_bucket_bound))
			{
				printf("\ncoucou3\n");
				increment = (array_upper[j] - lower_bucket_bound) / bucket_length;
				bucket[i] += increment ;
			}
		}
		printf("\nbucket[%d] = %f\n", i, bucket[i]);
		lower_bucket_bound = upper_bucket_bound;
		upper_bucket_bound += bucket_length;
	}
	return (bucket);
}

float multiplication(float *bucket1, float *bucket2, int *array_lowerx_tri, int *array_lowery_tri, int *array_upperx_tri, int *array_uppery_tri){

	int		i;
	int		j;
	int		min_hist_length;
	int		hist_lowest_bound;
	float	lower_bucket_bound1;
	float	lower_bucket_bound2;
	float	upper_bucket_bound1;
	float	upper_bucket_bound2;
	int		array_length1;
	int		array_length2;
	float 	min_hist_value;
	float	bucket_length1;
	float	bucket_length2;
	float   min_hist_value1 = array_lowerx_tri[0];
	float   min_hist_value2 = array_lowery_tri[0];
	int 	resultat = 0;
	int		hist_length1;
	int		hist_length2;

	hist_length1 = array_upperx_tri[ARRAY_LENGTH - 1] - array_lowerx_tri[0];
	hist_length2 = array_uppery_tri[ARRAY_LENGTH - 1] - array_lowery_tri[0];
	bucket_length1 = hist_length1 / statistic_target;
	bucket_length2 = hist_length2 / statistic_target;
	lower_bucket_bound1 = min_hist_value1;
	upper_bucket_bound1 = lower_bucket_bound1 + bucket_length1;
	lower_bucket_bound2 = min_hist_value2;
	upper_bucket_bound2 = lower_bucket_bound2 + bucket_length2;


	for (i = 0; i < statistic_target; i++)
	{
		for(j = 0; j < statistic_target; j++)
		{

			if(!((lower_bucket_bound2 < lower_bucket_bound1) && (upper_bucket_bound2 < lower_bucket_bound1)))
			{
				resultat += bucket1[i]*bucket2[j];
			}
			else if(!((lower_bucket_bound2 > upper_bucket_bound1) && (upper_bucket_bound2 > upper_bucket_bound1)))
			{
				resultat += bucket1[i]*bucket2[j];
			}

		}
		lower_bucket_bound1 = upper_bucket_bound1;
		upper_bucket_bound1 += bucket_length1;
		lower_bucket_bound2 = upper_bucket_bound2;
		upper_bucket_bound2 += bucket_length2;
	}
	return (resultat);
}

float moyenne(float* bucket){

	float moyenne;
	int i;
	for (i = 0; i < statistic_target; i++){
		moyenne += bucket[i];
		}
	moyenne = moyenne / ARRAY_LENGTH;
	return (moyenne);
	}

int	main(void)
{
    int array_lower1[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
    int array_upper1[ARRAY_LENGTH] = {14, 9, 15, 27, 30};
    int array_lower_tri1[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
    int array_upper_tri1[ARRAY_LENGTH] = {9, 14, 15, 27, 30};
    int array_lower2[ARRAY_LENGTH] = {0, 2, 10, 22, 50};
    int array_upper2[ARRAY_LENGTH] = {6, 13, 19, 30, 60};
    int array_lower_tri2[ARRAY_LENGTH] = {0, 2, 10, 22, 50};
    int array_upper_tri2[ARRAY_LENGTH] = {6, 13, 19, 30, 60};

	float *bucket1;
	float *bucket2;
	bucket1 = ft_equiwidth_freq(array_lower1, array_upper1, array_lower_tri1, array_upper_tri1);
	bucket2 = ft_equiwidth_freq(array_lower2, array_upper2, array_lower_tri2, array_upper_tri2);
	float resultat;
	resultat = multiplication(bucket1, bucket2, array_lower1, array_upper1, array_lower_tri1, array_upper_tri1);
	printf("\nresultat = %f\n", resultat);

	float moyenne1 = moyenne(bucket1);
	printf("\nmoyenne1 = %f\n", moyenne1);

	float moyenne2 = moyenne(bucket2);
	printf("\nmoyenne2 = %f\n", moyenne2);


	float resultat_nouveau;
	resultat_nouveau = (resultat / (moyenne1*moyenne2));
	printf("resultat2 = %f\n", resultat_nouveau);

	/*float estimation = estimation_cardinality_join(bucket1,bucket2);
	printf("join cardinality estimation = %f\n", estimation );*/
	free (bucket1);

	free (bucket2);
	return (0);
}
