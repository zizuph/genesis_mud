inherit "/std/armour.c";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

/* Created by Xeros of GondorMud 21 Nov 1993 for use in Genesis */

int added_skill;

void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntletses");
    set_short("pair of brigandine gauntlets");
    set_adj("brigandine");
    add_adj("leather");
    add_adj("black");
    set_long(BSN("A set of black leather gauntlets studded with sharp rivets, "+
        "small barbed hooks and sharp ridges of a dull black metal. Long plates "+
        "of the dull black metal are wedged between the double layers of leather "+
        "giving the gauntlets greater strength and durability."));
    set_ac(25);
    set_am(({1,2,-2}));
    set_at(A_ARMS | A_HANDS);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT,3500);
    add_prop(OBJ_I_VOLUME,275);
    add_prop(OBJ_I_VALUE,300+TP->query_skill(SS_TRADING));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({75,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({                                             
        BSN("The gauntlets provide enhanced protection."),10,
        BSN("They also gift the wearer with a measure of unarmed skill."),50}));
}

public int      
wear(object arm) {
        WRITE("You slide your hands and lower arms into the "+short()+".");
        SAY(" wears the "+short()+".");
    added_skill = (15 + ((TP->query_skill(SS_UNARM_COMBAT)) /5));
    if ((TP->query_skill(SS_UNARM_COMBAT) + added_skill) > 100)
    { 
        added_skill = (100-(TP->query_skill(SS_UNARM_COMBAT)));
    }
    TP->set_skill_extra(SS_UNARM_COMBAT, (TP->query_skill_extra(SS_UNARM_COMBAT) + added_skill));
    return 1; }

int remove(object arm) {
    WRITE("You pull the "+short()+" off your arms.");
    SAY(" removes the "+short()+".");
    TP->set_skill_extra(SS_UNARM_COMBAT,(TP->query_skill_extra(SS_UNARM_COMBAT) - added_skill));
    return 1; }
