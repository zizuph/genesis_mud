
/*  In the Basin of the Air Fountain

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("In the basin of the Air Fountain");
    set_long("You have swum into the basin of the Air Fountain and "+
        "to your delight have found nothing but air. Your lungs, "+
        "if they could speak, would be thanking you for the relief "+
        "you have given them. You can now see that the air is "+
        "circulated back to the bottom with a tube which is behind "+
        "several small holes in the top of the basin. When you are "+
        "ready, you can head back out into the water.\n");

    add_item(({"hole","holes","small hole","small holes"}),"You can "+
        "see nothing but air in the holes. Behind the holes you see "+
        "a large tube that leads down into the statues below you to "+
        "recirculate the air.\n");

    add_item(({"tube","large tube"}),"You cannot see much about the "+
        "tube as it is behind the holes.\n");

    add_item("basin","The basin is made of the same marble as the "+
        "statues below you are made from and has several small "+
        "holes in it for the air to travel into.\n");

    add_item(({"statue","statues"}),"You are wading above the statues "+
        "of the mermaids and tritons. It is good to be breathing air "+
        "once again.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);

    add_exit(THALC+"fountain","out", 0, 1);
}
