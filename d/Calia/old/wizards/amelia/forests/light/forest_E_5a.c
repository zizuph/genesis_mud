/*
*  by Amelia, for use in the Light Forest
*/
inherit "/std/room";
#include "room_tell.c"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h";
/*  */
void
create_room()
{
       set_short("The path through the light forest");
       set_long("You continue through the forest on a narrow path.  "+
                "It is very quiet and peaceful here.  "+
                "Through the trees ahead you can just make out "+
                "a stream of smoke from a chimney.  There must be "+
                "a dwelling ahead.\n");
/* add_items */
	add_item((({"foliage"})),
		("The bushes are closer together here, and the trees "+
		"are becoming larger.\n"));
	add_item((({"bush","bushes","foliage","greenery"})),
		("Mulberry and wildrose bushes grow "+
		"in abundance here.\n"));
	add_item((({"smoke", "stream", "chimney"})),
		("It appears to be smoke from a chimney of a "+
		"small building.\n"));
	add_item((({"forest", "trees"})),
		("This part of the forest is filled with "+
		"larger, older trees.\n"));
	add_item((({"path"})),
		("The path is very narrow here, winding between "+
		"trees and bushes.\n"));

	set_tell_time(180);
	add_tell("You smell the smoke of a wood fire.\n");
	add_tell("A twig snaps as you step on it.\n");

	add_exit((FPATH+"forest_E_4a"), "southwest", 0, 0);
	add_exit((FPATH+"forest_E_6a"), "east", 0, 0);
/* */       
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 0);
}

void
enter_inv(object ob, object from)
{
	start_room_tells();
	::enter_inv(TP, TO);
}

void
leave_inv(object ob, object to)
{
	remove_alarm(tell_alrm);
	::leave_inv(TP, TO);
}
