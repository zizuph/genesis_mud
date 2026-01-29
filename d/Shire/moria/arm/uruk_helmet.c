/*
	*Helm for the hulking uruk-hai in Moria
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
    set_name("helmet");
	add_name("helm");
    add_adj(({"battered","steel"}));
    set_short("battered steel helmet");
    set_pshort("battered steel helmets");
    set_long("Although this helmet is battered and dented in several places, it seems like it just might serve well as head protection.\n");
    set_ac(35 + random(10));
    set_am( ({ 1, 2, -3}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 2000 + random(100));
    add_prop(OBJ_I_VOLUME, 1500 + random(200));
}
