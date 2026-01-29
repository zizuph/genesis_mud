/* body_chn: A breastplate made from the carapace of some insect */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("breastplate");
    set_short("chitin breastplate");
    set_long("It's frightening to imagine the size of an insect whose "+
             "carapace is big enough to provide a plate that can cover "+
             "an entire humanoid torso. Still more frightening though is "+
             "the thought of a hunter that could bring one down....\n");
    set_adj("chitin");

    set_ac(40);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 11250);
    add_prop(OBJ_I_VOLUME, 5750);
}
