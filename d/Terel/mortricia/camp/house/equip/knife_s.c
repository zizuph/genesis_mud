/* A knife. Mortricia 920729 */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("plain knife");
    set_pshort("plain knives");
    set_long("It's a plain-looking knife.\n");
    set_adj("plain");
    set_hit(12);
    set_pen(12);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}
