inherit "/std/armour.c";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#define ENHANCE       20 /* the value by which unarmed combat is enhanced */
#define MAX_SKILL     81 /* the max skill someone can have and still benefit */

/* Created by Xeros of GondorMud 21 Nov 1993 for use in Genesis */

static int   addunarmed = 0; /* did I add the skill_extra? 0=no */

void
create_armour()
{
    set_name("gauntlets");
    set_name("gauntletses");
    set_short("studded leather gauntlets");
    set_adj("studded");
    add_adj("leather");
    set_long("A set of black leather gauntlets, covering both hands and " +
        "a good part of the arms. They are studded with sharp rivets, "+
        "small barbed hooks and sharp ridges of a dull black metal.\n");
    set_ac(19);
    set_am(({0,1,-1}));
    set_at(A_ARMS | A_HANDS);
    set_af(TO);

    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(19, A_HANDS));
    add_prop(OBJ_I_VOLUME,275);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({75,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({                                             
        BSN("The gauntlets provide enhanced protection."),10,
        BSN("They also gift the wearer with a measure of unarmed skill."),50}));
}

public int      
wear(object arm) {
    int     iarmed = (TP->query_skill(SS_UNARM_COMBAT) < MAX_SKILL);

    if(!iarmed) {
        WRITE("You slide the gauntlets onto your hands and lower arms.");
        SAY(" wears the "+short()+"."); }
    else {
        if(iarmed) {
            TP->set_skill_extra(SS_UNARM_COMBAT,TP->query_skill_extra(SS_UNARM_COMBAT) + ENHANCE);
            addunarmed = 1; }
        WRITE("You slide your hands and lower arms into the "+short()+".");
        SAY(" wears the "+short()+".");
    return 1;
    }
    return 1;
}

int remove(object arm) {
if(addunarmed) {
    TP->set_skill_extra(SS_UNARM_COMBAT,TP->query_skill_extra(SS_UNARM_COMBAT) - ENHANCE);
    addunarmed = 0; }
    WRITE("You pull the "+short()+" off your arms.");
    SAY(" removes the "+short()+".");
    return 1;
WRITE("You remove the "+short()+".");
SAY(" removes the "+short()+".");
return 1;
}
