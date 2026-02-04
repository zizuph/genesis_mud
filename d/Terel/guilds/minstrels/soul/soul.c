/** soul.c **/

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Genesis/lib/help";
inherit "/d/Genesis/specials/guilds/souls/spell_manager_soul";

#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"
#include "../guild_funs.c"

#include "idea.c"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>

#define ADJARRAY  ({"a perky","a frivolous","a funny","a silly", \
                    "a popular","a catchy","a happy","an annoying", \
                    "a clever","a cute","a mournful","a sad","an amusing"})

#define MORE_OBJ  "/std/board/board_more"
#define TR(x, y)     tell_room(environment(TP()),QCTNAME(TP())+(x), y)

#undef POWERDIR
#define POWERDIR "/d/Terel/cedric/guild/Power/"
#undef MUNDANEDIR
#define MUNDANEDIR "/d/Terel/cedric/guild/songs/mundane/"
#undef BALLADDIR
#define BALLADDIR "/d/Terel/cedric/guild/songs/ballad/"
#undef EPICDIR
#define EPICDIR "/d/Terel/cedric/guild/songs/epic/"

mapping top_list = ([ ]);

/*
 ****************************************************************************
 * The Minstrel Soul                                                        *
 * Here reside all the commands accessible to a Minstrel...                 *
 * Cedric 3/93                                                              *
 *                                                                          *
 * Notes:       BS = break_string                                           *
 *              CM = catch_msg                                              *
 *              NF = notify_fail                                            *
 *              TR = tell_room                                              *
 *              TP = this_player                                            *
 *              TO = this_object                                            *
 ****************************************************************************
 */


/*
 ****************************************************************************
 * Prototypes:
 */

void sing_song(mixed *args);
varargs int do_perform(string str, string special_verb);
void song_hurt(object player);
void start_power(string songfile, int evoc, int eins,
                 object *obs, object performer);

/*
 ****************************************************************************
 * Command soul ID
 */

public void
create()
{
    read_help_dir(MINSTREL_HELP_DIR, "help");
    set_help_type(({ "minstrel", "minstrels" }));
}

public string
get_soul_id()
{
   return "minstrel";
}

public int
query_cmd_soul()
{
   return 1;
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
 * Function:     query_cmdlist
 * Description:  Returns the list of commands available to members
 *               of the guild.
 *
 * Note:         PLEASE ADD NEW COMMANDS IN ALPHABETICAL ORDER.
 */

public mapping
query_cmdlist()
{
   seteuid(getuid(TO()));
   return ([
        /* Song of power name : Function name */
                "vibrato":"do_ability",
                "soothe":"do_ability",
                "refresh":"do_ability",
                "lux":"do_ability",
                "bravuro":"do_ability",
                "pax":"do_ability",
                "lento":"do_ability",
                "accelerando":"do_ability",
                "animato":"do_ability",
                "concerto":"do_ability",
                "bellicoso":"do_ability",
        // Commands
                "offer":"do_offer",
         	"perform":"do_perform",
         	"play":"do_perform",
         	"sing":"do_perform",
                "songeffects":"list_song_effects",
                "songnotes":"show_song_notes",
                "songs":"songs_of_power",
         	"repair":"do_repair",
                "top":"do_top_hundred",
         	"tune":"do_repair",
        // Emotes
         	"ahh":"do_ahh",
         	"mblink":"do_blink",
         	"bored":"do_bored",
         	"choir":"do_choir",
         	"clean":"do_clean",
         	"cross":"do_cross",
         	"entertain":"do_entertain",
         	"faint":"do_faint",
         	"face":"do_face",
         	"hum":"do_hum",
         	//"loudly":"do_loudly",
         	"mbow":"do_mbow",
         	"mcurtsey":"do_mcurtsey",
         	"midea" : "_idea",
         	"mwhistle":"do_hum",
         	//"mourn":"do_mourn",
         	"mmumble":"do_mumble",
         	"rehearse":"do_rehearse",
         	"scales":"do_scales",
         	"song":"do_song_emote",
         	"serenade":"do_serenade",
         	"set":"do_set",
         	//"softly":"do_softly",
         	"stop":"do_stop",
         	"throat":"do_throat",
         	"violin":"do_violin",
            ]) + help_cmdlist();
}

public mapping
query_ability_map()
{
    return ([
        "vibrato"      : MIN_SPELLS + "blast",
        "soothe"       : MIN_SPELLS + "soothe",
        "refresh"      : MIN_SPELLS + "refresh",
        "lux"          : MIN_SPELLS + "lux",
        "bravuro"      : MIN_SPELLS + "brave",
        "pax"          : MIN_SPELLS + "peace",
        "lento"        : MIN_SPELLS + "lento",
        "accelerando"  : MIN_SPELLS + "accelerando",
        "animato"      : MIN_SPELLS + "animato",
        "concerto"     : MIN_SPELLS + "concerto",
        "bellicoso"    : MIN_SPELLS + "bellicoso",
    ]);
}

public string
composite_possessive(object *livings)
{
    string *descs = allocate(sizeof(livings));
    int i;

    for (i = 0; i < sizeof(livings); i++)
    {
        descs[i] = QTPNAME(livings[i]);
    }

    return COMPOSITE_WORDS(descs);
}

tell_others(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(players);

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}

tell_othersbb(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(players);
    players = FILTER_IS_SEEN(this_player(), FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}

tell_targetsbb(string str, object *targets)
{
    object *players;
    players = FILTER_PLAYERS(targets);
    players = FILTER_IS_SEEN(this_player(), FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}

/*
 ****************************************************************************
 * THE DO_FUNCTIONS OF THE COMMAND SOUL. PLEASE ADD NEW DO_FUNCTIONS IN
 * ALPHABETICAL ORDER (THOUGH SUPPORTING FUNCTIONS MAY GO BEFORE OR AFTER
 * THE DO_FUNCTION).--Cedric
 ****************************************************************************
 */


/*
 ****************************************************************************
 * Function:     do_ahh
 * Description:  A simple Minstrel emote.
 */

int do_ahh()
{
    write("You go: ahhh....  and nod understandingly.\n");

    TR(" goes: Ahh....\n"+ QCTNAME(TP())+" nods "+TP()->query_possessive()
      + " head understandingly.\n",TP());

    return 1;
}

/*
 ****************************************************************************
 * Function:     do_blink
 * Description:  A simple Minstrel emote.
 */

int do_blink(string str)
{
   if (!str)
   {
      write("You blink.\n");
      say(QCTNAME(TP())+" blinks.\n");
      return 1;
   }
   return 0;
}

/*
 ****************************************************************************
 * Function:     do_bored
 * Description:  A simple Minstrel emote.
 */

int do_bored(string str)
{
    object *oblist;
    if (!strlen(str))
    {
        write("GAWD...the agony...you may as well take a nap.\n");
        tell_othersbb("Obviously bored with your existence, " +
            QTNAME(this_player()) + " proceeds to doze off.\n",
            ({ this_player() }));
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[with] [at] [the] %l")))
    {
        notify_fail("With whom are you bored?\n");
        return 0;
    }

    write("GAWD...the agony...you may as well take a nap.\n");

    tell_targetsbb("Obviously bored with your existence, " +
		  QTNAME(this_player()) + " proceeds to doze off.\n",
		   oblist);
    tell_othersbb("Obviously bored with " + desc_many(oblist) + ", " +
            QTNAME(this_player()) + " proceeds to doze off.\n",
            ({ this_player() }) + oblist);

   return 0;
}

/*
 ****************************************************************************
 * Function:     do_clean
 * Description:  A simple Minstrel emote.
 */

int do_clean(string str)
{
    object  inst;
    string  i_name;

    inst = present("minstrel_instrument",TP());

    if (str != inst->query_name() && str != "instrument")
    {
        NF("Clean what? Your "+inst->query_name()+", perhaps?\n");
        return 0;
    }
    if(inst)
    {
      i_name = inst->query_name();

      TP()->CM("You carefully clean and polish your "+i_name+".\n");

      TR(" carefully cleans and polishes "
         + TP()->query_possessive()+" "+i_name+".\n",TP());

      return 1;
    }

    TP()->CM(BS("You seem to have lost your instrument somehow.  "
            + "Please return to the Guild to get a new one!\n"));

    return 0;
}

/*
 ****************************************************************************
 * Function:     do_cross
 * Description:  A simple Minstrel emote.
 */

int do_cross(string str)
{
    if (str == "fingers" || str == "my fingers")
    {
        say(QCTNAME(TP())+" crosses "+TP()->query_possessive()+
            " fingers.\n");
        TP()->CM("You cross your fingers hopefully.\n");
        return 1;
    }
    NF("Cross what? Your fingers, perhaps?\n");
    return 0;
}

/*
 ****************************************************************************
 * Function:     do_choir
 * Description:  A function which will allow a group of Minstrels to
 *               join in song, thereby increasing the strength of the
 *               song's (Song of Power) effect.
 *
 * Note:         HAS NOT BEEN IMPLEMENTED.
 */

int do_choir(string str)
{

}

/*
 ****************************************************************************
 * Function:     do_entertain
 * Description:  A simple Minstrel emote.
 */

int do_entertain(string str)
{
   if (!str)
   {
      write("You entertain the crowd with your antics.\n");
      say(QCTNAME(TP())+" stands on "+TP()->query_possessive()+" head.\n");
      say(QCTNAME(TP())+" bounds about the room, making strange animal "
         + "noises.\n");
      say(QCTNAME(TP())+" sings a little ditty to liven your spirits.\n");
      say(QCTNAME(TP())+" touches "+TP()->query_possessive()+" nose with "
         + TP()->query_possessive()+" tongue...very impressive!\n");

      return 1;
   }
   return 0;
}

/*
 ****************************************************************************
 * Function:     do_faint
 * Description:  A simple Minstrel emote.
 */

int do_faint(string str)
{
   if (!str)
   {
      write("You gasp in astonishment and slump to the ground, overcome.\n");
      say(QCTNAME(TP())+" gasps in astonishment, and faints "
         + "dead on the spot.\n");

      return 1;
   }
   return 0;
}

/*
 ****************************************************************************
 * Function:     do_face
 * Description:  A simple Minstrel emote.
 */

int do_face(string str)
{
   object  *folks;
   int     i;

   folks = parse_this(str, "[at] %l");

   if (sizeof(folks)==0)
   {
      write("You make a face.\n");
      say(QCTNAME(TP())+" makes a face.\n");
      return 1;
   }

   if (sizeof(folks)==1)
   {
      TP()->CM("You make a face at "+QTNAME(folks[0])+"!\n");

      TR(" makes a face at "+QTNAME(folks[0])
         + "!\n", ({folks[0], TP()}));

      folks[0]->CM(QCTNAME(TP())+" makes a face at you!\n");

      return 1;
   }

   for (i=0;i<sizeof(folks);i++)
   {
      TP()->CM("You make a face at "+QTNAME(folks[i])+".\n");

      folks[i]->CM(QCTNAME(TP())+" makes a face at you.\n");
   }
   return 1;
}

/*
 ****************************************************************************
 * Function:     do_help
 * Description:  Calls up the appropriate Minstrel help file
 *               (located in "/d/Terel/cedric/guild/text/").
 */

int do_help(string str)
{
   string which;

    if (!strlen(str)) { return 0; }

   if (str == "minstrels")
   {
      TP()->CM("Usage: help minstrels <topic>\n"
         + "Where <topic> can be one of:\n"
         + "welcome, titles, emotes, songs, skills, set, choirs, lost_items, "
         + "mourn, tax, muses, epics, or voices.\n");

      return 1;
   }

   if (sscanf(str, "minstrels %s", which))
   {
      setuid();
      seteuid(getuid());

      switch (which)
      {
          case "welcome":
          case "titles":
          case "emotes":
          case "songs":
          case "skills":
          case "set":
          case "choirs":
          case "muses":
          case "mourn":
          case "tax":
          case "lost_items":
          case "voices":
          case "midea":
          clone_object(MORE_OBJ)->more(read_file(GUILDTEXT+which));
          return 1;
      }
   }

   return 0;
}

/*
 ****************************************************************************
 * Function:     do_hum
 * Description:  A simple Minstrel emote.
 */

int do_hum(string str)
{
   string *adjlist, verb;

   verb = query_verb();

   if (verb == "mwhistle") verb = "whistle";
      adjlist = ADJARRAY;

   if (str)
      return 0;

   TP()->CM("You "+verb+" "+adjlist[random(sizeof(adjlist))]
           + " little tune.\n");
   say(QCTNAME(TP())+" "+verb+"s "+adjlist[random(sizeof(adjlist))]
      + " little tune.\n");

   return 1;
}

/*
 * Function:    do_loudly
 * Description: The minstrel may want to sing/play/perform his or her songs
 *              loudly, in effect pumping more mana into the song.
 *              This is possible with the command "loudly play ...",
 *              "loudly perform ...", or "loudly sing ...". The do_loudly
 *              function sets a property in the minstrel to indicate that
 *              he/she is being loud, calls the rest of the string with
 *              command(), then resets the property.
 */
int do_loudly(string str)
{
    int result;
    string *words, verb;

    words = explode(str + " ", " ");
    verb = words[0];
    words = words - ({ verb });
    if (sizeof(words) < 1)
    {
        NF("Loudly sing? play? perform? mourn? what?\n");
        return 0;
    }
    TP()->add_prop(MINSTREL_I_VOLUME, LOUD);
    result = do_perform(implode(words, " "), verb);
    TP()->remove_prop(MINSTREL_I_VOLUME);
    return result;
}

/*
 ****************************************************************************
 * Function:     do_mbow
 * Description:  An elaborate Minstrel emote.
 *
 * Note:
 *
 * Switches:     audience      -  "Bow to your audience."
 *               barely        -  "Deign to acknowledge your many fans."
 *               coldly        -  "HUMPH...can't even buy a good audience."
 *               deeply        -  "For the royalty."
 *               farewell      -  " 'Til we meet again."
 *               flourish      -  "To impress the Ladies."
 *               formally      -  "With respect."
 *               jauntily      -  "With irreverance."
 *               romantically  -  *wink*
 */

int do_mbow(string str)
{
    string  how, target;
    object  *folks;
    int     i, notarget = 0;

    NF("Mbow how? Do <help minstrels emotes> for a list "
       + "of the subtle nuances in this seemingly simple greeting.\n");

    if (strlen(str)==0)
        how = TP()->query_prop("_minstrel_s_mbow");
    else
    {
        if (sscanf(str, "%s %s", how, target) != 2)
        {
            sscanf(str, "%s", how);
            target = "";
            notarget = 1;
        }
        folks = parse_this(target, "[to] %l");
    }

    switch (how)
    {
/*=========================================================================*/
        case "audience":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You bow to the room, basking in the applause.\n");
            say(QCTNAME(TP())+" bows to the room, basking in "
                + "the applause.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You bow to "+QTNAME(folks[0])
                     + ", basking in the applause.\n");

            TR( " bows to "+QTNAME(folks[0])+", obviously basking in the "
                + "applause.\n",({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())
                         + " bows to you, basking in your admiration.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You bow to "+QTNAME(folks[i])
                     + ", basking in the applause.\n");
            folks[i]->CM(QCTNAME(TP())
                         + " bows to you, basking in your admiration.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "barely":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You permit yourself a slight motion which might "
                  +"be confused with a bow.\n");
            say(QCTNAME(TP())+" makes a small motion which might "
                +"barely be considered a bow.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You permit yourself a slight nod to "
                     +QTNAME(folks[0])+".\n");
            TR( " makes a slight motion to "+QTNAME(folks[0])
                + " which might barely be considered "
                + "a bow.\n",({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" permits "+TP()->query_objective()
                         + "self a slight nod to you which might barely be "
                         + "considered a bow.\n");
            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You permit yourself a slight nod to "
                     + QTNAME(folks[i])+".\n");
            folks[i]->CM(QCTNAME(TP())+" permits "
                         + TP()->query_objective()
                         + "self a slight nod to you which might barely "
                         + "be considered a bow.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "coldly":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You execute a cold and distant bow.\n");
            say(QCTNAME(TP())+" executes a cold and distant bow.\n");
            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You acknowledge "+QTNAME(folks[0])
                     + " with a cold and distant bow.\n");
            TR( " acknowledges "
                + QTNAME(folks[0])
                + " with a cold and distant bow.\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())
                         + " acknowledges you with a cold and distant bow.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You acknowledge "+QTNAME(folks[i])
                     + " with a cold and distant bow.\n");

            folks[i]->CM(QCTNAME(TP())
                         + " acknowledges you with a cold and distant bow.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "deeply":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You kneel and bow deeply, brushing the ground with "
                  + "an arm in the time-honored manner.\n");
            say(QCTNAME(TP())+" kneels and bows deeply, brushing the "
                + "ground with an arm.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You kneel and bow deeply to "+QTNAME(folks[0])
                     + ", brushing the ground with an arm.\n");

            TR( " kneels and bows deeply to "+QTNAME(folks[0])
                + ", brushing the ground with an arm.\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" kneels and bows deeply to you, "
                         + "brushing the ground with an arm.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You kneel and bow deeply to "+QTNAME(folks[i])
                     +", brushing the ground with an arm.\n");
            folks[i]->CM(QCTNAME(TP())+" kneels and bows deeply to you, "
                         +"brushing the ground with an arm.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "farewell":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You perform a graceful bow and bid everyone farewell.\n");
            say(QCTNAME(TP())
                + " performs a graceful bow and bids farewell to all.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You perform a graceful bow and bid farewell to "
                     + QTNAME(folks[0])+".\n");

            folks[0]->CM(QCTNAME(TP())
                         + " performs a graceful bow and bids "
                         + "farewell to you.\n");

            TR( " performs a graceful bow and bids farewell to "
                + QTNAME(folks[0])+".\n",({TP(),folks[0]}));

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You perform a graceful bow and bid farewell to "
                     + QTNAME(folks[i])+".\n");
            folks[i]->CM(QCTNAME(TP())
                         + " performs a graceful bow "
                         + "and bids farewell to you.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "flourish":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You bow with a graceful sweep of the arm, "
                  + "ending with an intricate flourish.\n");
            say(QCTNAME(TP())
                +" bows with a graceful sweep of the arm, "
                + "ending with an intricate flourish.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You bow to "+QTNAME(folks[0])
                     + " with a graceful sweep of the arm, "
                     + "ending with an intricate flourish.\n");
            TR( " bows to "+ QTNAME(folks[0])
                + " with a graceful sweep of the arm, "
                + "ending with an intricate flourish.\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())
                         + " bows to you with a graceful sweep of the arm, "
                         + "ending with an intricate flourish.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You bow to "+QTNAME(folks[i])
                     + " with a graceful sweep of the arm, "
                     + "ending with an intricate flourish.\n");

            folks[i]->CM(QCTNAME(TP())
                         + " bows to you with a graceful sweep of the arm, "
                         + "ending with an intricate flourish.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "formally":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You bow with great respect.\n");
            say(QCTNAME(TP())+" bows with great respect.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You bow to "+QTNAME(folks[0])
                     + " with great respect.\n");

            TR( " bows to "+ QTNAME(folks[0])
                + " with great respect.\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" bows to you with great respect.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You bow to "+QTNAME(folks[i])
                     + " with great respect.\n");

            folks[i]->CM(QCTNAME(TP())
                         + " bows to you with great respect.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "jauntily":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You sketch a jaunty bow.\n");
            say(QCTNAME(TP())+" sketches a jaunty bow.\n");
            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You sketch a jaunty bow to "+QTNAME(folks[0])+".\n");

            TR( " sketches a jaunty bow to "
                + QTNAME(folks[0])+".\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" sketches a jaunty bow to you.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You sketch a jaunty bow to "+QTNAME(folks[i])+".\n");

            folks[i]->CM(QCTNAME(TP())+" sketches a jaunty bow to you.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "romantically":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You can only bow romantically <to> somebody.\n");
            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("You bow to "+QTNAME(folks[0])
                     + " with a motion calculated to make "
                     + folks[0]->query_possessive()+" heart skip a beat.\n");

            TR( " bows before "+ QTNAME(folks[0])+", but never takes "
                + TP()->query_possessive()+ " eyes off "
                + folks[0]->query_objective()+ ". "+QCTNAME(folks[0])
                + " is visibly moved by this simple "
                + "gesture.\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" bows before you, but never takes "
                         + TP()->query_possessive()
                         + " eyes off yours. You feel "
                         + "your heart skip a beat.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("You bow to "+QTNAME(folks[i])
                     + " with a motion calculated to make "
                     + folks[i]->query_possessive()+" heart skip a beat.\n");

            folks[i]->CM(QCTNAME(TP())
                         + " bows before you, but never takes his "
                         + "eyes off yours. You feel your heart skip a beat.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        case "quickly":
        TP()->add_prop("_minstrel_s_mbow",how);

        if (notarget)
        {
            write("You bow hurriedly, pressed for time.\n");
            say(QCTNAME(TP())+" bows hurriedly, obviously pressed for "
                + "time.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mbow to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("Pressed for time, you hurriedly bow to "+QTNAME(folks[0])
                     + ".\n");

            TR( " bows to "+ QTNAME(folks[0])
                + " hurriedly, clearly pressed for time.\n",
                ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" bows to you hurriedly, obviously "
                         + "pressed for time.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("Pressed for time, you hurriedly bow to "+QTNAME(folks[i])
                     + ".\n");

            folks[i]->CM(QCTNAME(TP())
                         + " bows to you hurriedly, clearly pressed for "
                         + "time.\n");
        }

        return 1;
        break;

/*=========================================================================*/
        default:
        write("Mbow how? Do <help minstrels emotes> for a list "
              + "of the nuances available in this seemingly simple "
              + "greeting.\n");
        return 1;
        break;
    }

    return 0;
}

/*
 ****************************************************************************
 * Function:     do_mcourtsey
 * Description:  An elaborate Minstrel emote.
 *
 * Note:         For Juanita!  ;)
 *
 * Switches:     audience      -  "Bow to your audience."
 *               barely        -  "Deign to acknowledge your many fans."
 *               coldly        -  "HUMPH...can't even buy a good audience."
 *               deeply        -  "For the royalty."
 *               farewell      -  " 'Til we meet again."
 *               flourish      -  "To impress the Gents."
 *               formally      -  "With respect."
 *               jauntily      -  "With bounce."
 *               romantically  -  *wink*
 */

int
do_mcurtsey(string str)
{
    string  how, target;
    mixed *array;
    object  *folks;
    int     i, notarget = 0;

    NF("Mcurtsey how? Do <help minstrels emotes> for a list of the subtle"+
       "nuances in this seemingly simple motion.\n");

    if (strlen(str)==0)
        how = TP()->query_prop("_minstrel_s_mbow");
    else
    {
        if (sscanf(str, "%s %s", how, target) != 2)
        {
            sscanf(str, "%s", how);
            target = "";
            notarget = 1;
        }
        folks = parse_this(target, "[to] %l");
    }
    switch(how)
    {
/*=========================================================================*/
    case "audience":
         TP()->add_prop("_minstrel_s_bow",how);

         if (notarget)
         {
            write("You curtsey to the room, basking in the applause.\n");
            say(QCTNAME(TP())+" curtseys to the room, basking in "
                + "the applause.\n");
            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }
         if (sizeof(folks)==1)
         {
            TP()->CM("You curtsey to "+QTNAME(folks[0])
                    + ", basking in their applause.\n");

            folks[0]->CM(QCTNAME(TP())
                         + " curtseys to you, basking in your applause.\n");

            TR( " curtseys to "+ QTNAME(folks[0])
              + ", basking in their applause.\n",({TP(),folks[0]}));

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You curtsey to "+QTNAME(folks[i])
                     + ", basking in their applause.\n");

             folks[i]->CM(QCTNAME(TP())
                         + " curtseys to you, basking in your applause.\n");
         }

    break;
/*=========================================================================*/
    case "barely":
         TP()->add_prop("_minstrel_s_bow",how);

         if (notarget)
         {
            write("You permit yourself a slight motion which might be "
                 + "confused with a curtsey.\n");

            say(QCTNAME(TP())+" makes a slight motion which sort of reminds "
               + "you of a curtsey.\n");

            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }
         if (sizeof(folks)==1)
         {
            TP()->CM("You permit yourself a slight motion towards "
                    + QTNAME(folks[0])+".\n");

            folks[0]->CM(QCTNAME(TP())+" permits "+TP()->query_objective()
                        + "self a slight motion towards you which might "
                        + "be considered a curtsey.\n");

            tell_room(environment(TP()), QCTNAME(this_player()) +
                " makes a slight motion towards " + QTNAME(folks[0])+
                " which might be mistaken for a curtsey.\n", ({TP(), folks[0]}));
            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You make a slight motion towards "+QTNAME(folks[i])
                     + ".\n");

             folks[i]->CM(QCTNAME(TP())+" makes a slight motion towards "
                         + "you which might be mistaken for a curtsey.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "coldly":
         TP()->add_prop("_minstrel_s_mbow",how);

         if (notarget)
         {
            write("You acknowledge the room with an empty curtsey.\n");
            say(QCTNAME(TP())+" acknowledges the room with a cold and "
               + "empty curtsey.\n");

            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {
            TP()->CM("You acknowledge "+QTNAME(folks[0])
                    + " with a cold, empty curtsey.\n");

            folks[0]->CM(QCTNAME(TP())
                        + " acknowledges you with a cold, empty curtsey.\n");

            TR( " acknowledges "+QTNAME(folks[0])
              + " with a cold and empty curtsey.\n",({TP(),folks[0]}));

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You acknowledge "+QTNAME(folks[i])
                     + " with a cold, empty curtsey.\n");
             folks[i]->CM(QCTNAME(TP())
                         + " acknowledges you with a cold and empty curtsey.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "deeply":
         TP()->add_prop("_minstrel_s_mbow",how);

         if (notarget)
         {
            write("You curtesy deeply, nodding your head down until it "
                 + "almost touches the ground.\n");

            say(QCTNAME(TP())+" curtseys deeply, nodding "
               + TP()->query_possessive()+" head almost to the ground.\n");

            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {

            TP()->CM("You curtsey deeply to "+QTNAME(folks[0])
                    + ", nodding your head almost to the ground.\n");

            folks[0]->CM(QCTNAME(TP())+" curtseys deeply to you, nodding "
                        + TP()->query_possessive()
                        + " head almost to the ground.\n");

            TR( " curtseys deeply to "+ QTNAME(folks[0])+", nodding "
              + TP()->query_possessive()
              + " head almost to the ground.\n",({TP(),folks[0]}));

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You curtsey deeply to "+QTNAME(folks[i])
                     + ", nodding your head almost to the ground.\n");

             folks[i]->CM(QCTNAME(TP())+" curtseys deeply to you, "
                         + "nodding "+TP()->query_possessive()
                         + " head almost to the ground.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "farewell":
         TP()->add_prop("_minstrel_s_mbow",how);

         if (notarget)
         {
            write("You curtsey gracefully to the room and bid "
                 + "all farewell.\n");
            say(QCTNAME(TP())+" curtseys gracefully and bids farewell.\n");

            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {
            TP()->CM("You curtsey to "+QTNAME(folks[0])+" and bid "
                    + folks[0]->query_objective()+" farewell.\n");

            folks[0]->CM(QCTNAME(TP())+" curtseys gracefully and bids "
                        + "farewell to you.\n");

            TR( " curtseys gracefully and bids farewell to "
              + QTNAME(folks[0])+".\n",({TP(),folks[0]}));

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You curtsey and bid farewell to "
                     + QTNAME(folks[i])+".\n");

             folks[i]->CM(QCTNAME(TP())
                         + " curtseys gracefully and bids you farewell.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "flourish":
         TP()->add_property("_minstrel_s_mbow",how);

         if (notarget)
         {
            write("You curtsey deeply, ending with an intricate "
                 + "flourish of the arm.\n");
            say(QCTNAME(TP())+" curtseys deeply, ending with an intricate "
               + "flourish of "+TP()->query_possessive()+" arm.\n");

            return 1;
         }
         if (sizeof(folks) == 0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {
            TP()->CM("You curtsey deeply to "+QTNAME(folks[0])
                    + ", ending with an intricate flourish of the arm.\n");
            TR( " curtseys deeply to "+ QTNAME(folks[0])
              + ", ending with an intricate flourish of "
              + TP()->query_possessive()+" arm.\n", ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())
                        + " curtseys deeply to you, ending with an intricate"
                        + " flourish of "+TP()->query_possessive()+" arm.\n");

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You curtsey deeply to "+QTNAME(folks[i])
                     + ", ending with an intricate flourish of your arm.\n");

             folks[i]->CM(QCTNAME(TP())+" curtseys deeply to you, ending "
                         + "with an intricate flourish of "
                         + TP()->query_possessive()+" arm.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "formally":
        TP()->add_prop("_minstrel_s_mbow",how);

         if (notarget)
         {
            write("You curtsey with great respect.\n");
            say(QCTNAME(TP())+" curtseys with great respect.\n");

            return 1;
         }
         if (sizeof(folks) == 0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {
           TP()->CM("You curtsey to "+QTNAME(folks[0])+" with great respect.\n");

           folks[0]->CM(QCTNAME(TP())+" curtseys to you with great respect.\n");

           TR( " curtseys to "+ QTNAME(folks[i])
             + " with great respect.\n",({TP(),folks[0]}));

           return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You curtsey to "+QTNAME(folks[i])
                     + " with great respect.\n");

             folks[i]->CM(QCTNAME(TP())
                         + " curtseys to you with great respect.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "jauntily":
         TP()->add_prop("_minstrel_s_mbow",how);

         if (notarget)
         {
            write("You bounce a happy little curtsey.\n");
            say(QCTNAME(TP())+" bounces a happy little curtsey.\n");

            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {
            TP()->CM("You bounce a happy little curtsey to "
                    + QTNAME(folks[0])+".\n");

            folks[0]->CM(QCTNAME(TP())
                        + " bounces a happy little curtsey towards you.\n");

            TR( " bounces a happy little curtsey towards "
              + QTNAME(folks[0])+".\n",({TP(),folks[0]}));

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM("You bounce a happy little curtsey towards "
                     + QTNAME(folks[i])+".\n");

             folks[i]->CM(QCTNAME(TP())
                         + " bounces a happy little curtsey towards you.\n");
         }

    return 1;
    break;

/*=========================================================================*/
    case "romantically":
         TP()->add_prop("_minstrel_s_mbow",how);

         if (notarget)
         {
            TP()->CM("You can only mcurtsey romantically <to> someone.\n");

            return 1;
         }
         if (sizeof(folks)==0)
         {
             NF("Mcurtsey to whom?\n");
             return 0;
         }

         if (sizeof(folks)==1)
         {
            TP()->CM(QCTNAME(folks[0])+" catches "
                    + folks[0]->query_possessive()
                    + " breath as you curtsey before "
                    + folks[0]->query_objective()
                    + " with a playful twinkle in your eye.\n");

            folks[0]->CM("You catch your breath as "+QTNAME(TP())
                        + " curtseys before you with a playful twinkle in "
                        + TP()->query_possessive()+" eye.\n");
            tell_room(environment(TP()),QCTNAME(folks[0])+" catches "
              + folks[0]->query_possessive()+" breath as "+QTNAME(TP())
              + " curtseys deeply before "+folks[0]->query_objective()
              + " with a playful twinkle in "
              + TP()->query_possessive()+" eye.\n",({TP(),folks[0]}));

            return 1;
         }

         for (i=0;i<sizeof(folks);i++)
         {
             TP()->CM(QCTNAME(folks[i])+" catches "
                     + folks[i]->query_possessive()
                     + " breath as you curtsey before "
                     + folks[i]->query_objective()
                     + " with a playful twinkle in your eye.\n");

             folks[i]->CM("You catch your breath as "+QTNAME(TP())
                         + " curtseys before you with a playful twinkle in "
                         + TP()->query_possessive()+" eye.\n");
         }

    return 1;
    break;

/*=========================================================================*/
      case "quickly":
      TP()->add_prop("_minstrel_s_mbow",how);

      if (notarget)
      {
            write("Pressed for time, you drop a quick curtsey.\n");
            say(QCTNAME(TP())+" drops a quick curtsey, obviously pressed for "
                + "time.\n");

            return 1;
        }
        if (sizeof(folks)==0)
        {
            NF("Mcurtsey to whom?\n");
            return 0;
        }

        if (sizeof(folks)==1)
        {
            TP()->CM("Pressed for time, you drop a quick curtsey to "
                     + QTNAME(folks[0]) + ".\n");

            TR( " drops a quick curtsey to "+ QTNAME(folks[0])
                + ", clearly pressed for time.\n",
                ({folks[0], TP()}));

            folks[0]->CM(QCTNAME(TP())+" drops a quick curtsey, obviously "
                         + "pressed for time.\n");

            return 1;
        }

        for (i=0;i<sizeof(folks);i++)
        {
            TP()->CM("Pressed for time, you drop a quick curtsey to "
                     +QTNAME(folks[i]) + ".\n");

            folks[i]->CM(QCTNAME(TP())
                         + " drops you a quick curtsey, clearly pressed for "
                         + "time.\n");
        }

        return 1;
        break;

/*=========================================================================*/
    default:
           write("Mcurtsey how?  Do <help minstrels emotes> for a list "
                + "of the nuances in this seemingly simple greeting.\n");

    return 1;
    break;
    }

    return 0;
}

/*
 ****************************************************************************
 * Function:    do_mourn
 * Description: When a Minstrel dies all members are notified of the sad
 *              fact via the bells in the Tower. If a minstrel chooses he
 *              can play a song of mourning for his dead comrade, joining
 *              a game-wide choir of mourning. The choir summons an avatar
 *              of the Muses, to stand watch over the corpse. The avatar
 *              will not allow anything to remove the contents of the corpse
 *              until the reincarnated minstrel arrives to claim his goods,
 *              or the duration of the avatar runs out. The duration and
 *              hit points of the avatar is determined by the number of
 *              minstrels who mourn, and how much mana they pump into the
 *              mourning. Of course, if the avatar is killed, all bets are
 *              off -- anything may remove items from the corpse.
 * Syntax:      mourn <name>
 */
int
do_mourn(string str)
{
#define MOURN_SONG MUNDANEDIR+"mourning.song"

    string name, adj, av_name, where_died;
    object avatar, *minstrels, deader;
    mixed *argarray = ({});
    int i;

    setuid();
    seteuid(getuid());
    NF("Whom did you wish to mourn? Remember that you may start the Mourning "
       + "Choir only for a departed Minstrel.\n");
    if (!str)
        return 0;

    str = lower_case(str);
#if 0
    if (!(deader = parse_this(str, "[the] %l")))
    {
        deader = find_player(str);
    }
    else if (sizeof(deader) > 1)
    {
#endif
    minstrels = ON_LINE();
    if (!parse_command(str, minstrels, "%o", deader))
        return 0;
    if (deader == TP())
    {
        NF("You cannot mourn yourself!\n");
        return 0;
    }
    name = deader->query_real_name();
    av_name = "minstrel_avatar_" + name;
    avatar = find_living(av_name);
    if (avatar)
    {   /* Avatar already exists */
        if (avatar->check_singer(TP()->query_real_name()))
        {
            TP()->CM("You have already joined that Choir; you can do no "
                     + "more for "+capitalize(name)+".\n");
            return 1;
        }
        if (TP()->query_mana() < TP()->query_stat(SS_LAYMAN))
        {
            TP()->CM("You begin to join the Choir, but quickly realize that "
                     + "you currently lack the energy to attempt so potent "
                     + "a Song.\n");
            return 1;
        }
        TP()->add_mana(- TP()->query_stat(SS_LAYMAN));
        TP()->CM("You join the Mourning Choir for "+capitalize(name)+", and "
                 + "add your voice to the distant and powerful music.\n");
        tell_room(environment(TP()),
                  QCTNAME(TP())+" looks up, eyes unfocused as though "
            + TP()->query_pronoun()+" hears a distant call. A look of "
            + "profound sadness passes over "+TP()->query_possessive()+" "
            + "face, and "+TP()->query_pronoun()+" begins a song....\n",TP());
        /* Wizards mourn only for effect, no mana aid provided */
        if (TP()->query_wiz_level() == 0)
        {
            avatar->inflate(TP(),TP()->query_stat(SS_LAYMAN));
        }
        for (i=0;i<sizeof(minstrels);i++)
        {
            if (minstrels[i] == deader)
            {
                deader->CM("From far, far away you hear "
                           + TP()->query_name()+" add "
                           + TP()->query_possessive()
                           + " voice to your Choir.\n");
            }
            else if (minstrels[i] == TP())
            {
                continue;
            }
            else if (present(minstrels[i],environment(TP())))
            {
                minstrels[i]->CM(QCTNAME(TP())+" joins the Mourning Choir.\n");
            }
            else if (name != GUILDMASTERJR)
            {
                minstrels[i]->CM("As if from a great distance, you hear "
                                 + TP()->query_name()+" add "
                                 + TP()->query_possessive()+" voice to the "
                                 + "Mourning Choir for "+capitalize(name)
                                 + ".\n");
            }
        }
#if 0
        argarray += ({read_file(MOURN_SONG), TP(), "sing", 1});
        sing_song(argarray);
#endif
    }
    else
    {   /* Avatar doesn't exist; start one */
        setuid();
        seteuid(getuid());

        if (TP()->query_mana() < 2 * TP()->query_stat(SS_LAYMAN))
        {
            TP()->CM("You begin to initiate a Choir, but quickly realize that "
                     + "you currently lack the energy to attempt so potent "
                     + "a Song.\n");
            return 1;
        }
        TP()->add_mana(- 2 * TP()->query_stat(SS_LAYMAN));
        avatar = clone_object(GUILDNPC+"avatar");
        TI()->CM("You begin a Mourning Choir for "+capitalize(name)
                 + ", projecting your voice across the land in an invitation "
                 + "to join the Choir.\n");
        say(QCTNAME(TI())+" begins a song, and "+TP()->query_possessive()
            + " voice swells in volume until it seems the whole world must "
            + "hear.\n",minstrels);
        where_died = TI()->query_prop("_minstrel_"+name+"_died_here");
        if (where_died == 0
            || avatar->move_living("M",where_died,1,1)
            || avatar->set_deader(name, TI(), av_name))
        {
            TI()->CM("Something prevents you from completing the song!\n");
            tell_room(environment(TI()),
                      QCTNAME(TI())
                      +" stops short, song unfinished, with a puzzled "
                      + "look on "+TI()->query_possessive()+" face.\n", TI());
            avatar->remove_object();
            return 1;
        }
        avatar->inflate(TP(),TP()->query_stat(SS_LAYMAN));

        tell_room(where_died, "From afar you hear a mournful dirge. The sound "
                  + "grows closer and you realize it is a choir of voices, "
                  + "singing together a song both powerful and sad. The sound "
                  + "of the choir continues to grow nearer, and though you "
                  + "can almost resolve individual voices you still "
                  + "can make out no source. The music swells, and reaches "
                  + "a deafening crescendo, and suddenly in a blast of sound "
                  + "seems to coalesce in this very spot! Above the corpse "
                  + "of "+capitalize(name)+" now stands a stern white figure, "
                  + "an embodiment of the Choir's music! Though she speaks no "
                  + "word, you find you know somehow that this white-clad "
                  + "apparition is the avatar of a powerful being indeed.\n",
                  TI());
        if (MASTER_OB(environment(this_interactive())) == where_died)
            TI()->CM("Inspired by the muses, your voice swells to a power "
                     + "that surprises even you. The music grows until it "
                     + "seems to have a life of its own, your poor frame a "
                     + "mere vehicle for the very music of the Muses. Your "
                     + "lone voice becomes one of a multitude. Above all you "
                     + "can hear the voice of "+deader->query_muse_name()+" "
                     + "leading the great Choir, mourning the loss of her "
                     + "beloved servant "+capitalize(name)+". And still the "
                     + "music swells, and reaches a deafening crescendo, and "
                     + "suddenly in a blast of sound seems to coalesce in "
                     + "this very spot! Above the corpse of "+capitalize(name)
                     + " now stands a stern white figure, an avatar of "
                     + deader->query_muse_name()+"!\n");
        for (i=0;i<sizeof(minstrels);i++)
        {
            if (minstrels[i] == deader)
            {
                deader->CM("Even unto death itself reaches the power of "
                           + deader->query_muse_name()+". From a distance "
                           + "past all imagining you hear the voice of "
                           + TI()->query_name()+" begin a Choir of Mourning "
                           + "for you.\n");
            }
            else if (present(minstrels[i],environment(TI())))
            {
                if (minstrels[i] != TI())
                    minstrels[i]->CM(QCTNAME(TI())
                                     +" begins a Choir of Mourning "
                                     + "for "+capitalize(name)+", and "
                                     + TI()->query_possessive()
                                     + " voice swells "
                                     + "until it seems the whole world must "
                                     + "hear.\n");
            }
            else if (name != GUILDMASTERJR)
            {
                minstrels[i]->CM("As if from a great distance, you hear "
                                 + TI()->query_name()+" begin a Choir of "
                                 + "Mourning for "+capitalize(name)+".\n");
            }
        }
/*      argarray += ({read_file(MOURN_SONG), TI(), "sing", 1});
        sing_song(argarray); */
    }
    return 1;
}

/*
 ***************************************************************************
 * Function:     do_mumble
 * Description:  A simple Minstrel emote.
 */

int
do_mumble(string str)
{
   int  stl;

   stl = strlen(str);

   if (str)
   {
      write("You mumble something about "+str+".\n");
      say(QCTNAME(TP())+" mumbles something about "+str+".\n");

      return 1;
   }

   write("You mumble under your breath.\n");
   say(QCTNAME(TP())+" mumbles something under "
      + TP()->query_possessive()+" breath.\n");

   return 1;
}

void
stop_singing_now(object player)
{
    player->change_prop("_minstrel_i_singing", 0);
}

/**************************
 * Function:     start_power
 * Description:
 */

void start_power(string songfile, int evoc, int eins,
                 object *obs, object performer)
{
   int result;

   result=songfile->do_song(performer, obs, performer->query_stat(SS_LAYMAN),
                            eins ? performer->query_stat(SS_DEX) : 0,
                            evoc ? performer->query_stat(SS_DIS) : 0,
                            evoc, eins, 100);

   performer->remove_prop("_minstrel_i_sop_alarm");

   switch (result)
   {
      case -1:    /* SONG FAILED COMPLETELY */
           performer->CM("The Song of Power fails!\n");
           performer->add_mana(-(songfile->query_mana_cost(result)/4));
           song_hurt(performer); /* DID THEY DAMAGE VOICE OR INSTRUMENT? */
           performer->remove_prop("_minstrel_i_singing");
      return;

      case 0:     /* SONG COULDN'T BE PLAYED */
           performer->remove_prop("_minstrel_i_singing");
      return;

      case 1..20: /* SONG PLAYED, BUT POSSIBLE DAMAGE */
           if (random(20)>result)
              song_hurt(performer); /* DID THEY DAMAGE VOICE OR INSTRUMENT? */
           performer->add_mana(-(songfile->query_mana_cost(result)));
           performer->remove_prop("_minstrel_i_singing");
      return;

      default:    /* SONG PLAYED EASILY */
             performer->add_mana(-(songfile->query_mana_cost(result)));
             performer->remove_prop("_minstrel_i_singing");
      return;
   }
}


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

/*
 ***************************************************************************
 * Function:    do_perform
 * Description: An outrageously complex function. Sings, plays, or performs
 *              a Mundane, Ballad, or Epic, softly or loudly.
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
       + "Where <type> is mundane, ballad, or power, and <song> is the "
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

   /* ---------------- Song of Power ----------------- */
    setuid();
    seteuid(getuid());

    if (minstrel = this_player()->find_spell(songstr))
    {
        if(this_player()->query_prop(LIVE_M_MOUTH_BLOCKED) &&
          (minstrel->query_spell_form_skill() == SG_VOCAL ||
           minstrel->query_spell_element() == SG_VOCAL))
        {
            notify_fail("You are unable to sing, and cannot perform the " +
                "Song of Power properly!\n");
            return 0;
        }

        if((minstrel->query_spell_form_skill() != SG_VOCAL &&
           minstrel->query_spell_element() != SG_VOCAL) &&
           query_verb() == "sing")
        {
            notify_fail("This Song of Power, ironically, doesn't " +
                "require singing to perform! Try playing or " +
                "performing it.\n");
            return 0;
        }

        if((minstrel->query_spell_form_skill() != SG_INSTRUMENTAL &&
           minstrel->query_spell_element() != SG_INSTRUMENTAL) &&
           query_verb() == "play")
        {
            notify_fail("This Song of Power doesn't require an " +
                "instrument to perform! Try singing or performing it.\n");
            return 0;
        }

        if(minstrel->is_minstrel_spell())
        {
            if(this_player()->query_prop(OBJ_I_HIDE))
            {
                write("It's too difficult to hide while performing, " +
                    "you're visible again.\n");
                this_player()->reveal_me(0);
            }

            this_player()->start_spell(songstr, affected, minstrel);
            // DEBUG("Spell found: " +songstr+ ", target: " +affected+ ".");
            return 1;
        }
    }
    else
    {
        songfile = SONG_INDEX->parse_song(songstr);
    }

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

/*==========================================================================*
 * Find an adverb appropriate to the minstrel's skill level.
 */
   if (verb == "sing")
       adverb = TP()->query_vocal_skill_adverb();
   else if (verb == "play")
       adverb = TP()->query_instrument_skill_adverb();
   else /* verb == "perform" */
       adverb = TP()->query_minstrel_skill_adverb();

   if (i>1 && j>1 && TP()->query_skill(SG_INSTRUMENTAL)
                           + TP()->query_skill(SG_VOCAL))
      adverb = "nevertheless "+adverb;

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

   /* ---------------- Mundane ----------------- */
   if (wildmatch(MUNDANEDIR+"*",songfile))
   {
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
                    NF("Another Minstrel is currently performing here. " +
                        "You should wait until they finish.\n");
                    return 0;
                }
            }
       }

       TP()->change_prop("_minstrel_i_singing", 1);
       if (TP()->query_prop(MINSTREL_I_VOLUME) == SOFT)
           adverb = "softly and " + adverb;
       else if (TP()->query_prop(MINSTREL_I_VOLUME) == LOUD)
           adverb = "loudly and " + adverb;
       TP()->CM(capitalize(selftext+"you "+adverb+" "+verb+" "
                           + newtitle+":\n"));

       say(capitalize(songtext+QTNAME(TP())+" "+adverb+" "+verb+"s a song: \""
                      + newtitle+"\".\n"), TP());

       if (verb != "play")
           sing_song(argarray);
       return 1;
   }
   /* ---------------- Ballad or Epic ----------------- */
   if (wildmatch(BALLADDIR+"*", songfile) ||
       wildmatch(EPICDIR+"*", songfile))
      {
      if (special_verb && strlen(special_verb))
          verb = special_verb;
      else if (verb=="")
          verb = query_verb();

      argarray = ({});

      if (TP()->query_mana() < 7)
      {
         write("You are mentally drained; the singing of a Ballad is "
              + "beyond your powers right now.\n");
         return 1;
      }
      text = implode(filter(explode(read_file(songfile, 2)+"\n", "\n"),
            "comment_filter", TO()), "\n");
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
                    NF("Another Minstrel is currently performing here. " +
                        "You should wait until they finish.\n");
                    return 0;
                }
            }
       }

      TP()->change_prop("_minstrel_i_singing", 1);
      if (TP()->query_prop(MINSTREL_I_VOLUME) == SOFT)
          adverb = "softly and " + adverb;
      else if (TP()->query_prop(MINSTREL_I_VOLUME) == LOUD)
          adverb = "loudly and " + adverb;
      TP()->CM(capitalize(selftext+"you "+adverb+" "+verb+" "
              + newtitle+ ((verb != "play") ? ":\n" : ".\n")));

      say(capitalize(songtext+QTNAME(TP())+" "+adverb+" "+verb+"s a song: \""
         + newtitle+"\".\n"), TP());

      if (verb == "play")
            set_alarm(10.0, 0.0, &stop_singing_now(TP()));
      else
            sing_song(argarray);

      obs = ON_LINE();

      for (i=0;i<sizeof(obs);i++)
          if (!present(obs[i], environment(TP()))
              && obs[i]->query_hear_ballads()
              && TP()->query_prop(MINSTREL_I_VOLUME) > SOFT)
          {
              if (TP()->query_special_title() ||
                  (obs[i]->query_met(TP()->query_real_name())
                   && (verb != "play"
                      || TP()->query_skill(SG_INSTRUMENTAL) > 90)))
              {
                  /* We've met, and either you're singing and we        *
                   * recognize your voice, or you're playing and        *
                   * you're so highly skilled that we recognize your    *
                   * playing style.                                     */
                  obs[i]->CM(BS("As if from a great distance, "
                                + "you hear " + TP()->query_name()
                                + " " + verb + "ing \""+ newtitle +"\".\n"));
              }
              else
              {
                  if (verb == "play")
                      obs[i]->CM(BS("As if from a great distance, you hear "
                                    +LANG_ADDART(TP()->query_instrument_name())
                                    + " "
                                    + TP()->query_instrument_skill_adverb()
                                    + " "+ verb + "ing \""+ newtitle
                                    + "\".\n"));
                  else if (verb == "sing")
                      obs[i]->CM(BS("As if from a great distance, you hear "
                                    + LANG_ADDART(TP()->query_race_adj())
                                    + " voice "
                                    + TP()->query_vocal_skill_adverb() + " "
                                    + verb + "ing \""+ newtitle + "\".\n"));
                  else /* verb == "perform" */
                  {
                      if (TP()->query_vocal_skill_adverb() ==
                          TP()->query_instrument_skill_adverb())
                          obs[i]->CM(BS("As if from a great distance, you "
                                        + "hear "
                                        + LANG_ADDART(TP()->query_race_adj())
                                        + " voice "
                                        + TP()->query_vocal_skill_adverb()
                                        + " singing and playing \""+ newtitle
                                        + "\" on " + TP()->query_possessive()
                                        + " " + TP()->query_instrument_name()
                                        + ".\n"));
                      else
                          obs[i]->CM(BS("As if from a great distance, you "
                                        + "hear "
                                        + LANG_ADDART(TP()->query_race_adj())
                                        + " voice "
                                        + TP()->query_vocal_skill_adverb()
                                        + " singing and "
                                        + TP()->query_instrument_skill_adverb()
                                        + " playing \""+ newtitle + "\" on "
                                        + TP()->query_possessive() + " "
                                        + TP()->query_instrument_name()
                                        + ".\n"));
                  }
              }
          }
          else if (present(obs[i], environment(TP())))
              obs[i]->CM(BS("The great Ballad stirs something "
                            + "deep within your Minstrel's soul.\n"));

      if (TP()->query_prop(MINSTREL_I_VOLUME, SOFT))
          TP()->add_mana(-3); /* Singing a ballad uses a little mana. */
      else
          TP()->add_mana(-7);

      return 1;
   }

   return 0;
}
/*=========================================================================*/

void break_power(object player)
{
    int alarm_id;
    object instrument = present("minstrel_instrument",player);

    // Make us remove the alarm
    alarm_id = player->query_prop("_minstrel_i_sop_alarm");

    // If we have no alarm, return
    if(!alarm_id)
        return;

    // Stop playing
    remove_alarm(alarm_id);

    player->catch_msg("Your focus is broken, and " +
            "you are unable to complete the Song of Power.\n");

    // Damage the instrument
    song_hurt(player);

    // Allow them to start a new song
    player->remove_prop("_minstrel_i_sop_alarm");
    player->remove_prop("_minstrel_i_singing");
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


/**************************
 * Function:     song_hurt
 * Description:  Rolls the dice to see if the player hurt their voice
 *               or instrument in attempting to play a song beyond their
 *               ability.
 */

void song_hurt(object player)
{
    if (random(10) == 1)
    {
        object instrument = present("minstrel_instrument",player);

        player->catch_tell("Hmmmmm...something seems wrong with your "
                   + instrument->query_name()+".\n");
        instrument->add_damage(random(5));
   }
}


/*=========================================================================*/


/*
 ****************************************************************************
 * Function:     do_rehearse
 * Description:  A simple Minstrel emote.
 */

int
do_rehearse(string str)
{

}

/*
 ****************************************************************************
 * Function:     do_repair
 * Description:  Tune or repair a minstrel's instrument.
 *               do_repair employs the task system. The difficulty of
 *               the task varies with the level of damage to the instrument,
 *               and the relevant skill is tune/repair instruments (#130053)
 */

int
do_repair(string str)
{
   object instrument, ob, fork, *forks;
   int i;

   NF("Usage: "+query_verb()+" <instrument>.\n");

   instrument = present("minstrel_instrument", TP());

   if (!str)
      return 0;

   if (!parse_command(str, TP(), "%o", ob))
      return 0;

   if (ob != instrument)
      return 0;

   if (instrument->query_damage() > 5 && query_verb() == "tune")
   {
      NF("Your "+instrument->query_name()+" is beyond tuning! It has "
        + "been damaged and must be repaired.\n");

      return 0;
   }

   if (instrument->query_damage() <= 5 && query_verb() == "repair")
   {
      NF("Your instrument is out of tune, not damaged. Why not tune it?\n");

      return 0;
   }

   if (instrument->query_damage() < 1)
   {
      NF("Your "+instrument->query_name()+" is in perfect shape!\n");

      return 0;
   }

   forks = filter(all_inventory(this_player()), &->query_minstrel_fork());

   if (!sizeof(forks))
   {
       write("You don't have a tuning fork!\n");
       return 1;
   }

   forks = filter(forks, not @ &->query_prop(OBJ_I_BROKEN));

   if (!sizeof(forks))
   {
       write("All of your forks are broken!\n");
       return 1;
   }

   fork = forks[0];

   if (query_verb() == "tune")
   {
      if (!fork)
      {
         NF("You need a tuning fork to properly judge the pitch of your "
           + "instrument.\n");

         return 0;
      }

      fork->strike_minstrel_fork();

      if (TP()->resolve_task(200 + 100 * instrument->query_damage(),
               ({SG_TUNE_REPAIR})) > 0)
      {
         TP()->CM("You successfully bring your "+instrument->query_name()
                 + " back into perfect pitch.\n");

         instrument->set_damage(0);

         return 1;
      }
      else
      {
         TP()->CM("You try your best, but find your skills unequal to the "
                 + "task.\n");
         return 1;
      }
   }
   if (TP()->resolve_task(100 * instrument->query_damage(),
            ({SG_TUNE_REPAIR})) > 0)
   {
      TP()->CM("You successfully repair your "+instrument->query_name()
              + ".\n");

      instrument->set_damage(random(6));

      return 1;
   }
   else
   {
      TP()->CM("You try your best, but find your skills unequal to "
              + "the task this time.\n");

      return 1;
   }
}

/*
 ****************************************************************************
 * Function:     do_scales
 * Description:  A simple Minstrel emote.
 */

int
do_scales(string str)
{
   if (!str)
   {
      write("In an effort to annoy that someone special, you "
           + "take out your instrument and practice your scales.\n");
      say("In a blatant effort to annoy you, "+ QCTNAME(TP())+" takes out "
         + TP()->query_possessive()+" instrument "
         + "and begins to practice "+ TP()->query_possessive()+" scales..."
         + "over and over.\n");

      return 1;
   }
   return 0;
}

/*
 ****************************************************************************
 * Function:     do_serenade
 * Description:  A simple Minstrel emote.
 */

int
do_serenade(string str)
{
   object  *folks;
   int     i;

   folks = parse_this(str, "%l");

   if (sizeof(folks)==0)
   {
      NF("Whom do you intend to serenade?\n");

      return 0;
   }

   if (sizeof(folks)==1)
   {
      TP()->CM("You serenade "+QTNAME(folks[0])+" with a lilting tune.\n");

      TR( " serenades "+QTNAME(folks[0])
        + " with a lilting tune.\n", ({folks[0], TP()}));

      folks[0]->CM(QCTNAME(TP())+" serenades you with a lilting tune.\n");

      return 1;
   }

   for (i=0;i<sizeof(folks);i++)
       if (folks[i]!=TO())
       {
          folks[i]->CM(QCTNAME(TP())+" serenades you with a lilting "
                      + "tune.\n");

          TP()->CM("You serenade "+QTNAME(folks[i])+" with a lilting "
                  + "tune.\n");
       }
   return 1;
}

/*
 ****************************************************************************
 * Function:     do_set
 * Description:  Let the player set many options, including mood (which
 *               influences the random choice of 'say' verbs), and whether
 *               or not the player can hear certain things.
 *
 * Arguments:    str - should be '<attribute> <setting>'
 * Returns:      1 if successful,  0 otherwise.
 */

int
do_set(string str)
{
   string  attribute="", setting="";

   NF("You may set the following attributes:\n mood, bells, dais, "
     + "ballads, exc_verbs.\n");

   if (!strlen(str))
      return 0;

   parse_command(str, ({}), "%w %s", attribute, setting);

   if (attribute != "mood" && attribute != "bells" && attribute != "dais" &&
       attribute != "ballads" && attribute != "exc_verbs") return 0;

   switch (attribute)
   {
       case "mood":
       NF("Your current mood is: "+TP()->query_mood_name()+".\n"
          + "You may set these moods:\nangry, brave, carefree, "
          + "conversational, haughty, impatient, jovial, neutral, "
          + "observant, plaintive, random, "
          + "romantic, sad, sarcastic, serious, "
          + "secretive, song.\n");

       if (!strlen(setting))
           return 0;

       switch (setting)
       {
           case "secretive":
           TP()->set_mood(SECRETIVE);
           write("You lower your voice.\n");
           say(QCTNAME(TP())+" lowers "+TP()->query_possessive()+" voice "
               + "and glances furtively about.\n");
           break;

           case "serious":
           TP()->set_mood(SERIOUS);
           write("You grow more serious.\n");
           say(QCTNAME(TP())+" grows serious.\n");
           break;

           case "jovial":
           TP()->set_mood(JOVIAL);
           write("A happy smile plays upon your lips.\n");
           say(QCTNAME(TP())+" seems to become quite jovial.\n");
           break;

           case "brave":
           TP()->set_mood(BRAVE);
           write("You straighten your back and look Life right in "
                 + "the eye.\n");
           say(QCTNAME(TP())+" straightens "+TP()->query_possessive()
               +" back and looks you right in the eye.\n");
           break;

           case "conversational":
           TP()->set_mood(CONVERSE);
           write("You settle back for a long talk.\n");
           say(QCTNAME(TP())+" settles comfortably back to "
               + "converse.\n");
           break;

           case "sad":
           TP()->set_mood(SAD);
           write("Depression settles upon you like a black fog.\n");
           say(QCTNAME(TP())+" looks crestfallen.\n");
           break;

           case "angry":
           TP()->set_mood(ANGRY);
           write("Your fury knows no bounds!\n");
           say(QCTNAME(TP())+ " grows visibly angry.\n");
           break;

           case "song":
           TP()->set_mood(SONG);
           write(BS("You feel the sudden desire to sing all your "
                    + "words. A natural impulse for a Minstrel..\n"));
           say(QCTNAME(TP())+" looks ready to burst into song!\n");
           break;

           case "sarcastic":
           TP()->set_mood(SARCASTIC);
           write("Yeah, sarcastic. Right.\n");
           TP()->command("grin sarcastically");
           break;

           case "neutral":
           TP()->set_mood(NEUTRAL);
           write("You carefully wipe all expression from your voice, "
                 + "settling on a bland monotone.\n");
           say("A bland look passes over the features of "
               + QCTNAME(TP())+".\n");
           break;

           case "romantic":
           TP()->set_mood(ROMANTIC);
           write("Your heart and voice fill with courtly love!\n");
           say(QCTNAME(TP())+" gets a dreamy, romantic look.\n");
           break;

           case "plaintive":
           TP()->set_mood(PLAINTIVE);
           write("You feel like complaining. The world is so unfair!\n");
           say(QCTNAME(TP())+" gets a plaintive pout.\n");
           break;

           case "carefree":
           TP()->set_mood(CAREFREE);
           write("You forget your problems for the moment and let your "
                 + "troubles slip away.\n");
           say(QCTNAME(TP())+" gets a carefree, untroubled look.\n");
           break;

           case "observant":
           TP()->set_mood(OBSERVANT);
           write("You furrow your brow in concentration.\n");
           say(QCTNAME(TP())+" peers observantly about.\n");
           break;

           case "impatient":
           TP()->set_mood(IMPATIENT);
           write("You tap your foot impatiently.\n");
           say(QCTNAME(TP())+" taps "+TP()->query_possessive()+" foot "
               + "impatiently.\n");
           break;

           case "haughty":
           TP()->set_mood(HAUGHTY);
           write("You hold yourself aloof from the crowd.\n");
           say(QCTNAME(TP())+" raises "+TP()->query_possessive()+" nose "
               + "with a haughty air.\n");
           break;

           case "random":
           TP()->set_mood(RANDOM);
           write(BS("You feel a bit unsteady, as if wavering at the "
                    + "brink of many different emotions.\n"));
           say(QCTNAME(TP())+" seems moody, as if unsure whether "
               + "to laugh or cry.\n");
           break;

           default: return 0;
       }
       return 1;

       case "exc_verbs":

       string *exc_verbs = PERFORM_MANAGER->query_mood_excluded_verbs(TP());

               //DEBUG("exc_verbs executed, setting: " +setting);

       if(!strlen(setting))
       {
               //DEBUG("NO settings called");
           if(!sizeof(exc_verbs))
           {
               //DEBUG("NO sizeof called");
               write("You currently are not excluding any mood verbs.\n");
               return 1;
           }

           if(sizeof(exc_verbs) == 1)
           {
               write("You currently are excluding the following verb: " +
                   exc_verbs[0]+ ".\n");
               return 1;
           }

           int exc_size = sizeof(exc_verbs);
           int psize;
           string ev = "";

           foreach(string verb: exc_verbs)
           {
               psize++;
               ev += verb;

               if(exc_size - psize == 1)
                   ev += ", and ";
               else if(exc_size - psize > 1)
                   ev += ", ";
            }

            write("You currently exclude using the following verbs: " +ev+ ".\n");
            return 1;
       }

       if(member_array(lower_case(setting), exc_verbs) > -1)
       {
            PERFORM_MANAGER->remove_mood_excluded_verbs(TP(), setting);
            write("You are no longer excluding yourself from using the " +
                "mood verb " +setting+ ".\n");
            return 1;
       }
       else
       {
            PERFORM_MANAGER->add_mood_excluded_verbs(TP(), setting);
            write("You exclude yourself from using the mood verb " +setting+ ".\n");
            return 1;
       }

       return 1;

       case "bells":

       if (TP()->query_hear_bells())
           NF("You currently hear the Bells of the Tower.\n"
              + "You may set bells to 'hear' or 'ignore'\n");

       else
           NF("You are currently ignoring the Bells of the Tower.\n"
              + "You may set bells to 'hear' or 'ignore'\n");

       switch (setting)
       {
           case "hear":
           write("You now hear the Bells of the Tower\n");
           TP()->set_hear_bells(1);
           break;

           case "ignore":
           write("You now ignore the Bells of the Tower\n");
           TP()->set_hear_bells(0);
           break;

           default: return 0;
       }
       return 1;

       case "dais":
       if (TP()->query_hear_dais())
           NF("You currently hear those speaking from the dais.\n"
              + "You may set dais to 'hear' or 'ignore'\n");
       else
           NF("You are currently ignoring those speaking from the dais.\n"
              + "You may set dais to 'hear' or 'ignore'\n");

       switch (setting)
       {
           case "hear":
           write("You now hear those speaking from the Dais.\n");
           TP()->set_hear_dais(1); break;

           case "ignore":
           write("You now ignore those speaking from the Dais.\n");
           TP()->set_hear_dais(0);
           break;

           default: return 0;
       }
       return 1;

       case "ballads":
       if (TP()->query_hear_ballads())
           NF("You currently hear those singing Ballads.\n"
              + "You may set ballads to 'hear' or 'ignore'\n");

       else
           NF("You are currently ignoring those singing Ballads.\n"
              + "You may set ballads to 'hear' or 'ignore'\n");

       switch (setting)
       {
           case "hear":
           write("You now hear those singing Ballads and Epics.\n");
           TP()->set_hear_ballads(1);
           break;

           case "ignore":
           write("You now ignore those singing Ballads and Epics.\n");
           TP()->set_hear_ballads(0);
           break;

           default: return 0;
       }
       return 1;

       default: return 0;
   }
}

/*
 * Function:    do_softly
 * Description: The minstrel may want to sing/play/perform his or her songs
 *              softly, in effect pumping less mana into the song.
 *              This is possible with the command "softly play ...",
 *              "softly perform ...", or "softly sing ...". The do_softly
 *              function sets a property in the minstrel to indicate that
 *              he/she is being quiet, calls the rest of the string with
 *              command(), then resets the property.
 */
int
do_softly(string str)
{
    int result;
    string *words, verb;

    words = explode(str + " ", " ");
    verb = words[0];
    words = words - ({ verb });
    if (sizeof(words) < 1)
    {
        NF("Softly sing? play? perform? mourn? what?\n");
        return 0;
    }
    TP()->add_prop(MINSTREL_I_VOLUME, SOFT);
    result = do_perform(implode(words, " "), verb);
    TP()->remove_prop(MINSTREL_I_VOLUME);
    return result;
}

/*
 ****************************************************************************
 * Function:     do_song_emote
 * Description:  A simple Minstrel emote.
 *
 * Usage:        Type 'song <str>'.
 */

int
do_song_emote(string str)
{
    if (str)
    {
       TP()->CM("You sing a little song about "+str+".\n");

       TR( " sings a little song about "
         + str+".\n",TP());
       return 1;
    }

    TP()->CM("You sing a little song.\n");

    TR( " sings a little song.\n",TP());

    return 1;
}

/*
 ****************************************************************************
 * Function:     do_stop
 * Description:  Lets the minstrel cease singing a song.
 */

int
do_stop(string str)
{
   int  result;

   NF("Stop what? Singing? Playing? Performing? Searching? What?!?\n");

   if (!str) return 0;

   if (str=="singing" || str=="playing" || str=="performing")
   {
       int alarm_id = TP()->query_prop("_minstrel_i_song_alarm");

       if (alarm_id)
       {
           TP()->CM("You cease "+str+".\n");
           say(QCTNAME(TP())+" suddenly ceases "+TP()->query_possessive()
               + " song.\n");
           TP()->change_prop("_minstrel_i_singing", 0);
           TP()->remove_prop("_minstrel_i_song_alarm");
           remove_alarm(alarm_id);
           return 1;
       }
       alarm_id = TP()->query_prop("_minstrel_i_sop_alarm");
       if (alarm_id)
       {
           TP()->CM(BS("You abrubtly halt the Song of Power, and almost "
                       + "collapse as all of its beauty and energy drains "
                       + "out of your soul again.\n"));

           say(QCTNAME(TP())+" abruptly halts the Song of Power, "
               + "visibly drained.\n");

           TP()->change_prop("_minstrel_i_singing", 0);
           TP()->remove_prop("_minstrel_i_sop_alarm");
           remove_alarm(alarm_id);
           return 1;
       }
       else
       {
           TP()->CM("Hmmm..are you sure you were "+str+" at all? Anyway, "
                    + "you've certainly stopped now.\n");
           TP()->remove_prop("_minstrel_i_sop_alarm");
           TP()->remove_prop("_minstrel_i_singing");
           remove_alarm(alarm_id);
           return 1;
       }

   }
   else
       return 0;
}

/*
 ****************************************************************************
 * Function:     do_throat
 * Description:  A simple Minstrel emote.
 */

int
do_throat(string str)
{
   if (!str)
   {
      write("You clear your throat for attention.\n");
      say(QCTNAME(TP())+" clears "+TP()->query_possessive()+" throat.\n");
      return 1;
   }
   return 0;
}

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
          // mixed songfile = SONG_INDEX->parse_song(song);
          mixed songfile = SONG_INDEX->find_song(song);

          // dump_array(songfile);

          if (!pointerp(songfile))
          {
              song_array -= ({ song });
              // DEBUG("Removing from top 20 " +song+ ".");
          }
          else if(!wildmatch(MUNDANEDIR+"*",songfile[0]))
          {
              song_array -= ({ song });
              // DEBUG("Removing from Top 20 " +song+ ".");
          }
      }

      foreach(string song: song_array)
      {
          count++;
          // mixed songfile = SONG_INDEX->parse_song(song);
          mixed songfile = SONG_INDEX->find_song(song);
          string song_type = "";

          // dump_array(songfile);

          if(count > 20)
              break;

          if (pointerp(songfile) && wildmatch(MUNDANEDIR+"*",songfile[0]))
          {
              song_type = ", composed by " +SONG_INDEX->query_author(songfile[0]);
          }
          if (pointerp(songfile) && wildmatch(BALLADDIR+"*",songfile[0]))
          {
              song_type = ", composed by " +SONG_INDEX->query_author(songfile[0]);
          }

          if(count > 9)
              list_str += count + ".  "+capitalize(song)+ song_type+ "\n";
          else
              list_str += count + ".   "+capitalize(song)+ song_type+ "\n";
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

      if(file_size(TOP_MUNDANE_LOG) >= 0)
      {
          rm(TOP_MUNDANE_LOG);
      }
      write_file(TOP_MUNDANE_LOG, list_str);

      list_str = generate_scroll_text(list_str, "The Genesis Top 20 Mundanes");
      write(list_str);

      return 1;
   }

   if (str == "ballad chart")
   {
      string * song_array = string_top_song_list();
      string list_str = "  The Genesis Top 20 Ballads  \n\n";
      int count = 0;

      // If not a ballad, remove
      foreach(string song: song_array)
      {
          // mixed songfile = SONG_INDEX->parse_song(song);
          mixed songfile = SONG_INDEX->find_song(song);

          if (!pointerp(songfile))
              song_array -= ({ song });
          else if(!wildmatch(BALLADDIR+"*",songfile[0]))
              song_array -= ({ song });
      }

      foreach(string song: song_array)
      {
          count++;
          // mixed songfile = SONG_INDEX->parse_song(song);
          mixed songfile = SONG_INDEX->find_song(song);
          string song_type = "";

          if(count > 20)
              break;

          // dump_array(songfile);

          if (pointerp(songfile) && wildmatch(MUNDANEDIR+"*",songfile[0]))
          {
              song_type = ", composed by " +SONG_INDEX->query_author(songfile[0]);
          }
          if (pointerp(songfile) && wildmatch(BALLADDIR+"*",songfile[0]))
          {
              song_type = ", composed by " +SONG_INDEX->query_author(songfile[0]);
          }

          if(count > 9)
              list_str += count + ".  "+capitalize(song)+ song_type+ "\n";
          else
              list_str += count + ".   "+capitalize(song)+ song_type+ "\n";
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


      list_str = generate_scroll_text(list_str, "The Genesis Top 20 Ballads");
      write(list_str);

      return 1;
   }

   notify_fail("Top what? Mundane chart? Or Ballad chart?\n");
   return 0;
}

/*
 ****************************************************************************
 * Function:     do_violin
 * Description:  A simple Minstrel emote.
 */

int
do_violin(string str)
{
   object  *folks;
   int     i;

   folks = parse_this(str, "[for] %l");

   if (sizeof(folks)==0)
   {
      write("You play a tiny violin, conjured up for the purpose.\n");
      say(QCTNAME(TP())+" plays a tiny violin.\n");

      return 1;
   }

   if (sizeof(folks)==1)
   {
      TP()->CM("You play a tiny violin for "+QTNAME(folks[0])+".\n");

      TR( " plays a tiny violin for "
        + QTNAME(folks[0])+".\n", ({folks[0], TP()}));

      folks[0]->CM(QCTNAME(TP())+" plays a tiny violin for you.\n");

      return 1;
   }

   for (i=0;i<sizeof(folks);i++)
   {
      TP()->CM("You play a tiny violin for "+QTNAME(folks[i])+".\n");

      folks[i]->CM(QCTNAME(TP())+" plays a tiny violin for you.\n");
   }
   return 1;
}


/*
 * Function:    print_spell_list
 * Description: Used in the prayers command, this will print out
 *              each classification of spells with a header.
 */
public string
print_spell_list(object * spellobjs)
{
    string message_text = "";
    int spells_known = 0;
    if (sizeof(spellobjs))
    {
        foreach (object spellobj : spellobjs)
        {
            if (!spellobj->query_spell_can_be_learned(this_player()))
            {
                // Only show spells that we actually know
                continue;
            }
            spells_known++;
            message_text += sprintf("%-=12.12s %-=57.57s\n",
                spellobj->query_spell_name(), spellobj->query_spell_desc()
                + " (" + spellobj->query_spell_ingredients_description()
                + ")");
        }
        message_text += "\n";
    }
    if (spells_known == 0)
    {
        return "";
    }
    return message_text;
}

/*
 * Function name: songs
 * Description:   List the songs of power.
 */
public int
songs_of_power(string str)
{
    string *powers;
    int max = 0;
    object songbook;

   if(present("minstrel_song_book", this_player()))
       songbook = present("minstrel_song_book", this_player());

    object *spellobjs = this_player()->query_spellobjs();
    spellobjs = filter(spellobjs, &wildmatch(MIN_SPELLS + "*") @ file_name);

    if (!sizeof(spellobjs))
    {
        write("You have not learnt any Songs of Power.\n");
        return 1;
    }

    string message_text = "Minstrel Songs of Power\n\n";
    message_text += print_spell_list(spellobjs);

    powers = SONGBOOK_MANAGER->query_power_songs(this_player()) || ({});
    max = songbook->query_power_max();

    if (!sizeof(powers))
    {

    }
    else if (objectp(songbook))
    {
    message_text += "You can currently copy up to " + LANG_NUM2WORD(max) +
        " Songs of Power in to your songbook.\n";
    }

    this_player()->more(generate_scroll_text(message_text,
                        "read your songbook for mundane, ballad, " +
                        "and epic songs"));
    return 1;
}

/*
 * Function:    show_spell_notes
 * Description: This function gets called when the command <spellnotes>
 *              executes. It goes through all the currently maintained
 *              effects and presents the requested note to the player
 */
public int
show_song_notes(string str)
{
    object player = this_player();
    object * effects = query_magic_effects(player);

    if (!sizeof(effects))
    {
        notify_fail("You are not maintaining any active song effects at the "
            + "moment so there are no notes to read.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Which song note do you wish to see?\n");
        return 0;
    }

    int effect_index;
    string effect_name, effect_target;
    if (sscanf(str, "%d", effect_index))
    {
        object effect;

        if (!effect_index || effect_index > sizeof(effects))
        {
            notify_fail("There is no song effect with that number.\n");
            return 0;
        }

        effect = effects[effect_index - 1];
        // Found the right effect.
        string message_text = "Song Details for "
            + capitalize(effect->query_spell_effect_name()) + "\n\n";
        string affecting = query_affecting_desc(player,
            effect->query_effect_target());
        message_text += sprintf("%-20s: %-=50.50s\n", "Name",
            effect->query_spell_effect_name());
        message_text += sprintf("%-20s: %-=50.50s\n", "Description",
            effect->query_spell_effect_desc());
        message_text += sprintf("%-20s: %-=50.50s\n", "Target", affecting);
        message_text += sprintf("%-20s: %-=50.50s\n", "About to Expire",
            effect->query_about_to_expire() ? "Yes" : "No");
        message_text += sprintf("%-20s: %-=50.50s\n", "Notes",
            strlen(effect->query_spell_effect_notes()) ?
            effect->query_spell_effect_notes() : "None");
        write(generate_scroll_text(message_text, "Minstrel Music System"));
        return 1;
    }

    notify_fail("Songnotes <number>?\n");
    return 0;
}

/*
 * Function:    list_song_effects
 * Description: This function gets called when the command <songeffects>
 *              executes. It goes through all the currently maintained
 *              effects (including spells) and presents it to the player.
 */
public int
list_song_effects(string str)
{
    object player = this_player();
    object * effects = query_magic_effects(player);

    int bViewOtherPlayer = 0;
    if (player->query_wiz_level() && strlen(str))
    {
        // Wizards are allowed to see the spelleffects for players.
        bViewOtherPlayer = 1;
        str = lower_case(str);
        if (!objectp(player = find_player(str)))
        {
            notify_fail("There is no player named " + capitalize(str)
                + " that you can view songeffects for.\n");
            return 0;
        }
        effects = query_magic_effects(player);
    }

    int index = 1;
    string message_text = "Currently Active Song Effects\n\n";

    if (bViewOtherPlayer)
    {
        message_text = "Currently Active Effects on "
            + capitalize(player->query_real_name()) + "\n\n";
    }

    message_text += sprintf("### %-15s %-20s %-20s %-5s\n", "Name",
        "Description","Target", "Notes");
    message_text += sprintf("--- %'-'15s %'-'20s %'-'20s %'-'|5s\n", "", "", "", "");

    foreach (object effect : effects)
    {
        string affecting = query_affecting_desc(player,
            effect->query_effect_target());

        if (effect->query_about_to_expire())
        {
            affecting += " *";
        }

        message_text += sprintf("%-3d %-=15.15s %-=20.20s %-=20.20s %|=5.5s\n",
            index++,
            effect->query_spell_effect_name(),
            effect->query_spell_effect_desc(),
            affecting,
            strlen(effect->query_spell_effect_notes()) ? "Yes" : "No");
    }

    if (!sizeof(effects))
    {
        message_text += sprintf("%|=64s\n", "-= No Active Effects =-");
    }

    message_text += "\n* indicates effect is about to expire\n";
    message_text += "\nTo see song's notes:   songnotes <num>\n";
    message_text += "\nTo end a song effect:  dispel <num>\n";
    message_text += "                       dispel <name>\n";
    message_text += "                       dispel <name> on <target>\n";
    message_text += "\nTo dispel all effects: dispel all\n";

    string additional_messages = player->customize_guild_spell_effect_messages(effects,
        message_text);

    if (strlen(additional_messages))
    {
        message_text += additional_messages;
    }


    write(generate_scroll_text(message_text, "Courtesy of the Muses, Divine " +
        "Arbiters of Music"));

    return 1;
}



/***************************** soul.c *****************************/
