/* eastroad coded by Ashbless */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Grassland");
    set_long(
        "You are standing in a grassy field, south of the east road. " +
        "The field extends to the west. " +
        "The road disappears west into a distant forest " +
        "and leads east out of sight beyond a thick " +
        "forest of aspen and pine. " +
        "This forest lies south and east of here, " +
        "stretching southwest and northeast towards " +
        "the road. A small path enters it to the east. " +
        "North of the road is farmland. " +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers.\n");

    add_exit(TDIR + "east4", "north");
    add_exit(TDIR + "grass3", "east","@@eblock");
    add_exit(TDIR + "grass2","west");

    add_item("distant forest", BS(
        "Far to the west, stands a forest of tall trees. " +
        "The road leads out of it to the east.",70));
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
    add_item(({"cloud","clouds","storm cloud","storm clouds",
        }),BS("These clouds do not look natural and give you " +
        "a feeling of forboding evil.",70));
    add_item(({"grassland","grassy field","ground","field"}),BS(
        "The field is covered with thick wild grass and " +
        "weeds, with intermittent patches of dirt. It " +
        "stretches to the west.",70));
    add_item(({"wild grass","thick grass","thick wild grass",
        "grass","weeds","dirt","patches"}),BS(
        "You notice nothing special.",70));
    add_item("forest","Which forest, the distant forest or thick forest?\n");
    add_item("thick forest",BS(
        "A thick forest of aspen and pine lies to the " +
        "south and east of you. It curves southwest and " +
        "northeast to the road. The undergrowth prevents " +
        "movement to the south but a small path leads into " +
        "it to the east.",70));
    add_item(({"small path","path"}),BS(
        "It cuts through the forest to the east.",70));
}

eblock()
{
    write(BS(
        "As you follow the path into the " +
        "forest, you become completely and utterly " +
        "lost. Fortunately a kindly gnome guides you " +
        "back out again. The wizards of Krynn really " +
        "should make clearer paths. Hopefully, they will " +
        "do this very soon. Try again later.",70));
    return 1;
}
