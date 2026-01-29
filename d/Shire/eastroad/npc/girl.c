/* Boar is /d/Shire/eastroad/npc/boar.c
 */
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

inherit SHIRE_MONSTER;

#include "/d/Shire/common/make_money.h"

#define BOAR_DEST ONE_OF_LIST(({ WER_DIR + "er23n", \
         WER_DIR + "er17", \
         EVENDIM_DIR + "ev3", WER_DIR+"er14", \
         WER_DIR + "er22", WER_DIR + "er5s" }))

#define QUEST_NAME "boar"

void
create_shire_monster()
{
    set_name("brunhilda");
    add_name(({"child","girl"}));
    set_living_name("_brunhilda_");
    set_title("Burrows");
    set_race_name("hobbit");
    add_adj(({"fragile","young"}));
    set_long("This young hobbit child looks as if she is missing something.\n");

    set_gender(1);
    set_appearance(95);
    set_alignment(200 + random(100));
    set_stats(({20,60,30,30,30,50}));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_skill(SS_DEFENCE, 67);
    set_skill(SS_UNARM_COMBAT, 53);

    set_act_time(5);
    add_act("sniff");
    add_act("cry");
    add_act("despair");

    set_chat_time(4);
    add_chat("That mean old boar, he took my ball!");
    add_chat("Do you think you could help me?");

    set_whimpy(75);
    set_cact_time(3);
    add_cact("scream");
    add_cact("panic");
    MAKE_MONEY;

    add_ask(({"ball","boar","quest","help"}), VBFC_ME("ask_ball"));

    set_introduce(1);   
}

string
ask_ball()
{
    object boar;

    if (TP->query_prop("_ball_color_"))
    {
	command("say I've told you already, can't you find it?");
	command("sniff");
	command("cry");
	return "";
    }


    if (CHECK_QUEST(TP, QUEST_NAME))
    {
	command("say Thanks, but you've already helped me.");
	return "";
    }


    command("say A mean old boar took my ball while I was playing.");
    command("frown");
    command("say I'd like you to get it back for me.");
    boar = clone_object(ER_BASE_DIR + "npc/boar");

    TP->add_prop("_ball_color_",boar->query_color());


    command("say I almost forgot, my ball is "+boar->query_color()+" colored.");
    command("say Good luck!");

    boar->move_living("void", BOAR_DEST);
    return "";

}

void
introduce_me(string who)
{
    object obj;
    int    ran;

    obj = present(who, ENV(TO));
    if (::introduce_me(who))
    {
	ran = random(3);
	if (ran == 0)
	{
	    command("say Hi, my name is Brunhilda!");
	    command("smile " + who);
	    command("say I'm missing my favorite ball.");
	}
	if (ran == 1)
	{
	    command("curtesy to " + who);
	    command("say I'm almost seven years old.");
	    command("say I'm missing my favorite ball!");
	}
	if (ran == 2)
	{
	    command("say Hi.");
	    command("say Have you seen my ball?");
	}
    }
}


void 
test_quest(object player, object obj)
{
    string colorp, colorb;
    colorp = player->query_prop("_ball_color_");
    colorb = obj->query_prop("_ball_color_");


    if (colorp != colorb)
    {
	command("say This is not my ball, I'm missing a "+colorp+" one!");
	return;
    }
    if (!REWARD_QUEST(player, QUEST_NAME))
    {
	command("say I appreciate your offer, but you already helped me.");
	return;
    }
    command("bounce");
    command("say Oh, thank you, you've found it!");
    command("giggle");
    player->remove_prop("_ball_color_");
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");
}

public void
give_back(object from, object obj)
{
    command("say Why did you think I wanted this?");
    write("The hobbit gives it back to you.\n");
    obj->move(from);
    return;
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
	return;
    if (obj->id("_brunhilda_ball_")) 
	set_alarmv(5.0,0.0,"test_quest",({from, obj}));
    else
    {
	set_alarmv(5.0,0.0,"give_back",({from, obj}));
	return;
    }
}

