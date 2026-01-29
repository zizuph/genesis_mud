/*
 * Orc for the roads in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit MAKE_MONEY;

#define MENTAL  ({"angry", "barbaric", "beastly", "bloodthirsty", "brutal", \
    "cold-blooded", "cranky", "cruel", "dangerous", "demonic", "deranged", \
    "evil", "feral", "ferocious", "fierce", "foul", "grim", "grouchy", \
    "insane", "mad", "malevolent", "mean", "murderous", "nasty", "rabid", \
    "raging", "ravening", "savage", "sinister", "terrible", "testy", \
    "wicked", "wild"})
#define PHYS    ({"big", "black-haired", "bloody", "broad", "dark-eyed", \
    "dark-skinned", "dirty", "fanged", "grey-skinned", "hairy", "large", \
    "massive", "orange-eyed", "powerful", "red-eyed", "reeking", "short", \
    "smelly", "squat", "squinty-eyed", "strong", "sturdy", "tall", \
    "towering", "ugly", "yellow-eyed", "yellow-tusked"})

void create_orc() {}

void create_monster()
{
    string mental, phys;

    seteuid(getuid());

    mental = ONE_OF_LIST(MENTAL);
    phys   = ONE_OF_LIST(PHYS);

    set_name("orc");
    add_name(FAERIE+ORC+"_");
    set_race_name("orc");
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " orc");

    set_long("The " + query_short() + " looks dirty and ferocious. It " +
        "is evil-looking, and ready to destroy anything it meets.\n");

    add_chat("Me killses elveses!");
    add_chat("Elveses only guds for eattin'");
    add_chat("Orcses will killses you");
    add_chat("You looks gud to eatses");
    add_chat("Elveses and dwarves be bad!");
    add_chat("Me findses eminies for big bosses");

    add_act("snarl");
    add_act("emote looks you up and down as a meal.");
    add_act("emote licks its lips hungrily.");
    add_act("emote scratches itself.");
    add_act("emote picks something out of its fang.");
    add_act("emote growls dangerously.");

    set_skill(SS_DEFENCE,       50+random(10));
    set_skill(SS_WEP_KNIFE,     50+random(10));
    set_skill(SS_WEP_AXE,       50+random(10));
    set_skill(SS_WEP_POLEARM,   50+random(10));
    set_skill(SS_WEP_SWORD,     50+random(10));
    set_skill(SS_UNARM_COMBAT,  50+random(10));
    set_skill(SS_AWARENESS,     50+random(12));
    set_skill(SS_PARRY,         50+random(10));

    set_gender(0);

    set_alignment(0);
    default_config_npc(50 + random(20));

//    set_alarm(1.0,0.0,"arm_me");
    set_m_in("lopes in");
    set_m_out("lopes");

    ADD_MONEY;

    create_orc();
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
            clone_object(ARM_DIR + "lbreastplate")->move(TO);
            break;
        }
        case 2:
        {
            clone_object(ARM_DIR + "i_greaves")->move(TO);
            break;
        }
    }

    clone_object(WEP_DIR + "longsword")->move(TO);

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
    int avg_stat;
    string how;

    avg_stat = query_average_stat();

    if (random(3))
    {
	    return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(avg_stat + random(30), W_IMPALE, TO, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "barely hurt";
            break;
        case 1..10:
            how = "lightly hurt";
            break;
        case 11..20:
            how = "painfully hurt";
            break;
        default:
            how = "severely hurt";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " slashes you with its claws!\n"+
		     "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " charges " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }

    return 1;
}

