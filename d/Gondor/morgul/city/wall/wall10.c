#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The southeast tower of the city is mounted in front " +
      "of the city walls where the southern and eastern walls meet. " +
      "The steep cliffs of the mountains are rising high into the " +
      "sky only a few fathoms south of the city wall. " +
      "To the east you see the dark slopes of the Ephel Duath rising " +
      "towards the pass high above the city. A flight of stairs is " +
      "leading down to the city streets here and one can enter the tower " +
      "through a doorway to the southeast.");
    set_road(1);
    set_side("southeast");

    add_item(({"tower","southeast tower","doorway"}), BSN(
      "The southeast tower is only a few meters higher than the walls themselves. " +
      "It is mounted in front of the walls so that from the tower one " +
      "has a clear view of the outer side of the city walls. From here, one " +
      "can enter the tower through a doorway to the southeast."));
    add_view_east();
    add_view_south();
    add_stairs_down();
    add_exit(MORGUL_DIR + "city/wall/wall09","north","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/towers/se_tow2","southeast","@@block_npc",1);
    add_exit(MORGUL_DIR + "city/wall/wall11","west","@@check_exit",1);
    add_exit(MORGUL_DIR + "city/barrstr1","down","@@block_npc",1);
}
