/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Wheat field");
    set_long(
        "You are standing amid an ocean of golden wheat, " +
        "which extends well to the north and west. " +
        "South and east of here is the east road. The road " +
        "travels east from a forest far to the west. " +
        "South of here, the road bends to the northeast, leading " +
        "towards a dark wood at the foot of some low mountains. Far to the " +
        "south, a lone peak dominates the sky, visible " +
        "behind thick woodlands that stretch to the east and west. " +
        "Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east6", "east");
    add_exit(TDIR + "field3", "west");
    add_exit(TDIR + "east5", "south");

    add_item(({"forest","distant forest"}),BS(
        "The road disappears into a forest far to " +
        "the west. You can't make out much detail from here.",70));
    add_item(({"wheat","golden wheat","ocean","field","wheat field"}),BS(
        "Coming past your waist and swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. The field stretches to the north and west.",70));
    add_item(({"road","east road"}),BS(
        "South and east of you is the east road of Solace. " +
        "South of here it turns northeast, leading towards " +
        "a dark wood at the foot of some low mountains. " +
        "Far to the west, it disappears " +
        "in to the cool shade of a distant forest.",70));
    add_item(({"mountains","low mountains","mountain range"}),BS(
        "A low range of mountains is visible on the eastern " +
        "horizon.",70));
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
    add_item(({"thick woodlands","woodlands"}),BS(
        "Thick woodlands of Aspen and pine stretch " +
        "to the east and west, south of the road.",70));
    add_item(({"dark wood","wood"}),BS(
        "It lies at the foot of a low mountain range and " +
        "the road leads into it. " +
        "Gnarled oak trees cast dark shadows on the surrounding area." +
        "",70));
}
