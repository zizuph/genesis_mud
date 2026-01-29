/* Piece of metal from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("metal");
    add_name("junk");
    add_name("piece");
    set_adj("shiny");
    set_short("shiny piece of metal");
    set_pshort("shiny pieces of metal");
    set_long("You have no idea where this comes from. It is twisted into " + 
        "a complex pattern.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

