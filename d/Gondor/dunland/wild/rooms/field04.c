#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/dunland/wild/dunlendings.h"

public void
create_area_room()
{

    set_areatype(4);
    set_areadesc("in a large open field");
    set_area("southeast");
    set_areaname("Dunland");
    set_land("Enedwaith");
    set_extraline("You stand in the northeast corner of a " 
      + "farming field. Along the edges of the field " 
      + "are several wooden houses. It looks like some "
      + "people have turned this farming field to some "
      + "kind of camp. The ground has been all trampled "
      + "up, so the field is hardly used for much farming "
      + "these days.");

    add_item(({"house","houses","wood"}), "The houses are "
      + "very simple, they give you the impression that "
      + "they have been built to serve for a temporarely "
      + "reason, perhaps while another building is "
      + "being built?\n");
    add_item(({"ground", "field", "farming field"}), "The "
      + "ground was obviously used to grow crops some "
      + "years ago, but now some simple wooden houses has "
      + "been built and the ground has been trampled up "
      + "because of heavy travelling.\n");

    set_no_exit_msg("east", "The only thing you can see to the " +
      "east is the western wall of a house.\n");
    set_no_exit_msg(({"north", "northeast"}), "The way to the " +
      "north is blocked by a fence. From what you see behind " +
      "it, there is no reason proceed further.\n");

    add_exit(DUN_WILD_ROOMS + "field03", "west", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field06", "southwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field07", "south", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field01", "northwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field08", "southeast", 0, 2);


    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(3)));
}
