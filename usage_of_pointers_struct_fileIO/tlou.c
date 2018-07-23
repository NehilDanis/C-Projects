#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _weapon //I used structure for weapons.
{
    int round;
    int dph;
    char *name;
    int damageformed;
    struct _weapon *next; //I used link list to combine weapons and players.
}weapon;

typedef struct _player //I used another structure for players.
{
    int health;
    int damage;
    char *name;
    weapon *current;
}player;



int main ()
{
    player *ellie=(player*)malloc(sizeof(player)); //I introduced all variables in dynamic memory.And I assigned values on them.
    ellie->health=100;
    ellie->damage=10;
    player *runner=(player*)malloc(sizeof(player));
    runner->name=(char*)malloc(10);
    strcpy(runner->name,"runner");
    player *stalker=(player*)malloc(sizeof(player));
    stalker->name=(char*)malloc(10);
    strcpy(stalker->name,"stalker");
    player *clicker=(player*)malloc(sizeof(player));
    clicker->name=(char*)malloc(10);
    strcpy(clicker->name,"clicker");
    player *bloater=(player*)malloc(sizeof(player));
    bloater->name=(char*)malloc(10);
    strcpy(bloater->name,"bloater");

    weapon *knife=(weapon*)malloc(sizeof(weapon));
    knife->dph=10;
    knife->next=NULL;
    knife->name=(char*)malloc(20);
    strcpy(knife->name,"knife");
    weapon *medipack=(weapon*)malloc(sizeof(weapon));
    medipack->name=(char*)malloc(20);
    strcpy(medipack->name,"medipack");


    ellie->current = knife; //I equalized knife to Ellie's first knife.
    char *line_i; //I used malloc function again to use dynamic memory
    line_i=(char*)malloc(sizeof(char)*150);
    char *line_o;
    line_o=(char*)malloc(sizeof(char)*150);
    int death_runner=0; //I introduce this 4 variables to calculate the number of each death monsters.
    int death_clicker=0;
    int death_bloater=0;
    int death_stalker=0;
    FILE *iPtr;//the pointer of input file
    FILE *oPtr;//the pointer of output file
    iPtr=fopen("input.txt","r"); //This line provide us to read the input file.
    oPtr=fopen("output.txt","w"); //This line provide us to write the results of code on the output file.

    while(!feof(iPtr)) //I understand that my code can arrive end of the input file or can not.
    {
        fscanf(iPtr,"%s",line_i);//I read the input file.
        if(strcmp(line_i,"runner")==0)//I used string function (strcmp)to compare the input file and variables.
        {
            runner->health=20; //I introduce the health point and damage of monster.
            runner->damage=5;
            while(ellie->health>0 && runner->health>0) 
            {
                fprintf(oPtr,"Ellie hits to runner with %s.\n",ellie->current->name);
                runner->health-=ellie->current->dph;
                ellie->current->round--;
                if(runner->health>0)
                {
                	fputs("Runner hits to Ellie.\n",oPtr);
                	ellie->health-=runner->damage;
            	}
            	if(ellie->current->round==0) //I checked the number of ammo of the first weapon.
                {
                    fprintf(oPtr,"Ellie run out of %s ammo.\n",ellie->current->name);
                    ellie->current=ellie->current->next;
                    fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
                }
            }//end of while
            if(runner->health<=0)
        	{
               	fprintf(oPtr,"Runner dies.Ellie has %d life point.\n",ellie->health);
                death_runner++;
           	}//end of if
            else if(ellie->health<=0)
        	{
                fprintf(oPtr,"Ellie is dead by runner.She killed %d runners,%d stalkers,%d clickers and %d bloaters.\n",death_runner,death_stalker,death_clicker,death_bloater);
                break;
            }


        }//end of if

        else if(strcmp(line_i,"stalker")==0) //I used string function (strcmp)to compare the input file and variables.
        {
            stalker->health=40; //I introduce the health point and damage of monster.
            stalker->damage=10;
            while(ellie->health>0 && stalker->health>0)
            {
                fprintf(oPtr,"Ellie hits to stalker with %s.\n",ellie->current->name);
                ellie->current->round--;
                stalker->health-=ellie->current->dph;
                if(stalker->health>0)
                {
                	fputs("Stalker hits to Ellie.\n",oPtr);
                	ellie->health-=stalker->damage;
                }
           	   if(ellie->current->round==0) //I checked the number of ammo of the first weapon.
                {
                    fprintf(oPtr,"Ellie run out of %s ammo.\n",ellie->current->name);
                    ellie->current=ellie->current->next;
                    fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
                }
            }//end of while
            if(stalker->health<=0)
            {
                fprintf(oPtr,"Stalker dies.Ellie has %d life point.\n",ellie->health);
                death_stalker++;
            }//end of if
            else if(ellie->health<=0)
            {
                fprintf(oPtr,"Ellie is dead by stalker.She killed %d runners,%d stalkers,%d clickers and %d bloaters.\n",death_runner,death_stalker,death_clicker,death_bloater);
                break;
        	}
        }//end of else if

        else if(strcmp(line_i,"bloater")==0) //I used string function (strcmp)to compare the input file and variables.
        {
            bloater->health=100; //I introduce the health point and damage of monster.
            bloater->damage=60;
            while(ellie->health>0 && bloater->health>0)
            {
               fprintf(oPtr,"Ellie hits to bloater with %s\n",ellie->current->name);
               bloater->health-=ellie->current->dph;
               ellie->current->round--;
               if(bloater->health>0)
               {
            		fputs("Bloater hits to Ellie.\n",oPtr);
               		ellie->health-=bloater->damage;
               }
           	   if(ellie->current->round==0) //I checked the number of ammo of the first weapon.
                {
                    fprintf(oPtr,"Ellie run out of %s ammo.\n",ellie->current->name);
                    ellie->current=ellie->current->next;
                    fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
                }
            }//end of while
            if(bloater->health<=0)
            {
                fprintf(oPtr,"Bloater dies.Ellie has %d life point.\n",ellie->health);
                death_bloater++;
            }//end of if
            else if(ellie->health<=0)
            {
                fprintf(oPtr,"Ellie is dead by bloater.She killed %d runners,%d stalkers,%d clickers and %d bloaters.\n",death_runner,death_stalker,death_clicker,death_bloater);
                break;
            }
        }//end of else if

        else if(strcmp(line_i,"clicker")==0) //I used string function (strcmp)to compare the input file and variables.
        {
           clicker->health=60; //I introduce the health point and damage of monster.
           clicker->damage=30;
           while(ellie->health>0 && clicker->health>0)
           {
               fprintf(oPtr,"Ellie hits to Clicker with %s.\n",ellie->current->name);
               clicker->health-=ellie->current->dph;
               ellie->current->round--;
               if(clicker->health>0)
               {
               		fputs("Clicker hits to Ellie.\n",oPtr);
               		ellie->health-=clicker->damage;
           	   }
           	   if(ellie->current->round==0) //I checked the number of ammo of the first weapon.
                {
                    fprintf(oPtr,"Ellie run out of %s ammo.\n",ellie->current->name);
                    ellie->current=ellie->current->next;
                    fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
                }
           }
           if(clicker->health<=0)
           {
               fprintf(oPtr,"Clicker dies.Ellie has %d life point.\n",ellie->health);
               death_clicker++;
           }
           else if(ellie->health<=0)
           {
               fprintf(oPtr,"Ellie is dead by clicker.She killed %d runners,%d stalkers,%d clickers and %d bloaters.\n",death_runner,death_stalker,death_clicker,death_bloater);
               break;
           }

        }
        else if(strcmp(line_i,"shotgun")==0) //I used string function (strcmp)to compare the input file and variables.
        {
        	weapon *shotgun=(weapon*)malloc(sizeof(weapon));//I introduced weapon.
		    shotgun->dph=20;
		    shotgun->round=8;
		    shotgun->next=NULL;
		    shotgun->name=(char*)malloc(20);
		    strcpy(shotgun->name,"shotgun");
        	shotgun->next=ellie->current;
        	ellie->current=shotgun;
        	fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
        }
        else if(strcmp(line_i,"revolver")==0) //I used string function (strcmp)to compare the input file and variables.
        {
			weapon *revolver=(weapon*)malloc(sizeof(weapon));//I introduced weapon.
		    revolver->dph=15;
		    revolver->round=6;
		    revolver->next=NULL;
		    revolver->name=(char*)malloc(20);
		    strcpy(revolver->name,"revolver");
        	revolver->next=ellie->current;
        	ellie->current=revolver;
        	fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
        }
        else if(strcmp(line_i,"molotov")==0) //I used string function (strcmp)to compare the input file and variables.
        {
        	weapon *MolotovCocktail=(weapon*)malloc(sizeof(weapon));//I introduced weapon.
		    MolotovCocktail->dph=100;
		    MolotovCocktail->round=1;
		    MolotovCocktail->next=NULL;
		    MolotovCocktail->name=(char*)malloc(20);
		    strcpy(MolotovCocktail->name,"molotov");
        	MolotovCocktail->next=ellie->current;
        	ellie->current=MolotovCocktail;
        	fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
        }
        else if(strcmp(line_i,"ak47")==0) //I used string function (strcmp)to compare the input file and variables.
        {
        	weapon *AK=(weapon*)malloc(sizeof(weapon));//I introduced weapon.
		    AK->dph=30;
		    AK->round=10;
		    AK->next=NULL;
		    AK->name=(char*)malloc(20);
		    strcpy(AK->name,"ak47");
        	AK->next=ellie->current;
        	ellie->current=AK;
        	fprintf(oPtr,"Ellie got the %s as the first weapon.\n",ellie->current->name);
        }

        else if(strcmp(line_i,"medipack")==0) //I used string function (strcmp)to compare the input file and variables.
        {
            medipack->damageformed=50;
            ellie->health+=medipack->damageformed;
            if(ellie->health>100)
            {
                ellie->health=100;
            }
            fprintf(oPtr,"Ellie has a medipack.Her life point is %d\n",ellie->health);
        }//end of else if
    }//end of the whole while statement

    if(ellie->health>0)
    {
        fprintf(oPtr,"Ellie is survived..She killed %d runners,%d stalkers,%d clickers and %d bloaters",death_runner,death_stalker,death_clicker,death_bloater);
    }
    fclose(iPtr);
    fclose(oPtr);
    return 0;
}


