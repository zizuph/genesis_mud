#pragma strict_types
/*
 * ~/stos.c
 *
 * Manager of the bath house
 *
 * Revisions:
 *   Lilith, Feb 2002: Created.
 *   Lucius, Jul 2017: Bath's recode.
 *
 */
inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/log_asks";

#include "../bath.h"
#include "/d/Avenir/include/relation.h"

#include <money.h>
#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

/* 5 platinum */
#define COST	8640

#define CMD(x)	command(x)
#define SAY(x)	command("say " + x)


private string *exclaim = ({
    "Excellent!", "Marvellous!", "Wonderful!", "Splended!",
});

public void 
create_monster(void)
{
    if (!IS_CLONE)
	return;

    set_name("stos");
    set_living_name("stos");
    set_race_name("human");
    set_adj(({ "calm", "serene" }));
    add_name(({"boss", "manager"}));
    set_long("He is perhaps the calmest, most serene person "+
      "you have ever seen.\n");

    set_gender(G_MALE);
    set_stats(({ 78, 106, 57, 85, 70, 94 }));

    set_alignment(0);
    set_chat_time(60);
    add_chat("The Shadow elves use the private baths of course. Can't "+
      "have them bathing with the common people.");
    add_chat("I've private rooms to rent, ask for a list.");
    add_chat("I've been rather busy since the Hegemon opened the "+
      "City to Outlanders. I recently had to turn away a Shadow "+
      "Warrior who wanted room four, because I'd rented it to "+
      "a gentleman from a place called 'Ansalon'.");
    add_chat("This bathhouse is very clean, I assure you.");
    add_chat("If you need soap, towels, or refreshments, do not "+
      "hesitate to ask an attendant.");
    add_chat("I hope the soap maker's guild gets me another batch soon.");

    set_act_time(120);
    add_act("sigh softly");
    add_act("peer search");

    set_default_answer(VBFC_ME("what_me"));   
    add_ask(({ "Hizbarin", "hizarbin" }), "say His is the domain of Water.", 1);
    add_ask(({ "darkness" }), "say It surrounds everything, "
      + "waiting to get in though the cracks that form in "
      + "our dreams, like the sands of an ever-encroaching desert.", 1);
    add_ask(({ "follow me" }), "say I most certainly will not.", 1);
    add_ask(({ "gate" }), "say There are many gates. Each is a portal "+
      "to possibility.", 1);
    add_ask(({ "hello" }), "say Greetings.", 1);
    add_ask(({ "help" }), "say I can sell you a key to the private rooms.", 1);
    add_ask(({ "improve" }), "say There is nothing may I teach you.", 1);
    add_ask(({ "introduce" }), "introduce myself", 1);
    add_ask(({ "job" }), "say I have none to give you.", 1);
    add_ask(({ "quest" }), "say You will need to seek elsewhere "
      + "for one.", 1);
    add_ask(({ "secret" }), "emote narrows his eyes.", 1);
    add_ask(({ "secrets" }), "say I have learned many in my life, "
      + "dark and terrible they are.", 1);
    add_ask(({ "seek" }), "say What do you seek?", 1);
    add_ask(({ "service" }), "say I serve the people of Sybarus.", 1);
    add_ask(({ "shadows" }), "say They are everywhere...", 1);
    add_ask(({"price", "cost"}), 
      "say The price to rent a private bath is "+
      MONEY_TEXT_SPLIT(COST) + ".", 1);
    add_ask(({"return"}), 
      "say You may 'return' the key to your private bath when finished.", 1);
    add_ask(({"rent", "renting", "rental", "rentals"}), 
      "say You may 'rent' one of our private baths by number.", 1);
    add_ask(({ "room", "rooms", "private rooms", "private", "private baths"}),
      "say Currently we have four private baths available for rent. "+
      "Just 'list' the rooms to see what is available.", 1);
    add_ask(({"key", "keys", "room key", "room keys "}), 
      "say You may use 'list' to determine which keys are available. "+
      "You may also 'return' them when finished.", 1);
    add_ask(({"list", "vacancy", "vacancies"}), 
      "say You may perform a 'list' of rooms or vacancies to see what "+
      "is available.", 1);
    add_ask(({ "soap maker's guild", "soap makers guild"}), 
      "say Its based in the Merchantile Pale, in the Village.");
    add_ask(({ "pale", "merchantile pale", "Merchantile Pale"}),
      "say Its one of the areas of the Village, the main marketplace.");
    add_ask(({ "village", "Village" }), 
      "Oh, its over on the main island, just south of the Bazaar. "+
      "I heard the merchant guilds are petitioning the Hegemon to "+
      "allow Outlanders in.");

    add_prop(CONT_I_HEIGHT, 200);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_MAGIC, 1);
    add_prop(OBJ_I_NO_ATTACK, 1);
}

public string
what_me(void)
{
    command("say I couldn't say.");
    return "";    
}

private string *voices = ({
    "speaks", "says", "whispers", "sings",
});

public string
race_sound(void)
{
    return one_of_list(voices);
}

private int
room_sort(string a, string b)
{
    int aa = LANG_WORD2NUM(a),
	bb = LANG_WORD2NUM(b);

    if (aa < bb)
	return -1;
    if (aa > bb)
	return 1;

    return 0;
}

public int
list_room(string str)
{
    if (str != "rooms" && str != "baths" && str != "vacancies")
    {
	SAY("List what!? Rooms, vacancies?");
	return notify_fail("");
    }

    string *rooms = MNGR->query_vacancies();
    int size = sizeof(rooms);

    if (!size)
    {
	CMD("sigh regret");
	SAY("I'm terribly sorry, but we do not have any "+
	    "vacancies at this time.");
	SAY("Please try us again later.");
	return 1;
    }

    rooms = map(sort_array(rooms, room_sort), capitalize);

    SAY("At present, "+ (size == 1 ? "this room " : "these rooms ") +
	(size == 1 ? " is " : " are ") +"available for rent:");

    SAY(COMPOSITE_WORDS(rooms) + ".");
    SAY("Rooms cost "+ MONEY_TEXT_SPLIT(COST) +" each to rent.");

    CMD(one_of_list(({"smile", "gesture", "bow"})) + " helpful");
    return 1;
}

public int
rent_room(string str)
{
    int num;
    object key;
    mixed *data;

    if (!strlen(str))
    {
	SAY("What was that? Enunciate please.");
	CMD("sigh audibly");
	return notify_fail("");
    }

    if (!parse_command(lower_case(str), ({ }),
	    "[the] [room] [number] %w", str))
    {
	CMD("eyebrow quizzically");
	SAY("I'm not clear on which room you are referring to.");
	return notify_fail("");
    }

    /* Allow renting by numeral. */
    if (sscanf(str, "%d", num))
	str = LANG_NUM2WORD(num);

    if (!MNGR->valid_room(str))
    {
	SAY("I must have misheard. Room "+ capitalize(str) +
	    " isn't available to rent.");
	CMD(one_of_list(({"smile", "gesture", "sigh"})) + " regret");
	return 1;
    }

    if (sizeof(data = MNGR->query_rented(str)))
    {
	SAY("I'm afraid that room number "+ capitalize(str) +
	    " is presently occupied.");
	CMD(one_of_list(({"smile", "gesture", "sigh"})) + " regret");

	if (this_player()->query_wiz_level())
	    dump_array(data, "RENTED: ");

	return 1;
    }

    if (TOTAL_MONEY(this_player()) < COST)
    {
	SAY("Renting that room will cost you "+
	    MONEY_TEXT_SPLIT(COST) +".");
	CMD("gesture expectant");
	return 1;
    }

    if (!MNGR->rent_room(str, this_player()))
    {
	SAY("I do apologize, but there is an issue with renting "+
	    "room "+ str +" presently.");
	CMD("bow apologetic");
	return 1;
    }

    if (!MONEY_ADD(this_player(), -COST))
    {
	MNGR->vacate_room(str);
	CMD("peer suspic "+ OB_NAME(this_player()));
	SAY("Are you trying to pay with phoney money?");
	return 1;
    }

    if (!objectp(key = MNGR->get_room_key(str)))
    {
	CMD("gasp");
	SAY("Egads! I have lost the key to that room!");
	return 1;
    }

    if (!key->move(this_player()))
	key->move(this_player(), 1);

    SAY(one_of_list(exclaim));

    write(query_The_name(this_player()) +
	" hands you a "+ key->short() +".\n");
    say(QCTNAME(this_object()) + " hands "+ QTNAME(this_player()) +
	" a "+ QSHORT(key) +".\n");

    SAY("You may 'return' the key when you are finished.");
    return 1;
}

private void
do_return_keys(object *keys)
{
    foreach(object ob: keys)
    {
	string room = ob->what_room();

	ob->remove_object();

	if (MNGR->vacate_room(room))
	{
	    SAY(one_of_list(exclaim) +
		" I shall have room "+ room +" cleaned immediately!");
	}
	else
	{
	    SAY(one_of_list(exclaim) +
		" I shall have room "+ room +" cleaned as soon as possible!");
	}
    }
}

public int
return_key(string str)
{
    int size;
    object key, *keys;
    string room, who = OB_NAME(this_player());

    if (!strlen(str))
    {
	SAY("Just 'return key' will work otherwise be more specific.");
	return notify_fail("");
    }

    keys = filter(all_inventory(this_player()), &->id(PRIV_KEY_ID));
    size = sizeof(keys);

    if (str == "key" || str == "all keys")
    {
	if (!size)
	{
	    CMD("hmm "+ who);
	    SAY("You do not appear to have one of our private bath keys.");
	    return 1;
	}

	if (size > 1 && str != "all keys")
	{
	    CMD("hmm "+ who);
	    SAY("You possess more than one of our private bath keys.");
	    SAY("You will to be more specific on which to return.");
	    SAY("Or.. 'return all keys' if you are certain.");
	    return 1;
	}

	do_return_keys(keys);
	return 1;
    }

    if (parse_command(str, ({ }),
	    "'key' [to] [private] [bath] [room] %w", room))
    {
	keys = filter(keys, &operator(==)(room) @ &->what_room());

	if (!(size = sizeof(keys)))
	{
	    CMD("hmm "+ who);
	    SAY("You do not appear to possess a key to room "+ room +".");
	    return 1;
	}

	do_return_keys(keys);
	return 1;
    }

    if (parse_command(str, keys, "[the] / [a] %o", key))
    {
	do_return_keys(({ key }));
	return 1;
    }

    CMD("blink");
    SAY("I cannot figure out what you are trying to return.");
    return notify_fail("");
}

public void 
init_living(void)
{
    ::init_living();

    add_action(list_room,  "list");
    add_action(rent_room,  "rent");
    add_action(return_key, "return");
}
