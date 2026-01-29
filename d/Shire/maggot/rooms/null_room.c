
/* 
	*A null-room, used for a special message in an
	*exit check in maggotfield southern rooms when
	*a player tries to enter the forest by going south.
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("An empty space in NOWHERE");

	set_long(short() + ". If you are mortal, you DEFINITELY " +
	"should not be here, send a bug report immediately.\n");
}

