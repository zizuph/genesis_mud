
/*  

   Room containing a giant clam, part of the mermaid quest. 
 
   coder(s):   Amelia 

   Modified by Maniac 7/9/96
   Changed desc in clam_block() / Hyde 27NOV15

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"

#include "defs.h"

#include SEA_QUESTS

inherit "/d/Calia/sea/std/sector_0_0_2_room";


object clam;

void
reset_room()
{
    if(!objectp(clam)) {
         clam = clone_object(SEA_CREATURES+"clam");
         clam->move_living("M",this_object());
    }
}


void
create_water_room()
{
    make_the_room("To the east you can see " +
        "through the clear water an alcove that appears to be full of " + 
        "oysters. Blocking the way, however, is a giant clam.\n", 
         3, 7, 2); 

    add_item(({"alcove", "oyster bed", "oysters", "oyster"}), 
             "There sure seem to be a lot of oysters in that alcove " +
             "over there!\n"); 

    add_swim_exit(SECTOR_PATH(3,6,2)+"wr_3_6_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(3,8,2)+"wr_3_8_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,7,2)+"wr_4_7_2", "west", 0, 1);
    add_swim_exit(OYSTER_ROOM, "east", "@@clam_block", 1); 
    add_swim_exit(SECTOR_PATH(4,6,2)+"wr_4_6_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,8,2)+"wr_4_8_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,7,1)+"wr_3_7_1", "up", 0, 0);

    reset_room();
}


int
clam_block()
{
    object tp = this_player(); 

    if (!objectp(clam) || clam->query_bound()) 
        return 0;

    tp->catch_msg("The giant clam opens and shuts menacingly, "+
         "forcing you back. It looks like you will have to " +
         "find some way to tie it.\n");
    say(QCTNAME(tp)+" tries to swim east but the giant clam "+
        "opens and shuts menacingly, forcing " + tp->query_objective() + 
        "back.\n", tp);
    return 1;
}

