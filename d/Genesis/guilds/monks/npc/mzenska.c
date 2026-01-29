/*
 * Createure that guards the inner parts of the Monks monestary.
 * The stats of the NPC depend on the amount of food it has been
 * given (which will be saved).
 * Cirion, 1999.08.15
 */
#pragma save_binary


#include "defs.h"
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit MONKLIB;

#define SAVE if (IS_CLONE) save_object (MONK_NPC + "mzenska")
#define LOAD if (IS_CLONE) restore_object (MONK_NPC + "mzenska")
#define HUNGER_ADJ	    1
#define HUNGER_LONG	    2

private static string *react_emotions = ({ });
private static string *react_commands = ({ });
private static int    *react_players = ({ });

// range of 0 - 1000
public int lizard_hunger = 300;

public void add_reaction (mixed emotion, string com, int use_player);

public int
query_base_stat (int index)
{
    int ret;

    // stats are exponentially proportional to the amount of
    // food it has been given.
    if (lizard_hunger == 0)
	lizard_hunger = 1;

    ret = (lizard_hunger * lizard_hunger) / 2000;

    if (ret <= 0)
	ret = 1;

    if (ret > 1000)
	ret = 1000;

    return ret;
}

public void
lizard_eat_food (int amount)
{
    int		perc_hp;

    // current percentage of HP the lizard has
    perc_hp = query_hp () * 100 / query_max_hp ();

    lizard_hunger += (amount / 100);

    if (lizard_hunger > 1000)
	lizard_hunger = 1000;

    // since raising stats won't raise a corresponding
    // amount of HP, retain the previous percentage
    // of HP.
    set_hp (query_max_hp () * 100 / perc_hp);
}

public void
devour (object food)
{
    int		amount;

    say (QCTNAME (this_object ()) + " devours "
	+ LANG_THESHORT (food) + ".\n", ({}));

    amount = food->query_amount ();
    if (food->num_heap () > 1)
	amount *= food->num_heap ();

    lizard_eat_food (amount);
    eat_food (food->query_amount (), 0);
    food->remove_object ();
}

/*
 * Description:	Feed the lizard and increase his strength.
 */
public int
feed (string str)
{
    mixed	    items;
    int		    i;
    int		    amount;

    if (!(strlen(str)) ||
	!parse_command (str, this_player (), "[the] [fire-lizard] "
	+ "'lizard' [with] [the] %i", items) || !pointerp (items)
	|| sizeof (items) <= 1)
    {
	notify_fail ("Feed the fire-lizard with what?\n");
	return 0;
    }

    for (i = 1; i < sizeof (items); i++)
    {
	if ((!function_exists ("create_food", items [i]))
	    || items [i]->query_amount () <= 0)
	{
	    write ("The fire-lizard does not want "
		+ LANG_THESHORT (items [i]) + ".\n");
	    continue;
	}

	if (lizard_hunger < 1000)
	{
	    this_player ()->catch_msg ("You feed " 
		+ LANG_THESHORT (items [i])
		+ " to " + QTNAME(this_object ()) + ".\n");
	    say (QCTNAME(this_player ()) + " feeds " 
		+ LANG_THESHORT (items [i])
		+ " to " + QTNAME(this_object ()) + ".\n");

	    devour (items [i]);


	}
    }

    SAVE;
    return 1;
}

public void init_living ()
{
    ::init_living ();

    add_action (feed, "feed");
}

void
default_config_npc (int i)
{
    int     j;
    for (j = 0; j < 6; j++)
        set_base_stat (j, i);
}

public string
query_hunger_desc (int desc_type)
{
    switch (lizard_hunger)
    {
	case -100000..10:
	    return desc_type == HUNGER_ADJ ? "starving" :
		"He is looking on the verge of death from hunger.";
	case 11..100:
	    return desc_type == HUNGER_ADJ ? "starving" :
		"He is looking extemely hungry.";
	case 101..200:
	    return desc_type == HUNGER_ADJ ? "very hungry" :
		"He is looking like he could eat a lot more.";
	case 201..300:
	    return desc_type == HUNGER_ADJ ? "hungry" :
		"He is looking a bit hungry.";
	case 301..400:
	    return desc_type == HUNGER_ADJ ? "thin" :
		"He is looking a but thin.";
	case 401..500:
	    return desc_type == HUNGER_ADJ ? "lean" :
		"He is looking rather lean.";
	case 501..600:
	    return desc_type == HUNGER_ADJ ? "strong" :
		"He is looking strong, although a bit hungry as "
		    + "usual.";
	case 601..700:
	    return desc_type == HUNGER_ADJ ? "fierce" :
		"He is looking strong and fierce, although he "
		    + "looks as though he could eat a bit more.";
	case 701..800:
	    return desc_type == HUNGER_ADJ ? "terrifying" :
		"He is looking fierce and terrible, like he "
		    + "could tear your limbs off by looking at "
		    + "them. He seems as though he might want to "
		    + "eat a bit more...";
	case 801..900:
	    return desc_type == HUNGER_ADJ ? "majestic" :
		"He is looking majestic and fierce.";
	case 901..10000:
	    return desc_type == HUNGER_ADJ ? "invincible" :
		"He is looking as if nothing could stop him. He "
		+ "also seems very well fed.";
    }

    return desc_type == HUNGER_ADJ ? "hungry" :
	"He looks like he could eat a bit more.";

}

public string
lizard_short ()
{
    return query_hunger_desc (HUNGER_ADJ) + " fire-lizard";
}

public int
is_food (object o)
{
    if (function_exists ("create_food", o))
	return 1;
    else
	return 0;
}

public void
eat_present_food ()
{
    object *food = filter (all_inventory (environment (this_object ())),
	is_food);

    if (sizeof (food) > 0)
	{
	devour (food [0]);
	}
}

public void
reset_npc ()
{
    lizard_hunger -= (10 + random (20));
    if (lizard_hunger < 1)
	lizard_hunger = 1;

    eat_present_food ();

    SAVE;
}

void
create_creature()
{
    set_name ("fire-lizard");
    add_name ("lizard");
    add_adj ("fire");
    add_adj ("sinuous");

    set_short ("@@lizard_short@@");

    set_long ("Long and sinuous, this fire lizard has ruby-red "
        + "eyes and long, sharp irridescent scales. He lies curled "
        + "at the base of the stairs, peering around intently.@@extra_desc@@\n");

    set_race_name ("lizard");

    set_alignment (500);

    default_config_npc (162);
    
    set_skill (SS_UNARM_COMBAT, 100);
    set_skill (SS_DEFENCE, 100);

    add_prop (LIVE_I_SEE_INVIS, 1);
    add_prop (LIVE_I_NEVERKNOWN, 1);    
    
    set_attack_unarmed (0,  100, 100, W_IMPALE, 50, "jaws");
    set_attack_unarmed (1, 100, 100, W_BLUDGEON, 50, "tail");
    set_hitloc_unarmed (0, ({ 100 }), 10, "head");
    set_hitloc_unarmed (1, ({ 100 }), 80, "body");
    set_hitloc_unarmed (2, ({ 100 }), 10, "tail");
    
    set_fatigue (9000);
    set_hp (40000);
    
    add_reaction (({ "pet", "hug", "cuddle", "pat",
        "ruffle" }), "purr", 1);
    add_reaction (({ "snuggle", "smile" }), "emote chirps happily.", 0);
    add_reaction ("grin", "leer misc", 1);

    add_reaction (({ "growl", "scowl", "snarl" }), "snarl", 1);
    add_reaction ("tackle", "blink", 0);
    add_reaction (({ "fart", "burp", "puke" }), "stare disgus", 1);

    add_reaction ("ack", "jump", 0);
    add_reaction ("agree", "nod sage", 1);
    add_reaction ("applaud", "bow clums", 0);
    add_reaction ("admire", "blush", 0);
    add_reaction ("apologize", "emote chirps happily.", 0);
    add_reaction ("avert", "avert", 1);
    add_reaction ("back", "snarl misc", 1);
    add_reaction ("beg", "shake", 1);
    add_reaction ("blank", "blank", 0);
    add_reaction ("blush", "sigh .", 0);
    add_reaction ("bow", "stare .", 1);
    add_reaction (({ "bat", "blow", "caress", "gesture", "grope",
        "fawn", "fondle", "french", "puke", "nuzzle",
        "nibble" }), "back", 1);
    add_reaction ("bite", "emote snaps is jaws.", 0);
    add_reaction ("blink", "blink .", 0);
    add_reaction ("boggle", "bounce", 0);
    add_reaction ("brighten", "emote chirps merrily.", 0);
    add_reaction ("beckon", "back", 1);
    add_reaction ("blanch", "emote chirps with concern.", 0);
    add_reaction ("bounce", "bounce", 0);


    /*
    add_reaction ("cackle", "bounce", 0);
    add_reaction ("clap", "bounce", 0);
    add_reaction ("confuse", "bounce", 0);
    add_reaction ("cower", "bounce", 0);
    add_reaction ("curse", "bounce", 0);
    add_reaction ("clear", "bounce", 0);
    add_reaction ("confused", "bounce", 0);
    add_reaction ("cringe", "bounce", 0);
    add_reaction ("curtsey", "bounce", 0);
    add_reaction ("cheer", "bounce", 0);
    add_reaction ("comfort", "bounce", 0);
    add_reaction ("congrat", "bounce", 0);
    add_reaction ("cross", "bounce", 0);
    add_reaction ("choke", "bounce", 0);
    add_reaction ("complain", "bounce", 0);
    add_reaction ("congratulate", "bounce", 0);
    add_reaction ("chortle", "bounce", 0);
    add_reaction ("compliment", "bounce", 0);
    add_reaction ("chuckle", "bounce", 0);
    add_reaction ("conf", "bounce", 0);
    add_reaction ("cough", "bounce", 0);
    add_reaction ("curl", "bounce", 0);
    add_reaction ("dance", "bounce", 0);
    add_reaction ("despair", "bounce", 0);
    add_reaction ("disagree", "bounce", 0);
    add_reaction ("drool", "bounce", 0);
    add_reaction ("duh", "bounce", 0);
    add_reaction ("eeks", "bounce", 0);
    add_reaction ("excuse", "bounce", 0);
    add_reaction ("explode", "bounce", 0);
    add_reaction ("eyebrow", "bounce", 0);
    add_reaction ("fidget", "bounce", 0);
    add_reaction ("flip", "bounce", 0);
    add_reaction ("forgive", "bounce", 0);
    add_reaction ("frown", "bounce", 0);
    add_reaction ("finger", "bounce", 0);
    add_reaction ("flirt", "bounce", 0);
    add_reaction ("fume", "bounce", 0);
    add_reaction ("feign", "bounce", 0);
    add_reaction ("flex", "bounce", 0);
    add_reaction ("fret", "bounce", 0);
    add_reaction ("gag", "bounce", 0);
    add_reaction ("giggle", "bounce", 0);
    add_reaction ("grimace", "bounce", 0);
    add_reaction ("grumble", "bounce", 0);
    add_reaction ("gasp", "bounce", 0);
    add_reaction ("glare", "bounce", 0);
    add_reaction ("grin", "bounce", 0);
    add_reaction ("grovel", "bounce", 0);
    add_reaction ("greet", "bounce", 0);
    add_reaction ("groan", "bounce", 0);
    add_reaction ("growl", "bounce", 0);
    add_reaction ("hang", "bounce", 0);
    add_reaction ("hmm", "bounce", 0);
    add_reaction ("hiccup", "bounce", 0);
    add_reaction ("hold", "bounce", 0);
    add_reaction ("hum", "bounce", 0);
    add_reaction ("ignore", "bounce", 0);
    add_reaction ("jump", "bounce", 0);
    add_reaction ("kick", "bounce", 0);
    add_reaction ("kiss", "bounce", 0);
    add_reaction ("knee", "bounce", 0);
    add_reaction ("kneel", "bounce", 0);
    add_reaction ("laugh", "bounce", 0);
    add_reaction ("leer", "bounce", 0);
    add_reaction ("lick", "bounce", 0);
    add_reaction ("listen", "bounce", 0);
    add_reaction ("love", "bounce", 0);
    add_reaction ("melt", "bounce", 0);
    add_reaction ("moan", "bounce", 0);
    add_reaction ("mourn", "bounce", 0);
    add_reaction ("mumble", "bounce", 0);
    add_reaction ("nod", "bounce", 0);
    add_reaction ("nudge", "bounce", 0);
    add_reaction ("oops", "bounce", 0);
    add_reaction ("ouch", "bounce", 0);
    add_reaction ("pace", "bounce", 0);
    add_reaction ("pat", "bounce", 0);
    add_reaction ("pinch", "bounce", 0);
    add_reaction ("ponder", "bounce", 0);
    add_reaction ("panic", "bounce", 0);
    add_reaction ("peer", "bounce", 0);
    add_reaction ("point", "bounce", 0);
    add_reaction ("pounce", "bounce", 0);
    add_reaction ("purr", "bounce", 0);
    add_reaction ("pant", "bounce", 0);
    add_reaction ("poke", "bounce", 0);
    add_reaction ("pout", "bounce", 0);
    add_reaction ("roar", "bounce", 0);
    add_reaction ("rolleyes", "bounce", 0);
    add_reaction ("rsay", "bounce", 0);
    add_reaction ("ruffle", "bounce", 0);
    add_reaction ("scold", "bounce", 0);
    add_reaction ("shudder", "bounce", 0);
    add_reaction ("sneer", "bounce", 0);
    add_reaction ("squeeze", "bounce", 0);
    add_reaction ("stumble", "bounce", 0);
    add_reaction ("scowl", "bounce", 0);
    add_reaction ("sigh", "bounce", 0);
    add_reaction ("sneeze", "bounce", 0);
    add_reaction ("squirm", "bounce", 0);
    add_reaction ("sulk", "bounce", 0);
    add_reaction ("scratch", "bounce", 0);
    add_reaction ("sing", "bounce", 0);
    add_reaction ("snicker", "bounce", 0);
    add_reaction ("stare", "bounce", 0);
    add_reaction ("swallow", "bounce", 0);
    add_reaction ("scream", "bounce", 0);
    add_reaction ("slap", "bounce", 0);
    add_reaction ("sniff", "bounce", 0);
    add_reaction ("startle", "bounce", 0);
    add_reaction ("swear", "bounce", 0);
    add_reaction ("shake", "bounce", 0);
    add_reaction ("smell", "bounce", 0);
    add_reaction ("snore", "bounce", 0);
    add_reaction ("steam", "bounce", 0);
    add_reaction ("sweat", "bounce", 0);
    add_reaction ("shiver", "bounce", 0);
    add_reaction ("smile", "bounce", 0);
    add_reaction ("snuggle", "bounce", 0);
    add_reaction ("stick", "bounce", 0);
    add_reaction ("swoon", "bounce", 0);
    add_reaction ("shout", "bounce", 0);
    add_reaction ("smirk", "bounce", 0);
    add_reaction ("sob", "bounce", 0);
    add_reaction ("stomp", "bounce", 0);
    add_reaction ("show", "bounce", 0);
    add_reaction ("snap", "bounce", 0);
    add_reaction ("spank", "bounce", 0);
    add_reaction ("stretch", "bounce", 0);
    add_reaction ("shrug", "bounce", 0);
    add_reaction ("snarl", "bounce", 0);
    add_reaction ("spit", "bounce", 0);
    add_reaction ("strut", "bounce", 0);
    add_reaction ("tackle", "bounce", 0);
    add_reaction ("thank", "bounce", 0);
    add_reaction ("tickle", "bounce", 0);
    add_reaction ("trust", "bounce", 0);
    add_reaction ("twitch", "bounce", 0);
    add_reaction ("tap", "bounce", 0);
    add_reaction ("think", "bounce", 0);
    add_reaction ("tingle", "bounce", 0);
    add_reaction ("twiddle", "bounce", 0);
    add_reaction ("tease", "bounce", 0);
    add_reaction ("thumb", "bounce", 0);
    add_reaction ("tremble", "bounce", 0);
    add_reaction ("twinkle", "bounce", 0);
    add_reaction ("wail", "bounce", 0);
    add_reaction ("weep", "bounce", 0);
    add_reaction ("whisper", "bounce", 0);
    add_reaction ("wince", "bounce", 0);
    add_reaction ("worship", "bounce", 0);
    add_reaction ("wait", "bounce", 0);
    add_reaction ("whimper", "bounce", 0);
    add_reaction ("whistle", "bounce", 0);
    add_reaction ("wink", "bounce", 0);
    add_reaction ("wring", "bounce", 0);
    add_reaction ("wave", "bounce", 0);
    add_reaction ("whine", "bounce", 0);
    add_reaction ("wiggle", "bounce", 0);
    add_reaction ("worry", "bounce", 0);
    add_reaction ("yawn", "bounce", 0);
    add_reaction ("yodel", "bounce", 0);
    */

    LOAD;

    heal_hp (query_max_hp ());

    // start to get hungry...
    set_alarm (1800.0, 3600.0, reset_npc);
}


public string
extra_desc ()
{
    if (this_player ()->query_prop (OBJ_I_INVIS) > 0)
        return " His eyes rest on you, even in your invisible "
            + "state. " + query_hunger_desc (HUNGER_LONG);
    else if (this_player ()->query_prop (OBJ_I_HIDE) > 0)
        return " He stares at you with disdain, despite "
            + "your efforts to hide yourself.\n" 
	    + query_hunger_desc (HUNGER_LONG);
    else
        return " " + query_hunger_desc (HUNGER_LONG);
}

public int
query_knight_prestige ()
{
    return -2;
}

public void
add_react (string emotion, string com, int use_player)
{
    react_emotions += ({ emotion });
    react_commands += ({ com });
    react_players += ({ use_player });
}

public void
add_reaction (mixed emotion, string com, int use_player)
{
    int         i;

    if (pointerp (emotion))
    {
        for (i = 0; i < sizeof (emotion); i++)
        {
            add_react (emotion [i], com, use_player);
        }
    }
    else
    {
        add_react (emotion, com, use_player);
    }
}


/*
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this NPC, or when it
 *                is performed on in the room in general, this function is
 *                called to let the NPC know about the emotion. This way we
 *                can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 */
public void
emote_hook(string emote, object actor, string adverb = 0)
{
    int             index;

    if ((index = member_array (emote, react_emotions)) != -1)
    {
        if (react_players [index])
        {
            if (command (react_commands [index]
                + " " + actor->query_real_name ()))
                return;
        }

        command (react_commands [index]);
    }
}
