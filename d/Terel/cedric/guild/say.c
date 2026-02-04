/*
 * /d/Terel/cedric/guild/say.c
 *
 * This module has been coded by /Mercade on November 9 1995 to allow the
 * members of the Minstrel Guild to speak their own way without having to
 * recreate a say-command. The mudlib speech module has been adapted to
 * allow this. The code that determines the sound the player makes has been
 * based on the implementation by Cedric. The sounds the player can make
 * are his too.
 *
 * /Mercade, November 9 1995.
 *
 * Modified by Arman as part of the guild transition to /d/Terel/guilds/minstrels/
 * - December 2019
 */

#pragma no_clone
#pragma no_inherit
#pragma resident
#pragma save_binary
#pragma strict_types

#include "/d/Terel/guilds/minstrels/guild_defs.h";

/*
 * This defines the number of moods (save the random mood), ergo the size
 * of the verbarray, the size of the askarray and the size of the exclaim-
 * array. We do this since these values are static, so we don't have to
 * have them computed at runtime all the time.
 */
#define SIZEOF_MOODS        (16)
#define SIZEOF_ASKARRAY     ( 5)
#define SIZEOF_EXCLAIMARRAY ( 9)

/*
 * Global variables.
 */
static string sound = "say";
static mixed verbarray = 
   ({ ({ "admit", "say", "murmur", "mutter", "conceed", "enunciate", "convey",
         "mention", "imply", "claim", "utter","think" }),
      ({ "giggle", "laugh", "snicker", "chuckle", "snort", "chatter",
         "babble", "jabber"}),
      ({ "declare", "announce", "proclaim", "cry", "exclaim" }),
      ({ "say", "convey", "suggest", "mention", "admit", "confess", "conceed",
         "suggest", "delineate", "answer", "reply", "aquiesce", "agree",
         "explain", "hint", "imply", "chatter", "claim", "think",
         "observe" }),
      ({ "sigh", "murmur", "mutter", "mumble", "confess", "whine", "sniff",
         "wail", "lament", "moan", "groan", "sob", "plead" }),
      ({ "snarl", "growl", "insinuate", "imply", "snort", "snap", "yell",
         "exclaim", "bark", "bellow", "roar", "shriek" }),
      ({ "chant", "intone", "sing", "trill", "croon", "carol", "warble",
         "howl", "incant", "ululate", "burst into song" }),
      ({ "sneer", "smirk", "snort", "retort", "snicker", "grin", "snap",
         "laugh", "chuckle", "scoff" }),
      ({ "say" }),
      ({ "breath", "coo", "whisper", "smile" }),
      ({ "whisper", "breath", "murmur", "insinuate", "hint", "whisper" }),
      ({ "whine", "moan", "complain", "sob", "plead", "snivel", "pout" }),
      ({ "twitter", "jabber", "coo", "sigh", "mention", "laugh" }),
      ({ "observe", "note", "explain", "indicate", "mention", "remark" }),
      ({ "utter", "blurt", "snap", "delineate", "say", "retort" }),
      ({ "decree", "delineate", "claim", "remark", "sneer", "announce" })
   });
static string *askarray =
      ({ "ask", "query", "ponder", "wonder", "inquire" });
static string *exclaimarray =
      ({ "declare", "announce", "cry", "exclaim", "yell", "bellow", "roar",
         "shriek", "howl" });

/*
 * Function name: race_sound
 * Description  : This function will return the sound the onlookers hear
 *                when a player speaks.
 * Returns      : string - the sound.
 */
public string
race_sound()
{
    if (wildmatch("*s", sound))
    {
	return sound + "es";
    }

    switch (sound)
    {
    case "reply":
	return "replies";
    case "query":
	return "queries";
    case "imply":
	return "implies";
    case "cry":
	return "cries";
    case "breath":
	return "breathes";
    case "burst into song":
	return "bursts into song";
    }

    return sound + "s";
}

/*
 * Function name: actor_race_sound
 * Arguments    : This will return the sound the actor will hear him or
 *                herself make.
 * Returns      : string - the sound.
 */
public string
actor_race_sound()
{
    int mood;

   string *exc_array = PERFORM_MANAGER->query_mood_excluded_verbs(this_player());

    switch(extract(this_player()->query_say_string(), -1))
    {
    case "?":
        askarray = askarray - exc_array; 
	sound = askarray[random(sizeof(askarray))];
        if(!sound)
            sound = "say";
	return sound;
	
    case "!":
        exclaimarray = askarray - exc_array;
	sound = exclaimarray[random(sizeof(exclaimarray))];
        if(!sound)
            sound = "say";
	return sound;
    }

    if ((mood = this_player()->query_mood()) == RANDOM)
    {
	mood = random(SIZEOF_MOODS);
    }
    else
    {
	mood--;
    }

    string *verbs = verbarray[mood]; 
    verbs = verbs - exc_array;

    sound = verbs[random(sizeof(verbs))];
        if(!sound)
            sound = "say";
    return sound;
}
