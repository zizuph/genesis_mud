/*
** Broadsword of Argosian Deuterian Commanders
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
    set_name(({"broadsword","sword"}));
    set_adj(({"orichalcum","argosian"}));
    set_short("orichalcum broadsword");
    set_long("It is a broadsword made of the reddish metal orichalcum, "+
             "engraved with a winged horse on the hilt.\n");
 
    set_hit(29); set_pen(26);
 
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1900);
}
