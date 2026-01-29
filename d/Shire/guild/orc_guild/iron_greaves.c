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
    add_adj(({"leather-lined","iron"}));
    set_short("leather-lined iron greaves");
    set_pshort("leather-lined iron greaves");
    set_long("These "+short()+" will probably protect you from some blows, but don't count on much, as they are in terrible condition.\n");
    
    set_ac(20);
    set_am( ({ 0, 0, 0}) );
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 1500 + random(500));
    add_prop(OBJ_I_VOLUME, 750 + random(100));
}
