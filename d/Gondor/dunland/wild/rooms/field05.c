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
    set_extraline("You find yourself in the west part of a "
      + "farming field. But the last year it cannot have been "
      + "used for farming. Small houses of wood have been built "
      + "on the field, and the ground looks like it is quite " 
      + "heavily travelled. You can spot a fence at the south "
      + "edge of the field and just to the east of here you "
      + "can see a plow. To your west you can enter one of "
      + "the houses.");

    add_item(({"house","houses","wood"}), "The houses are very "
      + "simple, they give you the impression that they have "
      + "been built to serve for a temporarely reason, "
      + "perhaps while another building is being built?\n");
    add_item(({"ground", "field", "farming field"}), "The "
      + "ground was obviously used to grow crops some years "
      + "ago, but now some simple wooden houses has been built "
      + "and the ground has been trampled up because of heavy "
      + "travelling.\n");
    add_item(({"fence", "broken fence"}), "Along the southern "
      + "edge of the field runs an old fence. It does not look "
      + "to be in a good shape.\n");
    add_item("plow", "In the middle of the field, just to "
      + "the east of here you can see a plow, it does not "
      + "look to be recently used.\n");

    set_no_exit_msg("northwest", "To the northwest you can only " +
      "see the southern wall of a house. You decide not to go " +
      "there.\n");
    set_no_exit_msg("southwest", "To the southwest you can only " +
      "see the northern wall of a house. You decide not to go " +
      "there.\n");
    set_no_exit_msg("west", "You walk up towards the house. It " +
      "looks very simple, there door is just right in front you. " +
      "Are you interested in going inside?\n");


    add_exit(DUN_WILD_ROOMS + "house03", "in", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field06", "east", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field11", "southeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field10", "south", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field03", "northeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field02", "north", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(2)));
}
