/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * okayguard.c
 *
 * Vader
 * Modified by Sorgum 950707
 * Modified by Lilith 09 Aug 2008
 *  Fixed cloning error by moving ::equip_me to end of the function.
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <money.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
            RIBOS_DIR + "weapon/ssword2",
            RIBOS_DIR + "armour/helmet2",
	    RIBOS_DIR + "armour/boots3",
	    RIBOS_DIR + "armour/s_armour2"		
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("knight");
    set_race_name("human");
    set_adj("over-confident");
    set_short("over-confident human knight");
    set_long("He is an over-confident human knight.  He looks like " +
	     "he is tough, but\nlooks can be decieving.\n");

    set_stats(({70 + random(10), 70 + random(10), 70 + random(10), 
		    45, 40, 53}));
    set_all_hitloc_unarmed(10);

    set_skill(SS_WEP_SWORD, 66);
    set_skill(SS_DEFENCE,   50);
    set_skill(SS_PARRY,     50);
    SET_MAX_HP;

    set_alignment(150);
    set_cact_time(1);
    add_cact("say Are you mad!  You have no hope of defeating me!");
    add_cact("cackle");
    add_cact("say Your skills are weak, young man!");
    add_cact("say Surely you know, You will have to die for this!");
    add_cact("grin");
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{

    FIX_EUID;
    MONEY_MAKE_SC(random(20)) -> move(TO);
    ::equip_me();
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield sword");
    TO->command("wear armour");
    TO->command("wear helmet");
    TO->command("wear boots");
}
