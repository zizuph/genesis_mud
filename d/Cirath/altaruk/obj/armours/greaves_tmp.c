inherit "std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>
 
void
create_armour()
{
    set_name("greaves");
    set_adj("scaled");
    add_adj("leather");
    set_short("pair of scaled leather greaves");
    set_pshort("pairs of scaled leather greaves");
    set_long("These leather greaves are fidded with scales" +
        " from an erdlu for better protection.\n");
 
    set_ac(30);
    set_at(A_LEGS);
    set_am(({ 2, 2, -4}));
 
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2500);
}
