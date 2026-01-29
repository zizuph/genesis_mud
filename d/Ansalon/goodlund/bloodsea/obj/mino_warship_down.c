/*
 * Below deck on the minotaur warship sailing the bloodsea.
 * Made by Cherek Jan 2007.
 */
 
#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include <composite.h>
#include <filter_funs.h>
inherit "/std/room.c";

void set_exit(string exit_name);

void
create_room() 
{

    set_short("Below main deck");
    set_long("You stand inside a dimly lit corridor below the " +
             "main deck of a minotaur warship. The passage leads " +
             "from the aft to the fore of the ship and along the " +
             "walls are several simple bunks placed. A few chests " +
             "and crates stands on the otherwise bare wooden floor. " +
             "A sturdy ladder leads back up.\n");
            
    add_item(({"corridor", "passage"}),
               "This space seem to be a combination of " +
               "sleeping quarters and storage room.\n");

    add_item(({"wall", "walls", "bunk", "bunks"}),
               "The bunks seem to be designed to exactly fit " +
               "these walls. They do not look very comfortable. \n");               
   
    add_item(({"chest", "chests", "crate", "crates"}),
               "They are all tightly secured and locked. \n");

    add_item(({"floor"}),
               "The wooden planks are well-polished and in good " +
               "shape even though you notice a few patches here " +
               "and there. \n");               

    add_item(({"patches", "planks"}),
               "It seems like the floor have been recently repaired, " +
               "perhaps evidence of battle. \n"); 
 
     add_item(({"ladder", "sturdy ladder"}),
                "It does look very sturdy.\n");                                         

    add_item(({"deck", "main deck", "ceiling"}),
               "The ceiling of this corridor is obviously the main " +
               "main deck of the ship. \n");    

     add_item(({"ship", "warship"}),
                "Everything on this ship seem to have been very " +
                "carefully designed. \n");
                
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

void set_exit(string exit_name)
{
    remove_exit("up");
    add_exit(exit_name, "up", 0, 1);

}

void clean_loot()
{
    cleanup_loot();

}