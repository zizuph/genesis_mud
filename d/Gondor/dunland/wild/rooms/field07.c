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
    set_extraline("You find yourself in the middle of a "
      + "farming field. From what you can tell, the field "
      + "has not been used for farming the last years. "
      + "To your west you can see a plow. Around the "
      + "the edges of the field some small houses of wood "
      + "have been built and the ground looks like it is quite " 
      + "heavily travelled. At the south edge of the field "
      + "stands a wooden fence.");

    add_item(({"house","houses","wood"}), "The houses are very "
      + "simple, they give you the impression that they have "
      + "been built to serve for a temporarely reason.\n");
    add_item(({"ground", "field", "farming field"}), "The "
      + "ground was obviously used to grow crops some years "
      + "ago, but now some simple wooden houses has been built "
      + "and the ground has been trampled up because of heavy "
      + "travelling.\n");
    add_item("fence", "Along the southern edge of the field runs "
      + "an old fence. It looks to be in a horrible shape.\n");
    add_item(({"plow","middle"}), "In the middle of the field, "
      + "just to the west of here, you can see a plow, it does "
      + "not look to be recently used, but you would have to "
      + "get closer to be sure.\n");

    set_no_exit_msg("northeast", "To your northeast you see the " +
      "wall of a house. You decide not to go there.\n");

    add_exit(DUN_WILD_ROOMS + "field03", "northwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field04", "north", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field06", "west", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field08", "east", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field11", "southwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field12", "south", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field13", "southeast", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(4)));
}
