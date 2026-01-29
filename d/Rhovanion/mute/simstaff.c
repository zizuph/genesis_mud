inherit "/std/weapon";
#include "/sys/wa_types.h"
void
create_weapon()
{
set_name("staff");
set_short("twisted staff");
set_long("How dare you kill my simulacrum and loot his body!");
add_adj("twisted");
set_hit(20);
set_pen(20);
set_wt(W_CLUB);
set_dt(W_BLUDGEON);
set_hands(W_ANYH);
}
