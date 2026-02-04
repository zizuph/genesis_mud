#pragma save_binary

inherit "/std/object.c";
inherit "/lib/commands";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <adverbs.h>

#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#define INS_SUBLOC "_instrument_subloc"
#define PERFORMER_HELP NEW_GUILD + "doc/performer_help.txt"
#define PERFORMER_REPUTATION NEW_GUILD + "doc/performer_reputation.txt"
#define AOD_MASTER ("/d/Emerald/common/guild/aod/obj/master")

#undef MUNDANEDIR
#define MUNDANEDIR "/d/Terel/cedric/guild/songs/mundane/"

#define MAXDAMAGE 10
#define TUNEDAMAGE      ({"is well tuned and in perfect repair",        \
      "seems slightly out of tune",                   \
      "sounds somewhat off-pitch",                    \
      "sounds out of tune",                           \
      "requires a thorough tuning",                   \
      "is painfully out of tune"})

#define LUTE_DAMAGE TUNEDAMAGE +\
({"has a broken string",                        \
      "has lost a tuning-peg",                        \
      "has a warped fret-board",                      \
      "has a fractured bridge",                       \
      "has a large crack in its sounding-case"})
#define LUTE_FIX ({"lute_string",\
      "lute_tuning_peg",\
      "lute_fret_board",\
      "lute_bridge",\
      "lute_big"})

#define STONE_DAMAGE TUNEDAMAGE +\
({"has a minor chip",                        \
      "has been chipped",                        \
      "has surface cracks",                      \
      "has deep structural cracks",                       \
      "is about to crumble into rubble"})

#define RECORDER_DAMAGE TUNEDAMAGE +\
({"is moldy and needs a good cleaning",         \
      "has a cracked mouth-piece",                    \
      "is badly warped by the humidity",              \
      "is missing its bottom section",                \
      "has a large crack between finger-holes"})
#define RECORDER_FIX ({"recorder_mouldy",\
      "recorder_mouth_piece",\
      "recorder_warped",\
      "recorder_broken",\
      "recorder_big"})

#define DULCIMER_DAMAGE TUNEDAMAGE +\
({"has a broken string",                        \
      "is without one of its hammers",                \
      "has lost several tuning-pegs",                 \
      "has a warped bridge",                          \
      "is broken completely in half"})
#define DULCIMER_FIX ({"dulcimer_string",\
      "dulcimer_hammer",\
      "dulcimer_tuning_peg",\
      "dulcimer_bridge",\
      "dulcimer_big"})

#define HARP_DAMAGE TUNEDAMAGE +\
({"has a handful of missing strings",           \
      "has a cracked forepillar",                     \
      "has a severely warped neck",                   \
      "has a crushed resonator",                      \
      "is broken completely in half"})
#define HARP_FIX ({"harp_strings",\
      "harp_forepillar",\
      "harp_neck",\
      "harp_resonator",\
      "harp_big"})

#define SHAWM_DAMAGE TUNEDAMAGE +\
({"has a dried-out and cracked reed",           \
      "has no mouthpiece",                            \
      "has some rusty and immobile keys",              \
      "has sustained heavy water damage",              \
      "has a shattered bell"})
#define SHAWM_FIX ({"shawm_reed",\
      "shawm_mouthpiece",\
      "shawm_keys",\
      "shawm_water_damage",\
      "shawm_big"})

#define VIOL_DAMAGE TUNEDAMAGE +\
({"is missing an A-string",                     \
      "has a loose and warped bow",                   \
      "has a splintered and collapsed bridge",        \
      "has lost all its tuning-pegs",                 \
      "has its fingerboard completely cracked off"})
#define VIOL_FIX ({"viol_string",\
      "viol_bow", \
      "viol_bridge",\
      "viol_tuning_pegs",\
      "viol_big"})

#define TRUMPET_DAMAGE TUNEDAMAGE +\
({"is blocked up and needs to be cleaned",      \
      "is badly rusted",                              \
      "needs a mouthpiece",                           \
      "has been severely dented",                     \
      "has been pounded almost completely flat"})
#define TRUMPET_FIX ({"trumpet_blocked",\
      "trumpet_rusty",\
      "trumpet_mouthpiece",\
      "trumpet_dented",\
      "trumpet_big"})

void do_things();

int     damage_level = 0;
string  *damage_desc;
mapping top_list = ([ ]);

void
init()
{
   ::init();
   add_action("do_inspect", "inspect");
   add_action("do_perform", "perform");
   add_action("do_offer", "offer");
   add_action("do_help", "help");
   add_action("do_reputation", "performance");
   add_action("do_top_hundred", "top");
   add_action("play_instrument", "play");
}

void
create_object()
{
   
   if (IS_CLONE) 
       set_alarm(1.0, 0.0, do_things);
}

int
query_damage()
{
   return damage_level;
}

void
set_damage(int i)
{
   damage_level = i;
}

void
add_damage(int i)
{
   damage_level +=i;
   if (damage_level>MAXDAMAGE)
      damage_level = MAXDAMAGE;
   if (damage_level<0)
      damage_level = 0;
}

void
set_damage_desc(string *the_arr)
{
   damage_desc = the_arr;
}

string
query_damage_desc()
{
   return "The " + query_name() + " " + damage_desc[query_damage()] + ".";
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str = "";
    string *indexes;
    int i;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    string reputation = PERFORM_MANAGER->query_reputation_level_desc(carrier);

    switch(subloc)
    {
	case INS_SUBLOC:
	if (for_obj == carrier)
	{
            str += "You are " + LANG_ART(reputation) + " " + reputation + 
                " performer of the realms.\n";
	}
	else
	{
            str += capitalize(carrier->query_pronoun()) + " is " + 
                LANG_ART(reputation) + " " + reputation + " performer of " +
                "the realms.\n";
	}

	return str;
	break;
	
	default:
	return TP()->show_subloc(subloc, carrier, for_obj);
    }
    return str;
}

void do_things()
{
   object holder;
   
   holder = environment(TO());
   seteuid(getuid(TO()));
   if (!IS_PERFORMER(holder))
      {
      holder->catch_msg(BS("The "+short()+" slips from your grasp. "
            + "As you stand and watch, dumbfounded, it becomes translucent and "
            + "gradually vanishes altogether.\n"));
      remove_object();
   }

   if(query_name() == "rock" && !AOD_MASTER->query_membership_status(holder))
   {
         holder->catch_msg(BS("The "+short()+" are so huge they fall from your grasp "
            + "and smash, revealing a lute which you pick up!\n"));
         object club_obj = clone_object(NEW_GUILDOBJ + "instrument_club");
         club_obj->set_name("lute");
         club_obj->move(holder, 1);
         remove_object();
   }

   if(query_name() != "rock" && AOD_MASTER->query_membership_status(holder))
   {
         holder->catch_msg(BS("The "+short()+" is so puny! You throw it " +
             "away and scavange some traditional ogre bluestone percussion " +
             "rocks!\n"));
         object club_obj = clone_object(NEW_GUILDOBJ + "instrument_club");
         club_obj->set_name("rock");
         club_obj->move(holder, 1);
         remove_object();
   }
   
   add_prop(OBJ_M_NO_DROP, "Drop your "
      +TO()->query_name()+"? You must be joking!\n");
   
   switch(query_name())
   {
      case "rock":
      set_damage_desc(STONE_DAMAGE);
      set_short("bluestone percussion rocks");
      add_adj("bluestone");
      add_adj("percussion");
      add_name("rock");
      add_name("rocks");
      set_long(BS(
            "A pair of huge bluestone rocks, shaped to fit perfectly " +
            "in to one's hands... assuming your hands are those of a " +
            "giant! The favoured instrument of ogre percussionists, " +
            "the primal smashing together of these rocks results in " +
            "a beat reverently referred to as Music With Rocks In. " +
            "You may inspect your rocks to assess their state of " +
            "tuning and general repair.\n"));
      break;

      case "lute":
      set_damage_desc(LUTE_DAMAGE);
      set_short("pear-shaped lute");
      add_adj("pear-shaped");
      set_long(BS(
            "The pear-shaped body of this beautiful lute has " +
            "been crafted from striped ribs of yew wood. " +
            "From the balsam wood bridge up the fretted neck " +
            "six strings have been tightly stretched, the lower " +
            "five in double courses. " +
            "A circular hole in the lute's body, beneath the " +
            "strings, allows the instrument to resonate " +
            "strongly. You may inspect your lute to assess its " +
            "state of tuning and general repair.\n"));
      break;
      
      case "recorder":
      set_damage_desc(RECORDER_DAMAGE);
      set_short("cherry wood recorder");
      add_adj("cherry");
      add_adj("wood");
      set_long(BS(
            "Fashioned from a deep red cherry wood, this recorder " +
            "is actually three sections fitted together: a flat, " +
            "lateral mouthpiece; a long middle piece with eight " +
            "fingerholes; and a small bell-shaped piece on the " +
            "end. A twirling vine of ivy has been carved into the " +
            "wood, running up and down the instrument's length. " +
            "You may inspect your recorder to assess its state of " +
            "tuning and general repair.\n"));
      break;
      
      case "dulcimer":
      set_damage_desc(DULCIMER_DAMAGE);
      set_short("beautiful dulcimer");
      add_adj("beautiful");
      set_long(BS(
            "This beautiful dulcimer has been crafted from a " +
            "large, trapezoidally shaped piece of white ash wood. " +
            "Two octaves of silvery strings, in double courses, " +
            "are suspended across the width of " +
            "the instrument. These strings weave intricately over " +
            "two central bridges at different lengths to produce " +
            "different pitches. Two hammers are kept in a " +
            "small compartment on the dulcimer's back. You may " +
            "inspect your " +
            "dulcimer to assess its state of tuning and general " +
            "repair.\n"));
      break;
      
      case "harp":
      set_damage_desc(HARP_DAMAGE);
      set_short("dark brown harp");
      add_adj("brown");
      add_adj("dark");
      set_long(BS(
            "This harp, made of a dark brown and fragrant spruce " +
            "wood, measures two and a half feet and is meant to be " +
            "pressed against the chest or rested in the lap. A " +
            "broad resonator supports a sounding board from which " +
            "29 strings, tuned diatonically, stretch up to the " +
            "neck, gently curving like a swan's. A narrow " +
            "forepillar reaches from the resonator's base to the " +
            "neck, forming a basic triangle. You may inspect your " +
            "harp to determine its state of tuning and general " +
            "repair.\n"));
      break;
      
      case "shawm":
      set_damage_desc(SHAWM_DAMAGE);
      set_short("long conical shawm");
      add_adj("long");
      add_adj("conical");
      set_long(BS(
            "This shawm is a long conical bore that flares out " +
            "into a two-inch bell. Made of stained walnut wood, it "+
            "may be disassembled into three basic parts: a small " +
            "mouthpiece with double-reed and pirouette, a long " +
            "section with drilled fingerholes, and the bell. " +
            "Three of the lower fingerholes are covered with pads; "+
            "keys maneuver the pads, making the shawm easier to " +
            "play. This is an alto shawm and its range is low, " +
            "rich, and melancholy. You may inspect your " +
            "shawm to assess its state of tuning and general " +
            "repair.\n"));
      break;
      
      case "viol":
      set_damage_desc(VIOL_DAMAGE);
      set_short("spruce-wood viol");
      add_adj("spruce");
      add_adj("wood");
      set_long(BS(
            "This dark spruce-wood instrument is roughly two " +
            "feet in length. The sounding-box has a flat back " +
            "and rounded shoulders which curve inward and then " +
            "out again to round off at the bottom. Six strings, " +
            "tuned in fourths and thirds, stretch over the bridge, "+
            "up a fretted fingerboard, and are held by tuning-pegs "+
            "at the top of the neck. A bow, held with palm " +
            "upward, is drawn across the strings to produce sound." +
            "  While playing the viol, the instrument may be rested "+
            "on the knee or pressed against the arm and shoulder. " +
            "You may inspect your viol to assess its state of " +
            "tuning and general repair.\n"));
      break;
      
      case "trumpet":
      set_damage_desc(TRUMPET_DAMAGE);
      set_short("shiny trumpet");
      add_adj("shiny");
      set_long(BS(
            "This long and slender trumpet has been fashioned " +
            "out of brass that shines with golden lustre. A silver "+
            "alloy mouthpiece may be detached from the smaller " +
            "end. From the mouthpiece, the bore of the trumpet " +
            "gradually increases in diameter, bending back around " +
            "itself only once and then flaring out into a bell. " +
            "Although the trumpet has no valves or keys, the " +
            "various pitches of the harmonic series may be " +
            "produced by manipulating the shape of the ombouchure " +
            "and pressure of air blown through the mouthpiece. " +
            "This trumpet has been tuned to the fundamental pitch " +
            "of D. You may inspect " +
            "your trumpet to assess its state of tuning and " +
            "general repair.\n"));
      break;
      
      default:
      holder->catch_msg("Yikes! Weird instrument type: "+query_name()+"\n");
      set_short("Minstrel club instrument");
      break;
   }
   add_name("minstrel_instrument");
   add_name("performer_instrument");


   if (living(holder))
   {
       holder->add_subloc(INS_SUBLOC, TO());
   }
}

string
query_auto_load()
{
   return MASTER_OB(TO())+":"+damage_level+"**"+query_name();
}

void
init_arg(string arg)
{   
   string name;

   setuid();seteuid(getuid());
   sscanf(arg, "%d**%s", damage_level, name);
   set_name(name);
   set_damage(damage_level);
}

int
do_help(string str)
{
    if(str == "performers")
    {
        string help_text = read_file(PERFORMER_HELP);

        TP()->catch_msg(help_text + "\n");
        return 1;
    }

    notify_fail("Help performers?\n");
    return 0;
}

int
do_reputation(string str)
{
    if(str == "reputation")
    {
        string help_text = read_file(PERFORMER_REPUTATION);

        TP()->catch_msg(help_text + "\n");
        return 1;
    }

    notify_fail("You mean 'performance reputation'?\n");
    return 0;
}

int
do_inspect(string str)
{
   object ob;
   
   if (!str) return 0;
   if (parse_command(str, TP(), "%o", ob) && ob == TO())
      {
      TP()->catch_msg(BS("This beautifully made "+query_name()+" is your chosen "
            + "instrument as a performer. Look after it well, for upon the condition "
            + "of your instrument the success of your songs depends. "
            + "Should the "+query_name()+" be damaged, or lose its perfect tone, "
            + "you may take the "+query_name()+" to an instrument workshop at either "
            + "the Minstrel's Guild in Terel or the Arts Quarter of Telberin; "
            + "for a cost any instrument may be repaired by the skilled "
            + "craftsmen therein.\n")+check_call("@@query_damage_desc@@\n"));
      say(QCTNAME(TP())+" carefully inspects "+TP()->query_possessive()+" "
	  + query_name()+" for damage.\n");
      return 1;
   }
   notify_fail("Inspect what?\n");
   return 0;
}

/*
 ****************************************************************************
 * Function:     comment_filter
 * Description:  Filters out lines begining with a "#" sign
 * 
 * Usage:        ARR = filter(ARR, "comment_filter", this_object);
 *               where ARR is the array of lines you wish to filter.
 */

int comment_filter(string line)
{
    if (line[0] == '#') 
        return 0;
    else 
        return 1;
}

/*
 ****************************************************************************
 * Function:     check_for_perform_object
 * Description:  Filters for the minstrel performance object
 * 
 */

public int
check_for_perform_object(object minstrel, object obj)
{
    if (!objectp(obj) || !obj->id("_minstrel_performance_object"))
    {
        return 0;
    }
    
    return 1;
}

/*
 ***************************************************************************
 * Function:    do_offer
 * Description: The function that starts a performance sequence in a bar
 *              or taproom.
 * Arguments:   str - returns 0 if not 'to perform'.
 */

int 
do_offer(string str)
{
    object * perform_obj;

    if (str != "to perform")
    {
        NF("Offer what? To perform?\n");
        return 0;
    }

    object loc = environment(this_player());

    if(!PERFORM_MANAGER->query_perform_location(this_player()))
    {
        NF("There is no one here willing to accept your offer of a " +
            "formal performance.\n");
        return 0;
    }

    int loc_size = PERFORM_MANAGER->query_perform_location(this_player());

    if(!loc_size || loc_size > 3)
    {
        NF("This venue has not been set up properly for performing. " +
            "Best contact your resident wizard to resolve the issue... " +
            "the show must go on!\n");
        return 0;
    }

    string location = PERFORM_MANAGER->query_perform_location_name(this_player());

    if((loc_size == PROMINENT_LOC) && 
        (REPUTATION(this_player()) < WELL_KNOWN_LVL))
    {
        write("The owner of " +location+ " has never heard of you, and " +
            "rejects your offer of a performance. You'll need to build " +
            "up your reputation in smaller establishments before you " +
            "will be allowed to perform in such a prominent location!\n");
        say(QCTNAME(this_player())+ " tries unsuccessfully to negotiate " +
            "a performance for the patrons of " +location+ ".\n");
        return 1;
    }

    string minstrel_prop = LAST_PERFORMED + this_player()->query_real_name();

    if(loc->query_prop(minstrel_prop) > time())
    {
        int expiry = loc->query_prop(minstrel_prop) - time();
        string expiry_text;

        // DEBUG("Offer to perform expiry time: " +expiry+ ".");

        expiry_text = "You can perform here again "; 

        if(expiry < 60)
        {
            expiry_text += "in less than a minute.";
        }
        else if(expiry < 3600)
        {
            expiry = expiry / 60;
            expiry_text += "in approximately " +LANG_NUM2WORD(expiry)+
                " " + ((expiry == 1) ? "minute." : "minutes.");
        }
        else
        {
            expiry = expiry / 3600;
            expiry_text += "in approximately " +LANG_NUM2WORD(expiry)+
                " " + ((expiry == 1) ? "hour." : "hours.");
        }

        NF("You have performed here recently. " +expiry_text+ "\n");
        return 0;
    }

    if(loc->query_prop(NEXT_PERFORM) > time())
    {
        int expiry = loc->query_prop(NEXT_PERFORM) - time();
        string expiry_text;

        // DEBUG("Offer to perform expiry time: " +expiry+ ".");

        if(expiry < 60)
        {
            expiry_text = "This venue would be ready for another " +
                "performance in less than a minute.";
        }
        else
        {
            expiry = expiry / 60;
            expiry_text = "This venue would be ready for another " +
                "performance in approximately " +LANG_NUM2WORD(expiry)+
                " " + ((expiry == 1) ? "minute." : "minutes.");
        }

        NF("A minstrel has performed here recently. " +expiry_text+ "\n");
        return 0;
    }

    perform_obj = filter(all_inventory(environment(this_player())), 
        &check_for_perform_object(this_player(),));

    if(sizeof(perform_obj))
    {
        if(perform_obj[0])
        {
            if(perform_obj[0]->query_minstrel_performer() == 
                this_player()->query_real_name())
            {
                NF("You are already negotiating with the owner!\n");
                return 0;
            }
            else
            {
                NF("Another Minstrel is currently negotiating to " +
                   "perform here.\n");
                return 0;
            }
        }
    }

    write("You negotiate with the owner to perform for the patrons of " +
        location+ ".\n");
    say(QCTNAME(this_player())+ " negotiates with the owner to perform " +
        "for the patrons of " +location+ ".\n");

    setuid();
    seteuid(getuid());
    object perform_object = clone_object(NEW_GUILDOBJ + "performance_obj");

    perform_object->set_performer(this_player(), location, loc_size);
    perform_object->move(loc, 1);

    return 1;
}

/**************************
 * Function:     sing_song
 * Description:  chops a song up into stanzas (based on newlines), sings the
 *               first stanza, and recurses on the remainder of the song.
 * 
 * Arguments:    args - a mixed arrat containing 4 arguments:
 *               text - the text to be sung
 *               player - the singer
 *               verb - the verb describing the performance (sing, play, etc)
 *               firstcall - a flag to indicate if this is the first stanza.
 * 
 * Notes:        For simplicity we assume that the songs to be sung follow
 *               a certain standard format, which it is the responsibility
 *               of obj/compose_input to ensure. Briefly, blank lines may
 *               only be newline chars (no extra whitespace) and stanzas are
 *               to be separated by one blank line. Each line of text is 
 *               also expected to begin with a \t (tab char) to aid 
 *               readability, and to end with the string "**" on its own line.
 */

void
sing_song(mixed *args)
{
   string text = args[0];
   object player = args[1];
   string verb = args[2];
   int firstcall = args[3];
   string *stanzas;
   int i;
   int alarm_id;
   
   stanzas = explode(text+"\n\n", "\n\n");
   
   if  (stanzas[0] == "**" )
   {
      player->change_prop("_minstrel_i_singing", 0);
      player->remove_prop("_minstrel_i_song_alarm");
      tell_room(environment(player),
        QCTNAME(player)+" "+verb+"s the final note, and trails into "
        + "silence.\n",player);
      
      player->CM("You "+verb+" the final note and cease your song.\n");
      return;
   }
   if (firstcall)
   {
      tell_room(environment(args[1]),stanzas[0]+"\n");
      args[3] = 0;
   }
   else
   {
      player->CM("You continue to "+verb+":\n"+stanzas[0]+"\n");
      
      tell_room(environment(player), QCTNAME(player)
         + " continues to "+verb+":\n"+stanzas[0]+"\n",player);
   }
   stanzas = stanzas[1..sizeof(stanzas)-1];
   
   args[0] = implode(stanzas, "\n\n");
   
   alarm_id = set_alarm(4.0, 0.0, &sing_song(args));
   player->add_prop("_minstrel_i_song_alarm", alarm_id);
}


/*
 ***************************************************************************
 * Function:    do_perform
 * Description: Sings, plays, or performs a Mundane.
 * Arguments:   str - the command line after the verb
 *              special_verb - used by do_loudly and do_softly to indicate
 *              whether the player is singing, playing, or performing.
 * Note:        terribly obfuscated code. Would benefit from being split into
 *              multiple functions.
 */

varargs int
do_perform(string str, string special_verb)
{
   object  song_book, *obs, minstrel, *perform_obj;
   mixed   songfile, *argarray, affected, affected_obs;
   string  songstr, songtext, selftext, *power;
   string  trash, newtitle, *title_words, verb, adverb, text;
   int     evocal, einstrumental, i, j, size, num;
   
   songfile =0; affected = 0; verb = "";

    if (!strlen(str))
    {
        notify_fail("Usage: "+query_verb()+" <type> <song> OR "+query_verb()+" <song>\n"
       + "Where <type> is mundane, and <song> is the "
            + "full or partial title, or the number of a song "
            + "in your book.\n");
 
        return 0;
    }
                                   
    song_book = present("minstrel_song_book", this_player());
   
    if (!parse_command(str, ({}), "%s 'for' / 'at' %s", songstr, affected))
    {
        affected = 0;
        songstr = str;
    }

    setuid();
    seteuid(getuid());

    songfile = SONG_INDEX->parse_song(songstr);

        if (stringp(songfile))
        {
            notify_fail(songfile + "\n");
            return 0;
        }

        if (pointerp(songfile))
        {
            if (sizeof(songfile) > 1)
            {
                write("Multiple matching songs.  Please specify more of the " +
                      "title or use the song number.\n");
                return 1;
            }

            songfile = songfile[0];
        }

    if (affected && !sizeof((affected_obs = parse_this(affected, "%i"))))
    {
        notify_fail("Play for whom?\n");
        return 0;
    }
   
/*==========================================================================*
 * Check the player's voice and instrument damage levels. If either is
 * greater than 5, disable it. If both are disabled, the player can't do it.
 */
 
   songtext = ""; selftext = "";
   
   switch (i = TP()->query_skill(SG_VOCAL_DAMAGE))
   {
      case 0: 
           evocal = TP()->query_skill(SG_VOCAL);
      break;
      
      case 1..5: 
           selftext += "somewhat handicapped by your weakened voice, ";
           songtext += "somewhat handicapped by "+TP()->query_possessive()
                    + " weakened voice, ";
           evocal = TP()->query_skill(SG_VOCAL)/i;
      break;
      
      default:
              selftext += "unable to use your shattered voice, ";
              songtext += "unable to use "+TP()->query_possessive()+" voice, ";
              
              evocal = 0;
              verb = "play";
      break;
   }
   
   switch (j = present("minstrel_instrument", TP())->query_damage())
   {
      case 0:
           einstrumental = TP()->query_skill(SG_INSTRUMENTAL);
      break;
      
      case 1..5: 
           if (songtext!="") { selftext += "and "; songtext += "and "; }
           selftext += "hindered by the poor tone of your damaged instrument, ";
           songtext += "hindered by the poor tone of "+TP()->query_possessive()
                    + " instrument, ";
           einstrumental = TP()->query_skill(SG_INSTRUMENTAL)/j;
      break;
      
      default:
             if (songtext!="") { selftext += "and "; songtext += "and "; }
             selftext += "unable to use your ruined instrument, ";
             songtext += "unable to use "+TP()->query_possessive()
                      +" ruined instrument, ";
             
             einstrumental = 0;
             verb = "sing";
      break;
   }
   
   if (i>5 && j>5)
      {
      NF(BS("Neither your voice nor your instrument is usable; you "
            + "cannot perform the song.\n"));
      return 0;
   }

   if (TP()->query_prop("_minstrel_i_singing"))
   {
       NF("You are already performing a song!\n");
       return 0;
   }

   
   /* 
    * At this point we have a valid song path+filename in songfile. Next, see
    * if the song attempted is a Mundane, Ballad, or Power, and act upon that:
    */

   newtitle = "";
   size = sizeof(title_words = explode(explode(read_file(songfile, 1, 1),
                                               "**")[0] + " "," "));
   
   for (j=0;j<size;j++)
       if (j<size-1)
          newtitle+=capitalize(title_words[j])+" ";
       else
          newtitle+=capitalize(title_words[j]);

   // DEBUG("Newtitle: " +newtitle+ ".\n");
   // DEBUG("Songfile: " +songfile+ ".\n");

   /* ---------------- Mundane ----------------- */
   if (wildmatch(MUNDANEDIR+"*",songfile))
   {
       // DEBUG("Mundane song found.\n");

       if (special_verb && strlen(special_verb))
           verb = special_verb;
       else if (verb=="") 
           verb = query_verb();
      
       text = implode(filter(explode(read_file(songfile, 2)+"\n", "\n"), 
                             "comment_filter", TO()), "\n");
       argarray = ({});
       argarray += ({text, TP(), verb, 1});

       // New performance functionality added here
       // Arman, October 2019

        perform_obj = filter(all_inventory(environment(this_player())), 
            &check_for_perform_object(this_player(),));

        if(sizeof(perform_obj))
        {
            if(perform_obj[0])
            {
                if(perform_obj[0]->query_minstrel_performer() == 
                    this_player()->query_real_name())
                {
                    if(!strlen(environment(this_player())->query_prop(MIN_PERFORMING)))
                    {
                       NF("Your audience isn't ready yet. Patience!\n");
                        return 0;
                    }
                    perform_obj[0]->set_perform_score(1, newtitle);
                }
                else
                {
                    NF("Another minstrel is currently performing here. " +
                        "You should wait until they finish.\n");
                    return 0;
                }
            }
       }
      
       TP()->change_prop("_minstrel_i_singing", 1);
       TP()->CM(capitalize(selftext+"you "+verb+" "
                           + newtitle+":\n"));
       
       say(capitalize(songtext+QTNAME(TP())+" "+verb+"s a song: \""
                      + newtitle+"\".\n"), TP());

       if (verb != "play")
           sing_song(argarray);
       return 1;
   }

   notify_fail("You fail to perform " +newtitle+ ".\n");
   return 0;
}
/*=========================================================================*/

/*
 ****************************************************************************
 * Function:     do_top_hundred
 * Description:  A list of the most performed mundanes of all time.
 */

int 
sort_by_top_list(string a, string b) 
{
    return top_list[b] - top_list[a]; 
}

string *
string_top_song_list()
{
    mixed * song_list;
    top_list = ([ ]);
    mapping songs = PERFORM_MANAGER->query_top_minstrel_mundanes();

    foreach(string name, int *var: songs)
    {
        int score = var[0];
        top_list += ([ name : score ]);
    }

    // dump_array(top_list);

    song_list = sort_array(m_indices(top_list), sort_by_top_list);

    // dump_array(song_list);

    return song_list;
}

int
do_top_hundred(string str)
{
   mixed songstr;

   if (str == "mundane chart") 
   {
      string * song_array = string_top_song_list();
      string list_str = "  The Genesis Top 20 Mundane Songs  \n\n";
      int count = 0;

      // If not a mundane song, remove
      foreach(string song: song_array)
      {
          mixed songfile = SONG_INDEX->find_song(song);

          // dump_array(songfile);

          if (!pointerp(songfile))
          {
              song_array -= ({ song });
          }
          else if(!wildmatch(MUNDANEDIR+"*",songfile[0]))
          {
              song_array -= ({ song });
          }
      }

      foreach(string song: song_array)
      {
          count++;
          mixed songfile = SONG_INDEX->find_song(song);
          string song_type = "";

          if (pointerp(songfile) && wildmatch(MUNDANEDIR+"*",songfile[0]))
          {
              song_type = ", composed by " +SONG_INDEX->query_author(songfile[0]);
          }

          list_str += count + ".  "+capitalize(song)+ song_type+ "\n";
      }

      int song_array_size = sizeof(song_array);

      if(song_array_size < 20)
      {
          for(song_array_size; song_array_size < 20; 0)
          {
              song_array_size++;
              if(song_array_size < 20)
                  list_str += song_array_size + ".  ............................\n";
              else
                  list_str += song_array_size + ".  ...........................\n";
          }
      }


      list_str = generate_scroll_text(list_str, "The Genesis Top 20 Mundanes");
      write(list_str);

      return 1;
   }

   notify_fail("Top what? Mundane chart?\n");
   return 0;
}

int
play_instrument(string str)
{
    string instrument = query_name();
    string inst_short = query_short();
    string inst, adverb;
  
    notify_fail("Play your " +inst_short+ " how?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    parse_command(str, this_player(), "[the] %w %w", inst, adverb);

    if(!strlen(adverb))
        adverb = "merrily";

    if (FULL_ADVERB(adverb) == "")
    {
        return 0;
    }

    adverb = FULL_ADVERB(adverb);

    if(inst == "instrument" || inst == instrument)
    {
	tell_object(environment(this_object()),"You play a song " +adverb+ 
            " on your " +inst_short+ ".\n");
	say(QCTNAME(this_player()) + " plays a song " +adverb+ " on " +
            this_player()->query_possessive()+ " " +inst_short+ ".\n");
	return 1;
    }

    return 0;
}

