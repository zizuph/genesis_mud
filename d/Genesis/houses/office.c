/*
 * Housing office - Varian, January 2020
 */

#pragma strict_types

#include <stdproperties.h>
#include "/d/Gondor/houses/defs.h"

inherit "/std/room";
public void

create_room()
{
	set_short("Housing office");
	set_long("This is Varian's housing office, where all the " +
		"big real estate deals go down!\n");

	add_exit("/w/varian/lounge", "northwest");
	add_exit("/d/Genesis/houses/display_room", "south");
	add_exit("/d/Genesis/houses/house_manager", "east");
}