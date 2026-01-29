inherit "/std/armour.c";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
                   
int added_skill1,
    added_skill2,
    added_skill3;

void
create_armour() {
    set_name("boots");
    add_name("boots of the forester");
    set_pname("pairs");
    set_adj("rugged");
    add_adj("leather");
    set_short("pair of rugged leather boots");
    set_pshort("pairs of rugged leather boots");
    set_long(BSN("Constructed of a tough, black leather spotted with various "+
        "shades of brown, these boots look like the perfect item for someone "+
        "who spends a lot of time out in nature. Hundreds of tiny, yet strong "+ 
        "metal rings are sown onto the leather in such a way as to be completely "+
        "silent when shaken or worn."));
    set_ac(19);
    set_am(({-3,2,1}));
    set_at(A_LEGS | A_ANKLES | A_FEET);
    set_af(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(19));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(19, A_FEET));
    add_prop(OBJ_I_VOLUME,350);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({
        BSN("These "+short()+" radiate a strong aura of enchantment."),1,
        BSN("They enhance the wearer's ability to survive outdoors."),35,
        BSN("They enhance location sense, acrobatic efforts, and climbing."),70}));
    add_prop(OBJ_S_WIZINFO,"The boots enhance the wearers climbing " +
             "skill by 15 + 1/5 of the wearers current skill. They also " +
             "enhance location sense 15 + 1/4 the wearers current " +
              "skill. Last they enhance the wearers acrobat skill " +
             "20 + 1/4 the wearers current skill. NOT IN GAME YET!\n");
}

public int
wear(object arm) {
    added_skill1 = (20 +((TP->query_skill(SS_ACROBAT))/4));
    added_skill2 = (15 +((TP->query_skill(SS_CLIMB))/5));
    added_skill3 = (15 +((TP->query_skill(SS_LOC_SENSE))/4));
    if((TP->query_skill(SS_ACROBAT) + added_skill1) > 100)
    { added_skill1 = (100-(TP->query_skill(SS_ACROBAT))); }
    if((TP->query_skill(SS_CLIMB) + added_skill2) > 100)
    { added_skill2 = (100-(TP->query_skill(SS_CLIMB))); }
    if((TP->query_skill(SS_LOC_SENSE) + added_skill3) > 100)
    { added_skill3 = (100-(TP->query_skill(SS_LOC_SENSE))); }
    TP->set_skill_extra(SS_ACROBAT,(TP->query_skill_extra(SS_ACROBAT)+added_skill1));
    TP->set_skill_extra(SS_CLIMB,  (TP->query_skill_extra(SS_CLIMB) + added_skill2));
    TP->set_skill_extra(SS_LOC_SENSE,(TP->query_skill_extra(SS_LOC_SENSE)+added_skill3));
    WRITE("You pull the "+short()+" up onto your feet and legs.");
    SAY(" wears the "+short()+".");
    return 1; }

public int
remove(object arm) {
    TP->set_skill_extra(SS_LOC_SENSE,(TP->query_skill_extra(SS_LOC_SENSE)-added_skill3));
    TP->set_skill_extra(SS_ACROBAT,  (TP->query_skill_extra(SS_ACROBAT) - added_skill1));
    TP->set_skill_extra(SS_CLIMB,    (TP->query_skill_extra(SS_CLIMB)  -  added_skill2));
    WRITE("You tug the "+short()+" off your legs and feet.");
    SAY(" removes the "+short()+".");
    return 1; }
