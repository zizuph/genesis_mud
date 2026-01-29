/* a common knife
** Date      Coder        Action
** -------   -----------  -----------------------------------------------
** 10/15/96  Zima         Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("knife");
    set_adj(({"common","steel","long"}));
    set_short("common steel knife");
    set_pshort("common steel knives");
    set_long("It is a common steel knife with a long blade.\n");
    set_hit(10);
    set_pen(10);
    set_hands(W_NONE);
    set_wt(W_KNIFE);
    set_dt(W_SLASH);
}
