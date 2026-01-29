/*
	*Greaves for the hulking uruk-hai in Moria
	*Altrus, July 2005
*/
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("guards");
    add_adj(({"steel","leg"}));
    set_short("steel leg guards");
    set_pshort("steel leg guards");
    set_long("These "+short()+" offer the wearer some protection. The curved steel plate covers the lower leg rather well, then joints at the knee, with another steel plate covering midway up the thigh.\n");
    
    set_ac(30 + random(5));
    set_am( ({ 1, 0, -1}) );
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 7500 + random(500));
    add_prop(OBJ_I_VOLUME, 2500 + random(500));
}
