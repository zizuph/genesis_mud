/*
   Pax Tharkas, Ground level, Armoury in west tower.

   armoury.c
   ---------

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
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;


void
create_pax_room()
{
   set_short("Armoury");
   set_long("You are standing in what appears to be an armoury. Row " +
            "after row of wooden weapon racks cover this room. Large " +
            "racks along the walls and smaller ones standing in rows " +
            "on the floor. This place could easily hold huge amounts of " +
            "weapons. Unfortunately the racks are all empty now.\n");

   add_item(({"rack", "racks"}), "Wooden racks in different sizes. The " +
            "large ones along the walls and the smaller ones in rows all " +
            "over the floor. The weapon racks are empty.\n");  
	
   INSIDE;

   add_exit(GROUND_LEVEL + "supply_room2", "south", 0);
}
