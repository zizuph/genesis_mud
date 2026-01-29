/* A list of the Minotaur emotes 
 *
 */

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <options.h>
#include <cmdparse.h>
#include "guild.h"



/*
 * Function name: emote_cmdlist
 * Description:   Get the emotes available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
emote_cmdlist()
{
    return ([
      /* Command name : Function name */
      "mbellow"    : "minbellow",
      "mclean"     : "minclean",
      "mcurse"     : "mincurse",
      "mgesture"   : "mingesture",
      "midle"      : "minidle",
      "mmight"     : "minmight",
      "moath"      : "minoath",
      "mrecite"    : "minrecite",
      "mscorn"     : "minscorn",
      "mslam"      : "minslam",
      "mstand"     : "minstand",
      "minolist"     : "minolist",
      "help"         : "help",

    ]);
}

int
minbellow(string str)
{
    string *how = parse_adverb_with_space(str, "victoriously", 0);
 
    if(strlen(how[0]))
    {
        NF("Bellow how?\n");
        return 0;
    }
 
    write("You throw your fists into the air and bellow"+how[1]+"!\n");
    all(" throws " +HIS(TP)+ " fists into the air and bellows"+how[1]+"!");
    return 1;
}


int
minclean(string str)
{
    if(strlen(str))
    {
        return 0;
    }
 
    write("You clean the gruesome remains of a foe from your horns.\n");
    allbb(" cleans the gruesome remains of a past foe from " +HIS(TP)+ " horns.");
    return 1;
}


int
mincurse(string str)
{
    object *ob;
 
    if( !strlen(str) )
    {
        write("You bellow a curse to Sargonnas, God of Vengeance and Treachery!\n");
        say(QCTNAME(TP) + " bellows a curse to Sargonnas, God of Vengeance and Treachery!\n");
        return 1;
    }
 
    ob = parse_this(str, "[at] [the] %l");
 
    if( !sizeof(ob) )
    {
        notify_fail("Curse whom?\n");
        return 0;
    }
 
    actor("You bellow a curse at",ob,", wishing upon " +HIM(ob[0])+ " the ire of Sargonnas, " +
       "God of Vengeance and Treachery!");
    target(" bellows a curse at you, wishing the ire of Sargonnas, God of Vengeance and " +
       "Treachery upon your head!", ob);
    all2act(" bellows a curse at",ob,", wishing upon " +HIM(ob[0])+ " the ire of Sargonnas, " +
       "God of Vengeance and Treachery!");
 
    return 1;
 
}

int
mingesture(string str)
{
    object *ob;
 
    if( !strlen(str) )
    {
        write("You gesture around, daring anybody to take on your mighty horns!\n");
        say(QCTNAME(TP) + " gestures around, daring anybody to take on " +HIS(TP)+ 
          " mighty horns!\n");
        return 1;
    }
 
    ob = parse_this(str, "[at] [the] %l");
 
    if( !sizeof(ob) )
    {
        notify_fail("Curse whom?\n");
        return 0;
    }
 
    actor("You gesture to",ob,", daring " +HIM(ob[0])+ " to take on your mighty horns!");
    target(" gestures at you, daring you to take on " +HIS(TP)+ " mighty horns!", ob);
    all2act(" gestures at",ob,", daring " +HIM(ob[0])+ " to take on " +HIS(TP)+
      " mighty horns!");
 
    return 1;
 
}

int
minidle(string str)
{
    if(strlen(str))
    {
        return 0;
    }
 
    write("You idly touch the sharp point of your horns, remembering the last foe they " +
       "ravaged.\n");
    allbb(" idly touches the sharp point on " +HIS(TP)+ " horns, remembering the last foe " +
       "they ravaged.");
    return 1;
}

int
minmight(string str)
{
    if(strlen(str))
    {
        return 0;
    }
 
    write("You make it clear that you have no time for the weak, as only the strong are worthy " +
       "of survival.\n");
    allbb(" makes it clear that " +HE(TP)+ " has no time for the weak, as only the strong are " +
       "worthy of survival.");
    return 1;
}


int
minoath(string str)
{
    if(strlen(str))
    {
        return 0;
    }
 
    write("You make it clear that minotaurs honour their oaths, and do not make them lightly.\n");
    allbb(" makes it clear that minotaurs honour their oaths, and do not make them lightly.");
    return 1;
}

int
minrecite(string str)
{
    if(strlen(str))
    {
        return 0;
    }
 
    write("You solemnly recite the litany of the Bloodsea minotaurs:\n" +
              "    We have been enslaved but have always thrown off our shackles.\n"+
              "    We have been driven back, but always returned to the fray \n" +
              "                      Stronger than before.\n" +
              "        We have risen to new heights when all other races\n " +
              "                     Have fallen into decay.\n" +
              "    We are the future of Krynn, the fated masters of the entire world.\n"+
              "        We are the children of destiny, the Bloodsea minotaurs.\n");
    allbb(" solemnly recites the litany of the Bloodsea minotaurs:\n" +
              "    We have been enslaved but have always thrown off our shackles.\n"+
              "    We have been driven back, but always returned to the fray \n" +
              "                      Stronger than before.\n" +
              "        We have risen to new heights when all other races\n " +
              "                     Have fallen into decay.\n" +
              "    We are the future of Krynn, the fated masters of the entire world.\n"+
              "        We are the children of destiny, the Bloodsea minotaurs.");
    return 1;
}

int
minscorn(string str)
{
    if(!E(TP)->query_ship())
    {
     write("You are not on a ship!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You scorn the crew of the ship as poor navigators in comparison to the " +
    "skilled minotaur seafarers of the Bloodsea.\n");
    allbb(" scorns the crew of this ship as poor navigators in comparison to the " +
    "skilled minotaur seafarers of the Bloodsea.");
    return 1;
}

int
minslam(string str)
{
    if(strlen(str))
    {
        return 0;
    }
 
    write("You slam your fist into your chest, exalting how superior the minotaur race is!\n");
    allbb(" slams " +HIS(TP)+ " fist into " +HIS(TP)+ " chest, exalting how superior the " +
    "minotaur race is!");
    return 1;
}

int
minstand(string str)
{
    if(!E(TP)->query_ship())
    {
     write("You are not on the deck of a ship!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You cross your arms and stand comfortably on the deck of the rolling ship.\n");
    allbb(" crosses " +HIS(TP)+ " arms and stands comfortably on the deck of the rolling " +
    "ship.");
    return 1;
}

int
is_mino(object ob)
{
    return ob->query_guild_member(GUILD_NAME);
}

/* Function name : minolist
 *       Lists the minotaurs presently in the game.
 */


int
minolist(string str)
{
    object *players;
    string txt = "", tmp;
    int i, wwidth = TP->query_option(1);
    int all = 0;

    if(wwidth < 11)
	wwidth = 78;

    if(str && (str == "v" || str == "verbose"))
	all = 1;

    players = filter(users(), "is_mino", this_object());

    write("The following Bloodsea minotaurs are currently logged on:\n");
    for(i = 0; i < sizeof(players); i++)
    {
	if(players[i]->query_invis() == 0)
	{
	    if(all)
		txt += break_string(players[i]->query_name() + " " +
		  players[i]->query_title() + "\n",wwidth-10,5)[5..];
	    else
	    {
		tmp = players[i]->query_guild_title_race();
		if(players[i]->query_wiz_level())
		    tmp = "";
		txt += break_string(players[i]->query_name() + " " +
		  (tmp && stringp(tmp) && strlen(tmp) ? tmp +
		    ", " : "") +
		  (players[i]->query_wiz_level() ? players[i]->query_title() : "the " +
		    players[i]->query_guild_title_lay()) + "\n",
		  wwidth-10,5)[5..];
	    }
	}
    }
    write(txt);
    return 1;
}



int
help(string str)
{
    string subject, filename;

    if(!str)
	return 0;

    if(sscanf(str, "guild %s", subject) != 1)
	if(sscanf(str, "minotaurs %s", subject) != 1)
	    if(sscanf(str, "minotaur %s", subject) != 1)
		return 0;

    filename = HELP_DIR + subject;
    if(file_size(filename) > 0)
    {
	setuid();
	seteuid(getuid());
	cat(filename);
	return 1;
    }

    NF("No help on that subject I'm afraid.\n");
    return 0;
}
