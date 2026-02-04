/*
 * 05/2008 - defense was never added, but was taken away upon removal.
 *           added defense as intended. (Novo)
 * 05/2008 - removed quest bit checks so all players get these bonuses.
 *           (Novo)
 *
 * Lucius, Jan 2018: Code cleanup and magic info corrections.
 *
 */
#pragma strict_types
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

public int added_skill;


void
create_terel_armour()
{
    set_name("boots");
    set_short("pair of black boots");
    set_pshort("pairs of black boots");
    set_long("It's a pair black boots with grey linings.\n");
    set_adj(({"black"}));

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({
             "These boots will endow the wearer with "+
             "an increased capacity for defence.\n",70}));
    add_prop(OBJ_S_WIZINFO,
	"These boots add up to 10 defence to the wearer. "+
	"They are found on Trevin, the assassin in Last. "+
	"/d/Terel/last/npc/assassin.c.\n");

    set_armour_size(ANY_SIZE);
    set_default_armour(20, A_FEET, 0, this_object());
}

mixed 
wear_terel_armour(object obj) 
{
    added_skill = ((10 + TP->query_stat(SS_DEX))/10);

    if (added_skill > 10)
        added_skill = 10;

    if ((TP->query_skill(SS_DEFENCE) + added_skill) > 100)
        added_skill = (100-(TP->query_skill(SS_DEFENCE)));

    TP->set_skill_extra(SS_DEFENCE,
        (TP->query_skill_extra(SS_DEFENCE) + added_skill));

    write("The "+short()+" pulse as you wear them.\n");
    return 0;
}

mixed 
remove(object obj)
{
    wearer->set_skill_extra(SS_DEFENCE,
	(wearer->query_skill_extra(SS_DEFENCE) - added_skill));

   added_skill = 0;
   return 0;
}

