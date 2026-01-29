/* Union Librarian
 *   Cirion, 050196
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


public void
create_monster()
{
    set_name("sonia");
    set_living_name("sonia");
    add_name("librarian");
    set_race_name("elf");
    set_adj("slender");
    add_adj("white-haired");
    set_title("the Union Archivist");
    add_name("human");
    set_long("She is of pale complexion, and her hair is "
      +"a shocking white, in stark contrast to her dark "
      +"grey eyes.\nShe has an enigmatic feeling about "
      +"her, of wisdom and great age.\n");

    set_gender(G_FEMALE);
    set_base_stat(SS_OCCUP, 45);
    set_stats(({ 24, 46, 25, 85, 71, 34 }));

    set_union_npc();
    TO->set_union_sphere(SPH_HISTORY);

    set_skill(SS_LANGUAGE,      99);
    set_skill(SS_WEP_KNIFE,     29);
    set_skill(SS_PARRY,         15);
    set_skill(SS_WEP_MISSILE,    8);
    set_skill(SS_ACROBAT,       20);
    set_skill(SS_AWARENESS,     85);
    set_skill(SS_DEFENCE,       40);
    set_skill(SS_UNARM_COMBAT,  24);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_SWAY,          40);

    set_alignment(-400);

    set_act_time(45);
    add_act("sigh softly");
    add_act("rub sphere");
    add_act("blink");
    add_act("emote smiles gently.");
    add_act("brood");

    set_cact_time(3);
    add_cact("wield all");
    add_cact("fling");
    add_cact("sway");

    add_ask(({ "alcintaron" }), "say Speak not that name aloud.", 1);
    add_ask(({ "books" }), "say Within them is held great wisdom.", 1);
    add_ask(({ "cartography" }),
	"say That is the sphere of maps and directions.", 1);
    add_ask(({ "council" }), "say I cannot speak of that.", 1);
    add_ask(({ "flame" }), "say The Flame is everywhere.", 1);
    add_ask(({ "help" }), "say There is no help I can offer you.", 1);
    add_ask(({ "language" }),
	"say Languages are a great skill to have, they bring order "+
	"from chaos, understanding from incomprehension.", 1);
    add_ask(({ "key", "keys" }),
	"say The keys are many, they open the way to mystery and "+
	"enlightenment. Have you a key for me?", 1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    equip(({ OBJ+"knife", OBJ+"robe", OBJ+"sandals" }));
}

private void 
return_unwanted(object what, object who)
{
    if (!objectp(what))
	return;

    if (present(who, environment()))
	command("usto "+ who->query_real_name() +" That is not for me.");

    if (!command("give "+ OB_NAME(what) +" to "+ OB_NAME(who)))
	what->remove_object();  
}

private void
key_test(object key, object player)
{
    object tablet;

    if (!present("_alcin_key", TO))
	return;

    if (!IS_MEMBER(TP))
    {
	command("say Thank you for turning that in.");
	return;
    }

    if (!IS_TORNU(TP))
    {
	command("usay However it is that you came by this key, "+
	  "it was not through the appropriate channels, for you "+
	  "are not yet Tornu. Thank you for turning it in, I "+
	  "will see that it is returned to its proper place.");
	return;
    }

    tablet = clone_object(OBJ +"alcin_tablet")->move(TO);

    command("emote runs her hand over the large brass key and smiles "+
	"a secretive smile.");

    set_alarm(2.0, 0.0, &command("emote turns toward the bookshelves "+
	    "and kneels on the floor."));
    set_alarm(4.0, 0.0, &command("emote does something near the bottom "+
	    "shelf, making several scraping noises."));
    set_alarm(8.0, 0.0, &command("emote rests something on her knees.\n"+
	    "It is partly concealed by the fold of her robe, so you are "+
	    "unable to discern what it is."));
    set_alarm(10.0, 0.0, &command("emote again does something that "+
	    "causes a scraping noise.\nYou hear the distinct 'snick' of "+
	    "a key turning in a lock."));
    set_alarm(14.0, 0.0, &command("emote stands, brushes at the folds "+
	    "of her robe, and returns to her writing desk."));     
    set_alarm(17.0, 0.0, &command("give tablet to "+
	    player->query_real_name()));
    set_alarm(19.0, 0.0, &command("whisper to "+ player->query_real_name() +
	    " One whose name is of such power it should be spoken aloud only "+
	    "in the sacred space has deemed you worthy of this great honour."));
    set_alarm(22.0, 0.0, &command("whisper to "+ player->query_real_name() +
	    " Bring that to the only one of Us who can make the object "+
	    "you seek."));
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (obj->id("_alcin_key"))
    {
	key_test(obj, from);
	return;
    }
    set_alarm(2.0, 0.0, &return_unwanted(obj, from));
}

public void
speech_hook(string verb, object actor, string adverb, object *oblist,
    	    string text, int target)
{
    if (!wildmatch("*lcintaron*", text))
	return;

    set_alarm(1.0, 0.0, &command("emote seems to pale slightly."));
    set_alarm(2.0, 0.0, &command("say Speak not that name aloud."));
}

public int
stop(string str)
{
    string where;
    object *oblist, book;

    if (!CAN_SEE(TO, TP) || !CAN_SEE_IN_ROOM(TO))
	return 0;

    if (present("Union_book_id", TP))
    {
	command("say Perhaps you should return the book before you leave.");
	command("emote stands in front of the door.");
	return 1;
    }

    oblist = deep_inventory(TP);
    if (objectp(book = present("Union_book_id", oblist)))
    {
	where = ENV(book)->short(TO);
	command("say Sorry, but I think a book has accidently "+
	    "fallen into your "+ where +".");
	command("say Maybe you should take it out before you go anywhere.");
	return 1;
    }

    return 0;
}

public void
init_living(void)
{
    ::init_living();
    add_action(stop,  "west");
}
