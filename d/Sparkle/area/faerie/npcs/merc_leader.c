/*
 * A mercenary for Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit MAKE_MONEY;

void arm_me();

void create_monster()
{
    string mental, phys, type;

    mental = ("shifty");
    phys  = ("one-eyed");
    type = ("mercenary");

    set_name("human");
    add_name(type);
    set_race_name("human");
    set_gender(G_MALE);
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " " + type);

    set_long("The " + query_short() + " looks dangerous and not too " +
        "trusting. He seems to be always looking over his shoulder, " +
        "as if he's hiding from somone or something. His hair is matted " +
        "and disheveled and his clothes are smelly and dirty.\n");

    default_config_npc(15+random(20));

    add_chat("I'm thirsty! Bring me some wine to calm my nerves!");
    add_chat("Where is that signal to get out of this forsaken land?");
    add_chat("This land reeks of those foul elves!");
    add_chat("I don't know how much more of this I can stand!");
    add_chat("They don't pay me enough to do this.");
    add_chat("That girl better not give us anymore trouble.");

    add_act("emote looks over his shoulder and watches you.");
    add_act("emote looks around.");
    add_act("emote checks to make sure he's not missing anything.");
    add_act("emote shouts Hey there, hurry up!");
    add_act("emote looks nervously at you.");
    add_act("emote mutters something under his breath.");
 
    add_cact("emote attacks you with renewed strength.");
    add_cact("emote shouts a battle cry at you.");
    add_cact("emote dodges your attack.");

    set_skill(SS_DEFENCE,       50+random(10));
    set_skill(SS_WEP_KNIFE,     50+random(10));
    set_skill(SS_WEP_AXE,       50+random(10));
    set_skill(SS_WEP_POLEARM,   50+random(10));
    set_skill(SS_WEP_SWORD,     50+random(10));
    set_skill(SS_UNARM_COMBAT,  50+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
    set_skill(SS_PARRY,         50+random(10));

    set_alignment(0);
    default_config_npc(60 + random(10));

    arm_me();

    set_m_in("sneaks in.");
    set_m_out("sneaks");

    ADD_MONEY;
    make_silver(20 + random(10));

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
            clone_object(ARM_DIR + "jacket")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "l_pants")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "e_spear")->move(TO);

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
            how = "barely hurt ";
            break;
        case 11..20:
            how = "hurt";
            break;
        default:
            how = "seriously hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " charges you!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " charges " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}

