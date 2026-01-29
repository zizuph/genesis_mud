/* Ashlar, 25 Jul 97 - The place where stabled horses are kept. */

inherit "/std/room";

#include "/d/Terel/include/Terel.h"

#include <stdproperties.h>

create_room()
{
	set_short("The stable's store");
	set_long("This is where horses are stored.\n");


	add_prop(ROOM_I_ALLOW_STEED,1);
	add_prop(ROOM_I_INSIDE,2);
	add_exit(CALATHIN_DIR+"stable.c","out");

	//disable resets
	    enable_reset(0);
   
}

