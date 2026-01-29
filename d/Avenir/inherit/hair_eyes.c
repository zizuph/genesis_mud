// file name:  hair_eyes.c
// creator(s): Lucius, July 2006
// purpose:    Compat inherit to provide npc's with Gelan style
//             hair and eyes functionality.
// note:       Call the two following functions to setup:
//
//	configure_hair(string length, string colour, string style)
//	configure_eyes(string type, string colout, int num_eyes)
//
//	       After, you have to add your own subloc, or
//	       describe it yourself manually. For an example,
//	       see near the end of this file.
//
// revision history:
//
#if 0
//
//  Add this to your npc's to see the configured hair / eyes.
//
public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc == hair_subloc())
	return gelan_hair();

    if (subloc == eyes_subloc())
	return gelan_eyes();

    return ::show_subloc(subloc, on, for_obj);
}
#endif

#pragma no_clone
#pragma strict_types

#include <stdproperties.h>

#define EYES_SUBLOC	"eyes"
#define HAIR_SUBLOC	"hairstyle"

#define EYES_SOUL	"/d/Calia/gelan/specials/eyes_cmdsoul"
#define HAIR_SOUL	"/d/Calia/gelan/specials/hair_cmdsoul"

public static int eyes_num = 2;
public static string eyes_desc, eyes_col, eyes_type;
public static string hair_desc, hair_len, hair_col, hair_style;

#define RAN_EMOTES
#ifdef RAN_EMOTES
public static string *hair_emotes = ({
    "hrun", "htoss", "htwist", "hstroke", "hbrush",
});

public static string *eyes_emotes = ({
    "eyeblink", "eyepeer", "eyerub", "eyetwinkle", "eyesparkle",
    "eyestare",
});
#endif

/*
 *  HAIR Section.
 */
public string
query_hairstyle(void)		{ return hair_desc;	}

public string
query_hair_length(void)		{ return hair_len;	}

public string
query_hair_colour(void)		{ return hair_col;	}

public string
query_hair_style(void)		{ return hair_style;	}

public void
add_hair_commands(void)
{
    this_object()->add_cmdsoul(HAIR_SOUL);
    this_object()->update_hooks();
}

static void
configure_hair(string len, string col, string stl)
{
    if (!strlen(len) || !strlen(col) || !strlen(stl))
	return;

    hair_len   = len;
    hair_col   = col;
    hair_style = stl;
    hair_desc  = hair_len +", "+ hair_col +" and "+ hair_style;

    this_object()->add_subloc(HAIR_SUBLOC, this_object());

    add_hair_commands();
}

/*
 *  EYES Section.
 */
public string
query_eyes(void)	    	{ return eyes_desc;	}

public string
query_eyes_colour(void)		{ return eyes_col;	}

public string
query_eyes_type(void)		{ return eyes_type;	}

public int
query_eyes_number(void)		{ return eyes_num;	}

public void
add_eyes_commands(void)
{
    this_object()->add_cmdsoul(EYES_SOUL);
    this_object()->update_hooks();
}

static void
configure_eyes(string type, string col, int num)
{
    if (!strlen(type) || !strlen(col))
	return;

    eyes_type = type;
    eyes_col  = col;
    eyes_num  = (num ?: 2);
    eyes_desc = eyes_type +" "+ eyes_col;

    this_object()->add_subloc(EYES_SUBLOC, this_object());

    add_eyes_commands();
}

public int
query_gelan_eyes_shadow(void)
{
    return strlen(eyes_desc);
}

/*
 *  DESC Section.
 */
static string
gelan_hair(void)
{
    if (!strlen(hair_desc))
	return "";

    return capitalize(this_object()->query_possessive()) +
	" hair is "+ hair_desc +".\n";
}

static string
gelan_eyes(void)
{
    if (!strlen(eyes_desc))
	return "";

    return capitalize(this_object()->query_pronoun()) +" has"+
	(eyes_num == 1 ? " one " : " ") + eyes_desc +
	(eyes_num == 1 ? " eye" : " eyes") + ".\n";
}

static string
hair_subloc(void)	{ return HAIR_SUBLOC; }

static string
eyes_subloc(void)	{ return EYES_SUBLOC; }


#ifdef RAN_EMOTES
/*
 *  EMOTES Section.
 */
static varargs object
random_target(int flag)
{
    object *obs = all_inventory(environment()) - ({ this_object() });

    if (flag)
	obs = filter(obs, query_interactive);
    else
	obs = filter(obs, living);

    return one_of_list(obs);
}

#define OB_NUM(ob)    (explode(file_name(ob) + "#0", "#")[1])
#define OB_NAME(ob)   ("ob_" + OB_NUM(ob))

public varargs int
_random_emote(string emote, string adverb, mixed who)
{
    if (!strlen(emote))
	return 0;

    if (strlen(adverb))
	emote += " "+ adverb;

    if (objectp(who))
	emote += " "+ OB_NAME(who);
    else if ((who == 1) && (who = random_target(0)))
	emote += " "+ OB_NAME(who);
    else if ((who == 2) && (who = random_target(1)))
	emote += " "+ OB_NAME(who);

    return command(emote);
}

public int
random_hair_emote(void)
{
    return _random_emote(one_of_list(hair_emotes));
}

public int
random_eyes_emote(void)
{
    return _random_emote(one_of_list(eyes_emotes));
}
#endif
