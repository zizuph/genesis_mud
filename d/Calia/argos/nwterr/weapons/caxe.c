/* a common axe
** Date      Coder        Action
** -------   -----------  -----------------------------------------------
** 10/15/96  Zima         Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("axe");
    set_adj("iron");
    set_short("iron axe");
    set_long("It is a common iron axe.\n");
    set_hit(8); set_pen(8);
    set_hands(W_NONE);
    set_wt(W_AXE);
    set_dt(W_BLUDGEON);
}
