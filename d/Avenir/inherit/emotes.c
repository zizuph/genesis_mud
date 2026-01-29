#pragma strict_types

#include <time.h>
#include <macros.h>
#include <cmdparse.h>

/*  Variables.     */
private static string emote_log;
private static mapping m_emotes = ([]);

/*  Declarations.  */
public nomask string emote_help(int brief);
public nomask string dump_emotes(void);
public nomask void prune_emotes(void);


/*  Prune emotes older than this (in seconds).  */
#define PRUNE  (3600)


/****************************************************************************
 * emote, : - emote something
 */

/*
 * Function name: cat_string
 * Description	: Concatenates an in-process emote string for observers.
 * Arguments	: mixed *org  - ({ object player, string to-concatenate })
 * 		  string what - optional string to concatenate.
 * 		  object *pls - living(s) to concatenate in string form.
 * 		  int poss    - whether to handle possessiveness.
 * Returns	: mixed * - the concatenated and modifed *org variable.
 *
 * Notes        : Capitalization rules have been removed as they would
 *                require a great deal more logic with other changes as
 *                well as no forseeably legit reason for its usage is
 *                forthcoming which adheres to the emote policies.
 */
private nomask mixed *
cat_string(mixed *org, string what, object *pls, int poss)
{
    int size = sizeof(pls);

    if (size == 1)
    {
    	if (pls[0] == org[0])
    	{
	       switch(poss)
	        {
	        case 3: case 1:
		    what = "your";
		    break;
	        default:
		    what = "you";
		    break;
	        }
	    }
	    else 
        {
            if (sizeof(org[1][1]) == 1)
            {
                if (org[1][1][0] == pls[0])
                {
                    poss += 2;
                }    
                switch (poss)
                {
                    case 1:
                        if (org[1][1][0]->query_possessive() != 
                            pls[0]->query_possessive())
                        {
                            poss += 2;
                        }    
                    break;
                    default:
                        if (org[1][1][0]->query_objective() != 
                            pls[0]->query_objective())
                        {
                            poss += 2;
                        }    
                    break;
                }    
            }
            switch(poss)
	        {
	        case 3:
        	    what = pls[0]->query_possessive();
	            break;
	        case 2:
        	    what = pls[0]->query_objective();
	            break;
	        case 1:
        	    what = pls[0]->query_the_possessive_name(org[0]);
                org[1][1] = pls;
	            break;
	        default:
        	    what = pls[0]->query_the_name(org[0]);
                org[1][1] = pls;
	            break;
            }
    	}
    }
    else if ((size > 1 ) && IN_ARRAY(org[0], pls))
    {
        if (size > 2)
	        what = "all of "+ (poss ? "your" : "you");
        else
            what = (poss ? "both your" : "both of you");
        org[1][1] = pls;
    }

    org[1][0] += what;
    return org;
}

/*
 * Function name: mk_item
 * Description	: Formulates the base values for the emote() emap mapping.
 * Arguments	: object ob - The observing player to create an entry for.
 * Returns	: mixed * - ({ object ob, string "" })
 */
private nomask mixed *
mk_item(object ob)
{
    return ({ ob, ({ "", ({}) }) });
}

/*
 * Function name: tell_them
 * Description	: Prints an emote to observers. Called by emote().
 * Arguments	: mixed *arg - array container player and string to print.
 * Returns	: void.
 */
private nomask void
tell_them(mixed *arg)
{
    arg[0]->catch_tell(
	this_player()->query_The_name(arg[0]) + arg[1][0] + "\n");
}

/*
 * Function name: emote
 * Description	: A command for flexible player emotions.
 * Arguments	: string arg - The syntax string for an emote.
 * Returns	: int 0/1 - failure/success.
 */
public nomask int
emote(string arg)
{
    object *pls;
    string *args;
    mapping emap;

    if (!strlen(arg))
	return notify_fail(emote_help(1));

    if (arg == "help")
    {
	write(emote_help(0));
	return 1;
    }

    if (arg == "report")
    {
	write(dump_emotes());
	return 1;
    }

    pls = all_inventory(environment(this_player()));
    pls = filter(pls, query_interactive);

    if (arg[0] != '\'')
        arg = " " + arg;

    args = explode(arg, "|");
    emap = mkmapping(pls, map(pls, mk_item));
    emap = map(emap, &cat_string(, args[0], 0, 0));

    if (sizeof(args) > 1)
    {
	int match, poss;

	pls = ({});

	foreach(string str : args[1..])
        {
	    object *arr;
	    string name = lower_case(str);

	    match++;

	    if (name[-2..] == "'s")
	    {
		poss = 1;
		name = name[..-3];
	    }
        else
        {
            poss = 0;
        }

	    if (sizeof(arr = filter(PARSE_THIS(name, "%o"), living)))
	    {
		if (IN_ARRAY(arr[0], pls))
		{
		    //poss += 2;
		    emap = map(emap, &cat_string(, "", arr, poss));
		}
		else
		{
		    pls += arr;
		    emap = map(emap, &cat_string(, "", arr, poss));
		}
	    }
	    else if (name == "them")
	    {
		emap = map(emap, &cat_string(, name, pls, 0));
	    }
	    else if (name == "their")
	    {
		emap = map(emap, &cat_string(, name, pls, 1));
	    }
	    else if (match % 2)
	    {
		notify_fail("You cannot see \""+ str +"\" here.\n");
		return 0;
	    }
            else
	    {
                emap = map(emap, &cat_string(, str, 0, 0));
	    }
        }
    }

    map(emap, tell_them);
    m_delkey(emap, this_player());

    m_emotes[time()] = ({ arg, this_player()->query_cap_name(),
	map(m_indexes(emap), &->query_cap_name()) });

    if (!random(5))
	prune_emotes();

    return 1;
}

public void notify_emote_room(object player)
{
    player->catch_msg("You have entered a free emote room.  <emote help> " +
      "for help on how to use it.\n");
}


/****************************************************************************
 * echo - echo something in a room
 *
public nomask int
echo(string str)
{
    if (!stringp(str))
    {
        notify_fail("Echo what?\n");
        return 0;
    }

    say(str + "\n");
    write("You echo: " + str + "\n");

    return 1;
}
 */

/*
 * Function name: init_emotes
 * Description	: Adds the emote command actions to players.
 */
public nomask void
init_emotes(void)
{
    add_action( emote, "emote" );
    add_action( emote, ":", 2  );
    add_action( emote, ";", 2  );
    set_alarm(0.1, 0.0, &notify_emote_room(this_player()));
//    add_action(  echo, "echo"  );
}

/*
 * Function name: emote_help
 * Description	: Provide usage help on the "emote" command.
 * Arguments	: int brief - Toggle between brief blurb or in-depth help.
 * Returns	: string - The help text.
 */
public string
emote_help(int brief)
{
//    if (brief)
    {
	return "Usage: : <emote string>, emote string can contain " +
	    "names of present people enclosed in '|' characters, which " +
	    "then will be identified by their met/nonmet names to "+
	    " observers. e.g. ': smile fondly at |zielia|'\n"+
        "emote report: Log the prior emotes so that they may "+
        "be reviewed by the AOP team for issues of harassment.\n";
    }
}

/*
 * Function name: set_emote_log
 * Description	: Set a file to log emotes to from dump_emotes.
 * Arguments	: string file - filepath to logfile.
 * Returns	: int 0/1 - failure/success.
 */
public nomask int
set_emote_log(string file)
{
    string str;

    if (!strlen(file))
	return 0;

    setuid();
    seteuid(getuid());

    str = ctime(time()) +": set_emote_log() called.\n";

    if (!write_file(file, str))
    {
	throw("set_emote_log() called with invalid path.\n");
	return 0;
    }

    emote_log = file;
    return 1;
}

/*
 * Function name: prune_emotes
 * Description	: Prunes emotes older than a certain time.
 */
public nomask void
prune_emotes(void)
{
    int *arr;
    int tval = (time() - PRUNE);

    arr = m_indexes(m_emotes);
    arr = filter(arr, &operator(<)(, tval));

    foreach(int key : arr)
	m_delkey(m_emotes, key);
}

/*
 * Function name: dump_emotes
 * Description	: Dumps emotes into a logfile and return a message.
 * Arguments	: None.
 * Returns	: string - A message saying what to do.
 */
public nomask string
dump_emotes(void)
{
    int *keys;
    string str;

    prune_emotes();

    str = ctime(time()) + ": dump_emotes() called by "+
	this_player()->query_cap_name() +"!\n"+
	"  From    == " + file_name(this_object()) + "\n";

    keys = sort_array(m_indexes(m_emotes));

    foreach(int key : keys)
    {
	mixed *vals = m_emotes[key];

	str += ctime(key) +": Emoter == "+ vals[1] +"\n";
	str += "  Emote   == "+ vals[0] +"\n";
	str += "  Present == "+ implode(vals[2], ", ") + "\n";
    }

    if (strlen(emote_log))
    {
	write_file(emote_log, str);
    }
    else
    {
	setuid();
	seteuid(getuid());

	log_file("emote_log", str, -1);
    }

    return "The emotes for the past "+ CONVTIME(PRUNE) +" have "+
	"been saved to a logfile to support your report. Be sure "+
	"to mail aop and the domain wizards for further followup.\n";
}
