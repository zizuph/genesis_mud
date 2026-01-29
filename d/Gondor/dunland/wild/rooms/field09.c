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
    set_areaname("Enedwaith");
    set_land("Dunland");
    set_extraline("You find yourself in the east part of a "
      + "farming field. But the last year it cannot have been "
      + "used for farming. Small houses of wood have been built "
      + "on the field, and the ground looks like it is quite " 
      + "heavily travelled. You can spot a fence at the south "
      + "edge of the field and in the middle of the field you "
      + "can spot a plow. To your east you can enter one of "
      + "the houses.");

    add_item(({"house","houses","wood"}), BSN(
	"The houses are very simple, they give you the impression "
	+ "that they have been built to serve for a temporarely reason, "
	+ "perhaps while another building is being built?"));
    add_item(({"ground", "field", "farming field", }), BSN(
	"The ground was obviously used to grow crops some years ago, "
	+ "but now some simple wooden houses has been built and the "
	+ "ground has been trampled up because of heavy travelling."));
    add_item(({"fence", "broken fence"}), BSN(
	"Along the southern edge of the field runs an old fence. It "
	+ "does not look to be in a good shape."));
    add_item(({"plow","middle"}), BSN(
	"In the middle of the field, far to the west of here, "
	+ "you can see a plow, it does not look to be recently "
	+ "used, but you would have to get closer to be sure."));
    add_item(({"bushes", "growth"}), "To the north stands thick " +
      "bushes. It is all overgrown and uninteresting.\n");
    add_item("fence", "The fence is old and covered with moss.\n");
    add_item("moss", "Moss is growing all over the fence.\n");

    set_no_exit_msg("northwest", "To the northwest you only see " +
      "the eastern wall of a house. You decide not to go there.\n");
    set_no_exit_msg(({"north","northeast"}), 
      "The north way is blocked by bushes and other growth. You " +
      "see nothing of interest there.\n");
    set_no_exit_msg("east", "To the east you see the door of " +
      "a house. To enter it, you just need to walk in.\n");
    set_no_exit_msg("southeast", "To way to the southeast is " +
      "blocked by an old fence. Behind it you see nothing of " +
      "interest.\n");

    add_exit(DUN_WILD_ROOMS + "house08", "in", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field08", "west", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field13", "southwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field14", "south", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(2)));
}
