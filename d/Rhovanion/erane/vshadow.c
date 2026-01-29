inherit "/std/shadow";

/* inherit "/std/guild/guild_lay_sh.c"; */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
string query_guild_style_occ() { return "everything"; }
string query_guild_name_occ() { return "All guilds"; }
string query_guild_style_lay() { return "everything"; }
string query_guild_name_lay() { return "Anything else"; }
int query_guild_tax_occ() { return 0; }
int query_guild_tax_lay() { return 0; }
*/

string query_def_post() { return "/d/Genesis/wiz/post"; }
int clean_up() { return 0; } /* Leave it alone */

#define SUBLOC "_rhovanion_wizard_"

/* I put it here so I wouldn't need the autoloading object. */

/*
 * THE GUILD SHADOW FOR THE MINSTRELS
 * 
 * Variables:
 * 
 * 
 * Functions:      i = int   s = string   o = object
 *  communicate()
 * 
 * 
 * Thanks to Karath for many suggestions regarding the say verbs!
 * Cedric 4/93
 * 
 * Helpful note: shadow_who is a variable containing the shadowed player.
 */

#define VERBARRAY							\
 ({  ({"admit","say","murmur","mutter","conceed","enunciate","convey",	\
       "mention","imply","claim","utter","think"}),			\
     ({"giggle","laugh","snicker","chuckle","chatter","babble",         \
       "jabber"}),							\
     ({"declare","announce","proclaim","cry","exclaim"}),		\
     ({"say","convey","suggest","mention","admit","confess","conceed",	\
       "suggest","delineate","answer","reply","aquiesce","agree",	\
       "explain","hint","imply","chatter","claim","think","observe"}),	\
     ({"sigh","murmur","mutter","mumble","confess","whine","sniff",	\
       "wail","lament","moan","groan","sob","plead"}),			\
     ({"snarl","growl","insinuate","imply","snap","yell",        	\
       "exclaim","bark","roar","shriek"}),      			\
     ({"chant","intone","sing","trill","croon","carol","warble",	\
       "howl","incant","ululate","burst into song"})			\
 })

#define ASKARRAY ({"ask", "query", "ponder", "wonder", "inquire"})
#define EXCLAIMARRAY ({"declare","announce","cry","exclaim","yell",	\
		       "bellow","roar","shriek","howl"})

string	    temp_name;

/*
 * Function:	query_mood
 * Description: What is the current mood of the minstrel?
 * Returns:	The number of the mood.
 */
int
query_mood()
{
    return shadow_who->query_skill(SG_FLAG)&MOODMASK;
}

/*
 * Function:	query_mood_name
 * Description: What is the current mood of the minstrel?
 * Returns:	A string containing the mood, e.g. "jovial".
 */
string
query_mood_name()
{
    switch(query_mood())
    {
	case NORMAL: return "random";
	case SERIOUS: return "serious";
	case JOVIAL: return "jovial";
	case BRAVE: return "brave";
	case CONVERSE: return "conversational";
	case SAD: return "sad";
	case ANGRY: return "angry";
	case SONG: return "song";
	
	default: return "Yikes! Don't know that mood...";
    }
}


public string
public_sound(string str, object target)
{
    string *arr;
    
    if (!interactive(target))
	return "says";
	    
    arr=explode(str, "");
    if (arr[sizeof(arr)-1]=="s")
    {
	str=str+"es";
	return str;
    }
    switch (str)
    {
	case "reply":		return "replies";
	case "query":		return "queries";
	case "imply":		return "implies";
	case "cry":		return "cries";
	case "burst into song":	return "bursts into song";
    }
    str=str+"s";
    return str;
}

public int
communicate(string str) /* Must have it here for special with ' */
{
    string  verb, *the_array;
    object  *plist;
    int	    index, i;

    verb = query_verb();
    if (str == 0)
	str = "";
    if (strlen(verb) && verb[0] == "'"[0])
	if (strlen(str))
	    str = extract(verb, 1) + " " + str;
	else
	    str = extract(verb, 1);
	
    switch (extract(str, strlen(str)-1))
    {
	case "?":
	    the_array = ASKARRAY;
	    break;
	case "!":
	    the_array = EXCLAIMARRAY;
	    break;
	default: 
	    if (query_mood()==NORMAL)
		the_array = VERBARRAY[random(sizeof(VERBARRAY))];
	    else
		the_array = VERBARRAY[query_mood()-1];
    }
    plist = all_inventory(environment(TP())) + ({environment(TP())});
    index = random(sizeof(the_array));
    for (i=0;i<sizeof(plist);i++)
	if (living(plist[i])&&plist[i]!=TP())
	    plist[i]->catch_msg(QCTNAME(TO())+" "
	    +public_sound(the_array[index], plist[i])
	    +": "+str+"\n", TP());
    
    if (this_player()->query_get_echo())
        write("You "+the_array[index]+": " + str + "\n");
    else
        write("Ok.\n");

    return 1;
}

/*
 * Function:	set_mood
 * Description: Minstrels may set their mood; the setting will be 
 *		reflected in 'say' verb choice as well as default
 *		settings for standard emotes (nod, grin, etc).
 * Arguments:	mood - the number of the mood; see defines in 
 *		guild_defs.h for the various moods.
 * Returns:	1 if successful, else 0.
 */
int
set_mood(int mood)
{
    shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)& (~MOODMASK));
    shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)+mood);
    return 1;
}


/*
 * Function:	query_hear_bells
 * Description: Can the player hear the Bells of the Tower? These ring every 
 *		reset and whenever a Minstrel enters the game.
 * Returns:	1 if the player can hear the Bells.
 */
int
query_hear_bells()
{
    return (shadow_who->query_skill(SG_FLAG)&BELLMASK) / BELLMASK;
}

/*
 * Function:	set_hear_bells
 * Description: Sets the bell_flag of the player
 * Arguments:	hear - 1 if the player wishes to hear the bells, 0 otherwise.
 */
void
set_hear_bells(int hear)
{
    shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)|BELLMASK);
}

/*
 * Function:	query_hear_dias
 * Description: Can the player hear others speaking from the dias in the 
 *		courtyard of the Minstrels HQ?
 * Returns:	1 if the player can hear the dias speakers.
 */
int
query_hear_dias()
{
    return (shadow_who->query_skill(SG_FLAG)&DIASMASK) / DIASMASK;
}

/*
 * Function:	set_hear_dias
 * Description: Sets the dias_flag of the player
 * Arguments:	hear - 1 if the player wishes to hear the dias speakers,
 *		0 otherwise.
 */
void
set_hear_dias(int hear)
{
    shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)|DIASMASK);
}

/*
 * Function:	query_hear_ballads
 * Description: Can the player hear the Ballads sung by other Minstrels? 
 * Returns:	1 if the player can hear the Ballads.
 */
int
query_hear_ballads()
{
    return (shadow_who->query_skill(SG_FLAG)&BALLADMASK) / BALLADMASK;
}

/*
 * Function:	set_hear_ballads
 * Description: Sets the ballad_flag of the player
 * Arguments:	hear - 1 if the player wishes to hear the Ballads, 0 otherwise.
 */
void
set_hear_ballads(int hear)
{
    shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)|BALLADMASK);
}

/* Shire stuff here */

string show_subloc(string subloc, object who, object for_obj)
{
    string str;
    int tmp;

    if ( subloc != SUBLOC )
    {
        return query_shadow_who()->show_subloc(subloc,who,for_obj);
    }
    if ( who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) )
    {
        return "";
    }
    if ( for_obj == who )
    {
        str = "You are ";
    }
    else
    {
        str = capitalize(who->query_pronoun())+" is ";
    }
    str += "a greatly admired member of the glorious Hin Warrior guild.\n";
    if ( for_obj == who )
    {
        str += "You are ";
    }
    else
    {
        str += capitalize(who->query_pronoun())+" is ";
    }
    str += "a mighty wizard of Rhovanion.\n";
    return str;
}

/* My custom death sequence, I'm a wizard anyway, what should it matter */

public void
do_die(object killer)
{
    if ( shadow_who->query_hp() > 0 )
    {
        return;
    }
    shadow_who->catch_msg("Death appears behind you.\n");
    shadow_who->catch_msg("Death says: COME WITH ME TRENIX, IT IS TIME.\n");
    tell_room(environment(shadow_who),
      "Death appears behind Trenix and begins to talk with him.\n",
      shadow_who);
    shadow_who->catch_msg("You smirk at Death and kick him in his boney "+
      "briches sending\nhim flying over the horizon.\n");
    tell_room(environment(shadow_who),
      "Trenix smirks at Death and kicks him in his boney briches sending\n"+
      "him flying over the horizon.\n",shadow_who);
    shadow_who->set_hp(shadow_who->query_max_hp());
    shadow_who->set_mana(shadow_who->query_max_mana());
    shadow_who->set_fatigue(shadow_who->query_max_fatigue());
    shadow_who->add_panic(shadow_who->query_panic()*(-1));
    return;
}

varargs string
query_name(int flag)
{
  if ( explode(file_name(previous_object()),"#")[0] ==
               "/d/Shire/common/guild/pipe" )
  {
    return "Trenix";
  }
  /* return "Trenix the Explorer"; */
  return "Trenix";
}

/* This is also done in my workroom. */

void set_sublocs(object obj)
{
    obj->add_subloc(SUBLOC, this_object());
    return;
}

/* EOF */
