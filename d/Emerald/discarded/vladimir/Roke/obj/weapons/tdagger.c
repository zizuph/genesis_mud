/* Vladimir 8-09-94 */
inherit "std/weapon";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_weapon()
{
 set_name("dagger");
 set_long("This dagger is long and viscious. The blade "+
          "is midnight black. The hilt is made from soft "+
          "leather that is died green wrapped around metal. "+
          "On the very bottom of this weapon is a symbol of "+
          "two crossed axes over a map of the world.\n");
 set_adj(({"viscious", "midnight-black"}));
 
 set_hit(32);
 set_pen(35);

 set_wt(W_KNIFE);
 set_dt(W_SLASH | W_IMPALE);
 set_hands(W_ANYH);
}
