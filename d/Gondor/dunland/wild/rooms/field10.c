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
    set_extraline("You find yourself in the southwest part of a " +
        "farming field. But the last year it cannot have been " +
        "used for farming. Small houses of wood have been built " +
        "on the field, and the ground looks like it is quite " +
        "heavily travelled. A broken fence adorns the southern " +
        "part of the field but to the southwest the is a gap in " +
        "in the fence and and a path is visable. In the middle " +
        "of the field you can spot a plow. To your west you can " +
        "enter one of the houses.");

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
	"In the middle of the field, just to the northeast of here, "
	+ "you can see a plow, it does not look to be recently "
	+ "used, but you would have to get closer to be sure."));

    set_no_exit_msg("south", "The way to the south is blocked by " +
        "an old fence. You see nothing of interest behind it.\n");
    set_no_exit_msg("southeast", "To the southeast you see the " +
        "western wall of a house. You decide not to go there.\n");
    set_no_exit_msg("northwest", "To the northwest you see the " +
        "southern wall of a house. You decide not to go there.\n");
    set_no_exit_msg("west", "To the west stands a house. To enter " +
        "it, just walk in.\n");

    add_exit(DUN_WILD_ROOMS + "house04", "in", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field05", "north", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field11", "east", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field06", "northeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "road01", "southwest", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(2)));
}
