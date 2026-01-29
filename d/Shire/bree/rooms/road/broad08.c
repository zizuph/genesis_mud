/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_areadesc("country");
    set_area("road");
    set_areaname("on the Hill");
    set_land("Bree");

    add_bree_desc("It winds up over the hill as it runs east and " +
        "down to a crossroad. Hobbit holes line the country road " +
        "and trees dot the hillside. A square building stands north " +
        "of here.\n");
    add_item(({"square building", "post", "post office"}),
        "The square building is wider than others in the town. A " +
        "sign swings from above the door.\n");
    add_item("sign", 
        "It is square and hangs above the door. A figure reading " +
        "several messages is painted on the sign.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    set_add_hobbit_holes();
    set_add_on_hill();

    add_exit(TOWN_DIR + "post", "north");
    add_exit(ROAD_DIR + "broad07", "southwest");
    add_exit(ROAD_DIR + "broad09", "northeast");
    add_exit(HOUSES_DIR + "hobbit01", "east", test_size);
}
string
read_sign()
{
    return "On the sign, above the coins, painted in bright silver " +
        "letters are the words: 'Post Office of Bree'.\n";
}
