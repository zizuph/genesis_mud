/*  A sleeping scout that is part of the Test of High Sorcery
 *
 *  Attacking the scout kills the scout, but also results in 
 *  the attacker being flagged as having done an 'evil' act.
 *
 *  Waking the scout results in the scout attacking the waker,
 *  However waker gets flagged as having done a 'noble' act.
 *
 *  The scout holds military orders outlining the planned 
 *  assault on the Tower, to be passed on to the Master of
 *  the Tower as part of the quest.
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit "/d/Krynn/std/monster";

#define ORDERS "/d/Krynn/guilds/wohs/test/obj/duke_orders"
#define SWORD "/d/Krynn/guilds/wohs/test/obj/steel_shortsword"

#define WOKE_GUARD        "_wohs_test_woke_soldier"
#define KILLED_GUARD      "_wohs_test_killed_soldier"

int sleeping = 1;
int found_orders = 0;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("scout");
    set_race_name("human");
    set_adj("ergothian");
    add_adj("experienced");
    set_short("experienced Ergothian scout");
    set_gender("G_MALE");
    set_long("Lying in an ensorcelled sleep on the ground here is a " +
        "human Ergothian scout. You can only assume this is due to " +
        "protective magicks of the grove, and the scout was not " +
        "welcome.\nThe Ergothian scout is wearing leather armour, " +
        "brown leggings, leather boots, and a green cloak.\n");

    set_stats(({80,80,80,80,80,80}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 82000);
    add_prop(CONT_I_HEIGHT, 185);

    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_AWARENESS, 1);

    set_all_hitloc_unarmed(20);
    add_prop(LIVE_S_EXTRA_SHORT, " lying on the ground in an " +
        "ensorcelled sleep");

/*
    add_search(({"scout","ergothian scout","Ergothian scout",
        "experienced ergothian scout","experienced Ergothian scout"}),
        10,"search_scout",1);
*/

    set_alignment(0);
}

void
arm_me()
{
    equip( ({ ORDERS }));
}

void
scout_die(object attacker)
{
    attacker->catch_tell("You kneel down before the helpless Ergothian " +
        "scout and slay him in his sleep.\n");
    tell_room(environment(attacker), QCTNAME(attacker)+ " kneels down " +
        "before the helpless Ergothian scout and slays him in his " +
        "sleep.\n", ({ attacker }), attacker);

    attacker->add_prop(KILLED_GUARD, 1);
    WOHS_MANAGER->add_wohs_test_props(attacker, KILLED_GUARD, 1);

    TO->heal_hp(-10000);
    TO->do_die(attacker);

}

public int
query_scout_sleeping()
{
   return sleeping;
}

public void
wake_scout(object attacker)
{
    int stat = attacker->query_average_stat();

    sleeping = 0;
    TO->remove_prop(LIVE_S_EXTRA_SHORT);
    attacker->catch_tell("You kneel down before the Ergothian scout " +
        "and shake him roughly, waking him from his ensorcelled sleep.\n");
    tell_room(environment(attacker), QCTNAME(attacker)+ " kneels " +
        "down before the Ergothian scout and wakes him from his " +
        "ensorcelled sleep.\n", ({ attacker }), attacker);

    attacker->add_prop(WOKE_GUARD, 1);
    WOHS_MANAGER->add_wohs_test_props(attacker, WOKE_GUARD, 1);    

    TO->set_long("Before you stands a human Ergothian scout.\nThe " +
        "Ergothian scout is wearing leather armour, brown leggings, " +
        "leather boots, and a green cloak.\n");
    TO->set_stats(({stat, stat, stat, stat, stat, stat}));
    TO->heal_hp(10000);

    TO->command("emote shakes his head groggily before noticing you.");
    TO->command("emote says with hostility to you: Wizard scum! You " +
        "will die for your treachery!");
    TO->command("emote draws his steel shortsword!");
    clone_object(SWORD)->move(TO, 1);
    TO->command("wield all");
    TO->command("kill " +attacker->query_real_name());

}

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    if(sleeping)
    {
       sleeping = 0;
       remove_prop(LIVE_S_EXTRA_SHORT);
       set_alarm(0.5, 0.0, &scout_die(attacker));
    }
}

void
search_now(object searcher, string what)
{
    if(!query_scout_sleeping())
    {
         searcher->catch_msg("The scout is awake! You can't search him now!\n");
         return;
    }	  

    searcher->catch_msg("You notice underneath the scout what looks like " +
        "furled military orders.\n");
    return;
}