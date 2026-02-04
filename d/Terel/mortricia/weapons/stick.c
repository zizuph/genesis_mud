/* A walking stick, not much of a weapon */
inherit "/std/weapon";
#include "/sys/wa_types.h"

#define BSN(xx)        break_string(xx + "\n", 70)

void
create_weapon()
{
    set_name("stick");
    set_short("walking stick");
    set_long(BSN(
	"It's a walking stick made of wood. " +
	"Not much of a weapon really."
    ));
    set_adj(({"walking", "wooden"}));
    set_hit(3);
    set_pen(3);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hands(W_BOTH);
}
