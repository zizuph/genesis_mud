/*
 * 
 * Forest location in northern parts of
 * the silent forest.
 *
 * Baldacin@Genesis, Dec 2003
 */
#include "ldefs.h"
inherit FORESTSTD;

#define COORDX 5
#define COORDY 2


void
create_room()
{
    int loc_type, cliffs;
    string extra_long;

    loc_type = MM_FOREST;
    cliffs = NOCLIFF;
    extra_long = "You draw your attention to a very large tree standing "+
      "here.";
    add_item(({"large tree", "very large tree"}), "This tree seem to be "+
      "of the same type as all the other trees but a whole lot bigger, both "+
      "in height and width. The trunk of the tree has been scratched in some "+
      "places, as if someone has climbed it.\n");
    
    add_cmd_item(({"large tree","very large tree"}),
        "climb","@@climb_tree");
        
    set_exit_desc(3, "west, southwest and southeast");
    
    make_me_forest(extra_long, loc_type, cliffs);

    add_exit(SFDIR + "nforest04_02.c",  "west", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
    add_exit(SFDIR + "nforest04_03.c", "southwest", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);
    add_exit(SFDIR + "nforest06_03.c", "southeast", 0, FOREST_FATIGUE, EXITNOTOBVIOUS);

}

int
climb_tree(string str)
{     
    write("You climb up the large tree.\n");
    TP->move_living("climbing the large tree", GUILDS + "amazon_race/rooms/platform.c", 1, 0);
    return 1;
}