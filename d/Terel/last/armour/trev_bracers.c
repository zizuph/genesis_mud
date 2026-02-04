/*
 * 05/2008 - removed quest bit checks so all players get these bonuses. 
 * (Novo)
 *
 * Lucius, Jan 2018: Code cleanup.
 */
#pragma strict_types
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

public int added_skill;


public void
create_terel_armour()
{
    set_name("bracers");
    set_adj("black");
    set_adj("steel");
    set_short("pair of black steel bracers");
    set_long("These are black steel bracers made of black cold steel. "+
                   "On the underside of both arms is an insignia of a black hand.\n");
    set_af(TO);
    set_ac(45);
    set_at(A_ARMS);
    set_am(({0,0,0}));
    set_armour_size(ANY_SIZE);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(10)+5);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,
               "The bracers provide excellent protection for the arms and "+
               "will raise a wearers sneak and hide to "+
               "a max of 10 based on the players dex.\n");
    add_prop(MAGIC_AM_ID_INFO,({
         "The bracers provide excellent protection.",50, 
         "The bracers will improve some thieving abilities of the wearer.",70}));
}

public mixed
wear_terel_armour(object obj)
{
   // Check the players dex and then add the extra skills in wielding.
    added_skill = ((10 + TP->query_stat(SS_DEX))/10);

    if (added_skill > 10)
        added_skill = 10;

    if ((TP->query_skill(SS_HIDE) + added_skill) > 100)
        added_skill = (100-(TP->query_skill(SS_HIDE)));

    if ((TP->query_skill(SS_SNEAK) + added_skill) > 100)
        added_skill = (100-(TP->query_skill(SS_SNEAK)));

    TP->set_skill_extra(SS_HIDE,
	(TP->query_skill_extra(SS_HIDE) + added_skill));

    TP->set_skill_extra(SS_SNEAK,
	(TP->query_skill_extra(SS_SNEAK) + added_skill));

    return 0; 
}

int
remove(object arm)
{
    object wearer = query_worn();

    // Remove the extra skill when the bracers are removed.
    wearer->set_skill_extra(SS_HIDE, 
            (wearer->query_skill_extra(SS_HIDE) - added_skill));
    wearer->set_skill_extra(SS_SNEAK, 
            (wearer->query_skill_extra(SS_SNEAK) - added_skill));

    wearer->catch_tell("As you unfasten the " + short() +
	" you feel as if you have forgotten something. \n");

    return 0; 
}

