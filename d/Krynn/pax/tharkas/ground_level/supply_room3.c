/*
   Pax Tharkas, Ground level, Supply room in west tower.

   supply_room3.c
   --------------

   Coded ........: 95/03/02
   By ...........: Jeremiah

   Latest update : 05/10/08
   By ...........: Cotillion
   - Don't clone infiniate amounts of rat.

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

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
   set_short("Large supply room");
   set_long("You are standing in the west end of a large supply room. " +
            "Sturdy shelves line the walls only interrupted by space " +
            "for the exits. Several shelves transverse the room " +
            "obscuring the view to the other part of the supply " +
            "room. \n");

   add_item("shelves", "Sturdy wooden shelves running along the walls " +
            "of this room. Right now they're almost all empty, except " +
            "for a few bundles of red clothings on some of the shelves " +
            "transversing the room.\n");

   add_item(({"clothing", "clothings"}), "You recognize these as the " +
            "military clothings worn by the red dragon army. They're " +
            "probably not worth the trouble of carrying.\n");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "supply_room2", "east", 0);
}
