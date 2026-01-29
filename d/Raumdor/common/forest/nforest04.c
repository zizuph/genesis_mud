/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    forest_details = " To the northwest you see what looks like a " +
        "small pond, apparenty connecting to the stream that runs " +
        "through here from the south.";
    ::create_room();
    add_item(({"pond"}),"You can't see much from here.\n");
    add_item(({"stream"}), "The stream looks clear and clean enough " +
           " to drink from.\n");
    add_exit(FOREST_DIR + "nforest16","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest17","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest05","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest85","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest83","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest03","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","northwest",0,FOREST_FATIGUE);
}

void
init()
{
    ::init();
    add_action("drink", "drink");
}

int
drink(string str)
{
    if (str == "from stream" || str == "from the stream")
    {
        write("Ahh! Refreshing!\n");
        say(QCTNAME(TP) + " drinks from the stream.\n",TP);
        TP->drink_soft(300);
        return 1;
    }
    notify_fail("Drink from what? The stream?\n");
    return 0;
}
