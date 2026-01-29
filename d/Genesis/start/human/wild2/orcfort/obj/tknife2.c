/* Vladimir 8-09-94 */

#pragma strict_types

inherit "std/weapon";

#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
    set_name("dirk");
    set_short("small nicked dirk");
    set_long("A small nicked dirk.\n");
    set_adj(({"small", "nicked"}));
 
    set_hit(5);
    set_pen(5);

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);
}
