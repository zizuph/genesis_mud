/*
 *	/d/Gondor/anorien/road/wr7.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define MIN_AWARE	15
#define MIN_TRACK	 5

public int     try_south();
public string  exa_forest();
public string  exa_track();

public string
aware_check()
{
    int     min = 2 * MIN_AWARE / 3;
    if (TP->query_skill(SS_AWARENESS) > 
	(min + random(min) + 1))
        return " There seems to be a track of some kind going south "
             + "through the forest here.";
    return "";
}
    

public void
create_area_room()
{
    set_areadesc("dark, gloomy forest");
    set_areatype(8);
    set_area("southwestern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dark green grass among the trees");
    set_extraline("You are inside the Druedain Forest, a gloomy place with "
      + "tall trees. This is said to be where the Druedain live, a strange "
      + "tribe of wild men still living in the stone-age. The Rohirrim have "
      + "not been particularly friendly to the Druedain, so better beware. "
      + "The road continues east and west.");
    set_vbfc_extra(aware_check);

    set_no_exit_msg(({"southeast","southwest"}),
        "The Druedain Forest is too thick to enter from here.\n");

    add_exit(ANO_DIR + "road/wr6",      "east",          0, 3, 0);
    add_exit(DRUEDAIN_DIR + "oldroad1", "south", try_south, 3, 1);
    add_exit(ANO_DIR + "road/wr8",      "west",          0, 3, 0);
    add_exit(ANO_DIR + "plains/an7w5n","northwest",0,5,1);
    add_exit(ANO_DIR + "plains/an9w5n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an8w5n","north",0,5,1);

    add_item("forest", exa_forest);
    add_item("track",  exa_track);
}

public int
try_south()
{
    if (TP->query_skill(SS_TRACKING) > MIN_TRACK) 
    {
        write("You find the beginning of an old track, which you follow south.\n");
        SAYBB(" disappears south into the forest.");
        return 0;
    }
    write(BSN("You do not dare to enter the Druedain Forest, being so "
      + "unskilled in tracking and location sense. You might get lost!"));
    return 1;
}

public string
exa_forest()
{
    if (TP->query_skill(SS_TRACKING) > MIN_TRACK)
        return BSN("Looking at the forest, your skilled eyes suddenly "
          + "discover an old track leading through the forest south of "
          + "here!");
    return BSN("You study the forest to see if you can catch a glimpse of "
      + "one of the legendary Druedain, but see nothing. The grey trees of "
      + "the Druedain Forest reveal nothing of interest to you.");
}

public string
exa_track()
{
    if (TP->query_skill(SS_TRACKING) > MIN_TRACK)
        return BSN("There is an old, hidden track running south through "
          + "the forest! Maybe you can find something interesting if you "
          + "follow it?");
    return "The only track which you see is the old West Road which you "
         + "are standing on.\n";
}

/*
 This was used while the plains were under construction. Now open
 Varian - August 2016

int
block()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}

*/