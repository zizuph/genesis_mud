/* Piece of metal from Kendermore, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("pipe");
    set_adj("meerschaum");
    add_adj("carved");
    set_short("carved meerschaum pipe");
    set_pshort("carved meerschaum pipes");
    set_long("This pipe looks damaged, and unable to smoke. However, it is " + 
        "still a beautiful work of art, with an amber bit. The bowl has a " + 
        "very detailed carving of a dwarven face.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 30);
}

