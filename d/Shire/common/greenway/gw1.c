inherit "/d/Shire/std/room";

#include "defs.h"
#include "/d/Shire/sys/defs.h"

create_shire_room()
{
    set_short("The Greenway");
    set_long("@@long_desc");

    add_item(({ "field", "fields" }), "The crops in the fields are bending in "
        + "the wind.\n");
    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
        + "and mules. There are also a few that indicate horses.\n");
    add_item(({ "bird", "birds" }), "They are only small black specks in the "
        + "sky.\n");

//   add_exit(STAND_PARENT + "bree/cross", "north", 0);
    add_exit("/d/Shire/bree/rooms/road/crossroad","north", "@@tree_north@@");
//    add_exit(STAND_DIR + "gw2", "south", 0);
    add_exit(STAND_DIR + "gw2", "south", "@@tree_south@@");

}

string long_desc()
{
    string str;

    str = "You are travelling on an old road winding its way through "
        + "the fields surounding it. The tracks on the road are "
        + "quite fresh and implies that the road is in constant use. "
        + "You can hear the birds sing in the distance.\n";

    return str;
}

void tree_north()
{

    tell_room("/d/Shire/bree/rooms/road/treetop.c", QCTNAME(TP) +
        " arrived from the south at the Crossroads.\n");
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) +
        " arrived from the south at the Crossroads.\n");
}

void tree_south()
{
    tell_room("/d/Shire/bree/rooms/road/treetop.c", QCTNAME(TP) +
        " heads south down the Greenway.\n");
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) +
        " heads south down the Greenway.\n");
}