/*
 * Traveller for the roads in Faerie
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
    int x,z;
    string *mental, *type;

    mental = ({"cagey", "crafty", "devious", "dirty", "dishonest",        "furtive", "lazy", "rascally", "roguish", "ruthless", "smelly",        "trecherous", "tricky", "ugly"});
    type = ({"pirate", "mercenary"});

    x = random(sizeof(mental));
    z = random(sizeof(type));
    set_name("human");
    add_name(type[z]);
    set_race_name("human");
    set_gender(random(2));
    set_adj(mental[x]);
    set_adj(query_gender_string());
    set_short(mental[x] + " " + query_gender_string() + " " + type[z]);

    set_long("The " + query_short() + " looks like a well travelled " +
        "human, is tanned from " + HIS_HER(TO) + "  many journies, " +
        "and has long dark hair. " + CAP(HE_SHE(TO)) + " has sparking " +
        "eyes that have probably seen many wonders.\n");

    default_config_npc(60+random(20));

    add_chat("The world is a big place, and I have seen most of it.");
    add_chat("You would not believe all the places I've seen.");
    add_chat("Rumor has it elves live in this forest.");
    add_chat("I'd be careful if I were you. There are orcs nearby.");
    add_chat("I am having a good day, how about you?");
    add_chat("So many places to see, so little time.");

    add_act("sigh tiredly");
    add_act("emote looks around.");
    add_act("stretch");
    add_act("yawn");
    add_act("emote searches the bushes for food to eat.");
    add_act("emote looks up at the sky.");
 
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

    arm_me();

    set_m_in("wanders in.");
    set_m_out("wanders");

    ADD_MONEY;
    make_silver(25 + random(10));
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

