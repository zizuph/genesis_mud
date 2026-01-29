inherit "/std/object";
#include "/d/Raumdor/defs.h"
/* Pile of bones, Sarr */

void
create_object()
{
    set_name("orb");
    add_adj("purple");
    set_short("purple orb");
    set_pshort("purple orbs");
    set_long("This purple orb is made of some unknown "
	+"purple steel-like material. It gives away a dim purple glow "
    +"in addition to feeling cold as ice.\n");
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1300);
    add_prop(OBJ_I_VALUE,1382);
}


