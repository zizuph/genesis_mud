/* goblin caves */

#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    object door, key;

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    set_short("goblin prison");
    set_long("This room in the goblin's prison is dark and it smells bad. "+
      "It is lit by single torch and so it is very dim.\n");

    add_item("torch", "It is small torch fastened to the wall.\n");
    add_item(({"wall","walls"}),BS("These walls seems to be natural. But "+
	"then again you have seen so many strange things in these "+
	"caves that you are not sure with anything you see or feel.\n"));

/*    door = clone_object(OBJ_DIR + "grating_1_u");
    door->move(this_object());

    door->set_key("gcave_cell_no_1"); /* Tells the door which key fits. */

	add_exit(ROOMS_DIR+"c95", "south");
}
