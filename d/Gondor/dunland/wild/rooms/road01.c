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
    set_area("northwest");
    set_areaname("Dunland");
    set_land("Enedwaith");
    set_extraline("You walk along a small path surrounded by thick " +
        "underbrush. The path leads northeast and south. To the " +
        "north, houses can be seen, looking as a rather newbuilt " +
        "camp.A broken fence looks to lead around it but there is " +
        "gap in the fence offering a way inside.");

    add_item(({"house","houses","wood"}), BSN(
	"The houses are very simple, they give you the impression "
	+ "that they have been built to serve for a temporarely reason, "
	+ "perhaps while another building is being built?"));
    add_item(({"ground", "field", "farming field", }), BSN(
	"The ground was obviously used to grow crops some years ago, "
	+ "but now some simple wooden houses has been built and the "
	+ "ground has been trampled up because of heavy travelling."));
    add_item(({"fence", "broken fence"}), BSN(
	"Its a very old fence, that wont hold anything either outside " +
        "or inside. The planks are hanging loose and they all look " +
        "rotten and covered with moss."));
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
    add_item("path", "There is a small path that leads to the " +
        "south and northeast. Northeast it leads into some kind " +
        "of camp.\n");
    add_item("gap", "There is a gap in the fence to the northeast, " +
        "offering a way into some kind of camp.\n");
    add_item("underbrush", "Thick underbrush surrounds the path, " +
        "you can see nothing special about it.\n");

    set_no_exit_msg(({"east", "southeast"}), "The way to the east is " +
        "not possible to pass through because of the thick " +
        "underbrush.\n");
    set_no_exit_msg("north", "Looking to the north, you see that you " +
        "cannot go further in that direction due to the wooden wall of " +
        "a house.\n");
    set_no_exit_msg(({"northwest", "west", "southwest"}), "The way " +
        "to the west is not possible to pass through because of the " +
        "thick underbrush.\n");

    add_exit(DUN_WILD_ROOMS + "field10", "northeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "road02", "south", 0, 2);

}
