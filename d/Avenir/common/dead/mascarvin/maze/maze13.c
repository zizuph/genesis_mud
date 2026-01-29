// Lilith Sept 2021: Added message when player finishes the maze.

#include "defs.h"
inherit MAZE + "maze";


int go_down()
{
    object   down = find_object(SKULL);

    if(down && sizeof(filter(all_inventory(down), interactive)))
    {
        write("There is someone already down in there, so "+
		    "you should wait a few minutes or try again later.\n");
        return 1;
    }

  write("You descend the winding staircase...\n");
  say(QCTNAME(TP) + " goes down.\n");
  return 0;
}


void
create_maze()
{
    string str;

    str = query_long();

    set_long(str + "\n   At last, something different! There are "
	     +"no words carved into the threshold of the staircase "
		 +"leading down into a glowing brightness that makes "
		 +"your eyes ache.\n");


    add_exit("skull", "down", go_down);
}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);
	if (!interactive(to))
		return;
    if (to->query_skill((SS_MASQ_STAGE) < STAGE_3_MAZE))
        to->set_skill(SS_MASQ_STAGE, STAGE_3_MAZE);
	
	to->catch_tell("You feel a tremendous sense of accomplishment as you "
	    +"realize you have found your way out of the maze!\n");
		
}