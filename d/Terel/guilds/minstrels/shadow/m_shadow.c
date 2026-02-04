#pragma save_binary

inherit "/std/guild/guild_lay_sh.c";
#include <macros.h>
#include <ss_types.h>
#include <flags.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

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
 *
 * revisions:  Lilith Apr 2022, added muse_punish() function
 */

/*
 * Prototypes:
 */
int query_random_voice();
int query_mood();

void banish_me();

public void     initialize_minstrel();
public object   query_top_shadow();

/*
 * Globals:
 */

string title_extra;
string special_title;

string *malevoices = ({ MALEVOICES });
string *femalevoices = ({ FEMALEVOICES });

void remove_lay_member();

public varargs string query_special_title(string who);

static string *minstrel_titles = ({ "Minstrel of NO Renown",
    "Apprentice Performer",
    "Accomplished Performer",
    "Apprentice Chorister",
    "Chorister",
    "Apprentice Psalmist",
    "Psalmist",
    "Apprentice Hymner",
    "Distinguished Hymner",
    "Apprentice Melodist",
    "Principal Melodist",
    "Apprentice Balladeer",
    "Balladeer of Great Prestige",
    "Apprentice Contrapuntist",
    "Celebrated Contrapuntist",
    "Apprentice Bard",
    "Bard of Renown",
    "Apprentice Troubadour",
    "Troubadour of Glorious Repute",
    "Apprentice Minstrel",
    "Most Honored Minstrel of the Commons",
    "Most Noble Minstrel of the Lays",
    "Most Exalted Minstrel of the Court",
    "Minstrel of the Tones",
    "Apprentice Precentor",
    "Honored Precentor of the Canticles",
    "Apprentice Cantor",
    "Eminent Cantor of the Antiphons",
    "Apprentice Scholar of Polyphony",
    "Elect Scholar of Polyphony",
    "Apprentice Illuminate of Mellifluous Song",
    "Illuminate of Mellifluous Song",
    "Apprentice Abecedarian of Sonority",
    "Lauded Abecedarian of Sonority",
    "Apprentice Docent of Harmony",
    "Exalted Docent of Harmony",
    "Apprentice Minister of the Concords",
    "Esteemed Minister of the Concords",
    "Apprentice Master of the Tones",
    "Illustrious Master of the Tones",
    "Candidate Doctor of Music",
    "Learned Doctor of Music",
    "August Doctor of Music",});

#define MAX_GUILD_LEVEL   42
#define DISTINGUISHED     9
#define AOD_MASTER        ("/d/Emerald/common/guild/aod/obj/master")
#define START             ("/d/Terel/cedric/guild/dorm")

/*
 * Functions:
 */
int query_guild_tax_lay()
{
    return GUILD_TAX;
}

string query_guild_style_lay() 
{
    return "cleric";
}

string query_guild_name_lay()
{
    return GUILD_NAME;
}

int query_guild_not_allow_join_lay(object player, string type,
                                   string style, string name)
{
   if (::query_guild_not_allow_join_lay(player, type, style, name))
      return 1;

   return 0;
}

mixed acceptable_member(object who)
{
    // Ogres are too big to play the instruments of the muses
    if (this_player()->query_guild_name_occ() == "Army of Darkness")
    {
        return "Your hands are too big to play the instruments " +
            "of the muses!\n";
    }

    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
    /*  Vampires of Faerun can temporarily turn players undead via
        /d/Faerun/kryptg/obj/undead_convert_poison.c

        This check is to make sure it doesn't boot the minstrel. */

        if(present("Faerun Convert To Undead Poison", this_player()))
        {
            return 1;
        }

        return "The muses reject your undead soul.\n";
    }

    return 1;
}

/*
 * Function:    query_guild_leader_lay
 * Description: should return 1 if shadow_who is a member of the Cycle
 */
int query_guild_leader_lay()
{
    if (query_special_title())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* 
 * Function:    query_guild_trainer_lay
 * Description: returns a path to the area where Minstrels train their 
 *              skills.
 */
mixed
query_guild_trainer_lay()
{
    return ({ GUILD+"cubicle",
              "/d/Emerald/telberin/arts/minstrel_guild_hall7", 
           });
}

/*
 * Function:    race_sound
 * Description: Points the mudlib towards say.c to pick a random "say" verb
 *              befitting the mood of the Minstrel.
 *              If the mood is neutral, return the "normal" speech.
 */
string race_sound()
{
    if (query_mood() == NEUTRAL)
    {
        return shadow_who->race_sound();
    }
    else
    {
        return (GUILD + "say")->race_sound();
    }
}

/*
 * Function:    actor_race_sound
 * Description: Points the mudlib towards say.c to pick a random "say" verb
 *              befitting the mood of the Minstrel.
 *              If the mood is neutral, return the "normal" speech.
 */
string actor_race_sound()
{
    if (query_mood() == NEUTRAL)
    {
        return shadow_who->actor_race_sound();
    }
    else
    {
        return (GUILD + "say")->actor_race_sound();
    }
}

/*
 * Function:    query_muse
 * Description: which Muse sponsors this Minstrel's musical endeavors?
 * Returns:     the number of the Muse (see guild_defs.h for a list of Muses).
 * Note:        This is only retained for backward compatibility
 */
int
query_muse()
{
    string muse;

    setuid();
    seteuid(getuid());

    if (muse = MEMBER_MANAGER->query_muse(shadow_who))
    {
        switch (muse)
        {
            case MUSE1: return 1;
            case MUSE2: return 2;
            case MUSE3: return 3;
            case MUSE4: return 4;
            default:    return 0;
        }
    }

    return (shadow_who->query_skill(SG_FLAG) & MUSEMASK) / MUSEMASKBASE;
}

/*
 * Function:    query_muse_name
 * Description: Returns the name of the muse of this minstrel.
 */
string
query_muse_name()
{
    string muse;

    setuid();
    seteuid(getuid());

    if (muse = MEMBER_MANAGER->query_muse(shadow_who))
    {
        return muse;
    }

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

public void
remove_old_songbook()
{
    if (sizeof(filter(all_inventory(shadow_who), &->remove_old_minstrel_songbook())))
    {
        setuid();
        seteuid(getuid());
        clone_object(MINSTREL_GUILD_OBJECT)->move(this_player(), 1);
        return;
    }

    if (!shadow_who->query_prop(PLAYER_I_AUTOLOAD_TIME))
    {
        return;
    }

    set_alarm(2.0, 0.0, remove_old_songbook);
}

public void
remove_performer_songbook()
{
    if (present("performer_song_book", shadow_who))
    {
        object book; 
        book = present("performer_song_book",shadow_who);
        if (book) book->remove_object();
        return;
    }

    if (!shadow_who->query_prop(PLAYER_I_AUTOLOAD_TIME))
    {
        return;
    }

    set_alarm(2.0, 0.0, remove_performer_songbook);
}

public void
remove_performer_instrument()
{
    if (present("performer_instrument", shadow_who))
    {
        object instrument; 
        instrument = present("performer_instrument",shadow_who);
        if (instrument) instrument->remove_object();
        return;
    }

    if (!shadow_who->query_prop(PLAYER_I_AUTOLOAD_TIME))
    {
        return;
    }

    set_alarm(2.0, 0.0, remove_performer_instrument);
}

public void
remove_cedric_songbook()
{
    if (present("cedric_song_book", shadow_who))
    {
        // DEBUG("cedric book detected in remove songbook func");

        object book; 
        book = present("cedric_song_book",shadow_who);
        if (book) book->remove_object();

        setuid();
        seteuid(getuid());
        if (!present("minstrel_song_book", shadow_who))
        {
            // DEBUG("minstrel book not detected in remove songbook func");
            clone_object(MINSTREL_GUILD_OBJECT)->move(shadow_who, 1);
        }

        return;
    }

    if (!shadow_who->query_prop(PLAYER_I_AUTOLOAD_TIME))
    {
        return;
    }

    set_alarm(2.0, 0.0, remove_cedric_songbook);
}

public void
send_minstrel_invite()
{
    object invite;
    string minstrel = capitalize(shadow_who->query_real_name());

    setuid();
    seteuid(getuid());

    shadow_who->catch_msg("A messenger appears before you, bows, and hands " +
        "you a formal invitation. He then turns and departs as swiftly as " +
        "he came.\n");
    tell_room(environment(shadow_who), "A messenger arrives and bows before " +
        QTNAME(shadow_who)+ ", passing " +shadow_who->query_objective()+
        " a formal invitation before swiftly leaving.\n", 
        ({ shadow_who }), shadow_who);

    invite = clone_object(NEW_GUILDOBJ + "minstrel_invite");
    invite->set_invite_name(minstrel);
    invite->move(this_player(), 1);
}

public void
initialize_minstrel()
{
    setuid();
    seteuid(getuid());

    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(GUILDSOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    if (!MEMBER_MANAGER->query_muse(shadow_who))
    {
        MEMBER_MANAGER->set_muse(shadow_who, query_muse_name());
    }

    if (MEMBER_MANAGER->query_council_position(shadow_who))
    {
        shadow_who->add_cmdsoul(CYCLE_SOUL);
    }

    if(!IS_PERFORMER(shadow_who))
    {
        PERFORM_MANAGER->add_member(shadow_who);

        int per_level = shadow_who->query_stat(SS_LAYMAN) / 21;

        if(per_level > 6)
            per_level = 6;

        PERFORM_MANAGER->set_reputation_level(shadow_who, per_level);
    }

    shadow_who->update_hooks(); 

    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }

    if (sizeof(get_dir(BANISHDIR+shadow_who->query_real_name()+"_banished")))
    {
        shadow_who->banish_me();
    }

    // Remove performer club song book
    if (present("performer_song_book", shadow_who))
    {
        remove_performer_songbook();
    }

    // Remove performer club song book
    if (present("performer_instrument", shadow_who))
    {
        remove_performer_instrument();
    }

    // Remove old guild object
    if (present("cedric_song_book", shadow_who))
    {
        // DEBUG("cedric minstrel book detected in init");
        remove_cedric_songbook();
    }

    // Clone the guild object
    if (!present("minstrel_song_book", shadow_who))
    {
        DEBUG("minstrel book not detected in init");
        clone_object(MINSTREL_GUILD_OBJECT)->move(shadow_who, 1);
    }

    // Clone invitation to Minstrel Guild in Telberin
    if (REPUTATION(shadow_who) >= DISTINGUISHED)
    {
        // DEBUG("reputation check called");
        if(!PERFORM_MANAGER->query_visited_telberin_guild(shadow_who))
            if (!present("minstrel_invitation", shadow_who))
                set_alarm(4.0, 0.0, &send_minstrel_invite());
    }

    set_alarm(2.0, 0.0, &remove_old_songbook());
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

/*
 * Function name: init_lay_shadow()
 * Description: This function is called from autoload_shadow and may
 *              be used to initialize the shadow when it's loaded.
 * Arguments: The argument string sent to autoload_shadow.
 */
void 
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.5, 0.0, initialize_minstrel);
    set_alarm(3.0, 0.0, &query_guild_keep_player(shadow_who));
}

int
query_guild_keep_player(object player)
{
    string name = shadow_who->query_real_name();

    if (shadow_who->query_prop(LIVE_I_UNDEAD))
    {
        shadow_who->catch_msg("The muses reject your undead soul.\n");
        set_alarm(1.0, 0.0, remove_lay_member);
    }

    // The AOD master might not be loaded
    setuid();
    seteuid(getuid());

    // Ogres are too big to play the instruments of the muses
    if (AOD_MASTER->query_membership_status(name))
    {
        DEBUG("query expel AoD called in Minstrel shadow");

        shadow_who->catch_msg("Your hands are too big to play the " +
            "instruments of the muses! You can no longer be a Minstrel.\n");
        set_alarm(1.0, 0.0, remove_lay_member);
    }

    return 1;
}

public int
query_cycle_member()
{
    setuid();
    seteuid(getuid());
    return !!MEMBER_MANAGER->query_council_position(shadow_who);
}

/*
 * Function:    query_special_title
 * Description: returns the special title of the minstrel, or 0 if the
 *              minstrel has no special title.
 * Note:        Special titles are reserved for important minstrels:
 *              the Minstrel of the Dawn,
 *              the Minstrel of the Day, 
 *              the Minstrel of the Dusk, and
 *              the Minstrel of the Night.
 *              These minstrels have special responsibilities, privileges,
 *              duties and they are appointed through joint action of the
 *              Cycle, which the four of them comprise.
 */
varargs mixed
query_special_title(string name = 0)
{
    setuid();
    seteuid(getuid());
    
    if (!special_title)
    {
        string cycle_title = MEMBER_MANAGER->query_council_position(shadow_who->query_real_name());
        if (strlen(cycle_title))
        {
            special_title = cycle_title;
        }
        else
        {
            special_title = "";
        }
    }

    return strlen(special_title) ? special_title : 0;
}

public int
query_guild_level_lay()
{
    int layman_stat = query_shadow_who()->query_stat(SS_LAYMAN);

    // guild stat of 202 is roughly where a Minstrel will have 11
    // spaces in their songbook for Songs of Power, so am making
    // that the new level cap - Arman Dec 2019

    float guild_level = itof(MAX_GUILD_LEVEL) * (itof(layman_stat) / 202.0);

    return MIN(MAX_GUILD_LEVEL, ftoi(guild_level));
}

public string
query_guild_title_lay()
{
   string str = minstrel_titles[query_guild_level_lay()];   

   if (query_special_title())
      str = query_special_title();

    if (!title_extra)
    {
        string ottext = read_file(MINSTREL_LOG + "old_timers_list");

        title_extra = "";

        if (strlen(ottext))
        {
            string *old_timers = explode(ottext, "\n");
            if (member_array(shadow_who->query_real_name(), old_timers) != -1)
            {
                title_extra = "Sage Minstrel of the Ages";
            }
        }
    }

    if (strlen(title_extra))
    {
        str += ", " + title_extra;
    }

    return str;
}

/*
* Function:query_mood
* Description: What is the current mood of the minstrel?
* Returns:The number of the mood.
*/
int
query_mood()
{
   return shadow_who->query_skill(SG_FLAG) & MOODMASK;
}

/*
* Function:query_mood_name
* Description: What is the current mood of the minstrel?
* Returns:A string containing the mood, e.g. "jovial".
*/
string
query_mood_name()
{
   switch(query_mood())
   {
      case RANDOM: return "random";
      case SERIOUS: return "serious";
      case JOVIAL: return "jovial";
      case BRAVE: return "brave";
      case CONVERSE: return "conversational";
      case SAD: return "sad";
      case ANGRY: return "angry";
      case SONG: return "song";
      case SARCASTIC: return "sarcastic";
      case NEUTRAL: return "neutral";
      case ROMANTIC: return "romantic";
      case SECRETIVE: return "secretive";
      default: return "Yikes! Don't know that mood...";
   }
}


/*
 * Function:    set_mood
 * Description: Minstrels may set their mood; the setting will be 
 *              reflected in 'say' verb choice as well as default
 *              settings for standard emotes (nod, grin, etc).
 * Arguments:   mood - the number of the mood; see defines in 
 *                     guild_defs.h for the various moods.
 * Returns:     1 if successful, else 0.
 */
int
set_mood(int mood)
{
   shadow_who->set_skill(SG_FLAG, 
                         shadow_who->query_skill(SG_FLAG) & (~MOODMASK));
   shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)+mood);
   return 1;
}


/*
 * Function:    query_hear_bells
 * Description: Can the player hear the Bells of the Tower? These ring every 
 *              reset and whenever a Minstrel enters the game.
 * Returns:     1 if the player can hear the Bells.
 */
int
query_hear_bells()
{
    return (shadow_who->query_skill(SG_FLAG)&BELLMASK) / BELLMASK;
}

/*
 * Function:    set_hear_bells
 * Description: Sets the bell_flag of the player
 * Arguments:   hear - 1 if the player wishes to hear the bells, 0 otherwise.
 */
void
set_hear_bells(int hear)
{
    if (hear)
        shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)|BELLMASK);
    else
        shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)& (~BELLMASK));
}

/*
 * Function:    query_hear_dais
 * Description: Can the player hear others speaking from the dais in the 
 *              courtyard of the Minstrels HQ?
 * Returns:     1 if the player can hear the dais speakers.
 */
int
query_hear_dais()
{
   return (shadow_who->query_skill(SG_FLAG)&DAISMASK) / DAISMASK;
}

/*
 * Function:    set_hear_dais
 * Description: Sets the dais_flag of the player
 * Arguments:   hear - 1 if the player wishes to hear the dais speakers,
 *                     0 otherwise.
 */
void
set_hear_dais(int hear)
{
   if (hear)
        shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)|DAISMASK);
    else
        shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)& (~DAISMASK));
}

/*
 * Function:    query_hear_ballads
 * Description: Can the player hear the Ballads sung by other Minstrels? 
 * Returns:     1 if the player can hear the Ballads.
 */
int
query_hear_ballads()
{
    if (shadow_who->query_wiz_level() &&
        shadow_who->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M)
    {
        /* Player is wizard with BUSY M set */
        return 0;
    }
    return (shadow_who->query_skill(SG_FLAG)&BALLADMASK) / BALLADMASK;
}

/*
 * Function:    set_hear_ballads
 * Description: Sets the ballad_flag of the player
 * Arguments:   hear - 1 if the player wishes to hear the Ballads, 0 otherwise.
 */
void
set_hear_ballads(int hear)
{
   if (hear)
        shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)|BALLADMASK);
    else
        shadow_who->set_skill(SG_FLAG, shadow_who->query_skill(SG_FLAG)& (~BALLADMASK));
}

/*
 * Function:    query_guild_skill_name
 * Description: When a player uses the skills command s/he should get the
 *              proper name of the skill.
 * Arguments:   type - the number of the skill
 * Returns:     0 if no skill of mine,  else the string.
 */
mixed
query_guild_skill_name(int type)
{
   switch(type)
   {
      case SG_READ_MUSIC:
        return "read music";
      case SG_VOCAL:
        return "sing";
      case SG_INSTRUMENTAL:
        return "play instrument";
      case SG_TUNE_REPAIR:
        return "repair instrument";
      case SG_FAKE_SKILL:
        return "";
      case SG_VOCAL_DAMAGE:
        return "";
      case SG_FLAG:
        return "";
      case SG_NATURAL_VOICE:
        return "";
   }
   return (string)query_shadow_who()->query_guild_skill_name(type);
}

/*
 * Function:    query_instrument_name
 * Description: what instrument has the Minstrel chosen to study?
 * Returns:     a string containing the name of the instrument.
 */
string
query_instrument_name()
{
    object instrument;

    instrument = present("minstrel_instrument", shadow_who);
    if (!instrument)
        return 0;
    else
        return instrument->query_name();
}

/*
 * Function:    query_instrument
 * Description: what instrument has the Minstrel elected to study?
 * Returns:     pointer to the instrument object
 */
object
query_instrument()
{
    object instrument;

    instrument = present("minstrel_instrument", shadow_who);
    return instrument;
}

/*
 * Function:    query_race_adj
 * Description: an adjective describing the race of the player
 * Returns:     'elvish', 'gnomish', 'dwarvish', etc.
 */
string
query_race_adj()
{
    string race = shadow_who->query_race_name();

    if (race == "elf")
        return "elvish";
    if (race == "drow")
        return "elvish";
    if (race == "gnome")
        return "gnomish";
    if (race == "human")
        return "human";
    if (race == "dwarf")
        return "dwarvish";
    if (race == "goblin")
        return "goblin's";
    if (race == "hobbit")
        return "hobbit's";
    if (race == "half-elf")
        return "half-elvish";
    if (race == "hobgoblin")
        return "goblin's";
    if (race == "minotaur")
        return "monstrous";
    if (race == "kender")
        return "kenderish";
    if (race == "halfling")
        return "halfling's";
    /* Default */
    return "odd";
}

/*
 * Function:    query_voice_adj
 * Description: Returns the singing voice of the Minstrel, eg one of
 *              "basso profundo", "basso", "baritone", "tenor" for males
 *              and "contralto", "alto", "mezzo soprano", "soprano" for
 *              females. A Minstrel's voice is determined by their 
 *              race + a random factor + their training. The random
 *              factor hasn't been coded in yet, however.
 */
string
query_voice_adj()
{
    int whichvoice;
    int training = shadow_who->query_prop(MINSTREL_I_VOICE_TRAINING);
    int random_voice = query_random_voice();
    
    switch (shadow_who->query_race_name())
    {
        case "elf":
        case "drow":
        if (shadow_who->query_gender() == 1)
            whichvoice =  3;
        else
            whichvoice = 3;
        break;
        case "gnome":
        if (shadow_who->query_gender() == 1)
            whichvoice =  3;
        else
            whichvoice =  3;
        break;
        case "human":
        case "half-elf":
        if (shadow_who->query_gender() == 1)
            whichvoice =  1;
        else
            whichvoice =  2;
        break;
        case "dwarf":
        if (shadow_who->query_gender() == 1)
            whichvoice =  0;
        else
            whichvoice =  0;
        break;
        case "goblin":
        case "minotaur":
        case "ogre":
        if (shadow_who->query_gender() == 1)
            whichvoice =  1;
        else
            whichvoice =  1;
        break;
        case "hobbit":
        case "halfling":
        case "kender":
        if (shadow_who->query_gender() == 1)
            whichvoice =  3;
        else
            whichvoice =  2;
        break;
        default:
        return "bizarre";
        break;
    }
    whichvoice += training + random_voice;
    if (whichvoice < 0)
        whichvoice = 0;
    if (shadow_who->query_gender() == 1)
    {
        if (whichvoice >= sizeof(femalevoices))
            whichvoice = sizeof(femalevoices) - 1;
        return (femalevoices[whichvoice]);
    }
    else
    {
        if (whichvoice >= sizeof(malevoices))
            whichvoice = sizeof(malevoices) - 1;
        return (malevoices[whichvoice]);
    }
}

/*
 * Function:    set_random_voice
 * Description: Every Minstrel has a voice (baritone, soprano, etc.) determined
 *              by his or her gender, race, and a random factor (ie the Minstrel's
 *              'natural' voice). This function assigns that random factor. Right
 *              now it is strictly random but it would be better to hash the
 *              Minstrel's name or something so that even if a Minstrel leaves the
 *              guild and rejoins his or her 'natural' voice would be unchanged.
 *              The skill SG_NATURAL_VOICE gets set to -1, 0, 1 to indicate that
 *              the Minstrel's voice is low, ordinary, or high for his or her
 *              race.
 * Arguments:   name - currently unused but should seed the random function
 *                     somehow.
 */
int
set_random_voice(string name)
{
    int voice = random(3)-1;
    
    shadow_who->set_skill(SG_NATURAL_VOICE, voice);
    return voice;
}

int
query_random_voice()
{
    return shadow_who->query_skill(SG_NATURAL_VOICE);
}

/*
 * Function:    query_vocal_skill_adverb
 * Description: How well can the Minstrel sing?
 * Returns:     an adverb: 'haltingly', 'skillfully', etc.
 */
string
query_vocal_skill_adverb()
{
    string adverb;
    
    switch (shadow_who->query_skill(SG_VOCAL))
    {   
    case 0..15: 
        adverb = "haltingly";
        break;
    case 16..30:
        adverb = "delicately";
        break;
    case 31..50:
        adverb = "ably";
        break;
    case 51..70:
        adverb = "skillfully";
        break;
    case 71..90:
        adverb = "brilliantly";
        break;
    default: 
        adverb = "expertly";
        break;
    }
    return adverb;
}

/*
 * Function:    query_instrument_skill_adverb
 * Description: How well can the Minstrel play his/her instrument?
 * Returns:     an adverb: 'haltingly', 'skillfully', etc.
 */
string
query_instrument_skill_adverb()
{
    string adverb;
    
    switch (shadow_who->query_skill(SG_INSTRUMENTAL))
    {   
    case 0..15: 
        adverb = "haltingly";
        break;
    case 16..30:
        adverb = "delicately";
        break;
    case 31..50:
        adverb = "ably";
        break;
    case 51..70:
        adverb = "skillfully";
        break;
    case 71..90:
        adverb = "brilliantly";
        break;
    default: 
        adverb = "expertly";
        break;
    }
    return adverb;
}


/*
 * Function:    query_minstrel_skill_adverb
 * Description: How well can the Minstrel sing and play?
 * Returns:     an adverb: 'haltingly', 'skillfully', etc.
 */
string
query_minstrel_skill_adverb()
{
    string adverb;
    
    switch ((shadow_who->query_skill(SG_VOCAL)
            + shadow_who->query_skill(SG_INSTRUMENTAL)) / 2)
    {   
    case 0..15: 
        adverb = "haltingly";
        break;
    case 16..30:
        adverb = "delicately";
        break;
    case 31..50:
        adverb = "ably";
        break;
    case 51..70:
        adverb = "skillfully";
        break;
    case 71..90:
        adverb = "brilliantly";
        break;
    default: 
        adverb = "expertly";
        break;
    }
    return adverb;
}

/* 
 * Function:    query_def_post
 * Description: Minstrels should be directed to the guild post office in the
 *              event of new mail.
 */
string
query_def_post()
{
    return CEDRICDIR + "guild/post";
}

#if 0
/* 
 * Function:    do_die
 * Description: This function shadows do_die in the player object. The idea
 *              is to let the minstrel die as usual, but to notify the guild
 *              in the process. We don't do so for wizards, since we don't
 *              want players wasting their mana mourning a wizard.
 * NOTE:        Important to call shadow_who->do_die so that the player
 *              continues to die after we tell the guild.
 */
void
do_die(object killer)
{
    if (shadow_who->query_hp() <= 0 && shadow_who->query_wiz_level() == 0)
    {
        int i;
        object *obs;
        
        if (shadow_who->query_real_name() != GUILDMASTERJR)
        {
            (GUILD+"office")->minstrel_died(killer,shadow_who);
            (GUILD+"tower_roof")->minstrel_died(shadow_who);
        }
        obs = ON_LINE();
        for (i=0;i<sizeof(obs);i++)
            obs[i]->add_prop("_minstrel_"+shadow_who->query_real_name()
                             +"_died_here",MASTER_OB(environment(shadow_who)));
    }
    shadow_who->do_die(killer);
}
#endif

/*
 * Function:    banish_me
 * Description: Called when the player has been banished from the guild by
 *              vote of the Cycle. Removes the instrument, songbook, and
 *              shadow.
 */
void
banish_me()
{
    object ins, book, scroll;

    shadow_who->CM("The Cycle has voted. You are to be banished from "
                   + "the August Order of Minstrels!\n\n");
    ins = present("minstrel_instrument", shadow_who);
    shadow_who->CM(BS("The "+ins->short()+" slips from your grasp. "
          + "As you stand and watch, dumbfounded, it grows translucent and "
          + "gradually vanishes altogether.\n"));
    if (ins) ins->remove_object();

    book = present("minstrel_song_book",shadow_who);
    if (book) book->remove_object();

    scroll = present("minstrel_scroll",shadow_who);
    if (scroll) scroll->remove_object();

    
    
    set_alarm(5.0,0.0,"muse_banish");
}

int
is_fork(mixed ob)
{
    if (function_exists("break_fork",ob))
	return 1;
    else
	return 0;
}

void
remove_lay_member()
{ 
    object ins, book, scroll;
    mixed *forks;

    setuid();
    seteuid(getuid());  

    shadow_who->clear_guild_stat(SS_LAYMAN);    
    shadow_who->remove_skill(SG_INSTRUMENTAL);
    shadow_who->remove_skill(SG_VOCAL);
    shadow_who->remove_skill(SG_READ_MUSIC);
    shadow_who->remove_skill(SG_TUNE_REPAIR);
    shadow_who->remove_skill(SG_FAKE_SKILL);
    shadow_who->remove_skill(SG_VOCAL_DAMAGE);
    shadow_who->remove_skill(SG_FLAG);

    present("minstrel_instrument", shadow_who)->remove_object();
    present("minstrel_song_book", shadow_who)->remove_object();
    filter(deep_inventory(shadow_who), is_fork)->break_fork();

    SONGBOOK_MANAGER->remove_songbook(shadow_who);
    MEMBER_MANAGER->remove_member(shadow_who);
    PERFORM_MANAGER->remove_member(shadow_who);

    if (shadow_who->query_default_start_location() == START)
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }

    write_file(LEAVE_LOG, capitalize(shadow_who->query_real_name()) +
        " " + ctime(time()) + "\n");

    shadow_who->remove_cmdsoul(GUILDSOUL);
    shadow_who->update_hooks();

    remove_guild_lay();
}

void
muse_banish()
{
    string logfile, *loglines;
    int i;
    
    shadow_who->CM("Suddenly, a wave of regret and "
                   + "sorrow crashes over you and you fall to the floor, "
                   + "overwhelmed. When you look up "
                   + shadow_who->query_muse_name()
                   +" stands before you with a look of disgust painful to "
                   + "bear. Her eyes speak volumes, but "
                   +shadow_who->query_muse_name()+" speaks only one word: "
                   + "\"Begone.\" \nYou lower your head in shame. The room "
                   + "grows dark and very, very quiet. When you next look up "
                   +shadow_who->query_muse_name()+" is gone, and you are deaf "
                   + "again, on your knees in a silent world...\n");
    logfile = read_file(LOGFILE);
    loglines = explode(logfile+"\n", "\n");
    for (i=0;i<sizeof(loglines);i++)
    {
        if (member_array(shadow_who->query_name(),
                         explode(loglines[i], ":"))!= -1)
            loglines -= ({loglines[i]});
    }
    logfile = implode(loglines, "\n");
    rm(LOGFILE);
    write_file(LOGFILE, logfile);
    shadow_who->clear_guild_stat(SS_LAYMAN);
    shadow_who->remove_skill(SG_INSTRUMENTAL);
    shadow_who->remove_skill(SG_VOCAL);
    shadow_who->remove_skill(SG_READ_MUSIC);
    shadow_who->remove_skill(SG_TUNE_REPAIR);
    shadow_who->remove_skill(SG_FAKE_SKILL);
    shadow_who->remove_skill(SG_VOCAL_DAMAGE);
    shadow_who->remove_skill(SG_FLAG);
    
    shadow_who->remove_cmdsoul(GUILDSOUL);
    shadow_who->remove_guild_lay();
    shadow_who->update_hooks();
    PERFORM_MANAGER->remove_member(this_player());

}

/* Called in minstrels who kill their guild npcs */
void
muse_punish()
{
    string logfile, *loglines;
    int i;
    
    shadow_who->CM("Suddenly, a wave of regret and "
                   + "sorrow crashes over you and you fall to the floor, "
                   + "overwhelmed. When you look up "
                   + shadow_who->query_muse_name()
                   +" stands before you with a look of disgust painful to "
                   + "bear. Her eyes speak volumes, but "
                   +shadow_who->query_muse_name()+" speaks: "
				   + "For your crime I have taken your instrument and your "
                   + "skills, for you have obviously learned nothing!\n"
                   +shadow_who->query_muse_name()+" speaks: "
				   + "Consider yourself fortunate not to be banished forever."
                   + "\nYou lower your head in shame. The room "
                   + "grows dark and very, very quiet. When you next look up "
                   +shadow_who->query_muse_name()+" is gone, and you are on "
                   + "your knees in a silent world...\n");

    present("minstrel_instrument", shadow_who)->remove_object();
    present("minstrel_song_book", shadow_who)->remove_object();
    filter(deep_inventory(shadow_who), is_fork)->break_fork();

    shadow_who->remove_skill(SG_INSTRUMENTAL);
    shadow_who->remove_skill(SG_VOCAL);
    shadow_who->remove_skill(SG_READ_MUSIC);
    shadow_who->remove_skill(SG_TUNE_REPAIR);
    shadow_who->remove_skill(SG_FAKE_SKILL);
    shadow_who->remove_skill(SG_VOCAL_DAMAGE);
    shadow_who->remove_skill(SG_FLAG);
}


/*public mixed
query_guild_trainer_lay()
{
    return ({"/d/Terel/cedric/guild/cubicle",
             "/d/Terel/cedric/guild/training"});
}*/

public void
remove_shadow()
{
    destruct();
}
    
public varargs int
break_spell(string msg, object breaker)
{
    int val = shadow_who->break_spell(msg, breaker);

    (GUILDSOUL)->break_power(shadow_who);

    return val;
}
