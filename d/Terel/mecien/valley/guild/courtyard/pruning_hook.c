/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* A knife. Mortricia 920729 */
inherit "/std/weapon";
#include "/sys/wa_types.h"

#define BSN(xx)     (break_string(xx, 72) + "\n")

void
create_weapon()
{
    set_name("pruning hook");
    add_name("hook");
    set_adj("silverish");
    set_long(BSN(
	"It is a long-handled, hooked cutting tool used for " +
	"pruning. It is made of silver and it looks sharp."
    ));
    set_hit(10);
    set_pen(30);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}
