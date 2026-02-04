/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * weakguard.c
 *
 * Vader
 * Modified by Sorgum 950707
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
            RIBOS_DIR + "weapon/ssabre",
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
	     "needs alot\nof training.\n");

    set_stats(({10 + random(10), 10 + random(10), 10 + random(10), 
		    20, 10, 10}));
    set_all_hitloc_unarmed(5);

    set_skill(SS_WEP_SWORD, 22);
    set_skill(SS_DEFENCE,   27);
    set_skill(SS_PARRY,     14);
    
    SET_MAX_HP;
    
    seq_new("do_things");
    seq_addfirst("do_things", ({"@@arm_me"}));

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
