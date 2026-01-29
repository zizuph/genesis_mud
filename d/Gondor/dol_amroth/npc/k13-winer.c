/* -*- Mode: C -*-
 *
 * npc/k13-winer.c
 *
 * By Skippern 20(c)02
 *
 * This is the lord of the mansion in k-13 in Dol Amroth
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

#define DELAY      5
#define PLACES     ({ DOL_SEWER + "g-05", DOL_HILLS + "k-13/garden1", \
                      DOL_TRADE + "streets/r-10", DOL_COMMON + "houses/g-08", \
                      DOL_CRAFT + "houses/a-04", DOL_COMMON + "houses/k-06", \
                      DOL_OTHER + "pier/k-02", DOL_CRAFT + "pier/b-01", \
                      DOL_SEWER + "g-05", DOL_SEWER + "g-05", DOL_SEWER + "g-05", \
                      DOL_TRADE + "warehouses/s-09" })

static object par;
       int    ran = random(2);

/* Prototypes */

/* Code */
void
wake_up(object tp)
{
    object token = present("I_do_quest_token.c", tp);

    tp->catch_tell("Oooooh! What a headache! The world is spinning as " +
		   "you slowly wake up. What happened back there? You " +
		   "open your eyes and looks around you.\n");
    tp->move(one_of_list(PLACES), 1);
    tell_room(environment(tp), QCTNAME(tp)+" stumbles in raving drunkenly, and passes out.\n", 0, tp);
    command("up");
    command("north");
    token->give_reward(tp, 3000);
    token->remove_object();
    par->remove_object();
    command("grin");
    tp->catch_tell("Better find your way home and rest.\n");
}

void
last_step(object tp)
{
    object o;

    tp->catch_tell("Things get blury and you black out.\n");
    o = clone_object(DOL_OBJ + "hangover");
    o->move(tp, 1);
    o->start_poison(0);
    set_alarm(itof(DELAY+ran), 0.0, &wake_up(tp) );
}

void
step_5(object tp)
{
    command("emote picks up a bottle.");
    command("grin evil");
    command("say Here is a piece of art. It is a bottle of Ithilian Sunrays, "+
	    "a wine much used for celebrations in the eastern regions.");
    command("emote fills something into a glass and hands you the glass.");
    tp->catch_tell("You drink the wine and returns the glass to the winer.\n"+
                   "Your mouth starts to feel numb.\n");

    command("emote continues to browse the shelves.");
    set_alarm(itof(DELAY+ran), 0.0, &last_step(tp) );
}

void
step_4(object tp)
{
    command("emote picks up a bottle.");
    command("smile rel");
    command("say This beauty is a rare piece, its an elven wine from " +
	    "northern Mirkwood. This comes from a crate my father ordered " +
	    "from Esgaroth after a dragon destroyed halve the city.");
    command("emote fills something into a glass and hands you the glass.");
    tp->catch_tell("You drink the wine and returns the glass to the winer.\n"+
                   "This was realy sweet.\n");

    command("emote continues to browse the shelves.");
    set_alarm(itof(DELAY+ran), 0.0, &step_5(tp) );
}

void
step_3(object tp)
{
    command("emote picks up a bottle.");
    command("smile rel");
    command("say I still have some of this. This is a 3010 Belfalas Green. " +
	    "The best white wine from this district. Semi-dry with a sense " +
	    "of flowers and the anger of youth.");
    command("emote fills something into a glass and hands you the glass.");
    tp->catch_tell("You drink the wine and returns the glass to the winer.\n"+
                   "Did he say semi-dry? This must have been very dry!\n");

    command("emote continues to browse the shelves.");
    set_alarm(itof(DELAY+ran), 0.0, &step_4(tp) );
}

void
step_2(object tp)
{
    command("emote picks up a bottle.");
    command("say This is a 3008 Tolfalas Cardignet, a fruity wine, with "+
	    "slightly dim color.");
    command("emote fills something into a glass and hands you the glass.");
    tp->catch_tell("You drink the wine and returns the glass to the winer.\n"+
		   "Ah, it tastes realy good.\n");

    command("emote continues to browse the shelves.");
    set_alarm(itof(DELAY+ran), 0.0, &step_3(tp) );
}

void
start_quest(object quester)
{
    quester->remove_prop(DOL_I_ASKED_WINER);

    if (!present(quester, environment(this_object())))
    {
	/* The player have spoiled the quest, so we have to return */
	command("swear");
	command("up");
	command("north");
	quester->remove_prop(DOL_I_WINER_QUEST);
	present("I_do_quest_token.c", quester)->remove_object();
    }
    command("say You still want to taste my wine. Lets get started.");

    par = clone_object("/std/paralyze");
    par->move(quester, 1);

    command("emote starts to browse his shelves.");
    set_alarm(itof(DELAY+ran), 0.0, &step_2(quester) );
}

void
down(object quester)
{
    command("down");

    set_alarm(5.0, 0.0, &start_quest(quester));
}

void
walk(object quester)
{
    command("say to "+quester->query_real_name()+" Walk this way.");
    command("emote raises from his chair.");
    command("south");
    
    quester->add_prop(DOL_I_WINER_QUEST, 1);

    set_alarm(3.0, 0.0, &down(quester) );
}

string ask_wine()
{
    object tp = this_player();
    int i;

    command("say I make the best wine in Gondor, and I have a cellar " +
	    "full of profe for it.");

    if (!tp->query_prop(DOL_I_ASKED_WINER))
	tp->add_prop(DOL_I_ASKED_WINER, 1);
    else i = tp->query_prop(DOL_I_ASKED_WINER);

    if (i == 1 || i == 3 || i == 5 || i == 7)
	return "";
    i++;
    tp->add_prop(DOL_I_ASKED_WINER, i);

    return "";
} 
string
ask_taste()
{
    object tp = this_player();
    int i;

    command("laugh");
    command("say You? Taste my wine? Dont make me laugh.");

    if (!tp->query_prop(DOL_I_ASKED_WINER))
        tp->add_prop(DOL_I_ASKED_WINER, 2);
    else i = tp->query_prop(DOL_I_ASKED_WINER);

    if (i == 2 || i == 3 || i == 6 || i == 7)
        return "";
    i = i + 2;
    tp->add_prop(DOL_I_ASKED_WINER, i);

    return "";
}
string
ask_test()
{
    object tp = this_player();
    int i;

    command("say So you want to test my wine? Interested in buying?");

    if (!tp->query_prop(DOL_I_ASKED_WINER))
        tp->add_prop(DOL_I_ASKED_WINER, 4);
    else i = tp->query_prop(DOL_I_ASKED_WINER);

    if (i == 4 || i == 5 || i == 6 || i == 7)
        return "";
    i = i + 4;
    tp->add_prop(DOL_I_ASKED_WINER, i);

    return "";
}
string
ask_vintage()
{
    object tp = this_player();
    int i;

    command("say I have some good vintages, and even some realy nice " +
	    "rarities, but I dont share my wine with anybody.");
    if (!tp->query_prop(DOL_I_ASKED_WINER))
        tp->add_prop(DOL_I_ASKED_WINER, 8);
    else i = tp->query_prop(DOL_I_ASKED_WINER);

    if (i == 8 || i == 9 || i == 10 || i == 11 || i == 12 || i == 13 || 
	i == 14 || i == 15)
        return "";
    i = i + 8;
    tp->add_prop(DOL_I_ASKED_WINER, i);

    return "";
}
string
ask_cellar()
{
    object o;

    if (this_player()->query_prop(DOL_I_ASKED_WINER) == 15)
    {
	command("say Ok, follow me down to the cellar, and I can "+
		"let you taste one or two of my bottles.");
	command("sigh");

	o = clone_object(DOL_OBJ+"quest/I_do_quest_token");
	o->set_task(DOL_Q_WINE);
	o->set_part(1);
	o->move(this_player(), 1);

	set_alarm(1.0, 0.0, &walk(this_player()) );

	return "";
    }
    command("say I will not let you down to my cellar.");
    return "";
}

public void
create_dunadan()
{
    FIX_EUID;

    set_living_name("araruna");
    set_name("araruna");
    add_name( ({ "dunadan", "master", "sir", "lord", "winer" }) );
    set_adj("slightly");
    add_adj("anumated");
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Renouned Winemaker");
    set_dunedain_house("Hador");
    set_long("He is a winemaker.\n");

    default_config_npc(75);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 85);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);

    add_prop(DOL_I_WINER_QUEST, 1);

    set_default_answer("I have no idea what you want.");
    add_ask("wine", &ask_wine() );
    add_ask("taste", &ask_taste() );
    add_ask("test", &ask_test() );
    add_ask("vintage", &ask_vintage() );
    add_ask("cellar", &ask_cellar() );

    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");

    set_alignment(550);

    set_chat_time(200);
    add_chat("The winestocks was good this year.");
    add_chat("3010 was a good your, if I could repete that before I die " +
	     "I would die as a happy man.");
    add_chat("I hope it doesn't mean trouble when the army leaves town this " +
	     "way.");

    set_act_time(75);
    add_act("ponder");
    add_act("glitter");
    add_act("gleam");
    add_act("silence");
    add_act("dpace");
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("grumble");
    command("say to "+name+" You know my wine?");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}
