inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "../merc.h"

public void
create_armour()
{
    set_name("gloves");
    set_pname("pairs");
    add_name(({"pair", "armour"}));
    add_pname("armours");
    set_adj("mercenary");
    add_adj(({"leather","black"}));
    set_short("pair of black leather gloves");
    set_pshort("pairs of black leather gloves");
    set_ac(5);
    set_at(A_HANDS);
    set_am( ({0,0,0}) );
    set_long("The black leather gloves are standard gloves. This "+
	"pair has a tiny dragon pressed into the leather on the "+
	"top of the right hand glove.\n");
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}
