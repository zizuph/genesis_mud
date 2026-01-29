/* chapel/obj/veil.c is cloned by chapel/store.c */
inherit "/std/armour";
 
#include <stdproperties.h>
#include "../chapel.h"
#include <wa_types.h>
 
void
create_armour()
{
    set_name("veil");
    set_short("translucent veil");
    set_long("It's a translucent veil that obscures "+
       "the face of the wearer just slightly.\n");
    set_ac(0);
    set_am(({   0,     0,      0 }));
     set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 288);
}
 
int
wedding_stuff()
{
    return 1;
}
 
mixed
wear_me()
{
    if (!this_player()->query_prop(IS_BRIDE))
     return "You cannot wear the " + short() + " unless "+
       "you are a bride!\n";
    return ::wear_me();
}
 
int
for_bride()
{
    return 1;
}
