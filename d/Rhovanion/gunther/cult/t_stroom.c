inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"
#include "guild.h"

add_stuff()
{
	seteuid(getuid(TO));
	
	clone_object(OBJ_DIR + "com_knife")->move(TO);
	clone_object(OBJ_DIR + "com_knife")->move(TO);
	clone_object(OBJ_DIR + "com_knife")->move(TO);
	clone_object(OBJ_DIR + "com_lthr")->move(TO);
	clone_object(OBJ_DIR + "com_lthr")->move(TO);
}

create_room()
{
	set_short("Store room.\n");
	set_long("Store room.\n");
	
	add_exit(CULT_DIR + "t_shop","west", 0);

	add_stuff();
}
