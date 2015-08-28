#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef neuro_h
#define neuro_h

#define NET_SIZE 200

struct net
{
	float neurons[NET_SIZE];
	float thresholds[NET_SIZE];
	float weights[NET_SIZE][NET_SIZE];
	float fire[NET_SIZE];

	void init_urand()
	{
		for (int i = 0; i < NET_SIZE; i++)
		{
			thresholds[i] = float(rand()%10001)/5000.0;
			for (int j = 0; j < NET_SIZE; j++)
				weights[i][j] = float(rand()%10001)/2500.0 - 2.0;
		}
	}

	void delta_urand()
	{
		for (int i = 0; i < NET_SIZE; i++)
		{
			thresholds[i] += (float(rand()%10001)/5000.0)/1000.0;
			for (int j = 0; j < NET_SIZE; j++)
				weights[i][j] += (float(rand()%10001)/2500.0 - 2.0)/1000.0;
		}
	}

	void send()
	{
		for (int i = 0; i < NET_SIZE; i++)
		{
			fire[i] = floor(neurons[i]/thresholds[i]);
			neurons[i] -= fire[i]*thresholds[i];
		}
	}

	void receive()
	{
		for (int i = 0; i < NET_SIZE; i++)
			for (int j = 0; j < NET_SIZE; j++)
				neurons[j] += fire[i]*weights[i][j];
	}
};

#endif
