
/* st_club.c
 * Club (Beer mug) for the SToryteller hobbit 
 * In the pub
 * GAmwich
 * Created 26 February 1995 by Farlong 
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("mug");
    set_adj("beer");
    add_adj("heavy");
    set_short("heavy beer mug");
    set_long("This heavy beer mug makes a useable club.\n");

    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);
    set_pen(2);
    set_hit(12);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE,20);


}
