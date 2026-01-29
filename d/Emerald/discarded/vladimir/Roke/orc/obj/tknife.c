/* Vladimir 8-09-94 */
inherit "std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_weapon()
{
 set_name("knife");
 set_long("A medium sized knife with large teeth on one edge and a sharp "+
          "blade on the other.\n");
 set_adj(({"jagged", "sharp"}));
 
 set_hit(15);
 set_pen(10);

 set_wt(W_KNIFE);
 set_dt(W_SLASH | W_IMPALE);

 set_hands(W_ANYH);
}
