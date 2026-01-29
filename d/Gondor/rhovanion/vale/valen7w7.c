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
    set_herbs_7();
    
    set_short("Vale of the Anduin");
    set_long("Your eyes drink in the sight of the tall, yellow grass which " +
        "covers the sloping hills, surrounding you in all directions. You " +
        "are at the bottom of a deep valley, carved out by the wild waters " +
        "of the great Anduin river as it flows down from the high mountains " +
        "in the north to empty out into the sea far to the south. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they become the Misty Mountains, their peaks lost in " +
        "the clouds high above. The shadowy edge of Mirkwood forest lines " +
        "the eastern edge of the valley, where the tall trees are black and " +
        "menacing.\n");

    add_exit(VALE_DIR + "valen6w7", "south",0,2,1);
    add_exit(VALE_DIR + "valen6w6", "southeast",0,2,1);
    add_exit(VALE_DIR + "valen7w6", "east",0,2,1);
    add_exit(VALE_DIR + "valen8w6", "northeast",0,2,1);
    add_exit(VALE_DIR + "valen8w7", "north",0,2,1);
}
