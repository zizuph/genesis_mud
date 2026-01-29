#pragma save_binary
#pragma strict_types


#include "/d/Shire/sys/defs.h"

inherit "city_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_gh_room() {}

nomask void
create_area_room()
{
    create_gh_room();
}

int
south_msg()
{

    SAYBB( " disappears south into the forest.");
    write("You track your way into the forest.\n");
    return 0;
}


int
north_msg()
{
    SAYBB(" heads north towards the hills.");
    write("You decide to hike towards the hills.\n");
    return 0;
}

int
forn_msg()
{
    SAYBB(" disappears north into the forest.");
    write("You track your way north into the forest.\n");
    return 0;
}

int
fors_msg()
{
    SAYBB(" disappears south into the forest.");
    write("You track your way south into the forest.\n");
    return 0;
}

int
fore_msg()
{
    SAYBB(" disappears east into the forest.");
    write("You track your way east into the forest.\n");
    return 0;
}

int
forw_msg()
{
    SAYBB(" disappears west into the forest.");
    write("You track your way west into the forest.\n");
    return 0;
}

int
hilln_msg()
{
    SAYBB(" heads north into the hills.");
    write("You decide to hike north into the hills.\n");
    return 0;
}

int
hills_msg()
{
    SAYBB(" heads south into the hills.");
    write("You decide to hike south into the hills.\n");
    return 0;
}


//  Below there are three levels of movement handicaps
//  How handicapped you are depends on your tracking skill.

int
move_hard()
{
    switch(TP->query_skill(SS_TRACKING))
    {
    case 0..20:
	return 5;
    case 21..45:
	return 4;
    case 46..70:
	return 3;
    default:
	return 2;
    }
}

int
move_medi()
{
    switch(TP->query_skill(SS_TRACKING))
    {
    case 0..20:
	return 4;
    case 21..45:
	return 3;
    default:
	return 2;
    }
}

int
move_easy()
{
    switch(TP->query_skill(SS_TRACKING))
    {
    case 0..20:
	return 3;
    default:
	return 2;
    }
}

int
add_lonelands()
{

//  This is a func included in the rooms in the lonelands so I
//  dont have to copy the same desc's over and over again.

    add_item(({"vegetation","flora"}),
      "At your current elevation, the dry earth and strong "+
      "winds are any but forgiving on the flora, what does "+
      "survive is typically tough grasses and small thorny "+
      "bushes, an indication of how tough life is out "+
      "here.\n");
    add_item("earth",
      "With the windswept elevation and little moisture the "+
      "earth below you is dry and cracked, leeched of "+
      "nutrients and eroded.\n");
    add_item("fauna",
      "Other than the occasional small bird, lizard or snake, "+
      "these lands are all but devoid of life.\n");
}
