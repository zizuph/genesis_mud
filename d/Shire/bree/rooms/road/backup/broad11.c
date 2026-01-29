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
    set_areaname("halfway up the Hill");
    set_land("Bree");

    add_my_desc("It continues to wind up the Hill as it heads south. " +
        "In the distance is a small orchard.\n");
    add_item(({"fruit trees"}),
        "The fruit trees grow south, towards the top of the hill. " +
        "They are large, and very old looking with gnarled branches " +
        "and full of leaves.\n");
    add_item(({"orchard"}),
        "It grows towards the top of the hill. It is full of fruit trees.\n");

    set_add_hobbit_holes();
    set_add_on_hill();
    reset_shire_room();

    add_exit(ROAD_DIR + "broad12", "southeast");
    add_exit(ROAD_DIR + "broad10", "northwest");

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
