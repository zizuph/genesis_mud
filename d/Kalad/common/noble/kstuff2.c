inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("sacks");
    add_name("flour");
    set_short("pile of flour sacks");
    set_long("Sitting in a corner, you see a pile of flour sacks, filled "+
    "with heavy flour. Some of them are open, and spilling out a little "+
    "bit of flour.\n");
    add_prop(OBJ_I_WEIGHT,190000);
    add_prop(OBJ_I_VOLUME,180000);
    add_prop(OBJ_I_VALUE,0);
}

   
