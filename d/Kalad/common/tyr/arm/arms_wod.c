/* arms_wod: A pair of wooden shoulder guards */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("bands");
    set_short("pair of wooden arm bands");
    set_pshort("pairs of wooden arm bands");
    set_long("Formed from hard circles of wood, these arm guard make up "+
             "for in protection what they loose in comfort.\n");
    set_adj("wooden");
    add_adj("arm");

    set_ac(20);
    set_am(({ 2, -3, 1}));
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 2700);
    add_prop(OBJ_I_VOLUME, 1350);
}
