/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * weakguard.c
 *
 * Vader
 * Modified by Sorgum 950707
 *
 * Lilith copied over from Ribos/castle/monster/weakguard.c
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
            RIBOS_DIR + "armour/hat",
	    RIBOS_DIR + "armour/boots2",
	    RIBOS_DIR + "armour/s_shirt"		
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
    set_adj("timid");
    set_short("timid human knight");  
    set_alignment(100);

    set_long("He is an extremely timid Ribos Knight.  You think he " +
	     "needs alot of training.\nHe appears to be so "+
             "badly frightened that he is incapable of movement. "+
             "Instead, he stares with glassy eyes at the stately "+
             "imposing statue, as if hypnotized.\n");

    set_stats(({70 + random(10), 70 + random(10), 70 + random(10), 
		    20, 10, 10}));
    set_all_hitloc_unarmed(5);

    set_skill(SS_WEP_SWORD, 22);
    set_skill(SS_DEFENCE,   27);
    set_skill(SS_PARRY,     14);
    
    SET_MAX_HP;
    
    set_act_time(5);
    add_act("shiver");
    add_act("shudder");
    add_act("whimper");
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    ::equip_me();
    FIX_EUID;
    MONEY_MAKE_CC(random(20)) -> move(TO);
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
    TO->command("wear hat");
    TO->command("wear shoes");
}
