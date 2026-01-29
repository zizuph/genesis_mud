/* A monster with skill
   Nick */

#include "defs.h"
#include "orc.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/monster";
inherit "/lib/unique";
inherit "/d/Faerun/std/team_code";
inherit "/d/Faerun/lib/assist_friend";
inherit MAKE_MONEY;

#define FAERUN_DIR "/d/Faerun/orcmaker/wep/"
#define ARMS   "orc_bracers"
#define LEGS   "orc_greaves"
#define BODY   "orc_breastplate"
#define HELMS  "elf_helm"

//#define MENTAL  ({"angry", "barbaric", "beastly", "bloodthirsty", "brutal", \
//    "cold-blooded", "cranky", "cruel", "dangerous", "demonic", "deranged", \
//    "evil", "ferel", "ferocious", "fierce", "foul", "grim", "grouchy", \
//    "insane", "mad", "malevolent", "mean", "murderous", "nasty", "rabid", \
//    "raging", "ravening", "savage", "sinister", "terrible", "testy", \
//    "wicked", "wild"})
//#define PHYS    ({"big", "black-haired", "bloody", "broad", "dark-eyed", \
//    "dark-skinned", "dirty", "fanged", "grey-skinned", "hairy", "large", \
//    "massive", "orange-eyed", "powerful", "red-eyed", "reeking", "short", \
//    "smelly", "squat", "squinty-eyed", "strong", "sturdy", "tall", \
//    "towering", "ugly", "yellow-eyed", "yellow-tusked"})


void arm_me();

create_monster()
{
    string mental, phys;

    seteuid(getuid());
    
    mental = ONE_OF_LIST(MENTAL);
    phys   = ONE_OF_LIST(PHYS);

    npc_name = ORC_CAMP_NPC;

    set_name("orc");
    add_name("_orc_lord");
    add_name(npc_name);
    add_name("orc lord");
    set_race_name("orc");
    set_adj(mental);
    set_adj(phys);
    set_short(mental + " " + phys + " orc");
    set_long("This is the largest orc in the camp. He has matted, black " +
        "hair and a long, dog-like face. His fangs are sharp an look " +
        "deadly. His skin is black with patches of fur. Various scars " +
        "cover his skin, evidence that he's clawed his way to the top. " +
        "His long arms have sharp claws which look dangerous.\n");

    set_skill(SS_DEFENCE, random(5) + 40);
    set_skill(SS_WEP_SWORD, 75);

    set_base_stat(SS_STR, 160, 10);
    set_base_stat(SS_DEX, 140, 10);
    set_base_stat(SS_CON, 160, 10);
    set_base_stat(SS_INT, 135, 10);
    set_base_stat(SS_WIS, 135, 10);
    set_base_stat(SS_DIS, 135, 10);

    set_skill(SS_DEFENCE,       60+random(10));
    set_skill(SS_WEP_CLUB,      60+random(10));
    set_skill(SS_WEP_AXE,       60+random(10));
    set_skill(SS_WEP_POLEARM,   60+random(10));
    set_skill(SS_WEP_SWORD,     60+random(10));
    set_skill(SS_UNARM_COMBAT,  60+random(10));
    set_skill(SS_AWARENESS,     60+random(12));
    set_skill(SS_PARRY,         60+random(10));

    arm_me();
    make_gold(5 + random(10));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 194);   
    add_prop(CONT_I_WEIGHT, 80000); 
    add_prop(CONT_I_VOLUME, 80000); 

    set_chat_time(12+random(14));
    add_chat("You smell worse than ogre!");
    add_chat("You worthless!");
    add_chat("Hey, what you looking at?");
    add_chat("Orcses rule!");
    add_chat("Me killed lots of enemies!");
    add_chat("Me waiting for reports from lazy orcses in fort!");
    add_chat("No orcses stronger than me!");

    set_act_time(14+random(20));
    add_act("flex");
    add_act("growl");
    add_act("emote snorts like a wild beast.");

    set_cchat_time(5+random(10));
    add_cchat("You no need leg, me remove it for you.");
    add_cchat("Me like beating you to dead.");
    add_cchat("You scream like pig!");
    add_cchat("Me wear your hide when you dead.");
}

void
arm_me()
{
    setuid();
    seteuid(getuid());


    clone_object(ARM_DIR + ARMS)->move(TO);
    clone_object(ARM_DIR + HELMS)->move(TO);
    clone_object(ARM_DIR + BODY)->move(TO);
    clone_object(ARM_DIR + LEGS)->move(TO);

    clone_unique(WEP_DIR + "thighbone", 7,
        ({ FAERUN_DIR + "whammer",
           FAERUN_DIR + "mstar",
           FAERUN_DIR + "cleaver",
           FAERUN_DIR + "falchion"}), 1)->move(TO, 1);


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

    hitresult = enemy->hit_me((avg_stat*2) + random(30), W_IMPALE, TO, -1);
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

void
init_living()
{
    ::init_living();
    init_team_pickup();
}
