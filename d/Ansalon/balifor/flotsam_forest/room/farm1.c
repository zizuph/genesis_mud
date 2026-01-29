#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Inside a rundown farmhouse");
    set_long("@@long_descr");

    add_item(({"house","small one-room house","room","small house","farmhouse",
	"rundown farmhouse","one-room house"}),
      "@@long_descr");
    add_item(({"table","legs","corner","three legged table"}),
      "A three legged table stands precariously in the corner. There is " +
      "nothing on it that interests you.\n");
    add_item("windows","All the windows in this house are so filthy " +
      "that you cannot see out of them at all.\n");
    add_item(({"bed","smelly unmade bed","smelly bed","unmade bed","wall"}),
      "Against one wall is a smelly unmade bed. It would not surprise you " +
      "to find that the owner is not the only creature to sleep in it.\n");
    add_item(({"smoking fireplace","fireplace","fire"}),
      "A lit fireplace merrily chuffs away.\n");

    add_exit(FROOM + "pathc","out",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within a rundown farmhouse. From the looks of things " +
    "this small one-room house has missed a woman's touch for quite some " +
    "time. A table stands precariously on three legs in the corner of " +
    "the room, and all the windows are covered in filth. " +
    "A smelly un-made bed sits next to a wall, while at the back of " +
    "the house is a smoking fireplace.\n";
}
