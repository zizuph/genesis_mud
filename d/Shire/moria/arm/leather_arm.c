/*
	*Leather bracers for the woodsmen of Archet
	*Altrus, June 2005
*/
inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("bracers");
    add_adj(({"thin","leather"}));
    set_short("thin leather bracers");
    set_pshort("thin leather bracers");
    set_long("These "+short()+" cover the forearms only. They are short and made from thin leather. They probably wouldn't protect you much in a fight.\n");
    
    set_ac(15);
    set_am( ({ -1, 0, 1}) );
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 1500 + random(500));
    add_prop(OBJ_I_VOLUME, 750 + random(100));
}
