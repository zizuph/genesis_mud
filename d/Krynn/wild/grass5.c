/*
 * Eastroad
 * Coded by Ashbless
 *
 * South exit change by Lunatari to not include SBLOCK()
 * We should expand this path instead.
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit  OUTWILDROOM

create_wild_room()
{
    set_short("Grassland");
    set_long(
        "You are standing in a grassy field, " +
        "which extends to the north and west. " +
        "Further west, stands a shady forest of tall trees " +
        "and a road lies far to the north. " +
        "The road enters the forest, leading towards the village " +
        "of Solace. Directly south and east of you is a thick " +
        "forest of aspen and pine. " +
        "A well-used trail enters it to the south. " +
        " Ominous on the northern horizon, unnatural looking " +
        "storm clouds claw the sky with dark fingers." +
        " There are some tracks on the ground.\n");

    add_exit(TDIR + "grass2", "north");
    add_exit(TDIR + "grass4", "west");
    add_exit(C_GNOME, "south");

    add_item("shady forest", BS(
        "West of you stands a forest of tall trees. " +
        "The road leads out of it to the east.",70));
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
        "stretches to the north and west.",70));
    add_item(({"wild grass","thick grass","thick wild grass",
        "grass","weeds","dirt","patches"}),BS(
        "You notice nothing special.",70));
    add_item("forest","Which forest, the shady forest or thick forest?\n");
    add_item("thick forest",BS(
        "Directly south and east of you is a thick forest " +
        "of aspen and pine. The dense undergrowth prevents " +
        "you from going east but a well-used trail " +
        "enters it to the south.",70));
    add_item(({"well-used trail","trail","well used trail"}),BS(
        "It leads south into a thick forest of aspen and pine. " +
        "It is obviously well-used for there are many footprints.",70));
    add_item(({"footprint","footprints","print","prints",
        "track","tracks"}),BS(
        "There are alot of footprints here, heading north " +
        "and south. The prints could only be made by very " +
        "small feet.",70));
}

sblock()
{
    write(BS("You walk through the forest into a grassy clearing.  " +
      	"You sense that there was a good deal more to your journey " +
      	"than just one step, but you can't remember it just now.  " +
      	"Still, it was a lot of fun.  You hope some wizard fills in " +
	"the details soon.", 70));
    return 0;
}
