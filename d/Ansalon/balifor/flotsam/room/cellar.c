#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("A dark, empty cellar");
    set_long("@@long_descr");

    add_item(({"stairs","staircase","spiral staircase"}),"A spiral " +
      "staircase that leads up, out of this malevolent place. You " +
      "hope that you will be using it soon.\n");
    add_item(({"walls","stone walls","cold stone walls"}),"Big blocks of " +
      "grey stone. You doubt that they have seen the light of day for many " +
      "years.\n");
    add_item("passageway","The passageway opens up in the southern wall.\n");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    add_exit(FROOM + "street29","up",0);
    add_exit(FROOM + "passage1","south",0);

    DARK;

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand at the bottom of a spiral staircase in a dark, empty " +
    "cellar. The presence of evil is stronger down here, as is the smell of " +
    "death. To the south the cold stone walls open up into a passageway " +
    "that leads into darkness.\n";
}
