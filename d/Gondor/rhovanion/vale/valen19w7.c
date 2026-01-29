/*
 * Vale of the Anduin.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "vale/base";

void 
create_vale_room()
{
    set_items_vale();
    set_items_east();
    set_items_river();
    set_items_mirk();
    set_items_gate();
    set_herbs_2();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellow-green grass surrounds you, swaying and brushing " +
        "against you with every faint breeeze which twists past you. You are " +
        "standing at the bottom of a deep valley, on the eastern banks of " +
        "the great river Anduin. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. At your feet, a small path begins " +
        "to wind its way towards the black trees of Mirkwood forest " +
        "which looms menacingly before you. Where the path meets the " +
        "forest, two lichen covered oak trees bend and twist together " +
        "their branches in a high arch, framing out the ivy strangled " +
        "entrance to Mirkwood known as the forest gate.\n");

    add_exit(VALE_DIR + "valen18w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen18w6", "southeast",0,2,1);
    add_exit(MIRK_EP_DIR + "p01", "east","@@fgate@@",2,1);
    add_exit(MIRK_N_DIR + "r01/f01", "northeast","@@nfor@@", 2,1);
    add_exit(VALE_DIR + "valen20w7", "north","@@block@@",2,1);
}

int
fgate()
{
write("Gathering a deep breath of courage, you pass through the forest " +
    "gate and into the gloomy depths of Mirkwood forest.\n");
return 0;
}

int
nfor()
{
write("The forest is so thick here that you cannot find an entrance, " +
    "however, the forest gate is right here! You can enter Mirkwood " +
    "forest by following the elf path eastward.\n");
return 1;
}

int
block()
{
write("The Anduin river appears to have flooded its banks, a soggy " +
    "marsh extending all the way to the trees of Mirkwood. You cannot " +
    "find any passage north from here.\n");
return 1;
}