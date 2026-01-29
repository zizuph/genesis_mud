#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"

inherit AREA_ROOM;

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
