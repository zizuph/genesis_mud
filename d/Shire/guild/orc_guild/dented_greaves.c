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
    set_name("greaves");
    add_adj(({"dented","steel"}));
    set_short("dented steel greaves");
    set_pshort("dented steel greaves");
    set_long("These "+short()+" are better than nothing, which is not saying much. They are so dented and cracked as to offer no protection in a real battle, and the leather straps are nearly worn through.\n");
    
    set_ac(10);
    set_am( ({ -1, 0, 1}) );
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 1500 + random(500));
    add_prop(OBJ_I_VOLUME, 750 + random(100));
}
