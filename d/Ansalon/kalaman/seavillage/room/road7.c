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
    set_short("Within sight of the village of Braeme");
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

    add_exit(VILLAGEROOM + "road8","north",0,3);
    add_exit(VILLAGEROOM + "road6","southwest",0,3);

    add_cmd_item(({"down cliff","cliff","cliffs","down","down cliffs"}),
      "climb","@@climb_cliff");
    reset_seavillage_room();
}

string
climb_cliff()
{
    write("You don't think you have a wish to fall to your death.\n"); 
    say(QCTNAME(TP) + " looks down at the waves crashing "+
      "into the broken rocks far below, and shudders, backing "+
      "away from the edge of the cliff.\n");
    return "";
}
string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You are within sight "+
    "of the tiny seaside village of Braeme, which lies through "+
    "the hills to the north.  To the south and southwest, "+
    "the rocky path winds tortuously through the sandstone "+
    "cliffs, leading many miles to the far off city of Kalaman. "+
    season_descr() + "\n";
}

