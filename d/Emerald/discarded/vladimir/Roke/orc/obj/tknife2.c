/* Vladimir 8-09-94 */
inherit "std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_weapon()
{
 set_name("knife");
 set_long("A small knicked dirk");
 set_adj(({"small", "knicked"}));
 
 set_hit(5);
set_pen(5);

 set_wt(W_KNIFE);
 set_dt(W_SLASH | W_IMPALE);

 set_hands(W_ANYH);
}
