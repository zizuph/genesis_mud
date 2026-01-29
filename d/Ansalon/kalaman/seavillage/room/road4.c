#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/seavillage/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define HARD_TO_CLIMB 35

inherit VILLAGE_ROAD;

void
reset_seavillage_room()
{
    return;
}

create_seavillage_room()
{
    set_short("On a path winding along the cliff tops");
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
      "are made of crumbling sandstone, and look dangerous "+
      "to climb. If you are skilled enough, you might however "+
      "be able to climb down here.\n");

    add_cmd_item(({"down cliff","cliff","cliffs","down","down cliffs"}),
      "climb","@@climb_cliff");

    add_exit(VILLAGEROOM + "road5","northeast",0,4);
    add_exit(VILLAGEROOM + "road3","south",0,4);

    reset_seavillage_room();
}

string
climb_cliff()
{
    if(this_player()->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
	write("You don't think you have a wish to fall to your death.\n"); 
	say(QCTNAME(TP) + " looks down at the waves crashing "+
	  "into the broken rocks far below, and shudders, backing "+
	  "away from the edge of the cliff.\n");
	return "";
    }
    write("You carefully and skillfully climb down the crumbling " +
      "sandstone cliffs, reaching a small cave on the shore.\n");
    tell_room(VILLAGEROOM + "cave","A sweating figure climbs down " +
      "the last stretch of crumbling cliff, and falls into the cave " +
      "in front of you!\n");
    say(QCTNAME(TP) + " precariously climbs down the cliff, out of sight.\n");
    TP->move_living("M",VILLAGEROOM + "cave",1,3);
    return "";
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "The rocky path winds its "+
    "way north east towards Braeme, or south towards "+
    "the far off city of Kalaman. The cliffs are not quite "+
    "as steep here. "+
    season_descr() + "\n";
}

