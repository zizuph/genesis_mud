#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>


int added_skill;

public void
create_terel_armour()
{
  set_name("bracers");
  set_adj("black");
  set_adj("steel");
  set_short("pair of black steel bracers");
  set_long("These are a pair of black steel bracers made of black cold steel.\n");
  set_af(TO);
  set_ac(40);
  set_at(A_ARMS);
  set_am(({0,0,0}));
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(10)+5);
  add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
  add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
  add_prop(OBJ_S_WIZINFO,
             "The bracers enhance a wearers two handed skill, 10 + " +
             "1/10 the wearers current dex stat. The bracers are " +
              "are for swordsman, they require 75+ sword skill. The bracers "+
             "are found after killing the giant troll," +
             " no others are in the game.\n");
  add_prop(MAGIC_AM_ID_INFO,({
       "The bracers provide a swordsman with a measure of two handed skill.",70}));
}

public mixed
wear_terel_armour(object obj)
{
    if(TP->query_race_name() == "dwarf")
        return -1;
    if(TP->query_alignment() < 200)
        return "The "+short()+" resists you.\n";
    if(TP->query_skill(SS_WEP_SWORD) < 76)
        return 0;

    added_skill = (10 + ((TP->query_stat(SS_DEX))/10));
    if(added_skill > 25)
        added_skill = 25;
    if ((TP->query_skill(SS_2H_COMBAT) + added_skill) > 100)
    {
        added_skill = (100-(TP->query_skill(SS_2H_COMBAT)));
    }
    TP->set_skill_extra(SS_2H_COMBAT, (TP->query_skill_extra(SS_2H_COMBAT) +
added_skill));
    return 0; 
}

int remove(object arm) {

    object wearer;
    wearer = query_worn();

    if(wearer->query_skill(SS_WEP_SWORD) < 75)
        return 0;

    wearer->set_skill_extra(SS_2H_COMBAT, 
            (wearer->query_skill_extra(SS_2H_COMBAT) - added_skill));
    return 0; 
}
