#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5

int array_lower1[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
int array_upper1[ARRAY_LENGTH] = {14, 9, 15, 27, 30};
int array_lower_tri1[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
int array_upper_tri1[ARRAY_LENGTH] = {9, 14, 15, 27, 30};

int array_lower2[ARRAY_LENGTH] = {0, 2, 10, 22,50};
int array_upper2[ARRAY_LENGTH] = {6, 13, 19, 30, 60};
int array_lower_tri2[ARRAY_LENGTH] = {0, 2, 10, 22, 50};
int array_upper_tri2[ARRAY_LENGTH] = {6, 13, 19, 30, 60};

int statistic_target = 255; 		//number of buckets

/*int		*ft_hist_length()
{
	int	first_length;
	int	second_length;
	int	array_length;
	int	min_hist_length;
	int	hist_lower_bound;
	int	*return_array;

	return_array = malloc(sizeof(int) * 3);
	if (!return_array)
		return NULL;
	return_array[2] = '\0';
	array_length = sizeof(array_upper_tri1)/sizeof(array_upper_tri1[0]);
	first_length = array_upper_tri1[array_length - 1] - array_lower_tri1[0];
	second_length = array_upper_tri2[array_length - 1] - array_lower_tri2[0];
	if (first_length <= second_length)
	{
		min_hist_length = first_length;
		hist_lower_bound = array_lower_tri1[0];
	}
	else
	{
		min_hist_length = second_length;
		hist_lower_bound = array_lower_tri2[0];
	}
	return_array[0] = min_hist_length;
	return_array[1] = hist_lower_bound;
	return (return_array);
}*/

float	*ft_equiwidth_freq(int *array_lowerx, int *array_upperx,int * array_lowerx_tri,int * array_upperx_tri)
{
	int		i;
	int		j;
	int		hist_lowest_bound;
	int		lower_bucket_bound;
	int		upper_bucket_bound;
	int		array_length;
	float	bucket_length;
	float	*buckets;
	float     increment;


	bucket_length = (array_upperx_tri[ARRAY_LENGTH-1] - array_lowerx_tri[0])/ statistic_target;
	printf("array_upperx_tri[-1] = %i\n",array_upperx_tri[ARRAY_LENGTH-1]);
	printf("bucket_length = %f\n",bucket_length);

	hist_lowest_bound = array_lowerx_tri[0];
	lower_bucket_bound = hist_lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;
	//array_length = sizeof(array_upper1)/sizeof(array_upper1[0]);
	//array_length = sizeof(array_upper1)/sizeof(array_upper1[0]);

	buckets = malloc(sizeof(float) * statistic_target + 1);
	if (!buckets)
		return NULL;
	buckets[statistic_target] = '\0';

	for (i = 0; i < statistic_target; i++)
	{
		for(j = 0; j < ARRAY_LENGTH; j++)
		{

			if((array_lowerx[j] > lower_bucket_bound) && (array_lowerx[j] < upper_bucket_bound))
			{	printf("nique le c\n");
				increment = (upper_bucket_bound - array_lowerx[j]) / bucket_length;
				buckets[i] += increment;
			}
			else if((array_lowerx[j] <= lower_bucket_bound) && (array_upperx[j] >= upper_bucket_bound))
			{
				buckets[i] += 1 ;
			}
			else if((array_upperx[j] < upper_bucket_bound) && (array_upperx[j] > lower_bucket_bound))
			{
				increment = (array_upperx[j] - lower_bucket_bound) / bucket_length;
				buckets[i] += increment ;
			}
		}
		printf("buckets = %f\n",buckets[i] );
		lower_bucket_bound = upper_bucket_bound;
		upper_bucket_bound += bucket_length;
	}
	return (buckets);
}
/*float estimation_cardinality_join(float* bucket1, float* bucket2){


	float *list_join;
	list_join = malloc(sizeof(float) * statistic_target+1 );
	list_join[statistic_target + 1] = '\0';


	int i;
	for (i=0; i < statistic_target ; i++){
		list_join[i] = bucket1[i] * bucket2[i];
	}

	float estimation;
	for(i=0; i < statistic_target; i++){
		estimation += list_join[i] ;
	}
	return (estimation);

}*/

float multiplication(float* bucket1, float* bucket2){

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
	float   min_hist_value1 = array_lower_tri1[0];
	float   min_hist_value2 = array_lower_tri2[0];
	int 	resultat = 0;

	/*if ( array_lower_tri1[0] >= array_lower_tri2[0]){
		min_hist_value = array_lower_tri2[0];
	}
	else{
		min_hist_value = array_lower_tri1[0];
	}*/
	bucket_length1 = (array_upper_tri1 - array_lower_tri1)/ statistic_target;
	bucket_length2 = (array_upper_tri2 - array_lower_tri2) / statistic_target;
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
	float *bucket1;
	float *bucket2;
	bucket1 = ft_equiwidth_freq(array_lower1, array_upper1,array_lower_tri1,array_upper_tri1);
	bucket2 = ft_equiwidth_freq(array_lower2, array_upper2,array_lower_tri2,array_upper_tri2);
	float resultat;
	resultat = multiplication(bucket1,bucket2);
	printf("resultat = %f\n", resultat);

	float moyenne1 = moyenne(bucket1);
	printf("moyenne1 = %f\n", moyenne1);

	float moyenne2 = moyenne(bucket2);
	printf("moyenne2 = %f\n", moyenne2);


	float resultat_nouveau;
	resultat_nouveau = (resultat / (moyenne1*moyenne2));
	printf("resultat2 = %f\n", resultat_nouveau);

	/*float estimation = estimation_cardinality_join(bucket1,bucket2);
	printf("join cardinality estimation = %f\n", estimation );*/
	free (bucket1);

	free (bucket2);
	return (0);
}