/* brut_axe.c: The axe of Brutus. */
#pragma save_binary

inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "defs.h"

create_weapon()
{
    set_name("axe");
    set_adj("mighty");
    set_short("mighty axe");
    set_long("A mighty axe, deadly in the hand of a master.\n");

    set_hit(35);
    set_pen(39);

    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
}
