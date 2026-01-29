#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <ss_types.h>
#include <macros.h>

#define LOOK_AT_TRAIL 59

inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("An animal trail within a dark and twisted forest");
    set_long("@@long_descr");

    add_item(({"forest","choking branches","branches","underbrush"}),
      "This part of the forest is dark and ominous. The tree branches " +
      "and choking underbrush seem to twist malevolently towards you " +
      "as if to impede your travel.\n");
    add_item(({"trail","animal trail"}),"@@animal_trail");

    add_exit(FROOM + "road14","northeast","@@leave_forest");
    add_exit(FOREST_PATH + "/dark_forest/path2","southwest","@@str_check");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand on an almost unnoticeable animal trail that heads " +
    "deep into the forest. You notice with some trepidation that much " +
    "of the forest in this region is dark and twisted, with choking " +
    "underbrush that seems to deliberately impede your travel.\n";
}

int
leave_forest()
{
    write("You let out a sigh of relief as you step out of the " +
      "twisted forest.\n");
    return 0;
}

string
animal_trail()
{
    if(TP->query_skill(SS_TRACKING) < LOOK_AT_TRAIL)
    {
	return "You are unable to determine what made these " +
	"tracks. The trail heads northeast and southwest.\n";
    }
    return "Hmm... your impressive tracking skills tell you that " +
    "the creature who made these tracks was huge, yet " +
    "almost impossibly skilled at moving through the forest " +
    "stealthfully. The trails heads northeast and southwest.\n";
}

int
str_check()
{
    if(TP->query_stat(SS_STR) > (40 + random(60)))
    {
	write("You manage to push your way through the grasping " +
	  "tree branches and choking underbrush...\n");
	return 0;
    }
    else
	write("Tree branches reach out and grab you, stopping " +
	  "you from travelling deeper into the forest!\n");
    say(QCTNAME(TP) + " tries to travel deeper into the " +
      "forest, but grasping branches and tree roots hold "+ HIM(TP)+
      " "+
      "back!\n");
    return 1;
}
