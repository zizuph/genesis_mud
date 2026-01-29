/* Stone sword of a satyr
**
** HISTORY
** Date      Action
** --------- -----------------------------------
** 3/21/95   Created (Zima)
**
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("sword");
    set_adj(({"crude","stone"}));
    set_short("crude stone sword");
    set_long("It is a crude short sword chiseled from stone.\n");
 
    set_hit(3); set_pen(3);
 
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
 
    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME, 1600);
}
