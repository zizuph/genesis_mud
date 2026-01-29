/* 
 *	/d/Gondor/rohan/farm/farm/garden1.c
 *	It belongs to a small farm in the Ered Nimrais
 *
 *	Olorin, Nov 1992
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Rabbit = allocate(1 + random(3));

public void
create_area_room() 
{
    set_areadesc("garden");
    set_areatype(0);
    set_area("west");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_mountain("Ered Nimrais");
    set_grass("");
    set_forest("");
    set_extraline("You are on a path through the garden. The garden must " +
        "have been magnificent, full of flowers, herbs, and fruit trees. " +
        "But like everything else, the garden has been deliberately " +
        "destroyed. There probably isn't anything of the slightest value " +
        "left. To the northeast is the yard.");

    add_exit(FARM_DIR + "farm/yard1", "northeast", 0, 1);

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
		     HERB_DIR + "garlic", HERB_DIR + "athelas",
		     HERB_DIR + "laurel", HERB_DIR + "oregano",
		     HERB_DIR + "curugwath", }), ({ "garden", }), 4);

    add_item("garden",
        "The garden has been devasted. It must have been a "
      + "wonderful place, but now it is in ruins. Vegetables, herbs, "
      + "flowers, and fruits are lying on the ground, smashed by a "
      + "dozen booted feet.\n");
    add_item("flowers",
        "The wonderful flowers are now in shambles. They "
      + "have been trampled on and lost all their beauty and grace.\n");
    add_item("herbs",
        "All the herbs you can see at a first glance are "
      + "useless, since they have been trampled into the ground. But "
      + "perhaps you will find something that has not been ruined if "
      + "you have a closer look.\n");
    add_item("vegetables",
        "The vegetables lying around are not fit for "
      + "consumption any more. Very hungry animals might be tempted to "
      + "eat them, but you doubt it.\n");
    add_item("fruits",
        "The fruits lying around are not fit for "
      + "consumption any more. Very hungry animals might be tempted to "
      + "eat them, but you doubt it.\n");
 
    reset_room();
}

public object
clone_npc(object npc, string file)
{
    npc = ::clone_npc(npc, file);
    npc->set_restrain_path(FARM_DIR);
    return npc;
}

public void
reset_room()
{
    ::reset_room();

    clone_npcs(Rabbit, NPC_DIR + "rabbit", 20.0 + 20.0 * rnd());
}
