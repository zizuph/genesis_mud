/*  Basement room in the Mansion.  Coded by Vader on 8/21/92    */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

create_room()
{
    set_short("Wine Cellar");
   set_long(break_string(
   "Row upon row of empty shelves line this room.  This once held " +
   "an impressive collection of fine wines.  Since wine is in such " +
   "demand, it has long since been stolen.  In one corner you see " +
   "what looks like the remains of a corpse.  A bloody trail leads " +
   "to it.\n", 70));

   add_item(({"trail", "bloody trail", "blood trail"}), 
    "This trail looks like it was made very recently.\n");

   add_item(({"remains", "remains of corpse", "corpse"}), 
    break_string("Small bits and pieces of various body parts lie " +
    "on the ground here.  The blood is splattered all over the place " +
    "in this corner.  You see several scratches in the floor that " +
    "suggest this corpse was carved like meat.\n", 70));

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);

   add_exit(BASE + "hall3", "west", 0);

}

