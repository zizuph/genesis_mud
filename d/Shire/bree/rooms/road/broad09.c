/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"

inherit ROAD_BASE;

object hobbit;

void
create_road_room()
{
    set_areadesc("country");
    set_area("road");
    set_areaname("on the Hill");
    set_land("Bree");

    add_bree_desc("Scattered trees grow in small groves and scattered " +
        "across the hill. They also line the the road which takes a " +
        "sharp turn as it winds down the hill. Gardens are scattered " +
        "about, and a white building stands north of here.\n");
    add_item(({"white building", "perfumery", "perfume shop"}),
        "The building is square and white. It is very clean with " +
        "some pretty flowers growing around it. A sign swings " +
        "above the door.\n");
    add_item("sign", 
        "It is square and hangs above the door. A group of different " +
        "shaped bottles is painted on the sign.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    set_add_hobbit_holes();
    set_add_on_hill();
    reset_shire_room();

    add_exit(TOWN_DIR + "perfumery", "north");
    add_exit(ROAD_DIR + "broad10", "east");
    add_exit(ROAD_DIR + "broad08", "southwest");
}
string
read_sign()
{
    return "On the sign, above the bottles, painted in bright white " +
        "letters are the words: 'Perfumery'.\n";
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(hobbit))
    {
        hobbit = clone_object(HOBBITMAKER);
        hobbit->set_type(CITIZEN);
        hobbit->set_power(100);
        hobbit->move(TO);
        hobbit->set_restrain_path("/d/Shire/bree");
        hobbit->set_random_move(2);
    }
}
