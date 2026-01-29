/*
 * Large common shield for large trolls
 * - Finwe, October 2001
 */
inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
mixed arm_slots;

int ac=30+random(5);
void
create_armour()
{
    set_name("shield");
    add_name("large_troll_shield");
    set_adj(({"large","steel"}));
    set_short("large steel shield");
    set_pshort("large steel shields");
    set_long("This "+short()+" is large and black. It is " +
        "oval shaped with dried blood on its surface. It looks " +
        "like it can protect most of the body.\n");
    add_item(({"blood", "dried blood"}),
        "The blood is black, and dried on the surface of the " +
        "shield. It runs down the front of the shield.\n");
    arm_slots = ({});

    set_ac(ac);
    set_am( ({-2, 1, 1 }) );
    set_likely_break(5);
    set_af(this_object());
    set_at(A_SHIELD);
    set_keep(1);

	add_prop(OBJ_I_WEIGHT, ac*100*(175+random(21)) / 100);
	add_prop(OBJ_I_VOLUME, ac*175*(125+random(21)) / 100);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac) * (150+random(25)) / 100);

  	arm_slots = ({ A_BODY, A_L_ARM, A_R_ARM, A_LEGS });
	set_shield_slot(arm_slots);
}
