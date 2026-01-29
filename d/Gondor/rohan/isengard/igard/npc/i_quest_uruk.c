/*
 * This file is IGARD_NPC + "i_quest_uruk.c"
 *
 * Which is modified from:
 *
 * The file /d/Gondor/morgul/npc/ithil_uruk.c
 *
 *	Olorin, July 1993
 *	General revision: Olorin, Feb 1996
 *
 * Last modified by Alto, 11 October 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/d/Gondor/bits.h"

inherit IGARD_LIB + "quest_funcs.c";

#define WEP_ARRAY1 ({IGARD_WEP + "i_largescim", IGARD_WEP + "i_largeaxe", IGARD_WEP + "i_largeclub", IGARD_WEP + "i_largehalberd", IGARD_WEP + "i_bestscim", IGARD_WEP + "i_bestaxe", IGARD_WEP + "i_besthalberd",})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY1 ({IGARD_ARM + "i_platemail"})
#define ARM_ARRAY2 ({IGARD_ARM + "i_helmet"})
#define ARM_ARRAY3 ({IGARD_ARM + "i_bracers"})

public int      find_home();
public int      go_back_home();
public string   initiate_quest();

object HOME;


public void
create_igard_uruk()
{
    clone_object(IGARD_ARM + "i_shoes")->move(TO);
    clone_object(IGARD_ARM + "i_greaves")->move(TO);
}

nomask void
create_igard_monster()
{
    int     rnd = random(41);

    set_name("uruk");
    set_pname("uruks");
    set_race_name("uruk");
    set_adj(alignlook());
    add_adj(alignlook2());
    set_long("This " + (implode(query_adjs()," "))
       + " uruk is one of the largest orcs you have seen. He stands as tall "
       + "as most men, although his arms dangle below his knees. His legs are "
       + "straight and long, and his eyes are much less sallow than those of "
       + "his orc kindred. With a shudder, you realize this is one of the "
       + "more successful and unnatural products of the breeding warrens in "
       + "the pits of Isengard. He looks intelligent and disciplined. It "
       + "seems wise to avoid crossing his path.\n");
    
    default_config_npc(95 + rnd / 2);
    set_base_stat(SS_INT, 65 + rnd);
    set_base_stat(SS_WIS, 65 + rnd);

    set_alignment(-350-rnd*10);

    set_skill(SS_WEP_SWORD,   85 + rnd);
    set_skill(SS_WEP_POLEARM, 85 + rnd);
    set_skill(SS_WEP_CLUB,    85 + rnd);
    set_skill(SS_WEP_AXE,     85 + rnd);
    set_skill(SS_WEP_KNIFE,   85 + rnd);
    set_skill(SS_PARRY,       85 + rnd);
    set_skill(SS_DEFENCE,     85 + rnd);
    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 90000 + rnd * 500);
    add_prop(CONT_I_VOLUME, 85000 + rnd * 500);    
    add_prop(LIVE_I_SEE_DARK, 5);

    set_chat_time(5 + random(15));
    add_chat("Where is that stinking courier? These hill orcs are "
        + "completely unreliable for anything involving work.");
    add_chat("I can't leave my post. Someone find that courier, and "
        + "double-time it, y'hear?");
    add_chat("What are you looking at? Move along!");
    add_chat("I'm going to flay the meat from his bones when I catch "
        + "him. Probably dozing over a bottle, like the rest of his ilk.");
    add_chat("Stinking hill orcs. A simple job to deliver a missive and "
        + "they foul it up. Just another mess for the Uruk Hai to clean "
        + "up, as usual.");
    add_chat("Have you seen Grsnick?");
    add_chat("That slackard Grsnick will be whipped, oh yes! The Boss "
        + "needs that information yesterday!");

    set_cchat_time(5 + random(10));
    add_cchat("You think to best me, runt? Come ahead, show me what you "
        + "have. It doesn't look like much from here.");
    add_cchat("That was your last mistake, mousie!");
    add_cchat("I'm glad this fight is taking so long. It gives me time to "
        + "decide which part of you to eat first.");
    add_cchat("I'll be scraping you off my shoes soon, runt.");
    add_cchat("Run while you can, little runt!");
    add_cchat("Uruk Hai!");

    set_act_time(15 + random(15));	
    add_act("grumble");
    add_act("get all from corpse");
    add_act("growl");
    add_act("stretch");		
    add_act("glare");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("growl"); 
    add_cact("frown"); 
    add_cact("yawn"); 

    set_alarm(1.0, 0.0, &find_home());

    set_default_answer( ({ "say Stop babbling! What do you want?" }) );

    add_ask_item(({"grsnick", "courier"}), "say Have you seen his flaming "
        + "hide? He has something the Boss wants. If you want a commission "
        + "you've come to the right place. I need someone to find that "
        + "stinking runt of a hill orc.");
    add_ask_item(({"missive", "information"}), "say I'm not going to tell "
        + "you, worm. If you want to know, ask for a commission.");
    add_ask_item(({"job", "task", "quest"}), "say What do I look like, a "
        + "wetnurse? If you want a commission, ask for one. Otherwise, go "
        + "away before I decide to kill you.");
    add_ask_item(({"boss", "saruman"}), "say He expected things done "
        + "yesterday, and here that hill orc Grsnick has gone and disappeared. "
        + "He needs finding more than he needs whipping, and thats saying "
        + "something.");
    add_ask_item(({"commission", "about commission", "for commission"}),
        "@@initiate_quest");

    create_igard_uruk();
}


static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
    Arm3 = ARM_ARRAY3;

    set_all_hitloc_unarmed(30);
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


string
initiate_quest()
{
    object player;
    string pname;

    player = this_player();
    pname = TP->query_real_name();

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Who is there? Come out, maggot!");
        return "";
    }

    if ((ENEMY) && (!WIZARD))
    {
        command("scowl " + TP->query_real_name());
        command("say You think I would hire a worm like you?");
        command("say I'll put you out of your misery!");
        command("kill " + pname);
        return "";
    }

    if (TP->test_bit("gondor", IGARD_GROUP, IGARD_COURIER_BIT))
    {
        TO->command("say What? You need more work? Go away, worm. If "
            + "you did your job right last time, I wouldn't still be "
            + "looking for him, would I?");
        return "";
    }

    if (GIQ)
    {
        TO->command("say You've been double dealing with those prisoners, "
            + "haven't you?");
        TO->command("kill " + pname);
        return "";
    }


    if (BIQ)
    {
        TO->command("say What are you standing around here for, slacker? "
            + "Get busy, and double-time it, y'hear?");
        return "";
    }

    if (GOODIE && !FRIEND)
    {
        TO->command("say I'll not hire the likes of you, worm.");
        TO->command("kill " + pname);
        return "";
    }


    if (FRIEND)
    {
        TO->command("say You don't look the sort I would normally trust "
            + "to do this job, but times are tight. You'll do.");
    }

    TO->command("grumble");
    set_alarm(2.0, 0.0, &command("say No doubt you know that we intend "
        + "to teach those pretty horse boys a lesson any day now. We got "
        + "word from a spy in their little golden hovel that a perfect "
        + "opportunity is coming up to raze the place."));
    set_alarm(7.0, 0.0, &command("say It all depends on the whelp Erkenbrand "
        + "being away with his band of dogs for the night."));
    set_alarm(11.0, 0.0, &command("grumble"));
    set_alarm(12.0, 0.0, &command("say Well this useless hill orc Grsnick was "
        + "entrusted to deliver a missive from the spy back here to the Boss. "
        + "He was seen passing the gate this morning, but did not check in "
        + "down at Orthanc. The Boss is not pleased!"));
    set_alarm(17.0, 0.0, &command("say The raid will not be successful "
        + "unless we know exactly when the golden hovel will be ripe for "
        + "the plucking, and time is passing swiftly."));

    set_alarm(22.0, 0.0, &command("say There on the floor is the only "
        + "clue I have of his whereabouts. Take it, find him, and get that "
        + "missive to the Boss, pronto!"));

    START_QUEST(TP, "IGARD COURIER QUEST");
    TP->add_prop(BADDIE_IGARD_QUEST, 1);

    switch (random(3))
    {
        case 0:
            set_alarm(25.0, 0.0, &send_igard_orcwarg());
            break;
        case 1:
            set_alarm(25.0, 0.0, &send_igard_furnace());
            break;
        case 2:
            set_alarm(25.0, 0.0, &send_igard_wall());
            break;
        default:
            break;
    }


    set_alarm(27.0, 0.0, &command("sigh"));
    set_alarm(28.0, 0.0, &command("say Move it, worm! Double-time!"));

    return "";
}
