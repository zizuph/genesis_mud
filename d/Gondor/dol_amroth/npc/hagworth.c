/* -*- Mode: C -*-
 *
 * hagworth.c
 *
 * Skippern 20(c)02
 * 
 * Mr Hagworth is a quest npc.
 */
inherit "/std/monster";

inherit "/d/Gondor/common/lib/binbit"; /* the binbit code */

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#define NO_LIGHT    ({ "This should have been done by the gards.", \
                       "They should have left a small company to do this.", \
                       "This is tiresom." })
#define EMOTE_ARR   ({ "think", "grin", "sigh", "ponder", "smile", "nod", \
                       "listen for sound", "hum", "pace", "close grate", \
                       "close grate", "close grate", "kill rat" })

/* Prototypes */
         void     do_my_act();
         void     get_armed();
public   string   give_task();
public   string   ask_charm();
public   string   ask_isaac();
         void     get_charm(object ob, object from);
         void     default_answer();

void okay_to_move() { set_random_move(10+random(20), 1); }
void lets_talk_here() { set_random_move(0); }

void
create_monster()
{
    FIX_EUID;

    set_living_name("tormir");
    set_name("tormir");
    add_name( ({ "human", "dunadan" }) );
    set_adj("tall");
    add_adj("black-haired");
    set_title("Hagworth");
    set_long("This tall black-haired human seems sad.\n");
    set_alignment(-250);
    set_gender(G_MALE);

    default_config_npc(75);
    set_base_stat(SS_DEX, 90);
    set_skill(SS_WEP_SWORD, 45);
    set_skill(SS_WEP_KNIFE, 55);
    set_skill(SS_AWARENESS, 50);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_default_answer(&default_answer());
    add_ask( ({ "task", "quest", "job" }), &give_task(), 1);
    add_ask( ({ "charm", "lucky charm" }), &ask_charm(), 1);
    add_ask( ({ "isaac", "sir isaac", }), &ask_isaac(), 1);

    set_restrain_path( ({ DOL_COMMON+"streets",DOL_COMMON+"piers" }) );
    set_monster_home(DOL_COMMON+"streets/g-05");
    okay_to_move();

    set_chat_time(50+random(100));
    add_chat("The city is so empty without the guard.");
    add_chat("Damn this guard just leaving us unprotected. What of " +
	     "the enemy attacks us?");
    set_act_time(10+random(100));
    add_act(&do_my_act());

    get_armed();
}

void
get_armed()
{
    clone_object(DOL_WEP + "sh-sword")->move(TO);
    clone_object(DOL_ARM + "lt-armour")->move(TO);
    clone_object(DOL_TG + "coat")->move(TO);
    clone_object(DOL_TG + "pants")->move(TO);
    clone_object(DOL_TG + "lboots")->move(TO);
    command("wear all");
    command("wield all");
}

string
default_answer()
{
    command("say I have no idea of what you are talking about.");
    return "";
}

public string
ask_charm()
{
    object tp = this_player();
    string name = tp->query_name();

    command("say Now listen here.");

    command("whisper to "+name+" The charm is important to me, it have " +
	    "given me lots of luck.");
    command("emote clears his throat to whisper more clearly.");
    command("whisper to "+name+" Besides, it was a gift from my love.");
    command("emote gets a look of sorrow in his eyes.");
    command("whisper to "+name+" She died in a fire some years ago.");
    command("sob");

    return "";
}

public string
ask_isaac()
{
    object tp = this_player();
    string name = tp->query_name();

    command("say to "+name+" Now, concentrate.");

    command("whisper to "+name+" Sir Isaac of Belecthor is a ship owner " +
	    "living up in the hillside district.");
    command("emote clears his throat to whisper more clearly.");
    command("whisper to "+name+" His mansion is easy to find, I think it " +
	    "is the first you meet when you go up there.");
    command("whisper to "+name+" Hi might have hidden it in the back garden.");

    return "";
}

/*
 * Function name:    enter_inv
 * Description  :    mask parent to catch herbs.
 * Arguments    :    object ob -- the entering object
 *                   object from -- source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("TormirLuckyCharm"))
    {
        get_charm(ob, from);
	return;
    }
    command("say I am not interested in your "+ob->query_short()+".");
    command("give "+ob->query_name()+" to "+from->query_name());
}

public void

cant_see_in_room()
{
    if (CAN_SEE_IN_ROOM(this_object()))
        return;

    command("light lamp posts");
    command("say "+one_of_list(NO_LIGHT));
    return;
}

void
do_my_act()
{
    if (!CAN_SEE_IN_ROOM(this_object()))
        cant_see_in_room();

    command(one_of_list(EMOTE_ARR));
}

void
tell_me_about_task(object tp)
{
    string name = tp->query_name();
    object token;

    command("whisper to "+name+" Now listen carefully.");
    command("emote clears his throat to whisper more clearly.");
    command("whisper to "+name+" Sir Isaac have an my lucky charm. " +
	    "He denies it tough, but I know he have it.");
    command("emote looks around to ensure nobody is listening.");
    command("whisper to "+name+" I would be grateful if you could " +
	    "get it back for me.");
    command("say to "+name+" Now be on your way.");

    token = clone_object(DOL_OBJ + "quest/I_do_quest_token");
    token->set_task(DOL_Q_TORMIR_CAHRM);
    token->set_part(1);
    token->move(tp);

    okay_to_move();
    return;
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings " + capitalize(name) +".");
    command("introduce me to "+name);
    command("grin evil");
    command("say Maybe you can do something for me, " + capitalize(name) +"?");
}

public void
add_introduced(string name)
{
    object    pl;
    /*
    if (!objectp(pl = find_player(name)) ||
        pl->query_met(query_real_name()))
        return;
    */
    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}

public string
give_task()
{
    object tp = this_player();
    
    if (present("I_do_quest_token.c", tp))
    {
        command("say I have no more tasks for you.\n");
	return "";
    }

    lets_talk_here();
    set_alarm(4.0, 0.0, &tell_me_about_task(tp));
    command("say Come closer and listen carefully.");

    return "";
}

void
get_charm(object ob, object from)
{
    object token = present("I_do_quest_token.c", from);

    if (!objectp(from))
    {
        log_file("DolAmrothError", "ERROR: No object from ("+ctime(time())+
		 ")\n");
	return 0;
    }
    if (!objectp(ob))
    {
        log_file("DolAmrothError", "ERROR: No object ob ("+ctime(time())+
		 ")\n");
	return 0;
    }


    if (token->query_task() == DOL_Q_TORMIR_CAHRM && token->query_part() == 2)
    {
        token->give_reward(from, 750);
	token->remove_object();
	ob->remove_object();
    }
    else
    {
        command("smile thank");
	ob->remove_object();
    }
}








