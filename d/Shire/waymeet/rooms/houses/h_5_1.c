/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A low-income hobbit hole
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>


inherit WAYM_LIB_DIR + "base_hobbit_hole.c";


void reset_shire_room();



void
create_hobbit_room()
{
	set_short("The Entryway");
	
	set_long("A small room, barely bigger than a closet, there is little more "
		+ "to the entryway than a few hooks on which to hang jackets. A door "
		+ "leads back out to Waymeet and the hallway extends west into the "
		+ "main living area of the Smial.\n");
	
	add_item( ({"hook", "hooks"}), "The hooks look to be about the right "
		+ "height for a hobbit to hang up her cloak after a day of gardening.\n");
	
	add_floor_poor("muddy");
	

	add_exit(WAYM_HOUSE_DIR + "h_5_2", "west");
	add_exit(WAYM_STREET_DIR + "street_2", "out");
}

void
reset_shire_room()
{
	
}

void
init()
{
	::init();
	

}

