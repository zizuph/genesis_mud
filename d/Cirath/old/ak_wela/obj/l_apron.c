inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("apron");
    set_short("heavy hide fishing apron.");
    set_long("A rather cumbersome apron made of heavy hide. The many "+
             "smelly fish scales on it suggests it was once used "+
             "by a fisherman.\n");
    set_adj("hide");
    add_adj("heavy");

    set_ac(25);
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 5000);
}
