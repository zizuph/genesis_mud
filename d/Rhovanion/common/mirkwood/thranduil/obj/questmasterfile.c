#include "/d/Rhovanion/defs.h"

int reward(object ob,int nr);
int display_assignment(int nr,object ob);

/* reward - decide if the player is worthy... in that case, reward him! */

int reward(object ob,int nr)
{
  /* here you add your own checking routines */
  
  switch(nr)
    {
    case 0: return 0;
    default: return 0;
    }
}

/* display_assignment - display the quest text */

int display_assignment(int nr,object ob)
{
  switch(nr)
    {
    case 0: ob->catch_msg("Yes! It works!!!\n");
      return 1;
    default: ob->catch_msg("There are no more quests for you to do!\n");
      return 1;
    }
}
