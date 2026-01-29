/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("East road");
    set_long(
        "You are on the east road. East of here the road bends " +
         "to the northeast, heading towards a dark wood at the foot " +
         "of some low mountains. The road leads west through farmland " +
         "towards a forest " +
        "and the village of Solace. " +
        "Thick woodlands parallel the road, less than a mile to the " +
        "south, and curve north to the road farther east. " +
        "Farther south, a lone peak is visible above the trees. " +
        "To the north is farmland and you can " +
        "occasionally catch a glimpse of farmers wading through the " +
        "tall golden wheat." +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east3", "west");
    add_exit(TDIR + "grass3", "south");
    add_exit(TDIR + "field3","north");
    add_exit(TDIR + "east5", "east");

    add_item("forest", BS(
        "Far to the west is a forest of tall trees. " +
        "The road leads out of it to the east.",70));
    add_item(({"tree","tall tree","tall trees","trees"}),BS(
        "These are the fabled Vallenwood trees of Solace, " +
        "some of the largest trees you have ever seen.",70));
    add_item(({"wheat","tall wheat","tall golden wheat",
        "farmlands","golden wheat","farmland","field","wheat field"}),BS(
        "Swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. The field stretches to the north, east, and west.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. " +
        "East of here it turns northeast, leading towards " +
        "a dark wood at the foot of some low mountains. " +
        "It winds through farmland and disappears " +
        "in to the cool shade of a forest far to the west.",70));
    add_item(({"mountains","low mountains","mountain range"}),BS(
        "A low range of mountains is visible on the eastern " +
        "horizon.",70));
    add_item(({"thick woodlands","woodlands"}),BS(
        "Thick woodlands of Aspen and pine stretch " +
        "to the east. West of here they curve north " +
        "towards the road.",70));
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
    add_item(({"dark wood","wood"}),BS(
        "It lies at the foot of a low mountain range and " +
        "the road leads into it. You can't make out much " +
        "detail from here.",70));
}
