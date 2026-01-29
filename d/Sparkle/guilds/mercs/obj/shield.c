inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "../merc.h"

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");
    set_adj("mercenary");
    add_adj(({"black","steel"}));
    set_short("black steel shield");
    set_pshort("black steel shields");
    set_ac(27);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("A standard small shield, forged of blackened steel. The "+
	"shield has a dragon etched in the face.\n");
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(27));
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}
