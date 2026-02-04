inherit "/std/room.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define TP              this_player
#define TO              this_object

void
create_room()
{
	object ob;

	set_short("Up a tree");
	set_long(BS("You are among the branches of the willow tree. The "
	+ "foliage of the tree is quite thick; you can hardly see the "
	+ "ground below you.\n"));
	add_exit("/d/Terel/mecien/valley/copse2.c","down");
	ob = clone_object("/d/Terel/mecien/valley/nest.c");
	ob->move(TO());
}

