#include "defs.h"
inherit THWIL_BASE_ROOM;
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>

void
create_thwil_room()
{
	set_short("The post office of Thwil");
	set_long("This is the post office in Thwil on the Isle of the Wise. " +
			"From here travellers can post a message to anyone in "+
			"the world.\n");
	add_prop(ROOM_I_INSIDE, 1);
	add_exit(THWIL + "tb", "south", 0);
	reset_room();
}

public void
init()
{
	::init();
	post_init();
}

public void
leave_inv(object ob, object to)
{
	::leave_inv(ob,to);
	post_leave_inv(ob, to);
}
