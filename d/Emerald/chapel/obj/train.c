/* chapel/obj/train.c is cloned by chapel/store.c */
inherit "/std/armour";
 
#include "../chapel.h"
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name("train");
    set_short("long, white silk train");
    set_long("It's a long, white silk train that magically "+
       "stays off the ground.\n");
    set_ac(0);
    set_am(({   0,     0,      0 }));
     set_at(A_TORSO);
    add_prop(OBJ_I_VALUE, 864);
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
