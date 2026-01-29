/* stairwy3.c: Top of staircase: Serpine, 4-24-95. */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
    	set_short("a small tunnel");
   	set_long("You are in a small tunnel carved in a rock formation. "+
            "Light eminates from the tunnel walls and a tunnel leads "+
            "north and south from here.\n"); 

 
    INSIDE

    add_exit(PSION_ROOM+"startspt.c", "northeast", 0, 1);
    add_exit(PSION_ROOM+"hallway2.c", "south", 0, 1);
    add_exit(PSION_ROOM+"training.c", "west", "@@dark_area", 1, 1);
    add_exit(PSION_ROOM+"counentr.c", "down", 0, 1);   
}

int
dark_area()
{
    string name = TP->query_real_name();

    TP->catch_msg("The darkness recedes as you pass through it.\n");

    if (CHECK_PUNISHMENT(EXPEL, name)) 
    {
        TP->catch_msg("Suddenly the darkness becomes very solid. "
          +"You feel your mind being invaded. You get a strong "
          +"sense of danger and decide that going that way is not "
          +"quite a good idea.\n");
        return 1;
    }

    if((!IS_MEMBER(TP))&&(!IS_WIZ(TP)))
    {
        TP->catch_msg("Suddenly the darkness becomes very solid. "
          +"You feel your mind being invaded. You get a strong "
          +"sense of danger and decide that going that way is not "
          +"quite a good idea.\n");
        return 1;
    }


    return 0;
}