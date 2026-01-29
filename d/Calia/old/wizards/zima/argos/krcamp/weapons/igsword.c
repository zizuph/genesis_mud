/* Sword of an imperial guard
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 1/30/96    Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("sword");
    set_adj(({"black","tempered","kretan"}));
    set_short("black tempered broadsword");
    set_long("It is a broadsword made of tempered orichalcum and enameled "+
             "black. The hilt is made of silver and engraved with a seven-"+
             "headed hydra on an inescustcheon.\n");
    set_hit(30); set_pen(23);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
