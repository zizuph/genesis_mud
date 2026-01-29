#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FOREST_IN;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Farmhouse");
    set_long("@@long_descr");

    add_item(({"farmhouse","small room","room"}),"@@long_descr");
    add_item(({"rocking chair","chair"}),"A wooden rocking chair sits near the fireplace.\n");
    add_item(({"large unlit stone fireplace","large stone fireplace",
	"large fireplace","stone fireplace","unlit fireplace","fireplace"}),
      "A stone fireplace, large enough that you could probably fit in it. " +
      "It is unlit and surprisingly it looks like it hasn't been lit in " +
      "a long time.\n");
    add_item(({"bookcase","small bookcase","books","southern wall","wall"}),
      "Against the southern wall stands a small bookcase. The books " +
      "on the shelf look fairly boring and nothing of interest to you.\n");

    add_exit(FROOM + "farm2","west",0);

    add_cmd_item(({"fireplace","fire"}),"enter","@@enter_fireplace");

    add_cmd_item(({"bookcase","bookshelf"}),({"push","pull","move"}),
      "@@push_book");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a small room at the back of the farmhouse. A " +
    "large unlit stone fireplace is the main feature in the room, with " +
    "a rocking chair sitting before it. A small bookcase stands against " +
    "the southern wall.\n";
}

string
enter_fireplace()
{
    write("You step inside the fireplace.\n");
    TP->move_living("into the fireplace",FROOM + "fireplace",1,0);
    return "";
}

string
push_book()
{
    write("You start pushing the bookcase... it starts wobbling, and " +
      "it almost falls on top of you! Smart move chump.\n");
    say(QCTNAME(TP) + " starts pushing at the bookcase, and almost " +
      "has it collapse on top of you! What a loser.\n");
    return "";
}

