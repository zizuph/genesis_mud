/*
   Pax Tharkas, Ground level, prison cell.

   cell.c
   ------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/02/03
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object door;

void
create_pax_room()
{
   set_short("Prison cell");
   set_long("You are standing in a very spartan furnitured room. " +
            "The room looks almost too much like a prison cell. The " +
            "walls are made of dark grey rock, giving the cell a " +
            "gloomy appearance. You wouldn't want to get stuck in " +
            "here. A narrow rickety folding bed and a small " +
            "table, both made of wood, is all thats in here. " +
            "The only way out of here is through the door.\n");
	
   INSIDE;

   add_item(({"bed", "folding bed"}), "It's an old rickety folding " +
            "bed, it doesn't look comfortable at all.\n");

   add_item(({"table", "small table"}), "A small wooden table. The " +
            "surface area not larger than that of a small shield.\n");
  
   door = clone_object(POBJ + "cell_door1b");
   door->move(TO);
}


