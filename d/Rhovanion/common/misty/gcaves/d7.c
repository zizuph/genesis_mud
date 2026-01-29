/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"


create_room()
{
  object door, key;

  seteuid(getuid());

  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("goblin prison");
    set_long("This room in the goblin's prison is dark and it smells bad. "+
             "It is lit by single torch and so it is very dim. "+
             "In the centre you see a hole leading down into a wet "+
             "stinking cell.\n");

    add_item("torch", "It is small torch fastened to the wall.\n");
  add_item(({"wall","walls"}),BS("These walls seems to be natural. But "+
              "then again you have seen so many strange things in these "+
              "caves that you are not sure with anythink you see or feel.\n"));

    door = clone_object(CAVE_DIR + "grating_3_u");
    door->move(this_object());

    door->set_key("gcave_cell_no_3"); /* Tells the door which key fits. */

  add_exit(CAVE_DIR+"d4", "south");
}

