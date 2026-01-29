inherit "/std/weapon";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_weapon()
{
    set_name ("mace");
    set_pname("maces");
    set_adj  ("obsidian-spiked");
    set_short("obsidian-spiked mace");
    set_pshort("obsidian-spiked maces");
    set_long ("A mace spiked with obsidian shards." +
        " It looks like a mean weapon.\n");

    set_hit(35);
    set_pen(35);
    likely_dull=5;
    likely_corr=-1;
    likely_break=10;

    set_wt(W_2H_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,2000);
}
