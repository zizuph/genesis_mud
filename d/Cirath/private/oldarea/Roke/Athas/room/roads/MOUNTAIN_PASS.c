inherit "/std/room";

#include "/d/Roke/common/defs.h"

public void
create_mountain_pass()	{
}

public nomask void
create_room()
{

	set_short("Mountain pass");
	set_long(BSS("You have entered an icy mountain pass in the eastern "+
		"parts of Athas. The sun is still shining bright, but the "+
		"height makes you cold and the climbing is tough.\n"));

	create_mountain_pass();

}
