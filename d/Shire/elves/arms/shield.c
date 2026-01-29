

#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"

int ac = 30+random(9);

void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj("tower");
    add_adj("large");
    set_short("large tower shield");
    set_pshort("large tower shields");
    set_ac(ac);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This is a " + short() + ". It was forged of high-steel " +
        "by the elves of Middle-earth. The shield is rectangular in shape " +
        "and fits over your arm. It is curves inward and protects most " +
        "of your body.\n");

	add_prop(OBJ_I_WEIGHT, ac*142*(120+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*142*(90+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (110+random(21)) / 100);
       
}

int *
query_shield_slots()
{
	return (::query_shield_slots() + ({ A_BODY }) );
}