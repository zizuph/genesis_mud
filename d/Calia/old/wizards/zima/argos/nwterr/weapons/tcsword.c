/*
** Longsword of Argosian Triterian Commanders
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 8/24/94   Created
** 8/10/95   Metal changed to orichalcum
**
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name(({"longsword","sword"}));
    set_adj(({"argosian","orichalcum"}));
    set_short("orichalcum longsword");
    set_long("Is is a longsword made of the reddish metal orichalcum, "+
             "engraved with a winged horse on the hilt.\n");
 
    set_hit(25); set_pen(23);
 
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME, 1600);
}
