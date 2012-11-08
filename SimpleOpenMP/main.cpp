#include <stdio.h>
#include <omp.h>
#include <math.h>

//int main(int argc, char* argv[])
//{
//	#pragma omp parallel
//	{
//		printf("I am thread %d of %d.\n", omp_get_thread_num()+1, omp_get_num_threads());
//	}
//	return 0;
//}


//int main(int argc, char* argv[])
//{
//	int result = 0;
//	int A[10000], i=0;
//	for(i=0; i<10000; i++)
//	{
//		A[i] = i;
//		result += A[i];
//	}
//	printf("Array-Summe VOR Rechnung: %d\n", result);
//	i=0;
//	int T[2];
//	T[0] = 0;
//	T[1] = 0;
//	#pragma omp parallel
//	{
//		#pragma omp for
//		for(i=0; i<10000; i++)
//		{
//			A[i] = (float)A[i] * sin((float)A[i]) * cos((float)A[i]) * 2;
//			T[omp_get_thread_num()]++;
//		}
//	}
//	i=0; result=0;
//	for(i=0; i<10000; i++)
//		result += A[i];
//	printf("Array-Summe NACH Rechnung: %d\n", result);
//	printf("Thread 1: %d Rechnungen\n", T[0]);
//	printf("Thread 2: %d Rechnungen\n", T[1]);
//	return 0;
//}




//int main(int argc, char* argv[])
//{
//	int result = 0;
//	int A[100], i=0, j=0;
//	for(i=0; i<100; i++)
//	{
//		A[i] = i;
//		result += A[i];
//	}
//	printf("Array-Summe VOR Rechnung: %d\n", result);
//	i=0;
//	int T[2];
//	T[0] = 0;
//	T[1] = 0;
//
//
//
//
//
//
//
//
//
//	#pragma omp parallel
//	{
//		#pragma omp for private(j)
//		for(i=0; i<100; i++)
//		{
//			for(j=0; j<10; j++)
//			{
//				A[i] = A[i] * 2;
//				T[omp_get_thread_num()]++;
//			}
//		}
//	}
//
//
//
//
//
//
//
//
//	i=0; result=0;
//	for(i=0; i<100; i++)
//		result += A[i];
//	printf("Array-Summe NACH Rechnung: %d\n", result);
//	printf("Thread 1: %d Rechnungen\n", T[0]);
//	printf("Thread 2: %d Rechnungen\n", T[1]);
//	return 0;
//}


//int main(int argc, char* argv[])
//{
//	int result = 0;
//	int A[100], i=0, j=0;
//	for(i=0; i<100; i++)
//	{
//		A[i] = i;
//		result += A[i];
//	}
//	printf("Array-Summe VOR Rechnung: %d\n", result);
//	i=0;
//	int T[2];
//	T[0] = 0;
//	T[1] = 0;
//	#pragma omp parallel
//	{
//		#pragma omp for private(j)
//		for(i=0; i<100; i++)
//		{
//			for(j=0; j<10; j++)
//			{
//				A[i] = A[i] * 2;
//				T[omp_get_thread_num()]++;
//			}
//		}
//	}
//	i=0; result=0;
//	for(i=0; i<100; i++)
//		result += A[i];
//	printf("Array-Summe before computing: %d\n", result);
//	printf("Thread 1: %d Rechnungen\n", T[0]);
//	printf("Thread 2: %d Rechnungen\n", T[1]);
//	return 0;
//}




int main(int argc, char* argv[])
{
	int result = 0;
	int A[100], i=0, j=0;
	for(i=0; i<100; i++)
	{
		A[i] = i;
		result += A[i];
	}
	printf("Array-sum before computing: %d\n", result);
	i=0;
	int* T = new int[omp_get_num_threads()+1];
	for (i = 0; i < omp_get_num_threads(); i++)
	{
		T[i] = 0;
	}

	int NumOfIters=0;

	#pragma omp parallel
	{
		#pragma omp for reduction(+: NumOfIters)
		for(i=0; i<100; i++)
		{
			for(j=0; j<10; j++)
			{
				A[i] = A[i] * 2;
				T[omp_get_thread_num()]++;
				NumOfIters++;
			}
		}
	}

	i=0; result=0;
	for(i=0; i<100; i++)
		result += A[i];
	printf("Array-sum AFTER computing: %d\n", result);
	for (i = 0; i < omp_get_num_threads(); i++)
	{
		printf("Thread %d: %d calculations\n", i, T[i]);
	}
	//printf("Thread 1: %d Rechnungen\n", T[0]);
	//printf("Thread 2: %d Rechnungen\n", T[1]);
	printf("numiters: %d iterations\n", NumOfIters);
	return 0;
}