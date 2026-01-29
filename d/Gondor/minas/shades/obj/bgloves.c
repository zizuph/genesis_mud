inherit "/std/armour";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

int added_skill;

void

create_armour() {
  set_name("gloves");
  add_name("pair");
  set_pname("gloves");
  set_adj("black");
  set_adj("leather");
  set_short("pair of black leather gloves");
  set_long("This pair of gloves is made of soft black leather.\n");
  set_af(TO);
  set_ac(5);
  set_at(A_HANDS);
  set_am(({0,0,0}));
  add_prop(OBJ_I_WEIGHT,400);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(10)+5);
  add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
  add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
  add_prop(OBJ_S_WIZINFO,"The gloves enhance a wearers climb skill, 10 + " +
             "1/5 the wearers current skill level. The gloves are " +
             "used by Talin, a Shade NPC. /d/Gondor/minas/shade/talin.c " +
             " no others are in the game.\n");
  add_prop(MAGIC_AM_ID_INFO,({
      BSN("The gloves provide the wearer with a measure of climb skill."),10}));
}

public int
wear(object arm) {

    TP->catch_msg("Your hands gently slide into the "+short()+".\n");
    SAY(" wears the "+short()+".");

    added_skill = (10 + ((TP->query_skill(SS_CLIMB))/5));
    if ((TP->query_skill(SS_CLIMB) + added_skill) > 100)
    {
        added_skill = (100-(TP->query_skill(SS_CLIMB)));
    }
    TP->set_skill_extra(SS_CLIMB, (TP->query_skill_extra(SS_CLIMB) + added_skill));
    return 1; }

int remove(object arm) {

  object wearer;
  wearer = query_worn();
    wearer->catch_msg("You slide your hands gently from the "+short()+".\n");
    say(QCTNAME(wearer)+" slides the "+short()+" off.\n");
    wearer->set_skill_extra(SS_CLIMB, (wearer->query_skill_extra(SS_CLIMB) - added_skill));
    return 1; }

