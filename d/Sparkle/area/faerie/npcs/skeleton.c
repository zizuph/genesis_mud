/*
 * Faerie skeleton
 * Found in the lower levels of the graveyard
 * By Finwe, August 2004
 * 
 * Removed non-bone leftovers from skeletons
 * Aeg, 1/21/2010
 *  
 * 10/08/14 Lavellan No corpse, no blinding by rangers, death message
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <files.h>      // for FILTER_CORPSE_OBJECTS

inherit "/std/monster";
inherit MAKE_MONEY;

void arm_me();

void
create_monster()
{
    int x,y;
    string *color, *size;
    color = ({"bleached", "grey", "splotched", "white"});
    size  = ({"large", "medium", "small"});

    x = random(sizeof(size));
    y = random(sizeof(color));
    set_short(size[x] + " " + color[y] + " skeleton");

    set_adj(size[x]);
    set_adj(color[y]);

    set_race_name("skeleton");
    set_adj("fetid");
    set_long("The " + short() + " looks terrible and old. It looks to be in " +
        "good condition with no missing bones visible. The skeleton is " +
        "grinning evilly at you with a bloodthirsty look in its eyes.\n");


    default_config_npc(80+random(20));

    set_act_time(5);
    add_act("emote rattles its bones at you fiercely.");
    add_act("emote grins evilly.");
    add_act("emote watches you with a deathly look.");
    
    set_cact_time(5);
    add_cact("emote attacks with renewed strength.");
    add_cact("emote grips his weapon tightly.");
    add_cact("emote dodges an attack.");

    set_skill(SS_DEFENCE,       70+random(10));
    set_skill(SS_WEP_KNIFE,     70+random(10));
    set_skill(SS_WEP_AXE,       70+random(10));
    set_skill(SS_WEP_POLEARM,   70+random(10));
    set_skill(SS_WEP_SWORD,     70+random(10));
    set_skill(SS_UNARM_COMBAT,  70+random(10));
    set_skill(SS_AWARENESS,     70+random(12));
    set_skill(SS_PARRY,         70+random(10));

    set_gender(2);
    
    add_prop(LIVE_I_UNDEAD, 20);

    /* Need to remove all non-bone leftovers */
    /*remove_leftover("nose");
    remove_leftover("kneecap");
    remove_leftover("intestine");
    remove_leftover("eye");
    remove_leftover("heart");
    remove_leftover("scalp");
    remove_leftover("kidney");
    remove_leftover("ear");
    remove_leftover("meat");*/
    
    // Corpse of a skeleton is silly...
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop("_ranger_i_not_blind",1);
    
    set_alignment(-100);
    default_config_npc(17);

    arm_me();

    set_m_in("walks in");
    set_m_out("walks");

    ADD_MONEY;
}

void
arm_me()
{
    int arm_count = random(2);

    switch(arm_count)
    {
        case 0:
            break;
        case 1:
            clone_object(ARM_DIR + "lgreaves")->move(TO);
            break;
        case 2:
            clone_object(ARM_DIR + "lbreastplate")->move(TO);
            break;
    }

    clone_object(WEP_DIR + "med_wep")->move(TO);

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
    int spirit_dex = query_stat(SS_DEX),
        spirit_str = query_stat(SS_STR);

    if (random(10))
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
            how = "barely hurt ";
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
 * I was also going to have it put bones on the ground, but 
 *      "torn and bloody remains of a skeleton skull" etc is silly
 * Returns 0, so it won't actually get a second life.
 *
 * Lavellan 
 */
int
second_life(object killer)
{
    tell_room(environment(this_object()), QCTNAME(this_object()) + 
        " disintegrates into dust, which scatters, and then is gone.\n",
        this_object());

    return 0;
}                                                     
