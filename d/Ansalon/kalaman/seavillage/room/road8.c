#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/seavillage/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit VILLAGE_ROAD;

void
reset_seavillage_room()
{
    return;
}

create_seavillage_room()
{
    set_short("Just south of the village of Braeme");
    set_long("@@long_descr");

    add_item("ocean","The ocean, even from here, looks rough.\n");
    add_item(({"village","braeme","Braeme"}),"This village is far "+
      "away out of sight.\n");
    add_item(({"kalaman","city","Kalaman"}),"Kalaman lies "+
      "out of sight a long way south west of here.\n");
    add_item(({"path","rocky path"}),
      "The path is desolate and windswept, and "+
      "looks like it sees little traffic these days.\n");
    add_item("bay","Far below, at the bottom of the cliffs lies "+
      "the bay that ships use to reach Kalaman by sea.\n");
    add_item(({"ship","ships"}),"There are no ships at sea at "+
      "the moment.  Perhaps the war keeps them away.\n");
    add_item(({"cliff","cliffs","high cliff","high cliffs"}),
      "These high cliffs "+
      "are made of crumbling sandstone, and look far too "+
      "dangerous to climb.\n");

    add_exit(VILLAGEROOM + "room1","north",0,1);
    add_exit(VILLAGEROOM + "road7","south",0,3);

    reset_seavillage_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "Just to the north of you, "+
    "the path enters a small village that is huddled against the "+
    "coast near a little inlet. To the south rise hills, while "+
"to the west lies the raging waters of the great ocean. "+
    season_descr() + "\n";
}

