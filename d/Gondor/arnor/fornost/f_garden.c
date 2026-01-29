/*
 *      /d/Gondor/arnor/fornost/f_garden.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_fornost()
{
    string *herbs;

    set_short("a forgotten garden in the ruins of Fornost");

    add_buildings();
    add_grass();
    add_ground();
    add_rubble();
    add_ruins();
    add_stones();
    add_walls();

    add_item("garden", BSN(
    "The garden may once have been cultivated, but all "+
    "signs of that are now long gone."));
    add_item("ground", "Plants of different kinds grow here.\n");
    add_item("bushes", "The green bushes ...\n");
    add_item("flowers", BSN(
    "The flowers are very beautiful. The fragrance in "+
    "the air must come from them."));
    add_item("street", "Not much of the street can be seen from here.\n");
    add_item(({ "smell", "fragrance", "air" }),
        "You cannot look at the air, but you can smell it.\n");
    add_item("plants", "Everywhere around, the plants seem to thrive.\n");

    add_cmd_item(({ "plants", "flowers" }), "pick", 
        "The plants are much more beautiful on the ground than in your pocket.\n");

    add_exit(FORNOST_DIR + "p_street", "west", 0, 3);
    add_exit(FORNOST_DIR + "c_wall", "east", 0, 3);

    add_cmd_item(({ "air", "the air", "fragrance", "the fragrance" }), 
        "smell", "The fragrance reminds you of some happy memory.\n");

    herbs = HERB_MASTER->query_herbs( ({ "hills", "middle earth", }) );

    set_up_herbs( ({ ONE_OF_LIST_WITH_SEED(herbs, 545923),
                     ONE_OF_LIST_WITH_SEED(herbs, 952107),
                     ONE_OF_LIST_WITH_SEED(herbs, 731680), }),
        ({ "garden", "grass", "ground", "bushes", "flowers" }), 8);
}

string
set_arnor_long()
{
    string desc;

    desc = "In a green and forgotten garden in the ruins "+
    "of Fornost. Bushes are growing among the tumbled walls. The air is "+
    "full of a sweet fragrance. Many wild yet beautiful flowers are "+
    "growing here. To the west is a street, and east another exit. ";
    desc += query_arnor_time();

    return BSN(desc);
}

void
reset_room()
{
    set_searched(0);
}
