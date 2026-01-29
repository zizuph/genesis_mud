/*
 * thief_soul.c
 *
 * This soul holds the general commands and feelings of the Cabal of Hiddukel
 *
 */

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <composite.h>
#include <formulas.h>
#include <std.h>

/*****************************************************************************
 * Soul identifying and autoloading
 *****************************************************************************/

string get_soul_id() { return "Cabal of Hiddukel"; }

int query_cmd_soul() { return 1; }

/*****************************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 *****************************************************************************/

public mapping
query_ability_map()
{
    return ([
        "cheapshot"     : (SPECIALS + "cheapshot"),
    ]);
}

mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
            /* Guild specials */
            "cheapshot"     :   "do_ability",
            /* Autosneak */
            "autosneak":"autosneak",
            /*"guilds":"guildlist",*/
            "help":"help",
            "showtitle":"show_title",
            /*"sign":"sign",*/
            "watch":"watch",
	     ]);
}

/*****************************************************************************
 * Here follows the functions. New functions should be added in alphabetic
 * order.
 ****************************************************************************/

/*
 * Global variables
 */


/******************************** stealth **********************************/
/* turn auto-sneaking on or off
*/
int
autosneak(string str)
{
    int old_as = TP->query_autosneak();
    int new_as;

    NF("Autosneak how?\n");
    if (!str)
      TP->set_autosneak(!old_as);
    else if (str == "on" || str == "yes")
      TP->set_autosneak(1);
    else if (str == "off" || str == "no")
      TP->set_autosneak(0);
    else
      return 0;

    new_as = TP->query_autosneak();

    if (new_as)
      write("You get ready to sneak about automatically.\n");
    else
      write("You stop sneaking about automatically.\n");
    
    return 1;
}


/********************* guildlist ********************************************/
/*
int
guildlist(string str)
{
    string name;
    object ob, paralyze;
    
    if (str)
      {
	  if (TP->query_wiz_level())
	    {
		name = C(str) + " is ";
		NF("No such player found.\n")
		  if (!(ob = find_player(str)))
		    return 0;
	    }
	  else 
	    {
		write("Curious aren't we?\n");
		return 1;
	    }
      }
    else
      {
	  ob = TP;
	  name = "You are ";
      }
    
    str = ob->list_major_guilds();
    if (str)
      write(name + "member of the following guilds:\n" + str);
    else
      write(name + "not member of any guilds.\n");
    
    return 1;
}
*/
/********************* help *************************************************/
int
help(string str)
{
    string subject, filename;

    if (!str)
      return 0;
    
    if (sscanf(str, "cabal %s", subject) != 1)
      if (sscanf(str, "thief %s", subject) != 1)
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


/************************* show_title ***********************************/
int
show_title(string str)
{
    int show = P(THIEF_OBJ_ID, TP)->query_show_title_on_intro();
    if (!str)
      {
	  write("Show thief title on introductions: "+ (!show ? "NO" : "YES")
		+ ".\nYour title is currently:\n " + TP->query_thief_title() +
		".\n");
	  return 1;
      }
    show = !(str != "on" && str != "yes");
    P(THIEF_OBJ_ID, TP)->set_show_title_on_intro(show);
    write("Show thief title on introductions: "+ (!show ? "NO" : "YES") +
	  ".\n");
    return 1;
}


/******************************** watch ************************************/
/* watch an opponent to judge his awareness
 */
int
watch(string pers)
{
    int value, i;
    string str;
    object who, *dummy;
    NF("Watch who?\n");
    if (!pers)
      return 0;
      dummy = FIND_STR_IN_ARR(pers,FILTER_OTHER_LIVE(all_inventory(E(TP))));
    if (sizeof(dummy))
      who = dummy[0];
    if (who == TP)
      return 0;
    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, who))
      return 0;
    value = (10 * who->query_skill(SS_AWARENESS));
    if (!value)
      value = 10 * (who->query_stat(SS_INT) +
		    who->query_stat(SS_WIS)) / 3;

    value -= (who->query_attack() ? 500 : 0);
    i =  (200 * who->query_intoxicated() / who->intoxicated_max());
    value -= (i > 0 ? i : -i);
    i = (100 * who->query_fatigue() / who->query_max_fatigue());
    value -= (100 - i);
    value /= 10;
    value += (10 - random(20) - TP->query_skill(SS_AWARENESS));

    if (value < -50)
      str = "careless";
    else if (value < -10)
      str = "not alert";
    else if (value < 10)
      str = "a little alert";
    else if (value < 30)
      str = "alert";
    else if (value < 60)
      str = "very alert";
    else
      str = "extremely alert";
    write("You watch " + who->query_the_name(TP) + " from the corner of " +
	  "your eyes, appraising " + who->query_objective() + 
	  " carefully. You think " + who->query_pronoun() + " is " + str);
    if (value > 0 && random(100) < value)
      {
	  write(", but you also feel that " + who->query_pronoun() + 
		" noticed you studying " + who->query_objective() + ".\n");
	  tell_object(who,"You notice " + TP->query_the_name(who) +
			 " appraising you from the corner of " +
			 TP->query_possessive() + " eyes.\n");
      }
    else
      write(".\n");
    return 1;
}
