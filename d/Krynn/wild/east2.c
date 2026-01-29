/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("East road");
    set_long(
        "You are on the east road, near the village of Solace. " +
        "West the road enters a forest of tall trees, leading towards " +
	"the village. " +
        "About a mile to the south, thick woodlands follow the road " +
	"east towards " +
        "some low mountains. Further south, a lone peak is visible " +
        "above the trees. To the north is farmland and you can " +
        "occasionally catch a glimpse of farmers wading through the " +
        "tall golden wheat." +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east1", "west");
    add_exit(TDIR + "grass1", "south");
    add_exit(TDIR + "field1", "north");
    add_exit(TDIR + "east3", "east");

    add_item("forest", BS(
        "West of you stands a forest of tall trees. " +
        "The road leads out of it to the east.",70));
    add_item(({"tree","tall tree","tall trees","trees"}),BS(
        "These are the fabled Vallenwood trees of Solace, " +
        "some of the largest trees you have ever seen.",70));
    add_item(({"wheat","tall wheat","tall golden wheat","farmlands",
		"golden wheat","farmland","field","wheat field"}),BS(
        "Swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. The field stretches to the north and east.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. It stretches " +
        "east towards some low mountains and disappears " +
        "into the cool shade of a forest to the west.",70));
    add_item(({"mountains","low mountains","mountain range"}),BS(
        "A low range of mountains is visible on the eastern " +
        "horizon.",70));
    add_item(({"thick woodlands","woodlands"}),BS(
        "Thick woodlands of Aspen and pine stretch " +
        "for miles to the east, south of the road.",70));
    add_item(({"peak","mountain peak","lone peak"}),BS(
        "This lone mountain peak stands miles to " +
        "the south. An awesome view from here, you " +
        "can only imagine what it would look like " +
        "up close. The point is shrouded in soft " +
        "white clouds, in sharp contrast with the " +
        "dark clouds to the north.",70));
    add_item(({"cloud","clouds","storm cloud","storm clouds",
        }),BS("These clouds do not look natural and give you " +
        "a feeling of forboding evil.",70));

}
