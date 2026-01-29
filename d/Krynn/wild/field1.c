/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Wheat field");
    set_long(
        "You are standing amid an ocean of golden wheat, " +
        "which extends well to the north and east. " +
        "West of you is a forest of tall " +
        "trees. To the south a road runs out of the forest " +
        "leading east to a distant mountain range. Far to the " +
        "south, a lone peak dominates the sky, visible " +
        "behind thick woodlands that stretch to the east. " +
        "Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "field2", "east");
    add_exit(TDIR + "east2", "south");

    add_item("forest", BS(
        "West of you stands a forest of tall trees. " +
        "The cool shade looks inviting but dense " +
        "undergrowth blocks your path.",70));
    add_item(({"tree","tall tree","tall trees","trees"}),BS(
        "These are the fabled Vallenwood trees of Solace, " +
        "some of the largest trees you have ever seen.",70));
    add_item(({"wheat","golden wheat","ocean","field","wheat field"}),BS(
        "Coming past your waist and swaying rhythmically " +
        "in the wind, the golden wheat is ready to be " +
        "harvested. The field stretches to the north and east.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. It leads from the village " +
        "in the forest and winds towards mountains to the east.",70));
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
