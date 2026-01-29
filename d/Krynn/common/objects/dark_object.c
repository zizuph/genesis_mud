
/* This is the magic darkness created by the dragon
 * made by percy.
 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

void
create_object()
{
    set_name(({"lightobj", "_krynn_magic_darkness_"}));
    set_adj("magic");
    set_no_show();
    add_prop(OBJ_I_LIGHT, -5);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}
void 
set_duration(int dur) 
{ 
    set_alarm(itof(dur),0.0,"remove_obj"); 
}

void 
remove_obj() 
{
    tell_room(E(E(TO)), 
	      "The darkness fades away...\n");
    remove_object();
}



