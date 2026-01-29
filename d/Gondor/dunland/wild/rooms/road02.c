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
    set_areadesc("on a small path");
    set_area("southeast");
    set_areaname("Dunland");
    set_land("Enedwaith");
    set_extraline("You walk along a small path surrounded by thick " +
        "underbrush. The path leads north and south. To the " +
        "north, houses can be seen, looking as a rather newbuilt " +
        "camp.");

    add_item(({"house","houses","wood"}), BSN(
	      "The houses are very simple, they give you the impression "
	      + "that they have been built to serve for a temporarely reason, "
	      + "perhaps while another building is being built?"));
    add_item(({"ground", "field", "farming field", }), BSN(
	      "The ground was obviously used to grow crops some years ago, "
	      + "but now some simple wooden houses has been built and the "
	      + "ground has been trampled up because of heavy travelling."));
    add_item("path", "There is a small path that leads to the " +
        "south and northeast. Northeast it leads into some kind " +
        "of camp.\n");
    add_item("gap", "There is a gap in the fence to the northeast, " +
        "offering a way into some kind of camp.\n");
    add_item("underbrush", "Thick underbrush surrounds the path, " +
        "you can see nothing special about it.\n");

    set_no_exit_msg(({"east", "southeast", "northeast"}), "The way " +
        "east is blocked by thick underbrush.\n");
    set_no_exit_msg(({"west", "northwest", "southwest"}), "The way " +
        "west is blocked by thick underbrush.\n");

    add_exit(DUN_WILD_ROOMS + "road01", "north", 0, 2);
    add_exit(DUN_WILD_ROOMS + "road03", "south", 0, 2);

}
