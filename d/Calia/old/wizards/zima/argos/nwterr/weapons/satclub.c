/* Club of a satyr
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
    set_name("club");
    set_adj(({"heavy","wood"}));
    set_short("heavy wood club");
    set_long("It is a heavy wood club, not much more than a short log.\n");
    set_hit(3); set_pen(3);
    set_hands(W_NONE);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1400);
}
