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
    set_name("greaves");
    add_adj(({"iron","plate"}));
    set_short("iron plate greaves");
    set_pshort("iron plate greaves");
    set_long("These "+short()+" offer decent protection. The leather straps are old, but supple and well oiled. The iron is rather thick, making for a heavy load.\n");
    
    set_ac(35 + random(5));
    set_am( ({ 1, 0, -1}) );
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 7500 + random(500));
    add_prop(OBJ_I_VOLUME, 2500 + random(500));
}
