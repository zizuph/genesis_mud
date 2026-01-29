inherit "/std/object";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

create_object()
{
	set_short("board");
	set_adj("simple");
	add_adj("wooden");
	set_long(BS("A simple wooden board, about 70cm x 20cm in size. "
		+ "You can probably nail something to it. There are "
		+ "some tiny holes in it.", 70));
	add_prop(OBJ_I_WEIGHT, 1000);
	add_prop(OBJ_I_VOLUME, 500);
	add_prop(OBJ_I_VALUE, 5);
	set_name("board");
	add_name("board_for_sign");
	add_item(({"hole", "holes"}), "Maybe worms?\n");
}
