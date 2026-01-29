/*
 * /d/Shire/michel/npc/mardil.c
 *
 * A dying hobbit who longs to see his son.
 *
 * Glaurung 4-98
 */

inherit "/d/Shire/std/monster";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bits.h"
#include "/d/Shire/common/trollsh/new/defs.h"
#include <stdproperties.h>

//** Prototypes **//
void coin_response();
void favorable_response(object o, object p);
void junk_response(object o, object p);
void reward_dwarven_friend_quest(object o);
void suspicious_response(object o, object p);

void
create_shire_monster()
{
    FIXEUID

    set_living_name("_mardil_");
    set_name("mardil");
    set_race_name("hobbit");
    set_long("This poor hobbit looks like a bag of bones. He "+
        "seems incurable by medicine, perhaps he is holding "+
        "on for some news?\n");
    set_adj(({"weak","scrawny"}));
    set_stats(({30,30,40,80,100,30}));
    set_alignment(350);  
    set_introduce(1);
    set_gender(G_MALE);

    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_chat_time(7);
    add_chat("Where could he be?");
    add_chat("If you ever reach my age, I hope you will feel better than I do.");
    add_chat("Medicine is no good for me, I just want to see my son before I go.");
    add_chat("I don't mind dying so much as this pain.");

    set_act_time(5);
    add_act("emote rolls over in bed.");
    add_act("cough");
    add_act("sigh sadl");
  
    add_ask(({"son","troll","help","quest","job","task"}),VBFC_ME("ask_stuff"));
//  add_ask(({"Arthad","arthad"}),VBFC_ME("ask_arthad"));
    add_ask(({"gollin"}),VBFC_ME("give_dwarven_friend_quest"));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (function_exists("create_coins", ob) == "/std/coins")
    {
        set_alarm(1.0, 0.0, coin_response);   
        return;
    }

    if (member_array(SHIRE_DWARVEN_FRIEND_LETTER, ob->query_names()) < 0)
    {
        set_alarm(1.0, 0.0, &junk_response(ob, from));
        return;
    }

    if (!TP->query_prop(PLAYER_I_GOT_DWARVEN_LETTER))
    {
        set_alarm(1.0, 0.0, &suspicious_response(ob, from));
        return;
    }

    set_alarm(1.0, 0.0, &favorable_response(ob, from));
}

void
coin_response()
{
    command("say Thanks!");
    command("say I'll save this for Petunia.");
}

void
junk_response(object ob, object from)
{
    command("say What would I want with this?");
    if (objectp(present(from, ENV(TO))))
        command("give "+ob->query_name()+" to "+from->query_real_name());
    else
        command("drop "+ob->query_name());
}

void
suspicious_response(object ob, object from)
{
    command("say How did you come by this?!");
    command("peer suspic "+from->query_name());
    command("say Arthad must have misplaced my letter.");
    command("sigh");
    command("say It looks like your services are no longer need.");
    TP->add_prop(PLAYER_I_FAILED_MARDIL, 1);
    if (TP->query_prop(DWARVEN_FRIEND_QUEST))
        TP->remove_prop(DWARVEN_FRIEND_QUEST);
    ob->remove_object();
}

void
favorable_response(object ob, object from)
{
    if (from->query_prop(PLAYER_I_FAILED_MARDIL))
    {
        command("say Didn't I tell you I don't want your help anymore!");
        command("emote cumples up the letter and throws it away");
        ob->remove_object();
        return;
    }

    if (!from->query_prop(DWARVEN_FRIEND_QUEST))
    {
        command("say Who are you!? And why do you give me useless items!?");
        command("emote crumples up the letter and throws it away");
        ob->remove_object();
        return;
    }

    command("say Whats this?");
    command("emote puts on a pair of reading spectacles");
    command("emote mouth begins to quiver as he reads the bloodied letter");
    command("say Not Arthad too!");
    command("sob soft");
    command("say Now more than ever I must have my revenge!");
    command("emote crumples up the letter and throws it away");
    command("sigh");
    ob->remove_object();
    set_alarm(itof(random(5)), 0.0, &reward_dwarven_friend_quest(from));
}    

string
ask_stuff()
{
    command("say So you are looking for adventure eh? You think you ");
    command("say know something about my boy, eh?");
    command("say If you do, why don't you ask me about him...by name?");
    command("say But I doubt you know him, he was such a good son.");
    command("sigh");
    return "";
}

string 
give_dwarven_friend_quest()
{
    if (!TP->test_bit("shire", WESTERN_GROUP, BRACELET_BIT))
    {
        command("peer "+TP->query_name());
        command("say Somehow I doubt you know anything about my son!");
        command("say Please leave me to die in peace.");
        return "";
    }

    if (TP->test_bit("shire", WESTERN_GROUP, DWARVEN_FRIEND_BIT))
    {
        command("say Perhaps you can avenge both him and Arthad?");
        return "";
    }

    if (TP->query_prop(PLAYER_I_FAILED_MARDIL))
    {
        command("say You weren't able to help me last time.");
        command("say Please don't waste my time.");
        return "";
    }

    if (TP->query_prop(DWARVEN_FRIEND_QUEST))
    {
        command("glare " + TP->query_name());
        command("say Are you going to help me or not? ");
        command("say My days grow shorter as we speak!");
        return "";
    }

    command("say As you know, I have lost my son to those...those...");
    command("say stinking trolls of the trollshaws!");
    command("emote wipes a tear from his left eye");
    command("say I hired a dwarven friend, Arthad, to take care of them...");
    command("say but he has not returned to me for quite some time.");
    command("sigh");
    command("say I cannot rest until I know his fate and if he completed his job.");
    command("say He probably stopped at the Prancing Pony for a few kegs...");
    command("say and forgot all about me by now.");
    command("smirk");
    TP->add_prop(DWARVEN_FRIEND_QUEST, 1);
    return "";
}

void
reward_dwarven_friend_quest(object quester)
{
    if (objectp(present(quester,ENV(TO))))
    {
        command("say to "+quester->query_real_name()+" Thank you for your help.");
        command("say I wish the news had been better though.");
        command("frown");
    }

    if (quester->test_bit("shire", WESTERN_GROUP, DWARVEN_FRIEND_BIT))
        return;

    quester->set_bit(WESTERN_GROUP, DWARVEN_FRIEND_BIT);
    quester->add_exp(DWARVEN_FRIEND_EXP, 0);
    quester->remove_prop(DWARVEN_FRIEND_QUEST);
    quester->remove_prop(PLAYER_I_GOT_DWARVEN_LETTER);
    log_file(DWARVEN_FRIEND_QUEST_NAME,
        extract(ctime(time()),4,15) + " " +quester->query_name()+
        " rewarded with "+DWARVEN_FRIEND_EXP+" exp, "+
        "<"+quester->query_average_stat()+"> avg stats.\n");
    quester->catch_tell("You feel more experienced!\n");
}
