#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include HOBBIT_FILE

inherit HOBBITMAKER;

/* Function prototypes */
void test_mapping_quest(object player);
string give_task();
string give_map_task();
void give_item_back(object obj, object from);

void
create_hobbit()
{
    set_type(SHIRRIFFE);
    set_power(70);
    set_gender(G_MALE);
    set_living_name("puddifoot");
    set_name("puddifoot");
    set_family_name("Brandybuck");
    set_title("the Chief Shirriffe of the North Farthing");
    set_long("This is the Chief Shirriffe of the North Farthing. "+
      "He looks as if he has a lot on his mind- perhaps you could help?\n");
    set_adj(({"troubled","weary"}));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);

    disable_all_noise();
    set_chat_time(2);
    add_chat("The Shirriffes could use a good hand like you.");
    add_chat("I hope old Pott returns soon.");
    add_chat("If there's one thing I hate more than warm beer it's orcs.");
    add_chat("Sometimes I wish for excitement to happen.");
    add_chat("That encampment of orcs weighs heavily on my mind.");
    add_chat("If only we had a map!");
    add_chat("Hail Shire!");
    add_chat("How are you today?");

    add_ask(({"help","quest","map","orc","camp"}),VBFC_ME("give_map_task"));
    add_ask(({"old pott","pott","another problem"}),VBFC_ME("give_task"));
    add_ask(({"for reward","reward","prize","my prize"}),VBFC_ME("ask_reward"));
}

void
arm_hobbit()
{
    object  sword, tunic;

    FIXEUID;
    sword = clone_object(COMMON_DIR + "weapon/shortsword");
    sword->move(TO);
    command("wield all");
    tunic = clone_object(BREE_DIR + "arm/" + "ltunic");
    tunic->move(TO);
    command("wear all");

}

void
introduce_hobbit(string who)
{
    object obj;
    int    ran;

    if (obj = present(who,environment()))
    {
	ran = random(3);
	if (ran == 0)
	{
	    command("say Good day " + obj->query_cap_name() +", are you new in the area?");
	    command("introduce me");
	    command("smile " + who);
	    command("shake " + who);
	}
	if (ran == 1)
	{
	    command("bow to " + who);
	    command("introduce me");
	    command("say Welcome " + CAP(who) +", could you help me with something?");
	    command("smile serious " + who);
	}
	if (ran == 2)
	{
	    command("introduce me");
	    command("say Greetings " + CAP(who) + ".");
	    command("bow deeply to " + who);
	}
    }
}


void 
test_feather_quest(object player)
{
    if (!player->query_prop("_i_got_the_feather"))
    {
	command("say Did you kill Old Pott?");
	command("say Where did you get this? I won't accept it.");
	command("drop feather");
	return;
    }
    if (!REWARD_QUEST(player, "feather"))
    {
	command("say I appreciate the thought, but you already helped me.");
	return;
    }
    command("swear");
    command("say Well, I guess that is that then.");
    command("say Old Pott is dead and will never return.");
    command("sigh");
    command("say Well, thank you for helping, though it is grevious news.");
    command("congratulate " + player->query_name());
    player->remove_prop("_feather_quest");
    tell_object(player, "You feel much more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n", ({player}));
}

void 
test_mapping_quest(object player)
{
    if (!REWARD_QUEST(player, "mapping"))
    {
	command("say Hmmfh. You've already helped me.");
	return;
    }
    command("say Nice work there!");
    command("pat "+player->query_real_name()+ " back");
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n", ({player}));
}

string 
give_task()
{
    if (!CHECK_QUEST(TP, "feather"))
    {
	if (TP->query_prop("_feather_quest"))
	{
	    command("eyebrow " + TP->query_name());
	    command("say I've told you all that I know.");
	    command("say Please, go and find old Pott!");
	    return "";
	}
	command("say Old Pott, a shirriffe of these parts has been missing for days.");
	command("say His last assignment was to investigate an encampment of orcs...");
	command("say We fear the worst, but if you find him prisoner, return him!");
	command("say Though we have not much hope of that.");
	TP->add_prop("_feather_quest",1);
	return "";
    }
    else 
    {
	command("say You've done all you could, and I thank you again.\n");
	return "";
    }
}

string 
give_map_task()
{
    if (!CHECK_QUEST(TP, "mapping"))
    {
	if (TP->query_prop("_mapping_quest"))
	{
	    command("pat " + TP->query_name());
	    command("say I've told you all I that I know.");
	    command("say Are you not going to map the encampment?");
	    return "";
	}
	command("say We have seen fires coming from the hills for weeks now.");
	command("say Finally we understand what they mean- an encampment of orcs.");
	command("say We need more information before we can even think of fighting.");
	command("say I would like you to make a map of the camp. I'll reward you well.");
	command("say Just come back and ask for your prize.");
	TP->add_prop("_mapping_quest",1 + random(2));
	return "";
    }
    else 
    {
	command("say Say, could you help me with another problem?");
	command("say If so, remember to ask me about Old Pott.");
	return "";
    }
}

string 
ask_reward()
{
    if (!TP->query_prop("_i_mapped_the_orc_camp"))
    {
	command("say But your map is not complete!");
	command("say Even I have seen that much. I know you can do better!");
	command("smile");
	return "";
    }
    test_mapping_quest(TP);
    return "";
}

public void
enter_inv(object obj, object from)
{ 
    ::enter_inv(obj, from);
    if (!living(from))
	return;
    if (obj->id("_pott_feather_")) 
	test_feather_quest(from);
    else if (obj->id("_mapping_quest_map_")) 
	test_mapping_quest(from);
    else
	set_alarm(1.0, 0.0, &give_item_back(obj, from));
}

void
give_item_back(object obj, object from)
{
    command("say I have no need for such things.");
    command("give "+OB_NAME(obj)+" to "+from->query_real_name());
}
