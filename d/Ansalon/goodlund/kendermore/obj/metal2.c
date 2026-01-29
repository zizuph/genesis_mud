/* Piece of metal from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("map");
    add_name("parchment");
    add_name("junk");
    set_adj("old");
    add_adj("tattered");
    set_short("old tattered map");
    set_pshort("old tattered maps");
    set_long("This old tattered map looks like it dates from the Cataclysm!\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

