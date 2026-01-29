#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

static object Button;
public void reset_room();

public void
create_gondor()
{
    set_short("a small trail");
    set_long("The trees seem to thin out a bit here, allowing " +
      "more wind to flow between the branches.  " +
      "The grass here is lush and green, not allowing a glimpse " +
      "of the hard earth underneath.  " +
      "\n");

    add_item(({"grass","ground","trail"}),"The trail here is " +
      "little more than an area where the grass has been " +
      "trampled down.\n");

    add_item(({"tree","trees"}),"The trees in the area are tall " +
      "and strong.\n");

    add_exit(CAMP_ROOM_DIR + "trail2","south");
add_exit(ITH_DIR +"road/er4","north");

    reset_room();
}


public void
reset_room()
{
    if (!objectp(Button))
    {
	Button = clone_here(CAMP_OBJ_DIR + "button");
	Button->add_prop(OBJ_I_HIDE, 40);
Button->move(TO);
    }
}



