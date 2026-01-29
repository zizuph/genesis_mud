inherit "/std/object";
#include "/d/Raumdor/defs.h"
/* Pile of bones, Sarr
 * 2017-05-24 Malus: Added name "pile", fixed plural
 */


void
create_object()
{
    set_name("bones");
    add_name("pile");
    add_pname("piles");
    set_short("pile of bones");
    set_pshort("piles of bones");
    set_long("These are the remains of a human skeleton.\n");
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_VALUE,0);
    set_alarm(80.0,0.0,"decay");
}

decay()
{
   tell_room(E(TO),"The bones crumble to dust.\n");
   TO -> remove_object();
}

