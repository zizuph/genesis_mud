/*
   Pax Tharkas, Ground level, Large womens prison in the west tower.

   large_w_prison.c
   ----------------

   Coded ........: 95/03/02
   By ...........: Jeremiah

   Latest update : 95/03/30
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

void
create_pax_room()
{
   set_short("Large prison room");
   set_long("You are standing a huge dimly lit room. This room " +
            "probably covers almost half this level of the tower. " +
            "A large amount of people have been crowded into this room, " +
            "sitting, standing or lying down. The amount of people in " +
            "here makes the room seem small and the air feel heavy and " +
            "humid. The only things in here, except for the people, are " +
            "rows upon rows of thin mattresses. As far as you can see " +
            "there are only women in here. All of them are pale and " +
            "gaunt, obviously due to the lack of nourishing food.\n"); 

   add_item("people", "A large amount, too large for the size of this " +
            "room, of people have been crowded in here. It looks like " +
            "they are all women.\n");

   add_item("women", "The room is filled with women prisoners. They all " +
            "look pale and gaunt, lacking nourishing food. They all look " +
            "at you surprised by your arrival.\n");

   add_item(({"mattress", "mattresses"}), "Rude straw mattresses. They " +
            "look more like old sacks filled with straw, than actual " +
            "matresses.\n");
 
   INSIDE;

   add_exit(GROUND_LEVEL + "guard_room1", "north",0);
}
