/*
** Longsword of Kretan Triterian Commanders
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 11/12/94   Created
** 8/10/95   Metal changed to orichalcum
**
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name(({"longsword","sword"}));
    set_adj(({"charred","orichalcum","kretan"}));
    set_short("charred orichalcum longsword");
    set_long("It is a longsword made of the metal orichalcum, charred "+
             "black with a seven-headed Hydra on the hilt.\n");
 
    set_hit(25); set_pen(23);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME, 1600);
}
