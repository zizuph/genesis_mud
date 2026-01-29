/* A common shortsword
** Date       Coder     Action
** ---------  --------  ----------------------------------
** 10/15/96   Zima      Created
*/
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void create_weapon() {
    set_name("shortsword");
    set_adj(({"common","steel"}));
    set_short("steel shortsword");
    set_long("It is a common steel shortsword, undecorated but useful.\n");
    set_hit(15); set_pen(17);
    set_hands(W_NONE);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
