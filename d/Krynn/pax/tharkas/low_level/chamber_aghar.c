/*
   Pax Tharkas, Low level, chamber of the Aghar.

   chamber_aghar.c
   ---------------

   Coded ........: 95/01/10
   By ...........: Jeremiah

   Latest update : 04/10/08
   By ...........: Cotillion

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object *rats = ({ 0, 0, 0, 0 });

void
reset_pax_room()
{
    int i, size;
    
    /* Reset one rat each time, up to max of 4 */
    size = sizeof(rats);
    for (i = 0, size = sizeof(rats); i < size; i++)
    {
        if (!objectp(rats[i]))
        {
            rats[i] = clone_object(PMONSTER + "rat");
            rats[i]->move_living("arrives", TO);
            break;
        }
    }
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Chamber of the Aghar");
   set_long("You are in a large room. Most of the walls in this room " +
            "have collapsed, leaving huge heaps of boulders and rubble. " +
            "The only wall left intact is the northern wall, with the " +
            "only exit from this room. A long timber is balanced on a " +
            "boulder in the center of the room. At each end of the timber " +
            "is a wide, dish shaped container. Set on the ground by these " +
            "containers is a pile of large stones and a tall wooden box. " +
            "Huge mattresses have been spread on the floor beyond " +
            "either end of the timber.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_item(({"boulders", "rubble"}), "These are the remains of the " +
            "caved in walls.\n");

   add_item("boulder", "A large boulder used as the pivoting point " +
            "of what looks like a primitive balance.\n");

   add_item("balance", "Well.. it looks like a balance, and it probably " +
            "is. A primitive one though. It is made of a long timber " +
            "with a dish at each end, balancing on a boulder.\n");

   add_item(({"box", "wooden box"}), "This is a plain wooden box made " +
            "of rough bright wood.\n");

   add_item(({"mattress", "mattresses"}), "Large mattresses made of rough " +
            "canvas. Judging from the straw sticking out through some " +
            "holes in the canvas, you figure that the mattresses are " +
            "probably filled with the stuff.\n");

   add_item("timber", "A long timber of solid wood, almost as thick as " +
            "a human leg, balancing on a boulder in the center of the " +
            "room.\n"); 

   add_item("pile", "A pile of large stones.\n");

   add_item(({"stone", "stones"}), "Large stones in different shapes and " +
            "sizes.\n");

   add_item(({"dish", "container"}), "A large dish at each end of a " +
            "long timber. These containers look most of all like a " +
            "huge shield or a very large bowl.\n");

   add_exit(LOW_LEVEL + "corridor6", "north", 0);
} 
