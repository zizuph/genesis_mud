/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * strongguard.c
 *
 * Vader
 * Modified by Sorgum 950707
 * Modified by Lilith 080809 
 *  Upped stats, made it a better mid-range npc.
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
            RIBOS_DIR + "weapon/ssword",
            RIBOS_DIR + "armour/helmet",
	    RIBOS_DIR + "armour/boots",
	    RIBOS_DIR + "armour/s_armour"		
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
    set_adj("confident");
    set_short("confident human knight");
    set_long("He is a very confident Ribos Knight.  Better think " +
	     "twice before\nmessing with him.\n");
    set_stats(({120 + random(10), 140 + random(10), 120 + random(10), 
		    100, 100, 100}));
    set_all_hitloc_unarmed(25);

    set_skill(SS_WEP_SWORD, 66);
    set_skill(SS_DEFENCE,   50);
    set_skill(SS_PARRY,     70);
    
    SET_MAX_HP;

    set_cact_time(1);
    add_cact("say Are you mad!  You have no hope of defeating me!");
    add_cact("cackle");
    add_cact("say I have tested the skills of greater fighters than you!");
    add_cact("say Surely you know, You will have to die for this!");
    add_cact("grin");    
    set_alignment(250);
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    FIX_EUID;
    MONEY_MAKE_SC(random(30)) -> move(TO);
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
