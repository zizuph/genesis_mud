inherit "/std/guild/guild_lay_sh.c";
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

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
     ({"giggle","laugh","snicker","chuckle","snort","chatter","babble",	\
       "jabber"}),							\
     ({"declare","announce","proclaim","cry","exclaim"}),		\
     ({"say","convey","suggest","mention","admit","confess","conceed",	\
       "suggest","delineate","answer","reply","aquiesce","agree",	\
       "explain","hint","imply","chatter","claim","think","observe"}),	\
     ({"sigh","murmur","mutter","mumble","confess","whine","sniff",	\
       "wail","lament","moan","groan","sob","plead"}),			\
     ({"snarl","growl","insinuate","imply","snort","snap","yell",	\
       "exclaim","bark","bellow","roar","shriek"}),			\
     ({"chant","intone","sing","trill","croon","carol","warble",	\
       "howl","incant","ululate","burst into song"})			\
 })

#define ASKARRAY ({"ask", "query", "ponder", "wonder", "inquire"})
#define EXCLAIMARRAY ({"declare","announce","cry","exclaim","yell",	\
		       "bellow","roar","shriek","howl"})

string	    temp_name;

query_guild_tax_lay() { return 7; }
query_guild_style_lay() { return "cleric"; }
query_guild_name_lay() { return GUILD_NAME; }

query_guild_not_allow_join_lay(player, type, style, name)
{
    if (::query_guild_not_allow_join_lay(player, type, style, name))
	return 1;
    notify_fail(BS("Your evil deeds have blackened your heart and deafened your "
    + "ears to the beauty of music. Come back when you have cleansed your "
    + "soul of the darkness within.\n"));
    if (player->query_alignment() <-100)
	return 1;

    return 0;
}

query_title()
{
    string old_title, str;

    switch (shadow_who->query_stat(SS_LAYMAN))
    {
	case 0..2: str = "Minstrel of NO Renown"; break;
	case 3..4: str = "Apprentice Performer"; break;
	case 5..7: str = "Accomplished Performer"; break;
	case 8..9: str = "Apprentice Chorister"; break;
	case 10..12: str = "Chorister"; break;
	case 13..14: str = "Apprentice Psalmist"; break;
	case 15..16: str = "Psalmist"; break;
	case 17: str = "Apprentice Hymner"; break;
	case 18..19: str = "Distinguished Hymner"; break;
	case 20: str = "Apprentice Melodist"; break;
	case 21..22: str = "Principal Melodist"; break;
	case 23: str = "Apprentice Balladeer"; break;
	case 24..25: str = "Balladeer of Great Prestige"; break;
	case 26: str = "Apprentice Contrapuntist"; break;
	case 27..28: str = "Celebrated Contrapuntist"; break;
	case 29..30: str = "Apprentice Bard"; break;
	case 31..34: str = "Bard of Renown"; break;
	case 35..36: str = "Apprentice Troubadour"; break;
	case 37..38: str = "Troubadour of Glorious Repute"; break;
	case 39..41: str = "Apprentice Minstrel"; break;
	case 42..45: str = "Most Honored Minstrel of the Commons"; break;
	case 46..48: str = "Most Noble Minstrel of the Lays"; break;
	case 49..52: str = "Most Exalted Minstrel of the Court"; break;
	case 53..56: str = "Minstrel of the Tones"; break;
	case 57..60: str = "Apprentice Precentor"; break;
	case 61..62: str = "Honored Precentor of the Canticles"; break;
	case 63: str = "Apprentice Cantor"; break;
	case 64..65: str = "Eminent Cantor of the Antiphons"; break;
	case 66: str = "Apprentice Scholar of Polyphony"; break;
	case 67..68: str = "Elect Scholar of Polyphony"; break;
	case 69: str = "Apprentice Illuminate of Mellifluous Song"; break;
	case 70..71: str = "Illuminate of Mellifluous Song"; break;
	case 72: str = "Apprentice Abecedarian of Sonority"; break;
	case 73..74: str = "Lauded Abecedarian of Sonority"; break;
	case 75: str = "Apprentice Docent of Harmony"; break;
	case 76..77: str = "Exalted Docent of Harmony"; break;
	case 78: str = "Apprentice Minister of the Concords"; break;
	case 79..80: str = "Esteemed Minister of the Concords"; break;
	case 81..82: str = "Apprentice Master of the Tones"; break;
	case 83..84: str = "Illustrious Master of the Tones"; break;
	case 85..86: str = "Candidate Doctor of Music"; break;
	case 87..88: str = "Learned Doctor of Music"; break;
	default: str = "August Doctor of Music"; break;
    }    
    if (shadow_who->query_real_name()==GUILDMASTER)
	str = "Guildmaster of the Minstrels";
    old_title = shadow_who->query_title();
    if (strlen(old_title))
	old_title += " and ";
    else
	old_title = "";
    return old_title+str;
}

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

/*
 * Function:	query_guild_skill_name
 * Description: When a player uses the skills command s/he should get the
 *		proper name of the skill.
 * Arguments:	type - the number of the skill
 * Returns:	0 if no skill of mine,  else the string.
 */
mixed
query_guild_skill_name(int type)
{
    switch(type)
    {
	case SG_READ_MUSIC:
	    return "read music";
	    break;
	case SG_VOCAL:
	    return "sing";
	    break;
	case SG_INSTRUMENTAL:
	    return "play instrument";
	    break;
	case SG_TUNE_REPAIR:
	    return "tune/repair instrument";
	    break;
	case SG_VOCAL_DAMAGE:
	    return "";
	    break;
	case SG_FLAG:
	    return "";
	    break;
    }
    return 0;
}

/*
 * Function: query_muse
 * Description: Which Muse sponsors this Minstrel's musical endeavors?
 * Returns: the number of the Muse (see guild_defs.h for a list of Muses).
 */
int
query_muse()
{
	return (shadow_who->query_skill(SG_FLAG) & MUSEMASK) / MUSEMASKBASE;
}

/*
 * Function: query_muse_name
 * Description: Returns the name of the muse of this minstrel.
 */
string
query_muse_name()
{
    switch(query_muse())
    {
	case 1:
	    return MUSE1;
	case 2:
	    return MUSE2;
	case 3: 
	    return MUSE3;
	case 4: 
	    return MUSE4;
	default: 
	    return "<Yikes! Problem with the Muse! See the Guildmaster!>";
    }
}

/*
 * Function: set_muse
 * Description: set the player's Muse number.
 * Arguments: muse - the number of the muse.
 */
void
set_muse(int muse)
{
	shadow_who->set_skill(SG_FLAG,shadow_who->query_skill(SG_FLAG) & (~MUSEMASK));
	shadow_who->set_skill(SG_FLAG,shadow_who->query_skill(SG_FLAG) + muse*MUSEMASKBASE);
}

#ifdef 0
/*
 * The following functions provide support for the Entice spell.
 * They are here to notify the Minstrel's familiar when attacked.
 */
/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (random(10))
        call_out("help_friend", 1, attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say You scum, stop fighting my friend!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
#endif
