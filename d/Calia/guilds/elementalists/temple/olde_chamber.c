

 /* East Chamber of the Worshippers Temple
  * by Jaacar
  * July 22nd, 1996
  *
  * Modified on Feb 28, 2015 to remove ability to construct tools here.
  * One should use the new Elemental Temple - Petros
  */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include "defs.h"

void
create_room()
{
    set_short("A small chamber");
    set_long("This small chamber has a wooden table with a "+
        "bench in front of it. It appears at one time the "+
        "table maybe have had several tools on it but now "+
        "there is nothing but dust. In the corner of the "+
        "chamber you see an old small forge, and an empty "+
        "pool that looks like it was once filled with water. "+
        "The adobe walls are covered by a roof of grass and "+
        "straw, which have become blackened near the area "+
        "surrounding the forge. The ground is a uniformly green, "+
        "evenly cut grass. The only exit is back to the west.\n");

    add_item(({"wooden table","table"}),"The table is not very "+
        "large, but roomy enough for one person to sit at.\n");

    add_item(({"wall","walls"}),"The adobe walls are made from "+
        "the same stones you have seen throughout the temple. "+
        "They are blackened near the area surrounding the forge.\n");
    add_item("bench","The bench is large enough for one person "+
        "to sit on, and made of the same wood as the table. It "+
        "appears to be well used.\n");

    add_item(({"forge","small forge","old forge","old small forge"}),
        "The forge is simply a small stone pit with an area in "+
        "the middle that could contain a flame.\n");

    add_item(({"pool","empty pool"}),"The pool is constructed from small "+
        "stones placed in a circular form. You can tell it used to "+
        "contain water by the distinct line inside of it.\n");

    add_item("grass","Every blade of grass here is the same shade "+
        "of green, and exactly the same height.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(ELEMENTALIST_TEMPLE+"old_entrance","west",0,1);
}
