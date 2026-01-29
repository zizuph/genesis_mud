#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();

static object  wraith;

public void
create_morgul_room()
{
    set_extraline("Through the door in the north wall you can go back "
      + "into the guard room. The only piece of furniture here is a "
      + "large wooden desk.");
    set_road(9);
    set_short_desc("in the office of the Captain of the Guard of the Mordor Gate");
    set_side("east");

    add_exit(MORGUL_DIR + "city/gateh4", "north", "@@check_exit@@", 1);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,-1);
    add_item(({"desk", "wooden desk", "large desk"}), BSN(
        "It is a large desk made from a heavy dark wood. It is "
      + "completely empty. Apparently, a wraith has not much use for "
      + "furniture."));
  reset_room();
}

public void
reset_room()
{
    if (!objectp(wraith))
        wraith = clone_npc(wraith, MORGUL_DIR + "npc/ithil_wraith");
}
