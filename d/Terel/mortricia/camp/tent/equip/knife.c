/* A knife. Mortricia 920729 */
inherit "/std/weapon";
#include "/sys/wa_types.h"

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("simple knife");
    set_pshort("simple knives");
    set_long("It's a simple-looking knife.\n");
    set_adj("simple");
    set_hit(8);
    set_pen(8);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}
