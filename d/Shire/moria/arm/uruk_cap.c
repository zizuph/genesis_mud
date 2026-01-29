/*
	*Cap for the hulking uruk-hai in Moria
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
    set_name("cap");
    add_name("helm");
    add_adj(({"pointed","iron"}));
    set_short("pointed iron cap");
    set_pshort("pointed iron caps");
    set_long("This is a rather crudely made iron cap. It is pitted and corroded all over the surface, and even has rust gathering on the edges. At least it is not completely broken.\n");
    set_ac(25 + random(5));
    set_am( ({ 0, 0, 0}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 1200 + random(250));
    add_prop(OBJ_I_VOLUME, 1000 + random(250));
}
