/* Sword of an imperial guard (argosian)
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 8/25/96    Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("sword");
    set_adj(({"silver","tempered","argosian"}));
    set_short("tempered argosian broadsword");
    set_long("It is a broadsword made of tempered orichalcum and enameled "+
             "silver. The hilt is made of steel and engraved with a winged "+
             "horse on an inescustcheon.\n");
    set_hit(30); set_pen(23);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
