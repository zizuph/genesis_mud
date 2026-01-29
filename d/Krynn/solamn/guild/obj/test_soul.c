/*
* Solamnian_soul.c - Soul for the Knights of Solamnia 
* 
* This soul holds the special skills and certain commands (rescue,
   * block, help, mercy, wimpy) of the Solamnian Knights
* 
* Commands found in other files:
* Emotes - /d/Krynn/solamn/guild/obj/lib/sol_emotes1.h & sol_emotes2.h
* Non-emote commands - /d/Krynn/solamn/guild/obj/lib/sol_cmds.h
* Combat special - /d/Krynn/solamn/guild/lib/kattack.h
*
*
* Made by Nick and Rastlin (When? Who knows? Haven't the Knights always
   * existed?) updated March 93 by Nick and Percy updated July 94 by Grace
* 
*
* Updates:
* -block and mercy commands Oct 94 by Aridor 
* -wimpy/whimpy commands Oct 94 by Aridor 
* -invite command Jan 95 by Aridor 
* -subdivision into lib files Dec 95 by Grace
* -emote changes Oct 95 by Morrigan
* -removal of bash and kick, replaced with kattack Nov 96 by Morrigan
* -removal of contact Nov 96 by Morrigan
* -moving of the invite command from the soul to the medal Nov 96 by 
*  Morrigan
*
* 
*/

#pragma save_binary

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <formulas.h>
#include <options.h>
#include <state_desc.h>
#include "/d/Krynn/open/sys/combat.h"
#include "../guild.h"

#define HELP_DIR    "/d/Krynn/solamn/guild/log/help_dir/"
#define KNIGHT_HITS "k_knight_hits"
#define DELAY       5

#define NORMAL_EXITS ({"north","south","east","west","up","down","enter",\
      "out","northwest","northeast","southwest","southeast"})
#define TRANSLATE_EXIT (["n":"north",\
      "s":"south",\
      "e":"east",\
      "w":"west",\
      "u":"up",\
      "d":"down",\
      "se":"southeast",\
      "sw":"southwest",\
      "ne":"northeast",\
      "nw":"northwest"])

/********************************************************************
* Soul identifying and autoloading
   ********************************************************************/

string
get_soul_id()
{
   return "Solamnian Knight";
}

int
query_cmd_soul()
{
   return 1;
}

/***********************************************************************
* The list of verbs and functions. Please add new in alphabetical order.
***********************************************************************/

mapping
query_cmdlist()
{
   setuid();
   seteuid(getuid());
   
   return ([ "observe": "observe" ]);
}

#include "/d/Krynn/solamn/guild/obj/lib/sol_cmds.h"/* NON-EMOTE COMMANDS */
#include "/d/Krynn/morrigan/open/observe.h"

/*
* Global variables
*/


/***********************************************************************
*  Guild-specific skills.
   *  New skills should be added in alphabetic order.
**********************************************************************/


/************************ rescue **************************************/
int
rescue(string str)
{
   object          ob, *others, *obj;
   int             i, j;
   
   NF("Rescue who?\n");
   if (!str || !sizeof(obj = parse_this(str, "%l")))
      return 0;
   ob = obj[0];
   NF("You cannot rescue because you can't see " + QTNAME(ob) + "!\n");
   if (!CAN_SEE(TP, ob))
      return 0;
   others = all_inventory(E(TP)) - ({ob}) - ({TP});
   for (i = 0; i < sizeof(others); i++)
   if (others[i]->query_attack() == ob) 
      {
      j = F_RESCUE(TP, ob);
      if (random(RESCUE_HIT) > random(j)) 
         {
         TP->catch_msg("You fail to rescue " + QTNAME(ob) + ".\n");
         ob->catch_msg(QCTNAME(TP) +
            " tries to rescue you but fails.\n");
         say(QCTNAME(TP) + " fails to rescue " + QTNAME(ob) + ".\n",
            ({ob, TP}));
         return 1;
       }
      TP->attack_object(others[i]);
      others[i]->attack_object(TP);
      TP->catch_msg("You heroically rescue " + QTNAME(ob) + ".\n");
      say(QCTNAME(TP) + " heroically rescues " + QTNAME(ob) + ".\n",
         ({ob, TP}));
      ob->catch_msg(QCTNAME(TP) + " rescues you heroically.\n");
      
      if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 2000)
         TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 2000);
      
      return 1;
   }
   TP->catch_msg("There is no one here hitting on " + QTNAME(ob) + ".\n");
   return 1;
}


/************************************************************************
*      Special attacks & Guild-specific skills end here
   ***********************************************************************/


/********************* help ********************************************/
int
help(string str)
{
   string subject, filename;
   
   if (!str)
      return 0;
   
   if (sscanf(str, "guild %s", subject) != 1)
      if (sscanf(str, "knight %s", subject) != 1)
      if (sscanf(str, "knights %s", subject) != 1)
      return 0;
   
   
   filename = HELP_DIR + subject;
   if (file_size(filename) > 0) 
      {
      setuid();
      seteuid(getuid());
      cat(filename);
      return 1;
   }
   NF("No help on that subject I'm afraid.\n");
   return 0;
}

/* Added by Morrigan Nov 96
* This command allows the Knight to set his preferred weapon and primary
* hand by typing <primary left/right>. The Knight will then swing with 
* the preferred weapon a percentage of the time which is defined in the
* /d/Krynn/solamn/guild/obj/lib/kattack.h file.
*/

int
primary(string which)
{
   object medal = P("pal_med", TP);
   int pr;
   string prs;
   
   NF("You don't have a medal, you should seek guidance.\n");
   if (!medal)
      return 0;
   
   if (!which)
      {
      pr = medal->query_primary();
      if (pr == 1)
         prs = "left";
      else
         prs = "right";
      write("-= Primary hand: "+prs+" =-\n");
      return 1;
   }
   
   NF("Set your primary hand as `right' or `left'?\n");
   if (which == "left")
      {
      medal->set_primary(1);
      write("-= Primary hand: left =-\n");
      return 1;
   }
   else if (which == "right")
      {
      medal->set_primary(0);
      write("-= Primary hand: right =-\n");
      return 1;
   }
   
   return 0;
   
}


/********************* mercy ************************************************/
int
mercy(string str)
{
   string          what;
   object          medal = P("pal_med", TP);
   
   NF("You don't have a medal, you should seek guidance.\n");
   if (!medal)
      return 0;
   if (!str)
      {
      what = (medal->query_generous() ? "ful" : "less");
      write("You are currently a merci" + what + " fighter!\n");
      return 1;
   }
   NF("Mercy on or off?\n");
   if (str == "yes" || str == "on")
      medal->set_generous(1);
   else if (str == "no" || str == "off")
      medal->set_generous(0);
   else
      return 0;
   
   what = (medal->query_generous() ? "ful" : "less");
   write("You are now a merci" + what + " fighter!\n");
   allbb(" gets a merci" + what + (medal->query_generous() ? " smile" :
         " expression") + " on " + POSSESSIVE(TP) +
      " face.");
   return 1;
}

int
merciful()
   {
   return mercy("yes");
}

int
merciless()
{
   return mercy("no");
}


/****************************************************************************
*  wimpy/whimpy, Knights may only set a rather low wimpy.
* NOTE: SHOULD THE ORIGINAL WIMPY CODE EVER BE CHANGED, BE SURE TO ADJUST
*       THIS CODE, TOO!!!!!!!!!
***************************************************************************/
int
whimpy(string str)
{
   string          how, *health = SD_HEALTH;
   int             wi, lim;
   
   if (!str)
      {
      wi = this_player()->query_whimpy();
      if (wi == 0)
         {
         write("You are not wimpy at all.\n");
         return 1;
       }
      if (wi > 99)
         wi = 99;
      wi = wi * sizeof(health) / 100;
      write("You are wimpy at: '" + health[wi] + "'.\n");
      return 1;
   }
   if (str == "brave")
      {
      this_player()->set_whimpy(0);
      write("Brave mode.\n");
      return 1;
   }
   wi = member_array(str, health);
   
   if (wi < 0)
      {
      notify_fail("No such health descriptions (" + str + ") Available:\n" +
            break_string(COMPOSITE_WORDS(health) + ".", 70, 3) + "\n");
      return 0;
   }
   wi = (100 * (wi + 1)) / sizeof(health);
   if (wi > 99)
      wi = 99;
   how = health[sizeof(health) * wi / 100];
   lim = WIMPY_LIMIT[TP->query_knight_level()] +
   WIMPY_LIMIT2[TP->query_knight_sublevel()];
   if (lim > 99)
      lim = 99;
   if (wi > lim)
      {
      wi = lim;
      if (health[sizeof(health) * wi / 100] != how)
         write("This wimpy level is not allowed for a Knight of " +
         "Solamnia!\n");
   }
   how = health[sizeof(health) * wi / 100];
   write("You are now wimpy at: '" + how + "'.\n");
   TP->set_whimpy(wi);
   return 1;
}
