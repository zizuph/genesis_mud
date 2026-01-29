/* Ashlar, 25 Jul 97 - The place where stabled horses are kept. */

inherit "/std/room";

#include "../local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


create_room()
{
	set_short("The stable's store");
	set_long("This is where horses are stored.\n");


	add_prop(ROOM_I_ALLOW_STEED,1);
	add_exit(NOUTER+"black/stable","out");
   
   INSIDE;  /* This is an inside room */
}

