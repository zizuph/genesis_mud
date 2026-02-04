/* A knife. Mortricia 920729 */
inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/d/Terel/common/terel_std_rec.h"

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_short("sharp knife");
    set_pshort("sharp knives");
    set_long("It's a sharp-looking knife.\n");
    set_adj("sharp");
    set_hit(14);
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);
}
