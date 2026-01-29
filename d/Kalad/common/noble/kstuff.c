inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("barrels");
    add_name("wooden");
    set_short("couple of wooden barrels");
    set_long("Two wooden barrels filled with what appears to be sugar "+
    "and water. They are heavy looking.\n");
    add_prop(OBJ_I_WEIGHT,190000);
    add_prop(OBJ_I_VOLUME,180000);
    add_prop(OBJ_I_VALUE,0);
}

   
