/* Vladimir 8-09-94 */

#pragma strict_types

inherit "std/weapon";

#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
    set_name("knife");
    set_short("jagged sharp knife");
    set_pshort("jagged sharp knives");
    set_long("A medium sized knife with large teeth on one edge and a sharp "+
             "blade on the other.\n");
    set_adj(({"jagged", "sharp"}));
 
    set_hit(15);
    set_pen(10);

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);
}
