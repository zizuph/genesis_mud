/*
 *   /d/Gondor/ithilien/poros/manor/cellar.c
 *
 *   A room inside the manor that is used as a hidden base by corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include "/d/Gondor/defs.h"

static object  jailer;

public void
reset_room()
{
    if (!objectp(jailer))
    {
      jailer = clone_object(POROS_DIR + "npcs/jailer");
      jailer->arm_me();
      jailer->move_living("down", TO);
    }
}

void
create_manor()
{
    set_area("oval shaped room");
    set_extraline("The room has racks on the walls, and a large table "
      + "stands in its center. Near the table an open brazier sits on "
      + "the floor. Three doors are along the western wall, while a "
      + "flight of steep stairs leads up to the east.");

    add_exit(POROS_DIR + "manor/westhall2", "up", 0, 1);

    add_item(({"racks"}), BSN(
        "From the racks on the walls hang shackles of various sizes."));

    add_item(({"shackles"}), BSN(
        "You realize the shackles are used to restrain unruly prisoners "
      + "who are to be moved or tortured."));

    add_item(({"table"}), BSN(
        "You notice the table has restraints for limbs along its sides. "
      + "Also traces of fresh blood can be seen on its surface. This "
      + "room is obviously used for the interrogation and torture of "
      + "captured prisoners."));

    add_item(({"brazier"}), BSN(
        "The metal brazier is very hot, and filled with glowing coals. "
      + "Considering the climate of the local region you determine that "
      + "this is used for a purpose, other than warmth..."));

    add_item(({"floor", "ground", "room"}), BSN(
      "The room has the distinct feeling of a torture chamber. You " 
      + "can see traces of blood on the floor here."));

    add_item(({"doors"}), BSN(
        "Upon closer inspection you notice that the doors lead into "
      + "three differnt cells. One in the southwestern, western, and "
      + "northwestern sides of the room respectfully."));

    add_item(({"door"}), BSN(
        "Which door? The southwestern, western, or northwestern?"));

    add_item(({"cells", "cell", "southwestrn cell", "western cell",
        "northwestern cell"}), BSN(
        "You can not tell from this side of the door, but it is likely "
      + "that that is where the corsairs keep their captured prisoners."));

    add_stairs();

    clone_object(POROS_DIR + "obj/door_cell1a")->move(TO);
    clone_object(POROS_DIR + "obj/door_cell2a")->move(TO);
    clone_object(POROS_DIR + "obj/door_cell3a")->move(TO);

    reset_room();
}
