/*
 * This file is IGARD_NPC + "i_quest_orc"
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

inherit "/d/Gondor/rohan/isengard/igard/npc/outside_monster.c";
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

public string   long_desc();
public void     long_text();
public int      find_home();
public int      go_back_home();
public string   assess_missive();

object HOME;

string long_looks;

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " orc with short crooked legs and long arms that hang almost "
       + "to the ground. Although it is not the biggest orc you have ever "
       + "seen, it looks big enough to cause trouble, especially when it "
       + "has friends around to help it.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " orc from the caverns beneath the Misty Mountains. He is so filthy "
       + "that you cannot tell what colour his skin would be when clean. He "
       + "wears the regalia of the White Hand, which marks him as one of a "
       + "horde of orcs pressed into service by the gangmasters of Saruman.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " orc seems somehow more intelligent and clever than is usual for "
       + "his kind. He watches you with a perceptive eye, as if probing for "
       + "weaknesses. He wears the regalia of the White Hand, suggesting that "
       + "he was born in the warrens of Isengard.\n";
	      break;
    default:
        break;
    }
}


public void
create_igard_orc()
{
}

nomask void
create_igard_monster()
{
    int     rnd = random(31);
 
    set_name("orc");
    set_pname("orcs");
    set_race_name("orc");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    default_config_npc( 45 + rnd / 3);
    set_base_stat(SS_INT, 25 + rnd / 2);
    set_base_stat(SS_WIS, 25 + rnd / 2);
    set_base_stat(SS_DIS, 55 + rnd / 6);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  45 + rnd / 3);
    set_skill(SS_WEP_CLUB,   45 + rnd / 3);
    set_skill(SS_WEP_KNIFE,  45 + rnd / 3);
    set_skill(SS_PARRY,      45 + rnd / 2);
    set_skill(SS_DEFENCE,    45 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    set_chat_time(5 + random(15));
    add_chat("Hee hee. This is a great place to hide.");
    add_chat("I is important, y'know! Courrrrier fer Isengard. Hick!");
    add_chat("Don't tell nobody bout my hideout, y'hear!");
    add_chat("I'll just sit in here and have a little drinkie winkie, I will.");
    add_chat("A little nap won't hurt nothin. Boss can wait a bit.");
    add_chat("What're you doin in here? This is my sleepin hole!");
    add_chat("Gots to get this missive to the Boss, but I needs a nap first!");

    set_cchat_time(5 + random(10));
    add_cchat("Let me be! I needs a nap.");
    add_cchat("Have pity on a poor drunken courier!");
    add_cchat("After I kill you, I'll have a nice nap.");
    add_cchat("I need a drink.");

    set_act_time(15 + random(15));	
    add_act("hiccup");
    add_act("yawn");

    set_cact_time(2 + random(2));
    add_cact("hiccup"); 
    add_cact("yawn"); 

    set_alarm(1.0, 0.0, &find_home());

    set_default_answer( ({ "say I'm too tired and drunk for nonsense! What "
        + "do you want?" }) );

    add_ask_item(({"grsnick", "courier"}), "say Yes, that's me. Now let me "
        + "sleep.");
    add_ask_item(({"boss", "saruman"}), "say He will probably kill me for "
        + "being late, but I needs a nap.");
    add_ask_item(({"missive", "about missive", "for missive"}),
        "@@assess_missive");

    create_igard_orc();
}


string
long_desc()
{
    return long_looks;
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
assess_missive()
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
        command("say I don't trust you, scum!");
        command("kill " + pname);
        return "";
    }

    if (TP->test_bit("gondor", IGARD_GROUP, IGARD_COURIER_BIT))
    {
        TO->command("say I'm tired of dealing with the likes of you. "
            + "Go away!");
        return "";
    }

    if (GIQ)
    {
        TO->command("say You stink of prisoner! Die!");
        TO->command("kill " + pname);
        return "";
    }


    if (GOODIE && !FRIEND)
    {
        TO->command("say Die, scum!");
        TO->command("kill " + pname);
        return "";
    }


    if (FRIEND)
    {
        TO->command("say You don't look entirely trustworthy, worm, but "
            + "I really need a nap.");
    }

    TO->command("yawn");
    set_alarm(2.0, 0.0, &command("say I just got back from a trip down to "
        + "the land of the horse boys, and I'm tired and need a good drink."));
    set_alarm(7.0, 0.0, &command("say I have a missive for the Boss, but I "
        + "can't bring myself to walk down to the tower now. Would you take "
        + "it for me?"));
    set_alarm(8.0, 0.0, &command("hiccup"));

    TP->add_prop(FINISHED_IGARD_CAVERNS, 1);
    TP->remove_prop(SENT_IGARD_CAVERNS);
    TP->add_prop(SENT_IGARD_ORTHANC, 1);

    setuid();
    seteuid(getuid());
    clone_object(IGARD_QUEST_OBJ + "courier_missive.c")->move(TP);

    set_alarm (9.0, 0.0, &player->catch_tell("The orc hands you a small "
        + "missive.\n"));
    set_alarm (9.0, 0.0, &tell_room(environment(), "The orc hands " 
        + QTNAME(TP) + " a small missive.\n", player));

    return "";
}


void
do_die(object killer)
{
    setuid();
    seteuid(getuid());

    if (!killer->query_prop(GOODIE_IGARD_QUEST))
    {
    tell_room(ENV(TO), "With his last breath, the orc tears his missive "
        + "to shreds!\n");
    }

    if (killer->query_prop(GOODIE_IGARD_QUEST))
    {
    setuid();
    seteuid(getuid());
    clone_object(IGARD_QUEST_OBJ + "courier_missive.c")->move(TO);

    killer->add_prop(FINISHED_IGARD_CAVERNS, 1);
    killer->remove_prop(SENT_IGARD_CAVERNS);
    killer->add_prop(SENT_IGARD_ORTHANC, 1);

    }

    ::do_die(killer);
}

