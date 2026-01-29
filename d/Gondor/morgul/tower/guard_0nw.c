/*
 * A guard room in the entrance of the tower.
 *
 * Created: Olorin, 1-nov-1995
 *
 */
inherit "/d/Gondor/morgul/tower/tower.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

object  mage;

void
reset_room()
{
    if (objectp(mage))
        return;

    mage = clone_object(MAGES_DIR + "newnpc/mage_guard");
    mage->arm_me();
    mage->move_living("down", TO);
}

void
create_morgul_tower_room()
{
    set_extra_long("The darkness is so deep that your light source hardly "
      + "illuminates the walls of this guard chamber. The only exit is "
      + "leading southeast back into the hallway.");

    set_room_type("guard room");
    set_level(0);

    add_exit(TOWER_DIR  + "tower_entrance", "southeast", 0, 1);

    add_walls();
    add_roof();
    add_floor();
    add_item(({"hallway","passage"}), BSN(
        "The hallway is barely visible beyond the gaping hole that is "
      + "the doorway leading out to the southeast."));

    reset_room();
}

