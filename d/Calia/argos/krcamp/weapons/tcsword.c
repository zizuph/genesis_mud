/*
** Sword of a Kretan Triterian Commander
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 1/25/96    Created
** 8/22/21    Changed hit/pen to 35/35 - Greneth
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("sword");
    set_adj(({"black","orichalcum","kretan","regular"}));
    set_short("black orichalcum sword");
    set_long("It is a regular sword made of orichalcum, enameled black and "+
             "embellished with a seven-headed Hydra on the hilt.\n");
 
    set_hit(35); set_pen(35);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
