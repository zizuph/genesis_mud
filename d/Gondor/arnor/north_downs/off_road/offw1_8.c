/*
 *      
 */
#pragma strict_types

#include "arnor_defs.h"
inherit NEW_ARNOR_ROOM;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
static object *Orc = allocate(5);

void
reset_room()
{
    int i;

    set_searched(0);
    clone_npcs(Orc, NPC_DIR + "std_orc", -1.0);

    if (sizeof(Orc))
    {
        for (i = 0; i < sizeof(Orc); i++)
        Orc[i]->clear_chat();
    }
}

public void
create_arnor()
{
    string extra = " Blood stains the ground in places. " +
        "There is a dense hedge of hawthorn bushes that " +
        "stands at the base of the hill to the east.";
    set_short("A sea of grass.");
    set_long(&set_grass_room_long(extra));
    remove_item("ground");
    add_item(({"ground", "blood"}), "Blood stains the ground " +
        "as if there were a recent battle. From its red colour " +
        "you know it is not orc blood.\n");
    add_item(({"hill", "mound", "base", "base of the hill"}),
        "A large green hill, more like a mound, stands to the " +
        "east. A hedge of hawthorn bushes is planted at its base.\n");
    add_item(({"hedge", "hawthorn bushes"}), "A dense stand of " +
        "hawthorn bushes is planted at the base of the mound " +
        "to the east. You notice that some of the branches " +
        "are broken, forming a sort of passage.\n");

    add_road_downs_tells();
    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC1)),
                    HERB_DIR + "redweed",
                    ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC2))}),
                    ({ "ridge", "hills", "hill", "grass", }), 5);
    add_exit(MOUND1 + "mound_entrance", "enter", &off_road(), 0, 1);
    add_exit(ND_OFFROAD + "offw1_7", "west", &off_road(), 0, 1);
    set_grass_wandering_msg();
    add_grass_room_items();
    reset_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }   
}

