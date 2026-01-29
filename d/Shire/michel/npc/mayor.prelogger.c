#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE
#include BITS_FILE

inherit HOBBITMAKER;

#define QUEST_NAME "bumbleberry"

/* Function prototypes */
void reward_good_quest(object player);
void reward_evil_quest(object player);
void test_pie_quest(object player);

void
create_hobbit()
{
    set_type(CITIZEN);
    set_power(75);
    set_name("will");
    set_living_name("will");
    set_family_name("Whitfoot");
    set_title("Mayor of the Shire");
    add_name("mayor");
    add_adj(({"flabby","pasty-faced"}));
    set_gender(G_MALE);
    set_long("Meet Will Whitfoot, the current Mayor of the Shire.  "+
      "He deals with all the problems of the Shire and sets out Patrols "+
      "Bounders and Postmen.  Ask him if you have any problems or if "+
      "you can provide him with a service.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 120*1000);
    add_prop(CONT_I_HEIGHT, 60);

    disable_all_noise();
    set_chat_time(9);
    add_chat("Who should I send to the South Bounds this week...hmm...");
    add_chat("The orcs are gathering around Bree, I hear.  I'm glad it's not us.");
    add_chat("I was elected Mayor just last year, so I have six years left.");
    add_chat("Good day, do you know anything about pies?");
    add_chat("I haven't eaten in what must be minutes.");
    add_chat("I love bumbleberry pie, especially if it has frosting.");
    add_chat("A Shirriffe went east about a month ago and hasn't returned.");
    set_act_time(5);
    add_act("emote turns through the pages in a bound book.");
    add_act("emote scribbles something on a crumpled piece of paper.");
    add_act("smile slee");
    add_act("chuckle");
    add_act("emote seems to be thinking of food.");
    add_act("greet all");

    set_cchat_time(9);
    add_cchat("Hold still and I'll really give it to you!");
    add_cchat("Why me? All I want in life is bumbleberry pie!");
    add_cchat("Guards! Guards! Guards!");
    add_cchat("I may not look dangerous, but I carry a big stick!");
    add_ask(({"shirriffe","east"}),VBFC_ME("ask_shirriffe"));
    add_ask(({"help","task","job","quest"}),VBFC_ME("ask_help"));
    add_ask(({"pie","pies","bumbleberry pie"}),VBFC_ME("ask_pie"));
    set_default_answer("The Mayor looks a bit confused by your question.\n");
}

void
arm_hobbit()
{
    object flail;
    FIXEUID

    flail = clone_object(MICH_DIR + "wep/stick");
    flail->move(TO);
    command("wield all");
}

string
ask_shirriffe()
{
    command("say You might look for the old woman Petunia in ");
    command("say her cottage on the other side of the East Road.");
    command("say It's her son that's missing, she'll be able to help you.");
    command("sigh");
    command("say Sometimes this job just isn't any fun.");
    return "";
} 


string
ask_help()
{
    command("say I sure could go for a bumbleberry pie!");
    command("sigh drea");
    command("say I would reward well anyone giving me a bumbleberry pie!");
    return "";
}

string
ask_pie()
{
    object plate;


    if(TP->query_prop("asked_for_plate"))
    {
	command("sigh");
	command("say I've already given you a plate.");
	command("say Snap to it!");
	return "";
    }

    plate = clone_object(MICH_DIR + "obj/pie_plate");
    plate->move(TO);
    command("say I love bumbleberry pies, and will do anything to get one!");
    command("drop plate");
    command("say Use this.");
    TP->add_prop("asked_for_plate",1);
    command("giggle misc");
    return "";
}

void
reward_evil_quest(object player)
{
    object death, plate;

    player->remove_prop("_had_the_pie_cooked_");
    player->set_bit(WESTERN_GROUP,BUMBLEBERRY_BIT);
    player->add_exp(BUMBLEBERRY_EXP,0);
    player->add_prop("_i_need_evil_align_",1);
    seteuid(getuid(TO));
    log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
      CAP(player->query_real_name()) + " rewarded with "+BUMBLEBERRY_EXP+" exp, "+
      "<"+player->query_average_stat()+"> avg stats.\n");
    tell_object(player,"You feel much more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
    command("eat pie");

    plate = clone_object(MICH_DIR + "obj/pie_plate");
    plate->add_prop(OBJ_I_VALUE, 134); /* Evil has its rewards */
    plate->move(TO);
    death = clone_object(MICH_DIR + "obj/bumbleberry_poison");
    death->move(TO);
    death->start_poison();
    command("emote begins to look a little sick.");
    return;
}

void
reward_good_quest(object player)
{

    player->remove_prop("_had_the_pie_cooked_");
    player->set_bit(WESTERN_GROUP,BUMBLEBERRY_BIT);
    player->add_exp(BUMBLEBERRY_EXP,0);
    seteuid(getuid(TO));
    log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
      CAP(player->query_real_name()) + " rewarded with "+BUMBLEBERRY_EXP+" exp, "+
      "<"+player->query_average_stat()+"> avg stats.\n");
    tell_object(player,"You feel much more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
    return;
}
void test_pie_quest(object player)
{
    int ix;
    ix = player->test_bit("Shire",WESTERN_GROUP,BUMBLEBERRY_BIT);
    if(player->test_bit("Shire",WESTERN_GROUP,BUMBLEBERRY_BIT))
    {
	command("say Yummy, thanks!  But this is not the first pie");
	command("say You've brought me.  Thanks anyway!");
	command("thank "+player->query_real_name());
	command("eat pie");
	return;
    }
    if(player->query_alignment() < -100)
    {
	command("say This pie looks MARVELOUS!!!");
	command("eat pie");
	command("pat "+player->query_real_name());
	reward_evil_quest(player);
	return;
    }

    command("say Lovely pie!");
    command("eat pie");
    command("emote rubs his stomach in sheer delight.");
    reward_good_quest(player);
    return;
}


void
enter_inv(object what, object from)
{
    int ran;

    ::enter_inv(what, from);

    if (!from)
	return;

    if(from->query_alignment() < -100)
    {
	if(what->query_prop("_poisoned_bumbleberry_pie_"))
	{
	    set_alarm(1.0,0.0,"test_pie_quest",from);
	    return;
	}
	command("say I wouldn't take anything from the likes of you!");
	what->move(from,1);
	command("emote returns the unwanted gift.");
	return;
    }

    if(what->query_prop("_i_am_bumbleberry_pie_"))
    {
	if(from->query_prop("_had_the_pie_cooked_"))
	{
	    set_alarm(1.2,0.0,"test_pie_quest", from);
	    return;
	}
	command("say Who gave you this pie? It's all mushy now, I don't");
	command("say reward mushiness.");
	command("eat pie");
	command("burp");
	command("smile sli");
	return;
    }

    command("say What is this?  Why would I want a "+what->short()+"?");
    command("drop "+ what->query_name());
    return;

}
