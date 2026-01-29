/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

int
clone_courier()
{
    seteuid(getuid());
    
    object courier;

    courier = clone_object("/d/Raumdor/common/beach/bountiful/npc/bount_ghast_courier");
    courier->move(this_object(), 1);
    
    tell_room(this_object(), "Someone rushes in from the west!\n");

    return 1;    
}


void
create_room()
{
    seteuid(getuid());
    
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " The the west the trees give way to a bleak and " +
        "narrow coast, cold waters blocking further travel." +
        " To the north, the land turns into a barren plain.";
    ::create_room();
    add_item(({"coast"}), "Cold and rocky, it is not suitable for travel " +
            "by foot.\n");
    add_item(({"waters","gulf"}), 
            "The sea gently rolls in the wind.\n");
    add_item(({"plain","flats"}),
            "The flats extend north into the mountains. They look lifeless.\n");
    add_item(({"mountains"}), "Mountains rise from the flats far to the " +
            "north.\n");
    set_no_exit_msg(({"northwest","west","southwest"}),
            "Cold waters dissuade you from proceeding that way.\n");
    add_exit(NFLATS_DIR + "nflats01","north",0,FOREST_FATIGUE);
    add_exit(NFLATS_DIR + "nflats02","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest74","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest60","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest59","south",0,FOREST_FATIGUE);
    
    add_npc("/d/Raumdor/common/beach/bountiful/npc/bount_ghast_courier", 1);
    
    //set_alarm(1.0, 1800.0, &clone_courier());
}

