/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_details = "A stream passes through here, flowing south to north. " +
        "To the northwest you see what looks like ruins.";
    ::create_room();
    add_item(({"ruins"}),"From here it looks like a circle of stones.\n");
    add_item(({"stream"}),"The streams flows down from the high mountains"+
    " to south and into the forest to the north. It looks clear "+
    "and clean enough to drink from.\n");
    add_exit(FOREST_DIR + "wforest70","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest71","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest57","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest43","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest42","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest41","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest55","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest69","northwest",0,FOREST_FATIGUE);
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
    object obj = TP;
    if (str == "from stream" || str == "from the stream")
    {
        write("Ahh! Refreshing!\n");
        say(QCTNAME(obj) + " drinks from the stream.\n",obj);
        obj->drink_soft(300);
        return 1;
    }
    notify_fail("Drink from what? The stream?\n");
    return 0;
}
