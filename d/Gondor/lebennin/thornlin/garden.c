#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master");

#include <macros.h>
#include <stdproperties.h>
#include "locals.h"

void
create_area_room()
{
    set_areatype(1);
    set_areadesc("garden");
    set_whereis("in");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("This is a small, not very well kept garden. Grass, "
      + "flowers and trees are growing wildly. North of the garden "
      + "is the main square of the village, to the south is a small "
      + "cottage.");

    add_item(({"house", "farm house", "cottage", }), BSN(
	"It is a small cottage, probably the home of one of the farmers living "
	+ "here in this village. From the looks of the cottage, the people "
	+ "living there are probably rather poor."));

    add_item("grass","The grass is growing tall and thick.\n");
    add_item("flowers","In between the grass there are many colourful "+
      "flowers.\n");
    add_item("trees","Many kind of trees are growing, but a willow "+
      "seems to dominate the garden.\n");
    add_item(({"willow", "tree", }), 
      "It is a large willow with long hanging branches.\n");
    add_item(({"garden", }), BSN(
	"The garden is rather small and not well kept. Grass, flowers "
	+ "and trees are growing wildly."));
    add_search_places(({"garden"}));

    add_exit(THORN_DIR + "r2c","north",0,1);
    add_exit(THORN_DIR + "house","south","@@enter_house",1);

}

int
enter_house()
{
    write("You walk through the door and enter the small house.\n");
    return 0;
}
