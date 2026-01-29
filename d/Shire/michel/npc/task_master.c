/*
 * 2005/05/16 Last update
 * 2011/07/21 Lavellan - Now destructs hay, won't get full and can't be stolen
 */

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit SHIRE_MONSTER;

#include MONEY_FILE

#define QUEST_NAME "hay"

// Prototypes
//void test_locket_quest(object player);
void test_locket_quest(object player, object obj);


void
create_shire_monster()
{
    if (!IS_CLONE)
	return;	

    set_living_name("_isembold_");
    set_name("isembold");
    set_title("Brambleberry");
    set_race_name("hobbit");
    set_long("This is one of the elderly hobbits living in Michel Delving. It looks like "
      +"he has been out travelling and adventuring a lot.\n");
    set_adj(({"tired","friendly"}));
    set_stats(({30,30,40,80,100,30}));
    MAKE_MONEY;
    set_alignment(350);

    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    set_chat_time(2);
    add_chat("I am too old to work the fields.");
    add_chat("A bit of wisdom comes in handy from time to time.");
    add_chat("My poor pony is hungry.");
    add_chat("Have you seen our inn here in Michel Delving?");

    add_ask(({"task","help","quest","job","pony"}),VBFC_ME("give_task"));

    set_introduce(1);

    add_equipment(BREE_DIR + "arm/ltunic");
}

int
introduce_me(string who)
{
    object obj = find_player(who);
    int    ran;

    if (::introduce_me(who))
    {
	ran = random(3);
	if (ran == 0)
	{
	    command("say Good day " + obj->query_cap_name() +", are you looking for a task here?");
	    command("smile " + who);
	    command("shake " + who);
	}
	if (ran == 1)
	{
	    command("bow to " + who);
	    command("say Welcome " + CAP(who) +", can i help you with something?");
	    command("smile serious " + who);
	}
	if (ran == 2)
	{
	    command("say Greetings " + CAP(who) + ".");
	    command("bow deeply to " + who);
	}
    }
}


void 
//test_locket_quest(object player)
test_locket_quest(object player, object obj)
{
    if (!player->query_prop("_i_asked_for_my_hay_"))
    {
	command("shout You stole this!");
	command("say I may be poor, but I won't feed my pony with stolen hay.");
	command("say Get out, you scoundrel.");
        command("emote kicks you away.");
        obj->remove_object();
	player->move_living("X","/d/Shire/michel/fairroad2",1);
	return;
    }
    if (!REWARD_QUEST(player, QUEST_NAME))
    {
	command("say I appreciate the thought, but you already helped me.");
        obj->remove_object();
	return;
    }
    command("stables");
    //command("drop hay");
    command("drop hays");
    command("get two gold coins");
    command("back");
    command("say Thank you, now my pony won't have to go without food."); 
    command("say This is for you.");
    if (!command("give two gold coins to "+ player->query_real_name()))
	command("drop two gold coins");
    player->remove_prop("_pony_hay_quest");
    player->remove_prop("_i_asked_for_my_hay_");
    tell_object(player,"You feel a little more experienced!\n");
}


string 
give_task()
{
    if (CHECK_QUEST(TP, QUEST_NAME))
    {
	command("say You've already helped me, though.");
	return "";
    }
    if (TP->query_prop("_pony_hay_quest"))
    {
	command("glare " + TP->query_name());
	command("say Well, git. I've told you what to do!");
	return "";
    }
    command("say My pony is hungry, please bring me some fresh Shire hay to feed him.");
    TP->add_prop("_pony_hay_quest",1);
    return "";
}

void
drop_junk(object o)
{
    command("say This isn't what I asked for.");
/*
    if (function_exists("create_object", o) == "/std/heap")
    {
        if (o->num_heap() == 1)
            command("drop "+o->singular_short());
        else
            command("drop "+o->num_heap()+" "+plural_short());
    }
    else
*/
        command("drop "+o->query_name());
}

public void
enter_inv(object obj, object from)
{ 
    ::enter_inv(obj, from);

    if (!living(from))
        return;
    if (obj->id("_pony_hay_")) 
        //set_alarm(1.0, 0.0, &test_locket_quest(from));
        set_alarm(1.0, 0.0, &test_locket_quest(from, obj));
    else
    {
        set_alarm(1.0, 0.0, &drop_junk(obj));
        return;
    }
}

