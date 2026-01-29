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
    set_name("helm");
    add_adj(({"blackened","steel"}));
    set_short("blackened steel helm");
    set_pshort("blackened steel helms");
    set_long("This steel helm seems well made. It's surface is blackened. It has several dents in it, but otherwise seems perfectly usable.\n");
    set_ac(30 + random(10));
    set_am( ({ 1, 1, -2}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 2000 + random(100));
    add_prop(OBJ_I_VOLUME, 1500 + random(200));
}
