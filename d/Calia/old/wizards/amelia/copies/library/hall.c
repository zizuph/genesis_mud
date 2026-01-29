#include "/d/City/defs.h"
inherit "/std/room.c";
#define PATH "/d/City/chaos/library/"
#include <std.h>
#include <macros.h>
#include <stdproperties.h>

create_room()
{
        set_short("The Great Hall of Statues");
	set_long("This long hallway has six statues standing along each "+
		"wall in various poses.  They look as if they are "+
		"likenesses of people of some historical improtance. "+
		"It is quite possible that thier stories may be found  "+
		"somwhere in the tomes of the library.  Sounds echo off "+
		"the marble walls and it almost seems as if the statues "+
		"are alive.\n");

	add_exit(PATH + "library","north");
	add_exit(PATH + "entry","out");
        add_prop(ROOM_I_INSIDE,1);

	add_item("statues","@@exa_statues");
        add_item("aelrin","This statue looks to be of an elven warrior.\n"+
		"He is standing as if in defiance, with a longsword drawn "+
		"and shield ready for battle.\n");
	add_item("loriana","This statue looks like a tall, long-haired "+
		"human.  She is dressed in long flowing robes and in one "+
		"hand she holds a staff.  It looks as if she is casting a "+
		"spell of some sort.\n");
}

exa_statues()
{
	return"There are twelve statues in the hall, six on each side. "+
	"The features are remarkably well preserved, a result of the "+
	"powerful preservation magicks at work in the library.  On the "+
	"base of each statue is carved a name, assumably of the person "+
	"represented by the statue.  They are:\n"+
	"Aelrin, Loriana,\n";
}
