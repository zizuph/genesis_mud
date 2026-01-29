/* Kentari, 29 Mar 98 - The place where stabled horses are kept. */

inherit "/std/room";

#include "../local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


create_room()
{
	set_short("The stable's store");
	set_long("This is where horses are stored.\n");


	add_prop(ROOM_I_ALLOW_STEED,1);
	add_exit(FROOM+"stable","out");
   
   INSIDE;  /* This is an inside room */
}

