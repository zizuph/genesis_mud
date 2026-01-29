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
    set_short("In a cave on the shore of the Estwilde coast");
    set_long("@@long_descr");

    add_item("cave","This cave has been hollowed out of "+
      "the cliff by the working of the sea.\n");
    add_item(({"cliff","cliffs","high cliff","high cliffs"}),
      "These high cliffs "+
      "are made of crumbling sandstone, and look dangerous "+
      "to climb. If you are skilled enough, you might however "+
      "be able to climb down here.\n");

    set_tell_time(120);
    add_tell("A particularly large wave crashes into the rocks "+
      "outside the cave, throwing up a plume of icy cold spray "+
      "that soaks you to the bone.\n");
    add_tell("The wind seems to be rising outside, whipping " +
      "the surf into a frenzy.\n");
    add_cmd_item(({"up cliff","cliff","cliffs","up","up cliffs"}),
      "climb","@@climb_cliff");


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
    write("You carefully and skillfully climb up the crumbling " +
      "sandstone cliffs, reaching the rocky path above.\n");
    tell_room(VILLAGEROOM + "road4","A sweating figure climbs up over " +
      "the edge of the cliff, and lies panting on the rocky path " +
      "in front of you!\n");
    say(QCTNAME(TP) + " precariously climbs up the cliff, out of sight.\n");
    TP->move_living("M",VILLAGEROOM + "road4",1,3);
    return "";
}

string
long_descr()
{
    return "This small, cramped cave is perched precariously "+
    "just above the crashing waves of the ocean. Far above you, the "+
    "cliffs tower out of sight. The floor of the cave "+
    "is covered with flotsam and jetsam, washed in from the "+
    "sea during high tides.\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
	start_room_tells();
}

