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
    set_extraline("You stand in the northwest part of a " 
      + "farming field. Along the edges of "
      + "the field are several wooden houses. It looks "
      + "like some people have turned this farming field "
      + "to some kind of camp. The ground has been all "
      + "trampled up, so the field is hardly used for much "
      + "farming these days. To the west you can enter "
      + "one of the houses.");

    add_item(({"house","houses","wood",}), "The houses are "
      + "very simple, they give you the impression "
      + "that they have been built to serve for a "
      + "temporarely reason, perhaps while another building "
      + "is being built?\n");
    add_item(({"ground", "field", "farming field", }), "The "
      + "ground was obviously used to grow crops some years "
      + "ago, but now some simple wooden houses has been "
      + "built and the ground has been trampled up because "
      + "of heavy travelling.\n");

    set_no_exit_msg("north", "You look towards the north but " +
      "quickly decide not to go there. All you see is the " +
      "southern wall of a house.\n");
    set_no_exit_msg("northwest", "Towards the northwest you see " +
      "nothing of interest. You decide not to go there.\n");
    set_no_exit_msg("southwest", "Towards the southwest you only " +
      "the northern wall of a house. You decide not to go there\n");
    set_no_exit_msg("west", "You walk closer to the house. It " +
      "looks very simple yet recently built.\n");
    set_no_exit_msg(({"southeast", "east"}),
      "You walk towards east, but quickly realize that the " +
      "way is blocked by a fence.\n");


    add_exit(DUN_WILD_ROOMS + "house02", "in", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field01", "northeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field05", "south", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field06", "southeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field03", "east", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field06", "southeast", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(2)));
}
