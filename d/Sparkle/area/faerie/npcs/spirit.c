/*
 * Faerie spirit
 * This NPC is found in the lowest levels of the graveyard
 * By Finwe, August 2004
 *
 * Removed leftovers from spirit. Spirits don't have bones!
 * Aeg, 1/21/10
 *  
 *  10/08/14 Lavellan No corpse, no blinding by rangers, death message 
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit MAKE_MONEY;

void arm_me();
void
create_monster()
{
    set_race_name("spirit");

    set_adj("ghostly");
    set_adj("evil");

    set_short("ghostly evil spirit");
    set_long("This " + short() + " looks mysterious but deadly. It appears " +
        "to have been elvish or human at one time but now has lost its " +
        "body. The spirit looks dangerous, and ready to destroy anything " +
        "in its way. However, it has enough substance to be able to " +
        "wield weapons.\n");

    set_skill(SS_DEFENCE,       70+random(10));
    set_skill(SS_WEP_KNIFE,     70+random(10));
    set_skill(SS_WEP_AXE,       70+random(10));
    set_skill(SS_WEP_POLEARM,   70+random(10));
    set_skill(SS_WEP_SWORD,     70+random(10));
    set_skill(SS_UNARM_COMBAT,  70+random(10));
    set_skill(SS_AWARENESS,     70+random(12));
    set_skill(SS_PARRY,         70+random(10));

    default_config_mobile(90+random(10));

    set_gender(2);
    add_prop(NPC_I_NO_LOOKS,   1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_UNDEAD, 20);

    set_act_time(5);
    add_act("emote floats past you.");
    add_act("emote shrieks something horrible.");
    add_act("emote touches you, leaving a feeling of dread.");

    set_cact_time(5);
    add_cact("emote attacks you with renewed strength.");
    add_cact("emote grips his weapon tightly.");
    add_cact("emote charges you.");

    /* Need to remove all organic leftovers */
    /*remove_leftover("nose");
    remove_leftover("tooth");
    remove_leftover("kneecap");
    remove_leftover("intestine");
    remove_leftover("nail");
    remove_leftover("skull");
    remove_leftover("thighbone");
    remove_leftover("eye");
    remove_leftover("heart");
    remove_leftover("scalp");
    remove_leftover("rib");
    remove_leftover("kidney");
    remove_leftover("ear");
    remove_leftover("meat");
    remove_leftover("toe");
    remove_leftover("finger");
    remove_leftover("jaw");*/
    // All organic leftovers? What non-organic leftovers are there?
    // Why not just give it no corpse?
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop("_ranger_i_not_blind",1);
    

    set_m_in("floats in");
    set_m_out("floats");

    arm_me();

    ADD_MONEY;
}

void
arm_me()
{
    int arm_count = random(2);

    switch(arm_count)
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            clone_object(ARM_DIR + "burlap_shirt")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "burlap_pants")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "lar_wep")->move(TO);

    command("wield all");
    command("wear all");

    return;
}

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    mixed *hitresult;
    string how;

    if (random(3))
    {
	return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(20 + random(30), W_IMPALE, TO, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "unhurt";
            break;
        case 1..10:
            how = "barely hurt";
            break;
        case 11..20:
            how = "hurt";
            break;
        default:
            how = "seriously hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " howls at you!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " howls at " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}


/*
 * (Mis?)using the second_life to give a death message.
 * Returns 0, so it won't actually get a second life.
 *
 * Lavellan 
 */
int
second_life(object killer)
{
    tell_room(environment(this_object()), 
        QCTNAME(this_object()) + " disperses into nothing.\n", this_object());
    return 0;
}

