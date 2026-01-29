/*
 *  An enchanted ring of swimming that is sometimes worn by 
 *  /d/Krynn/turbidus_ocean/living/ergothian_captain.c
 *
 *  Arman, January 2021.
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"

inherit "/lib/keep";

#define ARMOUR_CLASS 1

void
create_armour()
{
    set_name("ring");
    set_pname("rings");
    set_adj("blue-gemmed");
    add_adj("blue");
    add_adj("gemmed");
    set_short("blue-gemmed ring");
    set_pshort("blue-gemmed rings");
    set_long("This is a ring of gold, with small blue sapphires embedded " +
        "along its band.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This is an enchanted ring, and provides the wearer some " +
        "additional proficiency at swimming.\n",50}));
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));

    set_ac(ARMOUR_CLASS);
    set_at(A_FINGERS);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS) + 3000);
}

void
wear_message(object wearer)
{
    wearer->catch_msg("The " +short()+ " pulses gently as you " +
        "wear it, evoking a scent of salty sea air.\n");
    return;
}


mixed
wear(object what)
{
    TP->set_skill_extra(SS_SWIM, (TP->query_skill_extra(SS_SWIM) + 
        25));  /* Swimming +25 to skill */
    
    set_alarm(0.5, 0.0, &wear_message(TP));

    return 0;
}

mixed
remove(object what)
{
    TP->set_skill_extra(SS_SWIM, 
        (TP->query_skill_extra(SS_SWIM) - 25));

    return 0;
}
