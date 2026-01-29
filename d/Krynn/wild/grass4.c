/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Grassland");
    set_long(
        "You are standing in a grassy field, " +
        "which extends to the north and east. " +
        "Far to the north is a road and " +
        "west of you stands a shady forest of tall trees. " +
        "The road enters the forest, leading towards the village " +
        "of Solace. Directly south of you is a thick " +
        "forest of aspen and pine. " +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "grass1", "north");
    add_exit(TDIR + "grass5", "east");

    add_item("shady forest", BS(
        "West of you stands a forest of tall trees. " +
        "The cool shade looks inviting but dense " +
        "undergrowth blocks your path.",70));
    add_item(({"tree","tall tree","tall trees","trees"}),BS(
        "These are the fabled Vallenwood trees of Solace, " +
        "some of the largest trees you have ever seen.",70));
    add_item(({"road","east road"}),BS(
        "This is the east road of Solace. It stretches " +
        "east and west where it disappears " +
        "into the cool shade of a forest .",70));
    add_item(({"cloud","clouds","storm cloud","storm clouds",
        }),BS("These clouds do not look natural and give you " +
        "a feeling of forboding evil.",70));
    add_item(({"grassland","grassy field","ground","field"}),BS(
        "The field is covered with thick wild grass and " +
        "weeds, with intermittent patches of dirt. It " +
        "stretches to the north and east.",70));
    add_item(({"wild grass","thick grass","thick wild grass",
        "grass","weeds","dirt","patches"}),BS(
        "You notice nothing special.",70));
    add_item("forest","Which forest, the shady forest or thick forest?\n");
    add_item("thick forest",BS(
        "Directly south of you is a thick forest " +
         "of aspen and pine, which stretches for miles " +
         "to the east. The cool shade looks inviting " +
         "but the dense undergrowth prevents you from entering.",70));
}
