/*
 * This file is IGARD_NPC + "igard_archer"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_orc.c
 *
 * Olorin, July 1993
 * General upgrade, Olorin, February 1996
 * Last modified by Alto, October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_monster.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

public string   long_desc();
public void     long_text();
public int      find_home();
public int      go_back_home();

object HOME, actor, *inv;

string long_looks;
string alignlook();
string alignlook2();

#define WEP_ARRAY1 ({IGARD_WEP + "i_longbow"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY2 ({IGARD_ARM + "i_helmet"})
#define ARM_ARRAY3 ({IGARD_ARM + "i_greaves", IGARD_ARM + "i_bracers"})

string
alignlook() 
{
   string *alignlooks = ({"grim", "grumpy", "cruel", "angry", "stately",
       "mean", "solemn", "worried", "elderly", "young", "sinister",
       "wicked","eagle-eyed","patient", "ugly", "fierce","dangerous", "quiet",
       "skulking", "furtive", "sneaky", "nervous", "pensive", "thoughtful",
       "sickly", "clean-shaven", "fork-bearded", "surly",
       "unhealthy", "drunken", "lazy", "frightened", "devious"});
   return ONE_OF_LIST(alignlooks);
}


string
alignlook2() 
{
   string *alignlooks = ({"short", "stooped", "crippled", "limping", "sleepy",
       "muscular", "hulking", "dark", "huge", "twisted", "scarred",
       "greasy-haired","balding","tall", "skinny", "towering","bent-nosed", 
       "cross-eyed", "one-eyed", "hairless", "albino", "unhappy", "eager",
       "skulking", "furtive", "sneaky", "nervous", "white-haired", "tanned",
       "murderous", "deceitful", "conniving", "whining", "raging",
       "mischievous", "long-haired", "one-eared", "maniacal", "strange"});
   return ONE_OF_LIST(alignlooks);
}


void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " human in the armours of the White Hand, this fellow looks "
       + "uncomfortably similar to some of the orcs and uruks haunting "
       + "the caves and corridors of Isengard. His eyes are sallow and "
       + "his forehead is low and sloping. While his long arms look "
       + "unnatural dangling at his sides, they are especially good for "
       + "drawing the longbows used by the archers of Isengard.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " human who looks as if he would rather be someplace else. "
       + "He is not as tall nor as fair of skin and hair as the men "
       + "of Rohan, and yet there is something about him of lost "
       + "nobility and honour. His people fell under the sway of "
       + "Saruman long ago, but serve more out of fear than loyalty. "
       + "This man still looks ready to stick a few arrows into any "
       + "intruder, however, so beware.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " human appears to be of dunlending lineage. His hair is dark, "
       + "and his height is far less than that of the more noble lineages "
       + "of Rohan and Gondor. He is muscular and disciplined, however, "
       + "and looks willing and eager to use a longbow to silence any "
       + "troublemakers.\n";
	      break;
    default:
        break;
    }
}


public void
create_igard_archer()
{
}

nomask void
create_igard_monster()
{
    int     rnd = random(31);
 
    set_name("archer");
    set_pname("archers");
    add_name("human");
    add_name("_igard_archer");
    add_pname("humans");
    set_race_name("human");
    set_adj(alignlook());
    add_adj(alignlook2());
    add_adj("archer");
    set_short(alignlook() + " " + alignlook2() + " male archer");
    long_text();
    set_long(&long_desc());
    
    default_config_npc( 75 + rnd / 3);
    set_base_stat(SS_INT, 75 + rnd / 2);
    set_base_stat(SS_WIS, 75 + rnd / 2);
    set_base_stat(SS_DIS, 150);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  45 + rnd / 3);
    set_skill(SS_WEP_CLUB,   45 + rnd / 3);
    set_skill(SS_WEP_POLEARM,95 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  45 + rnd / 3);
    set_skill(SS_PARRY,      75 + rnd / 2);
    set_skill(SS_DEFENCE,    75 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   160 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 80000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 75000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    set_alarm(1.0, 0.0, &find_home());

    set_chat_time(15 + random(15));
    add_chat("I would love something decent to eat for a change. Why is "
        + "there never any steak?");
    add_chat("Those nasty Uruk Hai! Think they can boss us humans around? "
        + "They have a lesson awaiting them as soon as the Boss has his "
        + "attention elsewhere.");
    add_chat("What are you looking at? Move along!");
    add_chat("These filthy orcs stink!");
    add_chat("I cannot wait to pay back those pigs in Rohan. The debt "
        + "is long overdue.");
    add_chat("What happened to those men we sent to Fangorn in search of "
        + "firewood? The supply is running low and its growing cold outside.");
    add_chat("That slinking Grima gives me the creeps. Always looking at you "
        + "from under those creepy eyelids of his.");
    add_chat("Move along, lest I get bored and arrest you for loitering.");
    add_chat("There had better be no cowardly rangers slinking around "
        + "in here.");
    add_chat("I heard from my friend Ted that rangers sneak around all the "
        + "time because they are ashamed to be fighting on the losing side "
        + "of the war.");
    add_chat("I heard the Boss has special plans for those black-robed "
        + "hooded scum that have been passing through lately. Maybe he "
        + "wants to know why they are too cowardly to show their faces.");
    add_chat("You know, I hear tell those wimps in the black robes and "
        + "hoods spend most of their time picking flowers.");
    add_chat("I can't abide dwarves, always whining and begging for a "
        + "handout.");
    add_chat("That meat we had last night didn't look like beef or chicken. "
        + "If I didn't know better, I would think it was orc or human.");
    add_chat("My friend told me he saw a little man with furry feet one "
        + "time on a journey to the north. Little rodents should all be "
        + "squished, I say.");
    add_chat("I wish the Boss would finally turn us loose on Rohan. Those "
        + "horse brats need a lesson in humility.");
    add_chat("Who do these Uruk Hai think they are, ordering us around?");
    add_chat("Maybe when we are finished with Rohan, the Boss will let us "
        + "burn the elves out of the Golden Wood.");
    add_chat("I wasn't always a soldier, you know. I was a farmer until "
        + "the Rohirrim took my farm away in tribute to their king. At "
        + "least that's what the Boss told me.");

    set_cchat_time(5 + random(10));
    add_cchat("You will die for that!");
    add_cchat("For Isengard!");
    add_cchat("Death to all intruders!");
    add_cchat("You need a lesson in manners, friend.");
    add_cchat("If you know what is good for you, you'll drop any weapons "
        + "and run for your life!");
    add_cchat("Good, I was itching for a fight. If I wasn't going to kill "
        + "you, I'd probably buy you a beer.");

    set_act_time(15 + random(15));	
    add_act("scowl");
    add_act("get all from corpse");
    add_act("chuckle");
    add_act("grin");		
    add_act("grumble");		

    set_cact_time(2 + random(2));
    add_cact("smile dangerously"); 
    add_cact("grin wickedly"); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("emote throws back his head and lets out a mighty battlecry."); 

    create_igard_archer();
}


string
long_desc()
{
    return long_looks;
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;

    set_all_hitloc_unarmed(20);
}


int
find_home()
{
    HOME = environment(TO);
    return 1;
}

int
go_back_home()
{
    object foe;

    if (Victim->query_prop("_enemy_of_igard"))
    {
    foe = Victim;
    }

    if (environment(TO) == HOME)
    {
    return 1;
    }

    if ((TO->query_attack() != 0) || ((objectp(present(foe, ENV(TO))))
        && CAN_SEE(TO, foe)))
    {
    TO->command("kill " + foe->query_real_name());
    set_alarm(60.0, 0.0, &go_back_home());
    return 1;
    }

    tell_room(environment(TO), "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " adjusts his armours, peers dangerously around "
        + "and returns to his post.\n", ({TO}));

    tell_room(HOME, "The " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " arrives at his post, dusting off his "
        + "armours after a recent melee.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}


int
shoot_player(object player)
{
    int healed, health, pain;
    string body, shoots;
    string *bodyparts = ({"chest", "stomach", "thigh", "arm", "shoulder",
       "leg"});
    string *shootdescs = ({"slams", "thuds", "smashes", 
       "rips", "tears"});

    healed = TP->query_max_hp();
    health = TP->query_hp();
    pain = (health - (healed/6));
    actor = TP;
    inv = all_inventory(TO);

    body = ONE_OF_LIST(bodyparts);
    shoots = ONE_OF_LIST(shootdescs);

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, player))
    {
    return 1;
    }

    if (!sizeof(filter(inv, &->id("_igard_longbow"))))
    {
    return 1;
    }

    switch (random(3))
    {
    case 0:
        break;
    case 1:
    case 2:
        actor->catch_tell("An arrow " + shoots + " into your " + body + "!\n");
        tell_room(environment(actor), "An arrow slams into " + QTPNAME(TP) 
            + " " + body + "!\n", 
            ({actor}));

        TP->set_hp(pain);
        break;
    default:
        break;
    }
    return 1;
}


