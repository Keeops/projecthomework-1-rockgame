#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
int main()
{
	srand(time(NULL));
	int player1_matris[2][20], player2_matris[2][20],
	starting_player, other_player,
	temp_color, temp_number,
	temp_testing_player, temp_other_player,
	move_count = 0;
	
	void print_playerboard(int player){
	for (int i=0;i<2;i++)
	{
		if (i==0)
		{
			printf("Blue Rocks|  ");
		}
		else{
			printf("Red Rocks |  ");
		}
		for (int j=0;j<20;j++)
		{
			if (player==1)
			{
				printf("%d  ",player1_matris[i][j]);
			}
			else
			{
				printf("%d  ",player2_matris[i][j]);
			}
			
		}
		printf("\n");
	}
	}
	void printboard(){
		printf(" Player 1 |  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20\n");
		printf("----------|-------------------------------------------------------------\n");
		print_playerboard(1);
		printf("----------|-------------------------------------------------------------\n");
		printf("\n\n");		
		printf(" Player 2 |  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20\n");
		printf("----------|-------------------------------------------------------------\n");
		print_playerboard(2);
		printf("----------|-------------------------------------------------------------\n");

	}
	int test_rule_1(int testing_player, int other_player, int taken_rock_color, int taken_rock_number){	
		if ((taken_rock_number * 2)>20)
		{
			return 0;
		}
		if ((testing_player==1) && (player1_matris[taken_rock_color - 1][(((taken_rock_number)*2)-1)] == 0))
		{
			return 0;
		}
		else if ((testing_player==2) && (player2_matris[taken_rock_color - 1][(((taken_rock_number)*2)-1)] == 0))
		{
			return 0;
		}
		else{
			return 1;
		}
		
	}
	int test_rule_2(int testing_player, int other_player, int taken_rock_color, int taken_rock_number){
		if ((taken_rock_number - 4) < 1)
		{
			return 0;
		}
		int diff_color;
		if (taken_rock_color==1)
		{
			diff_color=2;
		}
		else{
			diff_color=1;
		}
//                                                     -5 cuz we have 0 to 19 index's we don't have 20th index
		if ((testing_player==1) && (player1_matris[diff_color - 1][(taken_rock_number)-5] == 0))
		{
			return 0;
		}
		else if ((testing_player==2) && (player2_matris[diff_color - 1][(taken_rock_number)-5] == 0))
		{
			return 0;
		}
		else{
			return 1;
		}
	}
	int test_rules(int rule_1, int rule_2){
		if ((rule_1 == 0) && (rule_2 == 0)){
			return 404;  
		}
		else if ((rule_1 == 1) && (rule_2 == 1))
		{
			int rdm;
			rdm = rand()%2 +1;
			if (rdm == 1)
			{
				return 1;
			}
			else{
				return 2;
			}
		}
		else{
			if (rule_1 == 1)
			{
				return 1;
			}
			else if (rule_2 == 1){
				return 2;
			}
		}
	}
	int giverock(int giver_player, int player, int color, int number){
		temp_color=color;
		temp_number=number;
		temp_testing_player=player;
		temp_other_player=giver_player;
		char col[10];
		if (giver_player==1)
		{
			player1_matris[color-1][number-1]-=1;
			player2_matris[color-1][number-1]+=1;
		}
		else{
			player2_matris[color-1][number-1]-=1;
			player1_matris[color-1][number-1]+=1;
		}
		if (color==1)
		{
			strcpy(col,"Blue");
		}
		else{
			strcpy(col,"Red");
		}
		printf("\n\n\n\n");
		printf("--------------------------------------------------------\n");
		printf("Player %d's %s colored %d number rock given to Player %d\n",giver_player, col, number, other_player);
		printf("--------------------------------------------------------\n");
		printf("                     New Board                    \n");
		printf("          ------------------------------          \n");
		printboard();
		move_count += 1;
	}
	
	for (int i=0;i<2;i++)
	{
		for (int j=0;j<20;j++)
		{
			player1_matris[i][j] = 1;
			player2_matris[i][j] = 1;
		}
	}
	starting_player = rand()%2 + 1;
	if (starting_player==1)
	{
		other_player=2;
	}
	else{
		other_player=1;
	}
	giverock(starting_player, other_player, rand()%2 +1, rand()%10 +1);
	
	while(1){
		int result, result_1, result_2;
		char col[10];
		result_1  = test_rule_1(temp_testing_player, temp_other_player, temp_color, temp_number);
		result_2 = test_rule_2(temp_testing_player, temp_other_player, temp_color, temp_number);
		result = test_rules(result_1, result_2);
		if (result==404)
		{		
			printf("\n\n\n\n\n");
			printf("--------------------------------------------------------\n");
			printf("                     GAME OVER                    \n");
			printf("          ------------------------------          \n");
			printf("                   PLAYER %d WON                  \n",temp_other_player);
			printf("          ------------------------------          \n");
			printf("                 TOTAL MOVES : %d                 \n",move_count);
			printf("--------------------------------------------------------\n\n\n");
			printf("                  THE FINAL BOARD                 \n");
			printf("          ------------------------------          \n");
			printboard();
			break;
		}
		else if (result==1)
		{
			giverock(temp_testing_player, temp_other_player, temp_color, (temp_number * 2));
			
		}
		else if (result == 2)
		{
			if (temp_color == 1)
			{
				giverock(temp_testing_player, temp_other_player, 2, (temp_number - 4));
				
			}
			else{
				giverock(temp_testing_player, temp_other_player, 1, (temp_number - 4));
				
			}
			
		}
		
	}
	return 0;
}