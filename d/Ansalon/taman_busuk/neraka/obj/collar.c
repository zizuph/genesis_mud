inherit "/std/armour";
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("collar");
    add_adj(({"spiked","black"}));
    set_short("spiked black collar");
    set_long("This is a leather collar coloured black and studded with "+
    "steel spikes.\n");
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VALUE,10);
    add_prop(OBJ_I_VOLUME,60);
    set_ac(1);
    set_at(A_NECK);
}

