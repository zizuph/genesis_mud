/**********************************************************************
 * - cabin.c                                                        - *
 * - Cabin for ship from MacDunn to SaMorgan                        - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Updated by Damaris@Genesis 08/2005                             - *
 * - Ported by Tapakah to new ship system 04/2009                   - *
 * - Fixed an incorrect reset bug 10/2021                           - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types
 

#include <macros.h> 
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Khalakhor/sys/defs.h"
#include "../ship.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIPROOM;

object desk;
 
string
sounds ()
{
	return "The ship rises slightly as it slices through a huge wave.\n";
}

int
object_missing_in_desk (string object_filename)
{
  object *items = filter(all_inventory(desk),
                         &wildmatch(object_filename + "#*", ) @ file_name);

  if (sizeof(items))
    return 0;
  clone_object(object_filename)->move(desk);
  return 1;
}

void
check_desk ()
{
  if (object_missing_in_desk(MAP) || object_missing_in_desk(GLOBE))
    tell_room(TO,
              "A young elf rushes in, places something on the "+
              "desk and rushes back out.\n");
}

void reset_room ()
{
	check_desk();
	::reset_room();
} 
 
void
create_room ()
{
  ::create_shiproom();
  
	set_short("the cabin of the Bella Diaz");
	set_long("   This is the captain's cabin of the Bella Diaz. "+
           "There is a large desk placed firmly in the corner of this "+
           "cabin. The cabin is small and cramped but adequate for the "+
           "captain's needs.\n");
	add_item(({"cabin","quarters","cramped quarters",}), query_long);
	add_item(({"timber","surrounding timber","wall","walls"}),
           "The walls are made of a sturdy timber, that would resist " +
           "any oceanic storm.\n");
	add_item("ceiling","The ceiling is constructed of wooden "+
           "beams.\n");
	add_item(({"beams","wooden beams"}),"The hefty beams of wood "+
           "are constructed of oak.\n");
	add_item("oak","The oak tree is a typical wood used for ship " +
           "construction.\n");
	add_item("floor","The floor is made of sturdy planks.\n");
	add_item(({"planks","sturdy planks"}),"The sturdy planks "+
           "appear to be constructed of oak.\n");
	add_item(({"walls","wooden walls","wall"}),"Each wall is "+
           "made of oak.\n");
	add_cmd_item(({"charts","navigational charts"}),({"get","take"}),
               "Taking the charts would only make sense if you were the " +
               "captain of a ship running between MacDunn and SaMorgan!\n");
	add_item("chart","Each chart appears similar. Perhaps looking "+
           "at all the charts may give you a better idea. One looks like "+
           "a map.\n");
	add_item("deck","The main deck of the ship lies outside the "+
           "cabin.\n");
	add_item(({"wax","melted wax","blob","blob of melted wax", "blob of wax"}),
           "The blob of melted wax is a combination of colours, perhaps "+
           "from a series of leaking candles.\n");
	add_item("chair","It's just a simple chair in front of the "+
           "table.\n");
	
	add_exit(DECK,"deck");
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_INSHIP);
	set_cabin_sound(sounds());
	desk=clone_object(DESK);
	desk->move(TO);
	reset_room();
}
 
