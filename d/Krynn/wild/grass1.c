/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Grassland");
    set_long(
        "You are standing in a grassy field, south of the east road. " +
        "West of you stands a forest of tall trees. " +
        "The road enters the forest, leading towards the village " +
        "of Solace. Less than a mile to the south, thick " +
        "woodlands follow the road east. " +
        "Farther south, a lone peak is visible " +
        "above the trees. North of the road is farmland. " +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east2", "north");
    add_exit(TDIR + "grass2", "east");
    add_exit(TDIR + "grass4", "south");

    add_item("forest", BS(
        "West of you stands a forest of tall trees. " +
        "The cool shade looks inviting but dense " +
        "undergrowth blocks your path.",70));
    add_item(({"tree","tall tree","tall trees","trees"}),BS(
        "These are the fabled Vallenwood trees of Solace, " +
        "some of the largest trees you have ever seen.",70));
    add_item(({"farmland","farmlands","wheat"}),BS(
        "It looks like fields of wheat but you can't " +
        "see much detail from here.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. It stretches " +
        "east and west where it disappears " +
        "into the cool shade of a forest .",70));
    add_item(({"thick woodlands","woodlands"}),BS(
        "Thick woodlands of Aspen and pine stretch " +
        "for miles to the east, south of here.",70));
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
    add_item(({"grassland","grassy field","ground","field"}),BS(
        "The field is covered with thick wild grass and " +
        "weeds, with intermittent patches of dirt. It " +
        "stretches to the south and east.",70));
    add_item(({"wild grass","thick grass","thick wild grass",
        "grass","weeds","dirt","patches"}),BS(
        "You notice nothing special.",70));
}
