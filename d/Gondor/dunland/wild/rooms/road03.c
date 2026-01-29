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
      "underbrush. The path leads north and southwest where it " +
      "to a larger road. To the north the path looks to be " +
      "leading to some kind of camp.");

    add_item(({"house","houses"}), BSN(
	"The houses looks to be made of wood, quite small."));
    add_item(({"ground", "field", "farming field", }), BSN(
	"The ground was obviously used to grow crops some years ago, "
	+ "but now some simple wooden houses has been built and the "
	+ "ground has been trampled up because of heavy travelling."));
    add_item("path", "There is a small path that leads to the " +
      "southwest and north.\n");
    add_item("road", "To the southwest the path connects to a " +
      "larger stone paved road.\n");
    add_item("underbrush", "Thick underbrush surrounds the path, " +
      "you can see nothing special about it.\n");

    set_no_exit_msg(({"east", "southeast", "northeast"}), "The way " +
      "east is blocked by thick underbrush.\n");
    set_no_exit_msg(({"west", "northwest"}), "The way " +
      "west is blocked by thick underbrush.\n");
    set_no_exit_msg("south", "The way south is blocked by thick " +
      "underbrush.\n");

    add_exit(DUN_WILD_ROOMS + "road02", "north", 0, 2);
    add_exit(DUN_DIR_ROAD + "r25", "southwest", 0, 2);

}
