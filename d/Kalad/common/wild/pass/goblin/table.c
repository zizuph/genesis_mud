inherit "/std/object";
#include "/d/Kalad/defs.h";
/* Sarr */

void
create_object()
{
    set_name("table");
    add_adj("wooden");
    set_long("A small wooden table with two chairs set beside it. "+
    "There are some mugs of beer on it, along with some dice. This "+
    "must be how the guards entertain themselves while on guard "+
    "duty.\n");
    add_prop(OBJ_M_NO_GET,"You don't want to do that.\n");
}

