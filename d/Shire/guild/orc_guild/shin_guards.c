/*
	*Cruddy armour for the orc race guild npc guard
	*Altrus, May 2005
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
    add_adj(({"leather","shin"}));
    set_short("leather shin guards");
    set_pshort("leather shin guards");
    set_long("These "+short()+" offer minimal protection. They have obviously been ill-treated.\n");
    
    set_ac(15);
    set_am( ({ 1, 0, -1}) );
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 1500 + random(500));
    add_prop(OBJ_I_VOLUME, 750 + random(100));
}
