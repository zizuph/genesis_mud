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
    set_extraline("You find yourself in the southeast part of a "
      + "farming field. But the last year it cannot have been "
      + "used for farming. Small houses of wood have been built "
      + "on the field, and the ground looks like it is quite " 
      + "heavily travelled. A broken fence adorns the southern "
      + "part of the field and in the middle of the field you "
      + "can spot a plow. To your southeast you can enter one of "
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
	+ "wont hold back any animals at all, since it is now broken. "
	+ "Moss is covering the wooden planks. Some planks are now "
	+ "hanging loose."));
    add_item(({"planks","wooden planks"}), BSN(
	"The planks of the fence in a horrible shape. Some are " 
	+ "hanging loose, some are rotten and most of them are "
	+ "covered in moss."));
    add_item("moss", "Most of the planks in the fence are " 
      + "covered with green moss.\n");
    add_item(({"plow","middle"}), BSN(
	"In the middle of the field, to the northwest of here, "
	+ "you can see a plow, it does not look to be recently "
	+ "used, but you would have to get closer to be sure."));
    add_item("bushes", "To the east stands large overgrown bushes.\n");

    set_no_exit_msg("southwest", "To the southwest you only see " +
        "the eastern wall of a house. You decide not to go there.\n");
    set_no_exit_msg("south", "The way to the south is blocked by an " +
        "old fence. You see nothing of interest behind it.\n");
    set_no_exit_msg("southeast", "To the southeast you see a house. " +
        "To enter it, just walk inside.\n");
    set_no_exit_msg("east", "The way east is blocked by large " +
        "overgrown bushes. It looks totally uninteresting.\n");
    set_no_exit_msg("northeast", "To the northeast you can see the " +
        "southern wall of a house. You decide not to go there.\n");

    add_exit(DUN_WILD_ROOMS + "house07", "in", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field13", "west", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field09", "north", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field08", "northwest", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(2)));
}
