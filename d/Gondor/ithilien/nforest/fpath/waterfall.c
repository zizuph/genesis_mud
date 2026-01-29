/*
 *      /d/Gondor/ithilien/nforest/fpath/waterfall.c
 *
 *      Coded 1993 by Elessar.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("waterfall");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("You are standing on a flat wet stone just by the " +
        "edge of a gorge, where a little stream comes rushing down " +
	"from the northeast, plunging out into a free fall over the " +
        "edge. The waterfall forms a beautiful veil, as the stream " +
        "pours down into the pool below. The walls of the gorge glisten " +
        "slickly, sprayed with a fine shower of water droplets from " +
        "the falls. Thickets of green broad-leaved bushes grow " +
        "alongside the stream, almost to the very edge of the " +
        "waterfall, and east is the only direction you can leave.");
    add_item(({"veil","waterfall","water","fall"}), BSN(
        "The waterfall plunges over a flat even edge at the top " +
        "of the gorge, shaping the fall into a thin veil of water. The " +
        "water pours into a pool some meters below."));
    add_cmd_item( ({ "water", "water from waterfall", "water from fall", }),
	"drink", BSN("You cannot reach the waterfall from where you are " +
	"standing, so you cannot drink water from it."));
    add_item( ({"stone", "wet stone", "flat stone"}), BSN("The flat stone " +
        "you are standing on, is wet from all the water from the waterfall. " +
        "Luckily you are not standing in the stream, for the water would have " +
        "had no mercy for you and death might be waiting if you if you would " +
        "fall down."));
    add_item(({"thicket","thickets","bush","bushes"}), BSN(
        "The green broad-leaved bushes form a dense thicket close to the " +
        "stream, which you can leave only to the east. To the west and the " +
        "south, the intertwining branches make your passage impossible."));
    add_exit(ITH_DIR + "nforest/fpath/bushes5", "east", 0, 2);
}
