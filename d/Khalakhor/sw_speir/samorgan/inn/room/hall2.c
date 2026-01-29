/**********************************************************************
 * - hall2.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../inn.h"

void
create_khalakhor_room()
{
	set_short("a long hallway");
	set_long("\n   This long hallway spreads north and south. "+
	"On each side of the hallway are two doors with posted "+
	"numerals 3 and 4. Soft but adequate light stems from decorative "+
	"brass lanterns hanging from the walls "+
	"along with a few paintings.\n");

	
	add_item(({"wooden floor", "floor", "flooring"}),
	"The flooring is made from joined planks of polished wood.\n");
	add_item(({"wood", "polished wood"}),
	"Some of the wood used here is highly polished and in very "+
	"good condition.\n");
	add_item(({"ceiling"}),
	"The ceiling is open with beams running crossways and isn't "+
	"really much to look at.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from wooden panels.\n");
	add_item(({"lanterns", "lantern", "brass lantern", "brass lanters"}),
	"These lanterns are made from brass and etched glass. They "+
	"are highly polished and not a speck of dust can be found on "+
	"their surface. They add to the d�cor of the hallway and give "+
	"subtle but adequate lighting to the area.\n");
	add_item(({"painting", "paintings"}),
	"The paintings are small and very stylish of the coutryside.\n");
	
	add_exit("hall3", "north");
	add_exit("hall1", "south");
	add_door_exit(IOBJ + "door4", "room4", "east");
	add_door_exit(IOBJ + "door3", "room3", "west");	
	add_fail("auto", "A wall stops you.\n");

}
