/*
 *   /d/Gondor/rohan/isengard/igard/npc/eraedan.c
 *
 *   A rohirrim involved in a tour into Isengard.
 *
 *   Alto, 24 August 2002
 */


#pragma strict_types

inherit "/d/Gondor/std/monster";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <math.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "../igard_defs.h"

int quest_in_progress = 0;

int give_tour();
int reward_tour(object from);

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
    set_adj("tall");
    set_adj("flaxen-haired");
    set_living_name("eraedan");
    set_name("eraedan");
    add_name("rohirrim");
    add_name("soldier");
    set_race_name("human");

    set_title("of Rohan");
    set_long("The tall man looks nervously up and down the road with something of a hunted "
        + "look. His height and flaxen hair clearly mark him a man of Rohan, and yet he wears "
        + "the armours of the White Hand. You notice that he is injured. Perhaps he could use "
        + "your help?\n");

    rnd = random(60);
    default_config_npc(120+rnd/2);
    set_base_stat(SS_DIS, 140 + rnd);
    set_alignment(350+rnd*10);
    set_skill(SS_WEP_SWORD, MIN(100, 75 + rnd));
    set_skill(SS_WEP_POLEARM, MIN(100, 75 + rnd));
    set_skill(SS_PARRY, MIN(100, 75 + rnd));
    set_skill(SS_DEFENCE, MIN(100, 75 + rnd));
    add_prop(CONT_I_HEIGHT,170+rnd);
    add_prop(CONT_I_WEIGHT,85000+rnd*500);
    add_prop(CONT_I_VOLUME,80000+rnd*500); 
    
    set_restrain_path("/d/Gondor/rohan/road/");
    set_monster_home("/d/Gondor/rohan/road/er1");
    set_random_move(10);


    setuid();
    seteuid(getuid());

    clone_object(IGARD_WEP + "i_largescim.c")->move(TO);
    clone_object(IGARD_ARM + "i_chainmail.c")->move(TO);
    clone_object(IGARD_ARM + "i_greaves.c")->move(TO);
    clone_object(IGARD_ARM + "i_helmet.c")->move(TO);


    set_chat_time(15);
    add_chat("Beware the voice of Curunir! He can make you do .. terrible things.");
    add_chat("I cannot go back in. They have me marked.");
    add_chat("The gates of Isengard should not be passed lightly!");
    add_chat("I now know that Orthanc conspires against us. Alas, Theoden sleeps.");
    add_chat("I must warn my kinsmen about Curunir! But one close to the ear of Theoden "
        + "is not to be trusted. How shall I be heard? Alas, I must try.");
    add_chat("Someone must go in my stead, someone unmarked by the gate guards.");
    add_chat("They are forging enough armour for a terrible host, I tell you.");
    add_chat("If only I had evidence! Even Grima could not say against me.");
    add_act("They shot me in the side as I tried to enter this morning. It slows me, and I have "
        + "need of haste.");

    set_cchat_time(5);
    add_cchat("Curse you! Do you hunt me in the name of the Hand?");
    add_cchat("I have urgent news for my King. I have no time to kill you! Alas I must.");
    add_cchat("Were I not injured already, you would certainly meet your doom this day!");
    add_chat("Rohan! Rohan!");

    set_act_time(7);
    add_act("worry");
    add_act("sigh tiredly");
    add_act("sweat");
    add_act("stare");
    add_act("emote glances down the road with a hunted look.");
    add_act("emote looks to the north and sighs wearily.");
    add_act("emote grasps his side and moans. Blood seeps through his fingers.");


    remove_prop(LIVE_I_NEVERKNOWN);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);


    set_default_answer( ({ "say What? I have no time for gibberish.", "boggle" }) );


    add_ask_item(({"saruman", "curunir", "wizard", "white hand"}), "say Hsst! Speak "
        + "not that name on the open road so loudly! Curunir, or as he is known "
        + "by the men of Gondor, Saruman, has ears everywhere! "
        + "And his voice, ah beware that voice, for it is supple and persuasive, "
        + "yet I have learned it is treacherous! "
        + "I must warn my King!");
    add_ask_item(({"voice", "voice of saruman", "saruman's voice"}), "say He "
        + "can make you believe up is down, black is white, good is evil. "
        + "Beware the voice of Saruman!");
    add_ask_item(({"wound", "injury"}), "say I took an arrow this morning at the "
        + "south gate of Isengard. I was marked by the archers. They knew I was a "
        + "spy. No doubt that scoundrel Grima sent news ahead.");
    add_ask_item(({"king", "theoden", "king theoden", "king of rohan"}), "say My "
        + "Lord, Theoden King, has fallen under the spell of Grima Wormtongue, they "
        + "say. I now know where the Worm has learned his forked tongue.");
    add_ask_item(({"grima", "wormtongue", "worm", "grima wormtongue"}), "say The "
        + "slinking worm is the advisor to my King. Long have I suspected him of "
        + "treason, but only now do I know how deep it runs. I must get to my King, "
        + "but without evidence my case is lost already.");
    add_ask_item(({"evidence", "proof"}), "say I must have evidence to present my King. "
        + "A large army masses in Isengard, but I must bring proof. If only someone "
        + "would help me. I barely have the strength to reach Meduseld.");
    add_ask_item(({"army", "orcs", "uruks", "orc", "uruk"}), "say A terrible army "
        + "of orcs and some new breed of orc, the uruks, masses within the ring wall of "
        + "Isengard. If you do not believe me, go and see yourself. You may not live "
        + "to tell about it, though!");
    add_ask_item(({"meduseld"}), "say Meduseld is the great hall of where my King "
        + "holds court in Edoras. Many years have passed, however, since any grand "
        + "feast was held there. Grima sees to that.");
    add_ask_item(({"edoras"}), "say The home of my people. If you follow this road "
        + "you will pass by it. Beware, though, the men of Rohan have grown suspcious, "
        + "as is wise in these times of peril.");
    add_ask_item(({"quest"}), "say Indeed I am on a quest to reach my King. If only "
        + "someone would help me!");
    add_ask_item(({"reward"}), "say I have neither the time nor patience for barter. "
        + "If you have what I need, give it to me!");
    add_ask_item(({"help"}), "@@give_tour");

    command("wield all");
    command("wear all");

    refresh_mobile();

}


public void
return_giggle(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        command("say So empathetic, giggling at an injured man.");
        break;
    case 1:
        command("peer . "+ actor->query_real_name());
        break;
    case 2:
        command("scowl . " + actor->query_real_name());
        break;
    default:
        break;
    }
}

public void
return_laugh(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
  	 return;

    switch (random(3))
    {
    case 0:
        command("say How can you laugh when Rohan is in such peril?");
	       break;
    case 1:
	       command("frown . " + actor->query_real_name());
	       break;
    case 2:
        command("say I used to laugh, until I passed the gates of Isengard.");
	       command("sigh .");
	       break;
    default:
        break;
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "giggle":
	           set_alarm(2.0, 0.0, &return_giggle(actor));
	           break;
        case "laugh":
	           set_alarm(2.0, 0.0, &return_laugh(actor));
	           break;
    }
}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));

    if ((!objectp(pl)) || (objectp(query_attack())))
        return;

    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}


void
give_it_back(object ob, object from)
{
    string what, who;
    what = (ob->query_name());
    who = from->query_real_name();
    command("give " + what + " to " + who);
    command("say Why would I want something like this?");
}

void
reward_tour(object from)
{
    object player;
    string who;

    player = this_player();

    who = from->query_real_name();

    if (!present(from, ENV(TO)))
        return;

    if (from->test_bit("gondor", IGARD_GROUP, IGARD_EVIDENCE_BIT))
        return;

    from->set_bit(IGARD_GROUP, IGARD_EVIDENCE_BIT);
    from->add_exp_quest(IGARD_EVIDENCE_EXP);
    from->catch_msg("You feel more experienced!\n");
    from->remove_prop(IGARD_EVIDENCE_TOURING);
    LOG_QUEST(from, IGARD_EVIDENCE_EXP, "IGARD EVIDENCE TOUR");
    
    return;
}


void
give_tour()
{
    string who;
    object from;
    
    from = this_player();
    
    who = from->query_real_name();

    command("say I suppose you may be trusted. I have little other choice.\n");


    if (from->test_bit("gondor", IGARD_GROUP, IGARD_EVIDENCE_BIT))
    {
        TO->command("say Indeed you have already proven your fidelity to "
            + "our cause. I thank you again, but require no more assistance "
            + "from you!");
        return;
    }

    if (from->query_prop(IGARD_EVIDENCE_TOURING))
    {
        command("say Please friend, speed is needed. Make haste!");
        return;
    }


    if(quest_in_progress)
        TO->command("say Another has already left to help me this day, but perhaps that "
            + "one has fallen to the gate guards as well. Perhaps you will survive where "
            + "your predecessor did not.");

    command("emote looks nervously down the road in search of pursuit.");
    set_alarm(1.0, 0.0, &command("sigh"));
    set_alarm(3.0, 0.0, &command("say For some time we have suspected the wizard Curunir, "
        + "or Saruman, to be up to some devilry."));
    set_alarm(6.0, 0.0, &command("frown"));
    set_alarm(7.0, 0.0, &command("peer carefully " + who));
    set_alarm(9.0, 0.0, &command("say Perhaps you have seen the maggot folk coming and "
        + "going, or smelt the cruel vapours rising from the plain of Isengard. I was sent "
        + "to find proof of this. As if such things are not evidence enough."));
    set_alarm(14.0, 0.0, &command("say Alas the ear of the King is held by one named Grima, "
        + "who my people have come to name 'Wormtongue', for indeed his voice has wormed "
        + "its way into the counsel of my Lord."));
    set_alarm(17.0, 0.0, &command("worry"));
    set_alarm(19.0, 0.0, &command("say His soothing voice has put my Lord, once a mighty "
        + "warrior, into the slumber of complacency!"));
    set_alarm(22.0, 0.0, &command("grumble"));
    set_alarm(23.0, 0.0, &command("say I went to Isengard, dressed in the armours of an orc "
        + "I slew near the wall. I passed the gate, and there I saw horrors beyond "
        + "our worst fears. In my shock and fear I fled the place, trembling and shaking, "
        + "although trying my best to hide it from the gate attendants."));
    set_alarm(25.0, 0.0, &command("shiver"));
    set_alarm(26.0, 0.0, &command("say Later, when I had regained my composure, I returned, "
        + "thinking to secure some written evidence of the massive armouries I observed there."));
    set_alarm(30.0, 0.0, &command("wince"));
    set_alarm(31.0, 0.0, &command("say Alas I had been marked as a spy, and arrows rained down upon "
        + "me from the wall. One bit especially deep into my side."));
    set_alarm(35.0, 0.0, &command("emote presses his hand more firmly against the wound "
        + "at his side."));

    from->add_prop(IGARD_EVIDENCE_TOURING, 1);
    START_QUEST(from, "IGARD EVIDENCE TOUR");
    set_alarm(36.0, 0.0, &command("say Please, I beg of you, go in my stead. There is an armoury "
        + "somewhere within that fortress. From the many foul orcs and uruks housed there, it "
        + "must contain vast stores of weapons and armours."));
    set_alarm(40.0, 0.0, &command("say Go there and return to me with evidence that I may present "
        + "to my King."));
    set_alarm(41.0, 0.0, &command("say It must be written evidence! No other will serve to "
        + "gainsay the voice of the Wormtongue!"));
    set_alarm(44.0, 0.0, &command("wave"));

    quest_in_progress = 1;
    return;
}


void
accept_evidence(object ob, object from)
{
    string who;

    who = from->query_real_name();

    if (from->test_bit("gondor", IGARD_GROUP, IGARD_EVIDENCE_BIT))
    {
        TO->command("say Thank you, but the evidence you gave me already will suffice.");
        set_alarm(1.0, 0.0, &give_it_back(ob, from));
        return;
    }

    if (from->query_prop(IGARD_EVIDENCE_TOURING))
    {
    command("say Ah! What is this?");
    set_alarm(1.0, 0.0, &command("smile"));
    set_alarm(2.0, 0.0, &command("say This is excellent! Not even Grima can soothe "
        + "Theoden King after he reads this!"));
    set_alarm(5.0, 0.0, &command("cheer"));

    ob->remove_object();

    set_alarm(7.0, 0.0, &command("thank " + who));
    set_alarm(9.0, 0.0, &reward_tour(from));
    return;
    }

    else
    {
    command("say I do not remember asking you for this! Who are you, and what do you want?\n");
    set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;

    }
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from))
        return;

    if (ob->id("_i_evidence_obj_"))
    {
        set_alarm(1.0, 0.0, &accept_evidence(ob, from));
        return;
    }

    set_alarm(1.0, 0.0, &give_it_back(ob, from));
}


public int
query_knight_prestige() { return -30; }

