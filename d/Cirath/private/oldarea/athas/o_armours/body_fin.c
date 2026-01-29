/* body_lth: Slightly better armour then burlap, but what isn't? */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("finery");
    set_short("pile of tasteless finery");
    add_name("pile");
    set_pshort("piles of tasteless finery");
    set_long("This gaudy mess consists of a chaotic collection of the "+
             "latest Athasian fashions and the noble's own uniquely "+
             "alien tastes. Useless for little else then kindling, it "+
             "no doubt brought a great deal of respect to its wearers, "+
             "from other nobles who appreciate such waste.\n");
    set_adj("tasteless");

    set_ac(13);
    set_am(({ -1, 0, 1}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 2750);
    add_prop(OBJ_I_VOLUME, 7500);
}
