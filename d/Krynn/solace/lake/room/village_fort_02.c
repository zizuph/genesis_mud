/*
 * Fortess room in the Toron minotaur village  
 * Made to inherit village_base_in.
 * Made by Cherek Jan 2007.
 */
 
#include "../local.h"

inherit VILLAGE_BASE_IN;

object takchuk;

void
reset_toron_room()
{

    if (!objectp(takchuk))
    {
        takchuk = clone_object(NPC + "minotaur_takchuk.c");
        
        takchuk->move(TO, 1);   
        
        tell_room(TO, "A minotaur arrives.\n", takchuk);     
    }

}

void
create_toron_room() 
{
    set_location("FORT");
    set_short("Inside a study in a wooden fortress");
    set_start_desc("You stand inside a room in the western part " +
                   "of a fortress made almost entirely of wood. ");
    set_long_desc("This particular room appears to be some kind " +
                  "study or library. Books are scattered in piles " +
                  "on the floor and the only real furniture are a " +
                  "massive oak table and a matching chair. Whoever " +
                  "owns this room must have just recently moved " +
                  "in. Several fine rugs and furs have been placed " +
                  "on the floor and a few large torches lights up " +
                  "the windowless room. There is a doorway in the " +
                  "east wall. ");

    add_item("fortress",
             "You can smell the fresh wood it is made of. \n"); 
             
    add_item("wood",
             "Every peice of wood is sleek and well-polished. \n");

    add_item(({"study", "room", "library"}),
               "The whole room is a mess. \n"); 
                
    add_item(({"wall", "walls", "logs", "log", "pole", 
               "poles", "plank", "planks"}),
               "The walls are remarkably sleek and well-polished. " +
               "Whoever built this fortress took great pride in " +
               "his or her work. \n");

     add_item(({"rug", "rugs", "fur", "furs", "floor", "ground"}),
                "These rugs and furs are in much better condition " +
                "then the rest you have seen in the village. They " +
                "do not even smell bad. \n");  

     add_item(({"torch", "torches"}),
                "They are just standard torches. Good for light " +
                "and good for heat. As always with torches, smoke " +
                "is a problem. \n");

     add_item(({"table", "oak table", "chair", "furniture"}),
                "You are slightly surprised to see real furniture " +
                "in this camp. Maybe the minotaurs who live here " +
                "are not as savage as you first thought. \n");

    add_item(({"book", "books", "pile", "piles"}),
               "You see all kinds of books but since you do not " +
               "understand the language you have no idea what " +
               "they are about. \n");

     add_item(({"doorway", "east wall"}),
                "The doorway leads back into the main hallway. \n");

    add_exit(ROOM + "village_fort_01","east",0,3);  

    reset_room();
}
