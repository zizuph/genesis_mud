#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include "locals.h"
#include <language.h>

void
create_area_room()
{
    set_areatype(3);
    set_areadesc("wide");
    set_whereis("near");
    set_cityname("Thornlin");
    set_crop("oats");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("To the north, a large mountain range is running from "
      + "east to west. South of the mountains, fields are covering the "
      + "land. South of here, the road leads west into the village.");

    add_item("road","The road comes from the east and runs west into the "+
      "village.");
    add_item(({"mountain","mountains", "mountain range", }),BSN(
	"The mountains reach about ten thousand feet up into the sky. "
	+ "The snow-covered tops have given this mountain range the name "
	+ "Ered Nimrais, or the White Mountains in the Common Tongue."));
    add_item("village", BSN("The village is surrounded by trees and "
	+ "fields. In the village there are people and cattle walking "
	+ "on the streets."));

    add_exit(THORN_DIR + "r7","south",0,2);
}

