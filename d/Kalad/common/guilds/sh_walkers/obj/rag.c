    inherit "/std/object";
#include "/d/Kalad/defs.h"
 /* Sarr */

void
create_object()
{
    set_name("rag");
    set_adj("dirty");
    add_adj("old");
    set_short("dirty old rag");
    set_long("This is a piece of old cloth. It is dirty and "+
    "looks worthless.\n");
    add_name("_kalad_rag");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,8);
}
