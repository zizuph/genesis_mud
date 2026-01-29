
 /* A Greensea village room coded by Maniac & Jaacar 
    It is the workplace of the herbalist Lobar. 

    9/11/96
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

object npc;

void
reset_room()
{
    if (!objectp(npc))
    {
        npc= clone_object(SEA_CREATURES+"herbalist");
        npc->move_living("rises from the ground", this_object());
    }
}

void
create_room()
{
    set_short("the Herbalist");
    set_long("The faint smell of stored and dried herbs "+ 
        "touches your nostrils as you look around. " + 
        "The walls are painted a deep natural green " +
        "and are hung with local wildflowers and sea grasses. " +   
        "On the neatly swept floor is stood a large collection of " +
        "plain unglazed earthenware jars, all of them labelled. " + 
        "There are also some baskets hung from the ceiling by " +
        "little chains, containing large bunches of herbs that " +
        "are being dried. A small desk stands at the far end of " +
        "the room.\n");  

   add_item(({"labels", "jar labels"}), 
       "You can find out from Lobar himself what he has in stock. " + 
       "There are often many of the best known herbs and some local " +
       "ones too kept here.\n"); 

   add_item(({"sea grasses", "grasses"}),
      "The grasses are sea grasses and dried pampas fronds.\n"); 

   add_item(({"wildflowers", "local wildflowers", "flowers"}), 
       "The seem to be recently picked, and vary greatly in colour.\n"); 

   add_item("floor", "It's neatly swept and there are lots of jars " +
                     "stood on it.\n"); 

   add_item(({"desk", "small desk"}), 
             "It would appear to be Lobar's working surface.\n"); 

   add_item(({"jars", "plain jars"}), 
            "There are a lot of them grouped on the floor. Not much " + 
            "to distinguish them apart from the labels, since they " +
            "are all of the same plain light dried clay colour.\n"); 

   add_item(({"baskets", "herbs", "chains", "baskets of herbs"}), 
            "Baskets containing drying herbs are hung from the ceiling " + 
            "by little chains.\n");  

   add_prop(ROOM_I_IS, 1);
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);

    add_exit(BEACH+"village6","north",0,0);

    reset_room();
}
