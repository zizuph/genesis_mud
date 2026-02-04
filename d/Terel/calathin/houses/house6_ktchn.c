/*  This is the standard kitchen for the poor houses in the northeast
    portion of Calathin.

    Coded by Vader on 7/23/92
    
    Modified by Tomas for new Calathin Code, 11/19/1999
*/

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"

create_room()
{
   set_short("Smelly kitchen");
   set_long(break_string("The smell here is terrible!!!  This kitchen has " +
    "been used to cook some pretty nasty stuff quite some time ago, and " +
    "now that it has rotted, it smells even worse.  " +
    "The kitchen consists of only a fireplace, and a counter top " +
    "that has many stains on it, including blood stains.\n", 70));

   add_item(({"fireplace"}), "This fireplace is used for cooking. There " +
    "are several weeks worth\nof ashes inside it, and a dirty spit rests " +
    "atop it, securely fastened\nby lock and key.\n");

   add_item(({"spit"}), "It is fastened to the fireplace by a lock.  These " +
    "peasants don't have\nmuch, but this spit is sometimes their most " +
    "treasured item.  Without\nit, they couldn't cook.\n");

   add_item(({"lock"}), "You've never seen the like.  You'll probably " +
    "never find the key.\n");

   add_item(({"blood", "blood stains", "stains"}),
    "It covers the entire counter.  You also notice it on the wall, " +
    "and the\nway it was splattered sends a chill up your spine!\n");

   add_item(({"counter", "counter top", "countertop"}),
    "It is made of old, rotted wood, and is stained along every portion " +
    "of its\nsurface.\n");

   add_exit(CALATHIN_DIR + "houses/house6", "south", 0);
}
 
