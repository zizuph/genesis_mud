/* Piece of rock found in Kendermore, Gwyneth, 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("rock");
    add_name("stone");
    add_name("junk");
    set_adj("gray");
    set_short("piece of gray rock");
    set_pshort("pieces of gray rock");
    set_long("This is a plain piece of rock, chipped from a larger piece.\n"); 
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 50);
}

