// 2000/04/10 Last update
// 2011/07/18 Lavellan - fixed adjectives

#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

/* Function prototypes */
void test_pie_quest(object player);

//#define tome COMMON_OBJ+"spelltome";

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
    //add_adj(({"flabby","pasty-faced"}));
    set_adj(({"flabby","pasty-faced"}));
    set_gender(G_MALE);
    set_long("Meet Will Whitfoot, the current Mayor of the Shire.  "+
      "He deals with all the problems of the Shire and sets out Patrols "+
      "Bounders and Postmen.  Ask him if you have any problems or if "+
      "you can provide him with a service.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(CONT_I_WEIGHT, 120*1000);
    add_prop(CONT_I_HEIGHT, 60);

/*
    disable_all_noise();
*/
    set_act_time(9);
    add_act("say Who should I send to the South Bounds this week...hmm...");
    add_act("say The orcs are gathering around Bree, I hear.  I'm glad it's not us.");
    add_act("say I was elected Mayor just last year, so I have six years left.");
    add_act("say Good day, do you know anything about pies?");
    add_act("say I haven't eaten in what must be minutes.");
    add_act("say I love bumbleberry pie, especially if it has frosting.");
    add_act("say A Shirriffe went east about a month ago and hasn't returned.");
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
    add_ask(({"tome","dusty tome","magic tome"}),VBFC_ME("ask_tome"));
    add_ask(({"testtome","tometest"}),VBFC_ME("ask_test"));
    set_default_answer("The Mayor looks a bit confused by your question.\n");
}

void
introduce_hobbit(string str)
{
    if (!present(str,ENV(TO)))
	return;

    command("introduce myself to "+str);
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
ask_tome()
{
    object spelltome;

    if (CHECK_QUEST(TP, "spelltome"))
    {
        command("say Seems you've lost your tome, here's a new one.");
        command("emote gives you a new spelltome.");
        spelltome = clone_object(COMMON_OBJ+"spelltome");
        spelltome->move(TP);
	return "";
    }
    command("say You haven't done that quest.\n");
    return "";
}

string
ask_test()
{
    if (!CHECK_QUEST(TP, "spelltome"))
    {
        command("say You haven't done that quest.\n");
	return "";
    }
    command("say Seems you've lost your tome, here's a new one.");
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

void test_pie_quest(object player)
{
    object plate, death;

    if (!REWARD_QUEST(player, "bumbleberry"))
    {
	command("say Yummy, thanks!  But this is not the first pie");
	command("say You've brought me.  Thanks anyway!");
	command("thank "+player->query_real_name());
	command("eat pie");
	return;
    }

    player->remove_prop("_had_the_pie_cooked_");
    player->catch_msg("You feel much more experienced.\n");

    if(player->query_alignment() < -100)
    {
	command("say This pie looks MARVELOUS!!!");
	command("eat pie");
	command("pat "+player->query_real_name());
	player->add_prop("_i_need_evil_align_",1);

	plate = clone_object(MICH_DIR + "obj/pie_plate");
	plate->add_prop(OBJ_I_VALUE, 134); /* Evil has its rewards */
	plate->move(TO);
	death = clone_object(MICH_DIR + "obj/bumbleberry_poison");
	death->move(TO);
	death->start_poison();
	command("emote begins to look a little sick.");
	return;
    }

    command("say Lovely pie!");
    command("eat pie");
    command("emote rubs his stomach in sheer delight.");
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
