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
    set_areaname("near the top of the Hill");
    set_land("Bree");

    add_my_desc("A small orchard grows west of here alongside the " +
        "road, probably planted by a hobbit family and tended by " +
        "their children. The road continues south as it reaches " +
        "the top of the hill and northwest back down to the base.\n");
    add_item(({"fruit trees", "apple trees"}),
        "The fruit trees are large and very old looking with gnarled " +
        "branches. They are old apple trees that were planted years " +
        "ago. Sweet fruit hangs from their branches, ready for " +
        "anyone to pick.\n");
    add_item(({"branches", "gnarled branches"}),
        "The gnarled branches are thick and bumpy looking. They " +
        "twist in wierd shapes but are full of fruit and covered " +
        "with deep green leaves.\n");
    add_item(({"leaves", "deep green leaves", "green leaves"}),
        "The leaves are oval shaped, about the size of a small hand. " +
        "They are a deep green color and grow all over the branches, " +
        "shading the fruit that hangs from the branches.\n");
    add_item(({"fruit", "apples"}),
        "They are large and very delicious looking. They hang " +
        "from the branches, waiting to be picked and enjoyed.\n");
    add_item(({"orchard"}),
        "It grows to the west of the country road. It is full of " +
        "apple trees.\n");

    set_add_hobbit_holes();
    set_add_on_hill();
    reset_shire_room();

    add_exit(ROAD_DIR + "broad13", "south");
    add_exit(ROAD_DIR + "broad11", "northwest");
    add_exit(ROAD_DIR + "orchard03", "west");
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
        command ("wield all");
    }
}
