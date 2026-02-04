/** soul.c **/

inherit "/cmd/std/command_driver";

#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"
#include "idea.c"

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define ADJARRAY  ({"a perky","a frivolous","a funny","a silly", \
		    "a popular","a catchy","a happy","an annoying", \
		    "a clever","a cute","a mournful","a sad","an amusing"})

#define MORE_OBJ  "/std/board/board_more"
#define TR(x, y)     tell_room(environment(TP()),QCTNAME(TP())+(x), y)

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

string get_soul_id()
{
   return "minstrel";
}

int query_cmd_soul()
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

mapping query_cmdlist()
{
   seteuid(getuid(TO()));
   return ([
	 "ahh":"do_ahh",
	 "mblink":"do_blink", 
	 "bored":"do_bored",
	 "choir":"do_choir", 
	 "clean":"do_clean",
	 "cross":"do_cross",
	 "entertain":"do_entertain",
	 "faint":"do_faint",
	 "face":"do_face",
	 "help":"do_help", 
	 "hum":"do_hum",
	 "loudly":"do_loudly",
	 "mbow":"do_mbow", 
	 "mcurtsey":"do_mcurtsey",
	 "mwhistle":"do_hum",
	 "mourn":"do_mourn", 
	 "mmumble":"do_mumble",
	 "perform":"do_perform", 
	 "play":"do_perform", 
	 "rehearse":"do_rehearse",
	 "repair":"do_repair", 
	 "scales":"do_scales",
	 "song":"do_song_emote",
	 "serenade":"do_serenade",
	 "set":"do_set",
	 "sing":"do_perform",
	 "softly":"do_softly",
	 "stop":"do_stop",
	 "throat":"do_throat",
	 "tune":"do_repair", 
	 "violin":"do_violin",
         "midea" : "_idea"]);
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
    TP()->CM("You go: ahhh....  and nod understandingly.\n");
    
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
   if (!str) 
   {
      write("GAWD...the agony...you may as well take a nap.\n");
      say("Obviously bored with your existence, "+QCTNAME(TP())
	 +" proceeds to doze off.\n");
      return 1;
   }
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
   
   if (str == "minstrels")
   {
      TP()->CM("Usage: help minstrels <topic>\n"
	 + "Where <topic> can be one of:\n"
         + "welcome, titles, emotes, songs, skills, set, choirs, lost_items, "
	 + "mourn, tax, midea, muses, epics, or voices.\n");
      
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
   
   verb = 
