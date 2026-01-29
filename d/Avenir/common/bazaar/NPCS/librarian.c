/* Creator Glinda may-95
   I wanted to add some atmosphere to my library, so heres the guy who
   works there. Now He did have to do a couple of things, and the
   library had to be slightly changed. The lib_exit command conjures an
   exit which can't be used if you have a book. So I made a small
   routine which removes the exit and makes another one (normal),
   which is called by the librarian when he dies.
   This fella also has a tiny newbie quest. Something about returning
   a book :)
 *
 * Revisions:
 * 	Lilith, Apr 1997:  Converted trigs to emote_hook so she can
 * 			   give out the quest!
 *	Gorboth, Oct 2014: Changed race name "librarian" to "human"
 * 	Lucius, Aug 2017:  Cleanups and fixes for "return book" quest.
 */
inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/givetask";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"

#include <money.h>

#define WIS_BOOK	"/d/Avenir/common/bazaar/Obj/books/wisdom"
#define QBOOK		"avenir_questbook_id"
#define QLOG		"/d/Avenir/log/quest/return_book"


public void
create_monster()
{
    ::create_monster();
    set_name("librarian");
    add_name(({"human"}));
    set_race_name("human");
    set_gender(G_MALE);
    add_adj("tall");
    add_adj("quiet");
    set_long("The tall librarian looks somewhat uncomfortable " +
      "with having visitors in his beloved, quiet library. " +
      "He peers at you from behind the counter as if asking " +
      "to do your business and leave, not necessarily in that " +
      "order.\n");

    default_config_npc(55);
    set_all_hitloc_unarmed(25);
    set_skill(SS_LANGUAGE,70);
    set_skill(SS_UNARM_COMBAT,55);
    set_skill(SS_BLIND_COMBAT,55);
    set_skill(SS_DEFENCE,55);
    set_skill(SS_AWARENESS,60);
    set_alignment(0);
    set_knight_prestige(-5);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    set_default_answer("@@hush@@");
    add_ask("[about] 'book' / 'gap' / 'books' / 'help' / 'quest' / 'task'",
	"@@give_quest@@");

    set_cchat_time(4);
    add_cchat("Please, no violence in my library.");
    set_cact_time(5);
    add_cact("sniff sadly");

    set_act_time(36);
    add_act("sigh");
    add_act("emote stares anxiously at the bookshelf.");
    add_act("emote dusts the books on the bookshelf.");
    add_act("emote peers into the pages of a book.");
    add_act("emote stares anxiously at a gap in the bookshelf.");
    add_act("emote squints off into the distance.");
    add_act("emote clears his throat.");
    add_act("smile sadly");

    MONEY_MAKE_CC(random(8))->move(this_object());
    equip(BAZAAR + "Obj/worn/robe");
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(from))
	to->set_librarian(TO);
}

public void
give_token(object from)
{
    object token = clone_object(COM +"obj/syb_coin");
    string str = token->short();

    token->move(from);
    from->catch_msg(QCTNAME(TO) + " smiles gratefully and hands "+
	"you one of his most treasured possessions, " + str + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " smile gratefully "+
	"and gives "+ str +" to " + QTNAME(from) + ".\n", ({ from }));
}

public void
finish_quest(object ob, object player)
{
    string who = player->query_real_name();

    ob->remove_object();

    if (!player->query_prop("_has_talked_to_librarian"))
    {
	command("say Why do you bring me this?");
	return;
    }

    if (!player->test_bit("Avenir",0,5))
    {
	reward_quest("Return Book", player, 0, 5, 1500, 45);
	command("thank " +who);
	command("whisper " +who +" Now that was pretty educational, eh?");
	MONEY_MAKE_SC(random(20))->move(this_object());
	command("give silver coins to " +who);
	write_file(QLOG, player->query_name()+ "  " + ctime(time()) + "\n");

	//Give a sybarun coin
	give_token(player);
    }
    else
    {
	command("whisper " +who +" I appreciate your repeated efforts. You " +
	  "could become a good librarian some day yourself! But don't " +
	  "you think someone else should be given the chance to show " +
	  "what they are worth too?");
	command("peer " +who);
    }
}

public string
give_quest(void)
{
    if (TP->test_bit("Avenir", 0, 5))
    {
	check_group_two(TP,({0, 0, 0, 0}));
	return "";
    }

    command("sigh");
    command("whisper " + OB_NAME(TP) +" I need your help.");
    command("whisper " + OB_NAME(TP) +" Someone borrowed a book "+
	"from the library.");
    command("whisper " + OB_NAME(TP) +" The Song of the Seer.");
    command("whisper " + OB_NAME(TP) +" But I cannot remember who "+
	"borrowed it!");
    command("despair");
    command("whisper " + OB_NAME(TP) +" I really need that book back!");
    command("whisper " + OB_NAME(TP) +" Do you think you can help me?");
    TP->add_prop("_has_talked_to_librarian", 1);
    return "";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (ob->id(QBOOK))
	set_alarm(1.0, 0.0, &finish_quest(ob,from));
}

public string
hush(void)
{
    switch(random(3))
    {
    case 0:
	command("emote points at the brass plaque.");
	return "";
    case 1:
	command("poke " + OB_NAME(TP) + " nose");
	command("whisper " + OB_NAME(TP) + " Can't you read?");
	return "";
    case 2:
	command("emote motions a finger across his lips.");
	return "";
    }
}

public void
return_whisper(object actor, string adverb)
{
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    command("peer inter "+ OB_NAME(actor));
    command("whisper to "+ OB_NAME(actor) +" I couldn't hear "+
	"you very well.");
}

public void
return_grope(object actor, string adverb)
{
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    command("blush angrily");
    command("slap "+ OB_NAME(actor));
}

public void
return_hug(object actor, string adverb)
{
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    command("emote smiles blushingly.");
    command("hug "+ OB_NAME(actor));
}

public void
return_hush(object actor, string adverb)
{
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    switch(random(3))
    {
    case 0:
	command("emote points at the brass plaque.");
	break;
    case 1:
	command("poke "+ OB_NAME(actor)+ " nose");
	command("whisper "+ OB_NAME(actor) +" Can't you read?");
	break;
    case 2:
	command("emote motions a finger across his lips.");
	break;
    }
}
/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
public void
emote_hook(string emote, object actor, string adverb)
{
    /* See if we want to trigger on the emote. If so, call a little alarm
     * for the reaction function.
     */
    switch(emote)
    {
    case "say":
    case "shout":
    case "laugh":
    case "applaud":
    case "giggle":
    case "cough":
    case "spit":
    case "growl":
    case "cackle":
    case "chuckle":
    case "cheer":
    case "rsay":
	set_alarm(3.0, 0.0, &return_hush(actor, adverb));
	return;

    case "hug":
    case "squeeze":
    case "cuddle":
	set_alarm(3.0, 0.0, &return_hug(actor, adverb));
	return;

    case "grope":
    case "fondle":
	set_alarm(3.0, 0.0, &return_grope(actor, adverb));
	return;

    case "whisper":
	set_alarm(3.0, 0.0, &return_whisper(actor, adverb) );
	return;
    }
}

public void
check_meet(object tp)
{
    object book;

    if (!present(tp, environment(TO)))
	return;

    if (!CAN_SEE(tp, TO))
	return;

    if (tp->query_prop("_is_cat_"))
    {
	command("whisper to "+tp->query_real_name()+" Shoo!");
	return;
    }

    if (!present("_wisdom_book", tp))
    {
	command("whisper to "+ tp->query_real_name() +
	    " I have something for you. It is a book of small wisdoms.");
	clone_object(WIS_BOOK)->move(TO);
	command("give enchiridion to "+ tp->query_real_name());
	return;
    }
}

public void
init_living(void)
{
    ::init_living();

    if (!IS_SYBARITE(TP) && !TP->query_prop("_is_cat_"))
	return;

    set_alarm(2.5, 0.0, &check_meet(TP));
}
