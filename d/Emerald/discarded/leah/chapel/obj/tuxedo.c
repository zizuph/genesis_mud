/* chapel/obj/tuxedo.c is cloned by chapel/store.c */
inherit "/std/armour";
 
#include <stdproperties.h>
#include "../chapel.h"
#include <wa_types.h>
 
void
create_armour()
{
    set_name("tuxedo");
    set_short("black tuxedo");
    set_long("This is a black tuxedo, impeccably "+
       "tailored.\n");
    set_adj("black");
 
    set_default_armour(0, A_BODY,  0,  0);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME,  680);
    add_prop(OBJ_I_VALUE, 1728);
   }
 
int
wedding_stuff()
{
    return 1;
}
 
mixed
wear_me()
{
    if (!this_player()->query_prop(IS_GROOM) &&
     !this_object()->query_prop(IS_DRIVER))
     return "You cannot wear the " + short() + " unless "+
       "you are a groom!\n";
    return ::wear_me();
}
 
int
for_groom()
{
    return 1;
}
