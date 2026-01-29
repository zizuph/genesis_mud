
 /* Join/Leave room for the Elemental Worshippers of Calia
  * by Jaacar
  * July 22nd, 1996
  */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"

void
create_room()
{
    set_short("At a silver altar");
    set_long("You have entered a large section of this temple. "+
        "Before you on the ground is a pure silver altar that "+
        "shines brightly in the sunshine which enters through a "+
        "small hole in the ceiling. Its bright radiance "+
        "fills your soul with peace and happiness. Surrounding the altar "+
        "are small bushes and bright yellow flowers. There are two "+
        "archways, one in each of the southern corners of this room. "+
        "You can also head out of the room to the north.\n");

    add_item(({"ceiling","hole","small hole","roof"}),"A bright beam "+
        "of sunlight streams forth through a small hole in the ceiling. "+
        "It appears to have been cut into the roof so as the sun will "+
        "always shine upon the altar when it is high in the sky above.\n");

    add_item(({"light","sunshine","sunlight","radiance","beam"}),
        "The radiance from the beam of sunlight is almost blinding as "+
        "it reflects off of the silver altar. Heat rises off of the "+
        "altar as the sunlight warms it.\n");

    add_item(({"pure silver altar","silver altar","altar"}),
        "The altar is crafted from pure silver and is polished "+
        "brightly. There are no markings whatsoever on it at all.  "+
        "It is surrounded by some small bushes and bright yellow "+
        "flowers.\n");

    add_item(({"bush","bushes","small bush","small bushes"}),
        "These small bushes are expertly trimmed, and well taken "+
        "care of, most likely by the inhabitants of this temple.\n");

    add_item(({"flower","flowers","yellow flower","yellow flowers",
        "bright flower","bright flowers","bright yellow flower",
        "bright yellow flowers"}),"As if by some sort of magic, "+
        "these flowers are perfect in every way. They are all "+
        "exactly the same height, have the same colour stems, "+
        "and have the same yellow petals.\n");

    add_prop(ROOM_M_NO_ATTACK,1);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);

    add_exit(ELEMENTALIST_TEMPLE+"old_entrance","north",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldpost","southwest",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldboard","southeast",0,1);
}
