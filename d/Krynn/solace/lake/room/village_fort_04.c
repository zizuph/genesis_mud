/*
 * Fortess room in the Toron minotaur village  
 * Made to inherit village_base_in.
 * Made by Cherek Jan 2007.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_IN;

void
create_toron_room() 
{
    set_location("FORT");
    set_short("Inside a storage room in a wooden fortress");
    set_start_desc("You stand inside a storage room in the eastern " +
                   "part of a fortress made almost entirely of wood. ");
    set_long_desc("This room does not seem to be entirely completed. " +
                  "The walls are bare and the floor is not even in " +
                  "place yet. Several crates and sacks have been " +
                  "stacked against the walls and it is not much space " +
                  "left to move around. A single torch lights up a " +
                  "rather dark and windowless room. There is a doorway " +
                  "in the west wall. ");

    add_item("fortress",
             "You can smell the fresh wood it is made of. \n"); 

    add_item("wood",
             "Every peice of wood is sleek and well-polished. \n"); 
             
    add_item(({"torch", "torches"}),
               "It is just a standard torch. Good for light and " +
               "good for heat. As always with torches, smoke is " +
               "a problem though. \n");

    add_item(({"wall", "walls", "logs", "log", "pole",
               "poles", "plank", "planks"}),
               "The walls are remarkably sleek and well-polished. " +
               "Whoever built this fortress took great pride in his " +
               "or her work. \n");

    add_item(({"floor", "ground"}),
               "There is no floor. Just a mix of dirt, and, well dirt. \n");

    add_item("dirt",
             "It is just dirty. Like dirt is supposed to be. \n");
               
    add_item(({"crate", "crates", "sack", "sacks"}),
               "You can only guess what is inside them. Probably " +
               "something valuable or something that cannot be stored " +
               "outside. You better not touch them. \n");

    add_item(({"doorway", "west wall"}),
             "The doorway leads back into the main hallway. \n");

    add_item(({"room", "storage room"}),
               "Its is clear this room is not completed yet. \n");           

    add_exit(ROOM + "village_fort_01","west",0,3);  

    reset_room();
}
