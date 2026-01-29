/* stairwy1.c: Bottom of staircase. Serpine, 4-24-95. */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
   	set_short("a small tunnel");
   	set_long("You are in a small tunnel carved in a rock formation. "+
            "Light eminates from the tunnel walls and a tunnel leads "+
            "north and south from here. To the west and east you can see "+
            "unnaturaly dark areas in the walls.\n");

   	add_item(({"area", "areas", "wall", "walls"}), "They look like doors of "+
            "some sort.\n");

   	INSIDE

   	add_exit(PSION_ROOM + "hallway2.c", "north", 0, 1);
   	add_exit(PSION_ROOM + "joinroom.c", "south", 0, 1);
    	add_exit(PSION_ROOM + "equiproom.c", "west", "@@dark_area", 1, 1);
    	add_exit(PSION_ROOM + "boardroom.c", "east", "@@dark_area", 1, 1);
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