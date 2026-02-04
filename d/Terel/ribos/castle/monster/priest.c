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
            RIBOS_DIR + "weapon/club",
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
    set_name("priest");
    set_race_name("human");
    set_adj("saintly");
    set_long("This priest believes that God will save us, and " +
	     "especially the King.\n");

    set_alignment(800);
    set_stats(({70 + random(10), 70 + random(10), 70 + random(10), 
			    80, 80, 80}));
    set_all_hitloc_unarmed(25);

    set_skill(SS_WEP_CLUB,  66);
    set_skill(SS_DEFENCE,   50);
    set_skill(SS_PARRY,     70);

    set_act_time(1);
    add_act("say Welcome my child.");
    add_act("say Is your soul at rest?  Come, pray with me.");
    add_act("comfort all");
    add_act("pray");

    SET_MAX_HP;
}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{

    FIX_EUID;
    MONEY_MAKE_CC(20) -> move(TO);
    ::equip_me();
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield club");
}
