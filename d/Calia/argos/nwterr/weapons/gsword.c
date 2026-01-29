/*
** Sword used by Argosian guards/soldiers
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 8/24/94   Created
** 8/10/95   Metal changed to orichalcum
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
   set_name("sword");
   set_adj(({"orichalcum","argosian"}));
   set_short("orichalcum sword");
   set_long("It is a plain sword made of the reddish metal orichalcum "+
            "with a winged horse engraved on the hilt.\n");
 
   set_hit(20);
   set_pen(20);
   set_hands(W_NONE);
   set_wt(W_SWORD);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 1500);
}
