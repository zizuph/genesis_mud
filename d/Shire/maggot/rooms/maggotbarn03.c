/* 
	*A room inside Maggot's barn
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_BARN;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("Inside a sturdy barn");
	
	set_long(short() + ". There are bits of hay on " +
	"the ground, as well as dirt that was probably tracked " +
	"in by the farm hands and animals. Tools hang on " +
	"walls and from the rafters. From the smell, the space " +
	"to west appears to be a stall for animals.\n");
	
	set_add_barn_main();
	set_add_rtells_barn();
	set_add_barn();
	
	add_exit(ROOM_DIR + "maggotbarn05", "north");
	add_exit(ROOM_DIR + "maggotbarn01", "south");
	add_exit(ROOM_DIR + "maggotbarn04", "west");

	reset_shire_room();
}

void reset_shire_room()
{
	
}
