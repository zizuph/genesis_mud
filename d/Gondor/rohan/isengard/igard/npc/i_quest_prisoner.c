/*
 * This file is IGARD_NPC + "i_quest_prisoner.c"
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

inherit "/d/Gondor/rohan/isengard/igard/npc/igard_prisoner.c";
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
private void    add_team();
public  int     add_2_friends(int i);
public string   initiate_quest();

static  int     Team_Size;
object HOME, actor;

string long_looks;

void
long_text()
{
    switch (random(3))
    {
    case 0:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " human who looks starved, beaten and abused. The conditions in "
       + "the squalid prison have been hard on this prisoner.\n";
	      break;
    case 1:
       long_looks = CAP(LANG_ADDART(implode(query_adjs()," ")))
       + " human who has almost no hope of escape. Things will not "
       + "go well for the prisoners when the Uruk Hai return in "
       + "number to quell the uprising.\n";
	      break;
    case 2:
       long_looks = "This " + (implode(query_adjs()," "))
       + " human glares about the room with proud and angry eyes. There "
       + "is blood of Rohan in this prisoner's veins. It seems clear "
       + "this is one of the leaders of the uprising.\n";
	      break;
    default:
        break;
    }
}


public void
create_human_prisoner()
{
}

nomask void
create_igard_prisoner()
{
    int     rnd = random(31);
    int     gender = random(2);
 
    set_name("human");
    set_pname("humans");
    set_race_name("human");
    set_adj(alignlook());
    add_adj(alignlook2());
    long_text();
    set_long(&long_desc());
    
    set_alignment(250 + rnd*10);
    set_gender(gender);

    switch(random(5))
    {
        case 0:
            default_config_npc( 45 + rnd / 3);
            set_base_stat(SS_INT, 25 + rnd / 2);
            set_base_stat(SS_WIS, 25 + rnd / 2);
            set_base_stat(SS_DIS, 55 + rnd / 6);
            set_skill(SS_WEP_SWORD,  45 + rnd / 3);
            set_skill(SS_WEP_CLUB,   45 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  45 + rnd / 3);
            set_skill(SS_PARRY,      45 + rnd / 2);
            set_skill(SS_DEFENCE,    45 + rnd / 2);
            break;
        case 1:
            default_config_npc( 55 + rnd / 3);
            set_base_stat(SS_INT, 35 + rnd / 2);
            set_base_stat(SS_WIS, 35 + rnd / 2);
            set_base_stat(SS_DIS, 65 + rnd / 6);
            set_skill(SS_WEP_SWORD,  55 + rnd / 3);
            set_skill(SS_WEP_CLUB,   55 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  55 + rnd / 3);
            set_skill(SS_PARRY,      55 + rnd / 2);
            set_skill(SS_DEFENCE,    55 + rnd / 2);
            break;
        case 2:
            default_config_npc( 65 + rnd / 3);
            set_base_stat(SS_INT, 45 + rnd / 2);
            set_base_stat(SS_WIS, 45 + rnd / 2);
            set_base_stat(SS_DIS, 75 + rnd / 6);
            set_skill(SS_WEP_SWORD,  65 + rnd / 3);
            set_skill(SS_WEP_CLUB,   65 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  65 + rnd / 3);
            set_skill(SS_PARRY,      65 + rnd / 2);
            set_skill(SS_DEFENCE,    65 + rnd / 2);
            break;
        case 3:
            default_config_npc( 75 + rnd / 3);
            set_base_stat(SS_INT, 55 + rnd / 2);
            set_base_stat(SS_WIS, 55 + rnd / 2);
            set_base_stat(SS_DIS, 85 + rnd / 6);
            set_skill(SS_WEP_SWORD,  75 + rnd / 3);
            set_skill(SS_WEP_CLUB,   75 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  75 + rnd / 3);
            set_skill(SS_PARRY,      75 + rnd / 2);
            set_skill(SS_DEFENCE,    75 + rnd / 2);
            break;
        case 4:
            default_config_npc( 85 + rnd / 3);
            set_base_stat(SS_INT, 65 + rnd / 2);
            set_base_stat(SS_WIS, 65 + rnd / 2);
            set_base_stat(SS_DIS, 95 + rnd / 6);
            set_skill(SS_WEP_SWORD,  85 + rnd / 3);
            set_skill(SS_WEP_CLUB,   85 + rnd / 3);
            set_skill(SS_WEP_KNIFE,  85 + rnd / 3);
            set_skill(SS_PARRY,      85 + rnd / 2);
            set_skill(SS_DEFENCE,    85 + rnd / 2);
            break;
        default:
            break;
    }


    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    

    set_alarm(1.0, 0.0, &find_home());

    set_chat_time(5 + random(15));
    add_chat("If we can only get to that courier first!");
    add_chat("We're locked down in here. We need someone who can get "
        + "out and find that courier before its too late!");
    add_chat("I think the plan will work, if only we can get to him first.");
    add_chat("Rohan will fall if we do not get that missive!");
    add_chat("I heard his name was Grsnick.");
    add_chat("They said he was a hill orc, not one of these cursed Uruks.");
    add_chat("Saruman is not pleased. He'll be even less pleased if we get "
        + "that missive first.");

    set_default_answer(({"say I'm sorry, that was completely incoherent."}));

    add_ask_item(({"grsnick", "courier"}), "say We overheard one of the guards "
        + "speaking of a courier orc named Grsnick. He has something very "
        + "important to our cause.");
    add_ask_item(({"orc", "hill orc"}), "say There is an orc who carries "
        + "a missive that we simply must capture, else all is lost!");
    add_ask_item(({"cause"}), "say We mean to prevent foul Saruman from "
        + "vanquishing King Theoden! We must find that orc!");
    add_ask_item(({"missive", "information"}), "say The missive carried "
        + "by the courier contains vital strategic information that could "
        + "be used against Rohan!");
    add_ask_item(({"plan"}), "say Our plans are our own, stranger! Unless "
        + "you intend to join our conspiracy, be off!");
    add_ask_item(({"job", "task", "quest"}), "say I'm not sure I can trust "
        + "you, stranger. Ask about the conspiracy, and just maybe I will.");
    add_ask_item(({"saruman"}), "say That foul traitor! We'll surprise him "
        + "yet, if only one of us can escape to find that courier.");
    add_ask_item(({"conspiracy", "about conspiracy", "about the conspiracy"}),
        "@@initiate_quest");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    create_human_prisoner();
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

    if (Victim->query_prop("_enemy_of_prisoners"))
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
        + TO->query_race() + " runs off to alert the other prisoners of "
        + "danger.\n", ({TO}));

    tell_room(HOME, "A " + (implode(query_adjs()," ")) + " " 
        + TO->query_race() + " runs into the cell.\n");

    TO->move_living("M", HOME, 1, 0);

    return 1;
}


private void
add_team()
{
    int     n, 
            p, 
            r;

    TO->set_leader();
    p = Team_Size + random(Team_Size/2 + 1);

    for (n = 0; n < p/3; n++)
    {
	       r = p - n*3;
       	if (r > 3) 
	       r = 3;
        set_alarm(1.0, 0.0, &add_2_friends(r));
    }
}

public void
set_team_size(int i)
{
    Team_Size = i;
}


public int
add_2_friends(int i)
{
    int    n = -1;
    object friend;
    object *arr;

    arr = filter(all_inventory(ENV(TO)), &->id("_igard_prisoner"));

    arr -= ({ TO });

    if (sizeof(arr) >= 1)
    {
    return 0;
    }

    if (i < 1) 
   	return 0;
    if (i > 3) 
   	i = 3;
    while (++n < i)
    {
        friend = clone_object(IGARD_NPC + "igard_human_prisoner");
       	friend->move_living("M", ENV(TO));
       	friend->arm_me();
       	TO->team_join(friend);
    }
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
        command("say Who is there? Come out where I can see you!");
        return "";
    }

    if ((PRISONER_ENEMY) && (!WIZARD))
    {
        command("scowl " + TP->query_real_name());
        command("say You think I would trust a villain like you?");
        command("say Die, traitor!");
        command("kill " + pname);
        return "";
    }

    if (TP->test_bit("gondor", IGARD_GROUP, IGARD_COURIER_BIT))
    {
        TO->command("say You are already a member of the conspiracy. "
            + "Hopefully your hard work paid off and Rohan is secure.");
        return "";
    }

    if (GIQ)
    {
        TO->command("say Please, time is pressing. Will you not begin?");
        return "";
    }


    if (BIQ)
    {
        TO->command("say Traitor! You are working for the Enemy!");
        TO->command("kill " + pname);
        return "";
    }

    if (BADDIE)
    {
        TO->command("say I'll not trust the likes of you, villain.");
        TO->command("kill " + pname);
        return "";
    }


    TO->command("worry");
    set_alarm(2.0, 0.0, &command("say You must be wondering what this "
        + "prison riot is all about. We have no hope of escape, but we are "
        + "hoping that in the confusion one of us might break free."));
    set_alarm(7.0, 0.0, &command("say You see, I heard the guards talking "
        + "this morning about a missing courier bringing intelligence back "
        + "from Rohan. They plan to sack and burn the place once they have "
        + "that information!"));
    set_alarm(11.0, 0.0, &command("worry"));
    set_alarm(12.0, 0.0, &command("say Fortunately, the courier, an orc "
        + "named Grsnick, did not take his delivery to Orthanc after checking "
        + "in at the gate this morning! If one of us can break free and find "
        + "him first, we can save Rohan!"));
    set_alarm(17.0, 0.0, &command("say If you can get out, find this orc, "
        + "kill him, and bring the missive back to me. Please help us, for "
        + "time is pressing!"));

    set_alarm(22.0, 0.0, &command("say One of the guards dropped a clue to "
        + "Grsnick's whereabouts when he came in to whip us this morning."));

    TP->add_prop(GOODIE_IGARD_QUEST, 1);
    START_QUEST(TP, "IGARD COURIER QUEST");

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
    set_alarm(28.0, 0.0, &command("say I don't know what that clue means, "
        + "but hopefully you will figure it out. Please hurry!"));

    return "";
}


void
give_it_back(object ob, object from)
{
    string what, who;
    what = (ob->query_name());
    who = from->query_real_name();
    command("give " + what + " to " + who);
    command("say Why would I want that?");
}


void
accept_missive(object ob, object from)
{
    string who;

    who = from->query_real_name();
    actor = TP;

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("say Who is there? Come out where I can see you!");
        return;
    }

    if ((PRISONER_ENEMY) && (!WIZARD))
    {
        command("scowl " + TP->query_real_name());
        command("say You think I would trust a villain like you?");
        command("say Die, traitor!");
        command("kill " + who);
        return;
    }

    if (TP->test_bit("gondor", IGARD_GROUP, IGARD_COURIER_BIT))
    {
        TO->command("say Hmm. You seem to have helped us already!");
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
    }

    if (BIQ)
    {
        TO->command("say Traitor! You are working for the Enemy!");
        TO->command("kill " + who);
        return;
    }

    if (BADDIE)
    {
        TO->command("say I'll not trust the likes of you, villain.");
        TO->command("kill " + who);
        return;
    }

    if (FIC)
    {
    command("say Ah! You retrieved the missive beyond all hope!");
    set_alarm(1.0, 0.0, &command("smile"));
    set_alarm(2.0, 0.0, &command("say Here, take this phony missive to "
        + "Saruman in its stead."));

    setuid();
    seteuid(getuid());
    clone_object(IGARD_QUEST_OBJ + "prisoner_missive.c")->move(TP);

    set_alarm (4.0, 0.0, &actor->catch_tell("The prisoner hands you a small "
        + "missive.\n"));
    set_alarm (4.0, 0.0, &tell_room(environment(), "The prisoner hands " 
        + QTNAME(actor) + " a small missive.\n", actor));

    set_alarm(5.0, 0.0, &command("grin"));

    ob->remove_object();

    set_alarm(7.0, 0.0, &command("thank " + who));
    return;
    }

    else
    {
    command("say Why would I want this?\n");
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;

    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!objectp(from))
    {
    return;
    }

    if (ob->id("_igard_courier_missive_"))
    {
        set_alarm(1.0, 0.0, &accept_missive(ob, from));
        return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
}


