/*
 *      /d/Gondor/arnor/fornost/hill_top.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 *      28-Oct-2020, Varian:    Room not resetting properly
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define LANGUAGE_NEEDED 10

public int     block();
static object *Orc = allocate(2);

public void
create_fornost()
{
    set_short("on a hilltop in the North Downs");

    add_grass();
    add_hills();

    add_item("ridge", BSN(
    "The ridge is connecting the southern hill with the other hills "+
    "spreading out northeast."));
    add_item("stones", "@@exa_stones");

    add_exit(FORNOST_DIR + "north_ridge", "south", 0, 2);
    add_exit(NORTH_DOWNS_DIR + "shallow_valley1", "north", block, 3);
    add_exit(FORNOST_DIR + "wall_tower", "down", block, 3);

    add_npc(NPC_DIR + "std_orc", 2);

    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("hills")), 
                         HERB_DIR + "madwort", 
                         HERB_DIR + "frostheal", }),
        ({ "ridge", "hills", "hill", "grass", }), 3);

    reset_room();
}

string
set_arnor_long()
{
    string desc;

    desc = "On the top of the this hill are the remains of a "+
    "watchtower. The tower is razed to the ground, only some sad parts of "+
    "the foundation are left. A few stones lie scattered on the hill. "+
    "Looking out you see the hills of the North Downs extending as far as "+
    "you can see to the north and northeast. A slope goes down to the "+
    "west. A ridge extends to the south. ";
    desc += query_arnor_time();

    return BSN(desc);
}

public int
block()
{
    if (TP->query_wiz_level())
    {
         write("This road is still closed for mortals, Wizard!\n");
         return 0;
    }
    write("That way is not open yet.\n");
    return 1;
}

string
exa_stones()
{
    if(TP->query_skill(SS_LANGUAGE) > LANGUAGE_NEEDED )
    {
        TP->catch_msg(
        "On one of the stones an orc has scrawled in orcish: "+
        "'Bolzog was here'.\n");
        return "";
    }
    if(TP->query_skill(SS_LANGUAGE) > LANGUAGE_NEEDED/2 )
    {
        TP->catch_msg(BSN(
        "Something has been written on one of the stones in orcish, "+
        "but you can't read it."));
    }
    else
    {
        TP->catch_msg(
        "Something is written on one of the stones in an unknown language.\n");
    }
    return "";
}

/*
 * public void
 * reset_room()
 * {
 *   clone_npcs(Orc, NPC_DIR + "std_orc", -1.0);
 * }
 */