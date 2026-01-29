/* Piece of shell for Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("shell");
    add_name("junk");
    set_adj("white");
    add_adj("piece");
    set_short("piece of white shell");
    set_long("This is a small, but beautiful piece of mother-of-pearl.\n"); 
    add_prop(OBJ_I_VALUE, 90);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

