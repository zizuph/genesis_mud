/*
 * Bard for the roads in Faerie
 * By Finwe, April 2005
 *
 * Typos fixed
 * Aeg, 2010
 *
 * Changed from neuter to male, Lavellan 20100608
 *
 */


#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit MAKE_MONEY;

void create_monster()
{
    int x,y,z;
    string *mental, *phys, *type;

    mental = ({"agreeable", "amicable", "articulate", "gossipy", 
        "long-winded", "bubbly", "happy", "coordinated", "eloquent", 
        "lyrical", "melodious", "musical", "sweet-sounding", "talkative"});
    phys  = ({"strong", "dashing", "chatty", "cheerful", "debonair", 
        "dashing", "energetic", "showy"});
    type = ({"bard", "minstrel", "troubadour", "balladeer"});

    x = random(sizeof(mental));
    y = random(sizeof(phys));
    z = random(sizeof(type));
    set_name("human");
    add_name(FAERIE+BARD+"_");
    add_name(type[z]);
    set_race_name("human");
    set_gender(random(2));
    set_adj(mental[x]);
    set_adj(phys[y]);
    set_short(mental[x] + " " + phys[y] + " " + type[z]);

    set_gender(0);

    set_long("The " + query_short() + " is a vagabond and poet. " + 
        CAP(HE_SHE(TO)) + " is a human who travels far and wide, telling " +
        "stories and singing ballads to everyone " +  HE_SHE(TO) + " meets.\n");

    default_config_npc(60+random(20));


    add_chat("Would you like to hear a ballad?");
    add_chat("My songs are well liked by everyone.");
    add_chat("I have travelled far and wide and know many stories.");
    add_chat("I just learned a new song, let me sing it to you.");
    add_chat("I just heard a new story, let me tell it to you.");
    add_chat("Everywhere I go I learn new stories to tell.");

    add_act("emote yodels a cheerful tune about a bad winter.");
    add_act("emote tells a story about a wicked witch.");
    add_act("emote sings a sad ballad about two star-crossed lovers.");
    add_act("emote tells a humourous tale about a lecherous barmaid and " +
        "a customer.");
    add_act("emote strums his guitar.");
    add_act("emote hums a merry tune.");
 
    add_cact("emote attacks you with renewed strength.");
    add_cact("emote dodges your attack.");

    add_cchat("I shall sing of this folly when we are done.");
    add_cchat("This is not good.");
    add_cchat("You will not defeat me.");
    add_cchat("That was a pretty bad maneuver.");
    add_cchat("I laugh in your face!");

    set_skill(SS_DEFENCE,       60+random(10));
    set_skill(SS_WEP_KNIFE,     60+random(10));
    set_skill(SS_WEP_AXE,       60+random(10));
    set_skill(SS_WEP_POLEARM,   60+random(10));
    set_skill(SS_WEP_SWORD,     60+random(10));
    set_skill(SS_UNARM_COMBAT,  60+random(10));
    set_skill(SS_AWARENESS,     60+random(12));
    set_skill(SS_PARRY,         60+random(10));

    set_alignment(0);

    set_alarm(1.0,0.0,"arm_me"); 
    set_m_in("saunters in");
    set_m_out("saunters");

    ADD_MONEY;
    make_silver(10 + random(10));

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
            clone_object(ARM_DIR + "i_greaves")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "lbreastplate")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "e_lsword")->move(TO);

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

    enemy->catch_tell(query_The_name(enemy) + " punches you!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " punches " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }
    
    return 1; /*  Important! Should not have two attacks in a round. */
}

