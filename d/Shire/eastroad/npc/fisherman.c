#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit SHIRE_MONSTER;

#include MONEY_FILE

#define SHIRE_I_ATTACKED_BODULAS  "_shire_i_attacked_bodulas"
#define QUEST_NAME "fishing"

void
create_shire_monster()
{
    if (!IS_CLONE)
	    return;

    set_name("bodulas");
    set_race_name("human");
    set_long("This tired human seems to be staring intently at the water.\n");
    set_adj(({"tired","sturdy"}));
    set_stats(({65,60,70,80,100,90}));
    MAKE_MONEY;
    set_alignment(350);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_DEFENCE,50);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 110);
    set_gender(G_MALE);

    set_chat_time(5);
    add_chat("I sure could go for something cold to drink!");
    add_chat("I am hungry.");
    add_chat("Just look at that fish jump!");
    add_chat("Drat, out of bait again!");
    add_chat("Beware of the orcs. I've seen some around here.");
    add_chat("Those Watchers are odd. They wander and wander but never " +
        "do anything.");
    add_chat("They say there are orcs around.");
    add_chat("I am so hungry.");
    add_chat("Watch out where ever you travel.");

    set_act_time(3);
    add_act("twiddle");
    add_act("sigh");
    add_act("looks for something intersting in the bushes.");



    add_ask(({"task","help","quest","fish","drink"}),VBFC_ME("give_task"));

    set_introduce(1); // We want this NPC to introduce themselves

    add_equipment(BREE_DIR + "arm/ltunic");
}

void
introduce_me(string who)
{
    object obj = find_player(who);
    int ran;

    if (::introduce_me(who))
    {
	ran = random(3);
	if (ran == 0)
	{
	    command("say Good day "+obj->query_cap_name()+", seen any fish here?");
	    command("smile " + who);
	    command("shake " + who);
	}
	if (ran == 1)
	{
	    command("eyebrow " + who);
	    command("say Well met, " + CAP(who) +", can you help me?");
	    command("smile grim " + who);
	}
	if (ran == 2)
	{
	    command("say Greetings " + CAP(who) + ".");
	    command("bow deeply to " + who);
	}
    }
}


string 
give_task()
{
    if (CHECK_QUEST(TP, QUEST_NAME))
    {
        command("say You've already helped me!");
        return "";
    }

    if (TP->query_prop("_fishing_quest"))
    {
        command("eyebrow " + TP->query_name());
        command("say Get going or it will be poor fishing weather soon!");
        return "";
    }

    command("say I hate to beg, but might you have a bite of chicken handy?");
    command("say On such a day, sitting by the riverside I should love ");
    command("say to have a bite of roast chicken, if you could manage it.");
    command("say And be swift, mind!");
    command("smile hungrily");
    TP->add_prop("_fishing_quest",1);
    return "";
}

void
give_second_task(object player)
{
    command("eat chicken");
    command("say Outstanding meal!");
    player->add_prop("_brought_chicken",1);
    command("say Say, you wouldn't have a spot of whiskey on you, would you?");
    command("say I like to wash down my chicken with some stout whiskey.");
    command("sigh dream");
}

void
give_third_task(object player)
{
    command("drink whiskey");
    command("gasp");
    command("say This really takes your breath away.");
    command("say Say, friend, I was just sitting here by the river fishing, ");
    command("say and have run out of bait.  Would you be so kind as to ");
    command("say fetch some worms for me?");
    command("say I will reward you well for some worms!");
    player->add_prop("_brought_whiskey",1);
}

void
give_fourth_task(object player)
{
    command("emote lets the worms wriggle around in his hand.");
    command("say Ah, very nice.");
    command("hmm");
    command("say I have lost my last hook in that drooping birch tree.");
    command("say Don't ask how it got there.");
    command("emote smiles sheepishly.");
    command("say I would appreciate it if you could replace it.");
    command("ponder");
    command("say I promised you a reward for the worms, but I'm broke now.");
    command("say I'll have something for you when you bring the hook.");
    command("smile seriously");
    player->add_prop("_brought_worms",1);
}

void
give_fifth_task(object player)
{
    command("emote holds the hook up to the light and smiles.");
    command("say Thank you so much!");
    command("say I am afraid I am in need still.");
    command("say Someone as good-hearted as you are would not leave ");
    command("say a person in need, would you?");
    command("say My fishing line is broken, could you bring some string?");
    command("say I will reward you well!");
    player->add_prop("_brought_hook",1);
}

void
give_sixth_task(object player)
{
    command("smile");
    command("oops");
    command("say One more thing...");
    command("say My fishing pole is broken, could you bring me something "+
      "to fish with?");
    command("say A stick preferably, not a nice fishing pole...");
    player->add_prop("_brought_string",1);
}

void
test_reward_tasks(object player)
{
    if (!player->query_prop("_brought_chicken"))
    {
        command("say Hey, did you not bring me something?");
        command("scratch");
        command("say I don't know what to do with you. You can't follow instructions.");
        command("sigh");
        return;
    }

    if (!player->query_prop("_brought_whiskey"))
    {
        command("say Hey, did you not bring me something?");
        command("scratch");
        command("say I can't do anything with you. Go away!");
        command("sigh");
        return;
    }

    if (!player->query_prop("_brought_worms"))
    {
        command("say Hey, did you not bring me something?");
        command("scratch");
        command("say You're hopeless, can't even take orders right.");
        command("sigh");
        return;
    }

    if (!player->query_prop("_brought_hook"))
    {
        command("say Hey, did you not bring me something?");
        command("scratch");
        command("say What do I do now? So close and yet so far. Go home!");
        command("sigh");
        return;
    }

    if (!player->query_prop("_brought_string"))
    {
        command("say Hey, did you not bring me something?");
        command("scratch");
        command("say I cannot fathom people like you, who don't follow orders. Go away.");
        command("sigh");
        return;
    }
    if (!REWARD_QUEST(player, QUEST_NAME))
    {
        command("say Sorry, but you've already helped me.");
        return;
    }

    command("giggle misc");
    command("say Ah, well, I've kept you long enough.");
    command("say Thanks indeed for fetching me my fishing supplies!");
    command("say Here is something for you, though.");

    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
}

void
failed_give(object obj,object from)
{
    command("say I have no need for such things.");
    write(TO->query_The_name(from)+" gives it back to you.\n");
    obj->move(from);
    return;
}

void
refuse_attacker(object pl)
{
    command("glare "+pl->query_real_name());
    command("say Why do you even suppose I'll accept anything");
    command("say from someone who attacks me?");
    command("say Now, bugger off!!");
    command("grumble");
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
    	return;
    
    if (from->query_prop(SHIRE_I_ATTACKED_BODULAS))
    {
        set_alarm(2.0,0.0, &refuse_attacker(from));
        return;
    }

    if (obj->id("chicken"))
    {
        set_alarm(2.0,0.0, &give_second_task(from));
        return;
    }

    if (obj->id("whiskey"))
    {
        set_alarm(2.0,0.0, &give_third_task(from));
        return;
    }

    if (obj->id("worm"))
    {
        set_alarm(2.0,0.0, &give_fourth_task(from));

            /* It looks like these worms don't reset unless they are
             * removed, so let's do that when it is given. (Gorboth)
             */
            obj->remove_object();
        return;
    }

    if (obj->id("hook"))
    {
        set_alarm(2.0,0.0, &give_fifth_task(from));
        return;
    }

    if (obj->id("string"))
    {
        set_alarm(2.0,0.0, &give_sixth_task(from));
        return;
    }

    if (obj->id("stick"))
    {
        set_alarm(2.0,0.0, &test_reward_tasks(from));
        return;
    }

    set_alarm(1.5,0.0, &failed_give(obj,from));

}

public void
attacked_by(object obj)
{
    ::attacked_by(obj);
    obj->add_prop(SHIRE_I_ATTACKED_BODULAS, 1);
}

