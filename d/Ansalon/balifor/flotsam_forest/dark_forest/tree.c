#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("On a great tree branch");
    set_long("You are perched on top of a great tree branch about five " +
      "metres above the ground. The tree's foliage surrounds you, and " +
      "you notice here and there the odd acorn.\n");

    add_item(({"great tree branch","tree branch","branch"}),
      "You stand upon a great tree branch about five metres above " +
      "the ground.\n");
    add_item(({"trees foliage","foliage"}),
      "The trees foliage surrounds you, protecting you from sight from " +
      "below, but obscuring your vision of the forest and clearing.\n");
    add_item(({"odd acorn","acorn","large acorn"}),"You notice a large " +
      "variety of acorns growing in this tree.\n");
    add_item(({"clearing","forest","down"}),"The foliage blocks " +
      "your view.\n");

    add_exit(FOREST_PATH + "/dark_forest/clearing","down","@@down");

    reset_flotsam_room();
}

int
down()
{
    write("You scamper down the tree...\n");
    return 0;
}
