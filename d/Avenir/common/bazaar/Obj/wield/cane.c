// Cane for Inquisitors
inherit "/d/Avenir/inherit/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_weapon()
{
    set_name("cane");
    add_name(({"club", "weapon" }));
    add_adj(({"steel_tipped", "kesoit"}));
    set_short("steel-tipped kesoit cane");
    set_long("This cane is made from the wood of the kesoit tree "+
        "of Sybarus, which is very strong and so dark it appears "+
        "black. A steel rod runs through the center, ending in a "+
        "sharp tip. The head of the cane is a smooth sphere made "+
        "of solid gold.\n");
    set_hit(17 + random(5));
    set_pen(20 + random(5));

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}

