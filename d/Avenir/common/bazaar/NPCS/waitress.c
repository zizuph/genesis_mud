// file name:	waitress.c
// creator(s):	Ilyian May 1995
// last update: Denis, May'97: Regular updates: triggers and such.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/include/paths.h";
# include "/d/Avenir/include/defs.h"
# include <money.h>
# include <ss_types.h>
# include <macros.h>

inherit "/std/monster";

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name(({"hofesta" , "waitress" , "grunshk"}));
    set_title("Grunshk, Junior Waitress of the Cavern");
    set_race_name("goblin");
    set_living_name("hofesta");
    set_adj("lithe");
    add_adj("cheerful");
    set_gender(G_FEMALE);
    set_long("This cute little 'thang is bouncing from table to "+
             "table, trying to earn a living in a tough area.\n");

    set_stats(({60, 35, 40, 27, 27, 27}));
    set_alignment(5);

    set_chat_time(8);
    add_chat("Hello there, Hon!");
    add_chat("The Bazaar can be a nasty place sometimes.");
    add_chat("I wish I was up at the Stormy Haven with Bakona.");
    add_chat("Watch out for the Punisher. He can get a 'lil nasty...");
    add_chat("The times they are a' changin'.");

    set_act_time(10);
    add_act("emote takes a mug from a table and sets it back over the bar.");
    add_act("wink human");
    add_act("yawn");
    add_act("emote sings: One of these days, you'll miss me, honey....");
    add_act("emote wipes down the bar with a dirty rag.");

    set_cact_time(10);
    add_cact("scream");
    add_cact("pout");
    add_cact("panic");

    set_cchat_time(5);
    add_cchat("Please, no! Don't hurt me!");
    add_cchat("Your Mama nevuh raised you right!");
    add_cchat("There go your chances for a free drink...");
}

public void
arm_me()
{
    seteuid(getuid());

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/wield/pclub")->move(TO);
    command("wield all");

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
    command("wear all");
}

static void
do_wink(string who)
{
    if (present(who, environment(this_object())))
    {
	    command("introduce myself");
	    command("wink " + who);
    }
}

static void
do_smile(object who)
{
    if (present(who, environment()))
	command("smile sweet at " + who->query_real_name());
}

static void
do_re_frown(object who)
{
    if (present(who, environment()))
    {
	command("say What's wrong, " + who->query_nonmet_name() + "?");
	command("say You look like y'all could use a drink..");
    }
}

public void
add_introduced(string who)
{
    set_alarm(itof(3 + random(4)), 0.0, &do_wink(who));
}

public void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "giggle")
	set_alarm(3.0, 0.0, &do_smile(actor));
    else
	if (emote == "frown")
	    set_alarm(3.0, 0.0, &do_re_frown(actor));
}
