/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * king.c
 *
 * Vader
 * Modified by Sorgum 950707
 * Modified by Lilith 09 Aug 2008
 *  Fixed cloning error by moving ::equip_me to end of the function.
 *  He's the King, I decided to have him holding some gems, too.
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Genesis/gems/gem.h"

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
            RIBOS_DIR + "castle/obj/treas_key"	});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("king");
    add_name("bor-el");
    set_race_name("human");
    set_short("King Bor-El");
    set_long("Bor-El, King of Ribos.  He is taking a bath.  Of course, " +
	     "as King, he doesn't have to bathe alone.  He is 'aided' by " +
	     "several young female servants.  They don't seem to mind, " +
	     "though as they each believe that they will one day become the " +
	     "Queen of Ribos.\n");

    set_stats(({170 + random(10), 170 + random(10), 170 + random(10), 
		    155, 160, 180}));
    set_all_hitloc_unarmed(30);

    set_act_time(1);
    add_act("say Melinda, rub down a little lower, please...");
    add_act("say Bay-El, go get the key from my desk.  Go to the " +
	    "treasury and get ten coins for each of these loyal " +
	    "servants.");
    add_act("say Marta, A little faster please.....");
    add_act("say Guard, keep your guard.  The Gypsie lady told me " +
	    "someone might attempt my life soon.  If he does, " +
	    "I will kill you.");
    add_act("say I hope the Sherrif can find this mysterious person " +
	    "who is trying to kill me.");
    add_act("say It is good to be the king.");
    add_act("grin");
    add_act("laugh");
    add_act("say Oh, ya'll are SOOOOO good to your King.");
    add_act("moan");
    set_alignment(350);
    SET_MAX_HP;
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    object key;

    FIX_EUID;
    MONEY_MAKE_SC(random(30)) -> move(TO);
    RANDOM_GEM(-1) -> move(TO);
    RANDOM_GEM(-1) -> move(TO);
    RANDOM_GEM(GEM_EXTREMELY_RARE) -> move(TO);
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
