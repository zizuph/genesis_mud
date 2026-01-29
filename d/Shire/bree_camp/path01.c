/*
 * Path in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit ENTER_BASE;

void
create_camp_room()
{
    set_short("Outside a large tent");
    set_extraline("Tents line the paths of the camp. They are of " +
        "varying sizes and descriptions. They provide shelter " +
        "for the inhabitants of the camp and ready places to " +
        "store their loot from raids. The paths are well worn " +
        "that run throughout the camp.\n" +
        "A large standard marks the entrance of the tent.");

    add_item(({"large standard", "standard"}),
        "This grisly pole is sunk into the ground. Large " +
        "black flags hang from it with fresh, decapitated " +
        "heads on its top.\n");
    add_item(({"fresh heads", "heads"}),
        "They are human, elf, and, dwarf heads, impaled on top " +
        "of the pole.\n");
    add_item(({"human heads", "elf heads", "dwarf heads"}),
        "They are decapitated heads impaled onto the large standard.\n");
    add_item(({"flags", "banners", "black banners"}),
        "The banners are large and completely black with a red " +
        "eye crudely painted in the center. They hang from the " +
        "tops of the poles.\n");
    add_item(({"poles", "pole", "grisly poles", "grisly pole"}),
		"The poles are about three times as tall as a human, " +
        "and rough looking. They are sunk deep into the ground " +
        "and decorated with black banners.\n");

    add_exit(CAMP_DIR + "path03", "south");

    set_tent_name("tent01");
    reset_shire_room();
}

void reset_shire_room()
{
    clone_camp_orcs();
}
