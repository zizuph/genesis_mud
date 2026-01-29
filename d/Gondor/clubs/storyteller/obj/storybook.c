/*
 * /d/Gondor/clubs/storyteller/obj/storybook.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * TBD:
 *	personalize appearance: perhaps apparent age of
 *		book reflects owner's tenure in club?
 *	make autoloading
 *
 * Modification Log:
 *  27 May 2002, Alto. Change "tell" to spin.
 *
 * 2021-02-14 - Cotillion
 * - Fixed performance issue in query_auto_load
 */

#pragma strict_types

inherit "/std/object";

#include <filter_funs.h>	/* for FILTER*	 		*/
#include <macros.h>		/* for QTNAME*	 		*/
#include <stdproperties.h>	/* for OBJ_I_*	 		*/
#include "/d/Gondor/defs.h"	/* always ...	 		*/
#include "storybook.h"		/* shared with archive room	*/
#include "/d/Gondor/clubs/storyteller/defs.h"

/* prototypes */
public void	create_object();
public void 	add_soul();
public void	set_owner(mixed owner);
public string	query_owner();
public void	enter_env(object dest, object from);
public int	leave_env(object from, object dest);
public void	init();
public int	read_book(string arg);
public int	add_story(string title, string info, string *text);
public int	erase_story(string title);
public int      measure_story(string title);
public int	find_story(string title);
public int	tell_story(string title);
public void	tell_story_alarm(int index, int count, int nsections);
public string	process_name_known(string line, object teller);
public string	process_name_unknown(string line, object teller);
public int	stop_story(string arg);
public void     give_the_end_message(object teller);
public string	book_long();
public string	book_short();

static int	Story_alarm;	/* so don't start two stories at once	*/
int		 Nstories;	/* # of stories in book			*/
string		*Story_titles;	/* lowercase titles of the stories	*/
string		*Story_info;	/* title/author/date for stories	*/
mixed		*Story_text;	/* contents of the stories		*/
				/*   (array of arrays of strings)	*/
static string	Owner;		/* capitalized name of owner		*/

/* 
 * Function name:	create_object
 * Description	:	set up the storybook
 */
public void
create_object()
{
    FIX_EUID;
    set_name("storybook");
    add_name( ({ "story book", "book", STORYBOOK_NAME, "Storyteller_Book" }) );
    set_adj( ({ "slim", "leatherbound" }) );
    set_short("storybook");
    set_long("The slim, leatherbound storybook looks fairly new.");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, "The storybook cannot be dropped!\n");
    Story_titles = ({ });
    Story_info = ({ });
    Story_text = ({ });
    Owner = "";
} /* create_object */

/*
 * Function name:	book_long
 * Description	:	sets the long description of the book
 */
string
book_long()
{
    string text = "The slim, leatherbound storybook looks fairly new.";
    int join_age = TELLERS->query_join_age(Owner);
    int current_age = find_living(lower_case(Owner))->query_age() * 2 / 86400;
    int st_age = current_age - join_age;

    if (st_age >= 100)
        text = "The storybook which you have had for as long as you can "+
		"remember now looks ancient and worn from its many years "+
		"of use. The leather is cracked and worn, and the pages "+
		"are as pliable as cloth.";
    else if (st_age >= 75)
	text = "The storybook which you have had for so long now is "+
		"weathered and worn from use. The leather is worn and "+
		"slightly cracked and the pages are no longer crisp.";
    else if (st_age >= 50)
	text = "The storybook which you have carried for a long time is "+
		"really showing its age now, with the leather becoming "+
		"more worn and the pages less crisp.";
    else if (st_age >= 25)
	text = "The storybook which you have carried for a while is just "+
		"beginning to show its age. You notice the leather starting "+
		"to wear on the binding, and the pages are not quite as "+
		"crisp as they once were.";
    else if (st_age >= 10)
	text = "The storybook looks used, the binding is now creased from "+
		"use and several pages have wrinkles in them.";
    else if (st_age >= 5)
	text = "The storybook looks pretty new, the binding is still in "+
		"good shape and the pages are crisp.";
    else if (st_age >= 2)
	text = "The storybook looks almost brand new, the binding is in "+
		"perfect shape and the pages are crisp.";
    else
	text = "The storybook is brand new.";


    if (strlen(query_owner()))
        text += " The name '"+query_owner()+"' has been embossed on the "+
	    "cover.";

    return text + " This was given to you when you became a Storyteller. "+
	"For a list of Storyteller commands, type 'help teller'.\n";
}

/*
 * Function name:	book_short
 * Description	:	sets the short description of the book
 */
string
book_short()
{
    string text = "storybook";
    int join_age = TELLERS->query_join_age(Owner);
    int current_age = find_living(lower_case(Owner))->query_age() * 2 / 86400;
    int st_age = current_age - join_age;

    if (st_age >= 100)
        text = "ancient storybook";
    else if (st_age >= 75)
	text = "weathered storybook";
    else if (st_age >= 50)
	text = "aged storybook";
    else if (st_age >= 25)
	text = "old storybook";
    else if (st_age >= 10)
	text = "used storybook";
    else if (st_age >= 5)
	text = "storybook";
    else if (st_age >= 2)
	text = "new storybook";
    else
	text = "brand new storybook";

    return text;
}

/*
 * Function name:	set_owner
 * Description	:	set who owns us, update description
 * Arguments	:	mixed owner -- either the owner's name (string)
 *				or the owner (object)
 */
public void
set_owner(mixed owner)
{
    if (objectp(owner))
    {
	Owner = owner->query_name();
    }
    else if (stringp(owner) &&
	     strlen(owner))
    {
	Owner = CAP(owner);
    }
} /* set_owner */

public string	query_owner()	{ return Owner; }

string
query_auto_load()
{
    return MASTER_OB(this_object()) + (strlen(Owner) ? (":" + Owner) : ":");
}

void
init_arg(string str)
{
    if (str && str != 0)
    {
        Owner = str;
        FIX_EUID
        restore_object(TELLERS_DIR + Owner);
    }

}

public void
add_soul()
{
    object  pl;

    FIX_EUID

    pl = ENV(TO);
    if (!interactive(pl))
        remove_object();

    set_short(book_short());
    set_long(book_long());

    pl->add_cmdsoul(TELLER_SOUL);
    pl->update_hooks();
}

/*
 * Function name:	enter_env
 * Description	:	after parent, be sure our env is a member
 * Arguments	:	object dest -- destination
 *			object from -- where we came from
 */
public void
enter_env(object dest, object from)
{
    string	tmpstr;

    ::enter_env(dest, from);

    if (!objectp(from) && interactive(dest))
    {
        // The book was just cloned in so we assume this is
        // it's owner.
        if (!strlen(Owner))
        {
            set_owner(dest);
            restore_object(TELLERS_DIR + Owner);
        }
    }

    if (dest->query_wiz_level() || IS_STORYTELLER(dest))
        return;
    else
        set_alarm(1.0, 0.0, &remove_object());
} /* enter_env */


/*
 * Function name:	leave_env
 * Description	:	mask parent to remove any story-telling alarms
 * Arguments	:	object from -- where we're leaving
 *			object dest -- where we're going
 */
public int
leave_env(object from, object dest)
{
    if (Story_alarm)
    {
	remove_alarm(Story_alarm);
	Story_alarm = 0;
    }
    ::leave_env(from, dest);
} /* leave_env */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    ::init();

    if (!IS_STORYTELLER(environment(this_object())))
    {
        remove_object();
        return;
    }

    add_action(read_book,	"read");
    add_action(tell_story,	"spin");
    add_action(stop_story,	"stop");
    add_action(erase_story,	"erase");
    add_action(measure_story,   "measure");

    set_alarm(0.1, 0.0, add_soul);
} /* init */


/*
 * Function name:	read_book
 * Description	:	read the storybook
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * N.B. For reading, we just call the archive, which already
 *	implements this.
 */
public int
read_book(string title)
{
    object	ob;
    int		i, size, length;
    string      tmpstr;
    string 	*text;

    if (!strlen(title))
    {
	notify_fail("Read what?\n", 0);
	return 0;
    }

    FIX_EUID;

    if (sscanf(title, "'%s'", tmpstr))
    {
	title = tmpstr;
    }

    if (title == "book" || title == "storybook" || title == "story book")
    {
	if (!Nstories)
	{
	    write("The storybook is empty.\n");
	}
	else
	{
	    write("The storybook holds the following stories:\n");
            for (i = 0, size = sizeof(Story_titles); i < size; i++)
                write(sprintf("   %-15s - %-50s", Story_titles[i],
			Story_info[i]) + "\n");
	}
	return 1;
    }

    i = member_array(title, Story_titles);

    if (i < 0)
    {
	NF0("Sorry, cannot find story with title '"+title+"'\n");
    }

    /* Use this to have the archive deliver the text 
    text = read_file(STORIES_DIR + ARCHIVES->get_story_filename(title)); 

    if (!strlen(tmpstr)
    {
        write("Flipping through your book, you can no longer find this "+
	    "story, it must have been lost somehow.\n");
	return 1;
    }*/


    /* Use this to have the book deliver the text */
    if (!sizeof(text = Story_text[i]))
    {
        write("Flipping through your book, you can no longer find this "+
	    "story, it must have been lost somehow.\n");
	return 1;
    }

    /* Use this if Archives are delivering text
    length = sizeof(explode(tmpstr, "\n")); */

    length = sizeof(text);
    tmpstr = implode(text, "\n");

    if ((length * 2) <= MAX_NO_MREAD)
    {
        write("You begin reading "+title+" from your "+short()+".\n");
	write(tmpstr + "\n");
    }
    else
    {
        write("You begin reading "+title+" from your "+short()+".\n");
	TP->more(tmpstr + "\n", 0);
    }

    return 1;

} /* read_book */


/*
 * Function name:	add_story
 * Description	:	add a story to the book
 * Arguments	:	string title -- the title
 *			string info -- title/author/date info
 *			string *text -- the contents
 * Returns	:	1 if successfully added,
 *			-1 if a story with this title already is in book,
 *			0 for any other error.
 */
public int
add_story(string title, string info, string *text)
{
    int		i;

    if (!strlen(title) ||
        !strlen(info) ||
        !sizeof(text))
    {
	return 0;
    }
    if ((i = member_array(title, Story_titles)) >= 0)
    {
	return -1;
    }
    Story_titles += ({ title });
    Story_info += ({ info });
    Story_text += ({ text });
    ++Nstories;

    save_object(TELLERS_DIR + Owner);

    return 1;
} /* add_story */


/*
 * Function name:	erase_story
 * Description	:	erase a story from the book
 * Arguments	:	string title -- the title of the story to nuke
 * Returns	:	1 on success, 0 on failure
 */
public int
erase_story(string title)
{
    int		i, j;
    string	tmpstr;

    if (!strlen(title))
    {
	NF0("Erase what?\n");
    }
    if (sscanf(title, "'%s'", tmpstr))
    {
	title = tmpstr;
    }

//    tmpstr = LOW(title);

    if ((i = member_array(title, Story_titles)) < 0)
    {
	NF0("There is no story named '"+title+"' to erase.\n");
    }

    /* it would be shorter to do: a -= ({ a[i] }) for each of
     * the titles, info and text arrays. however, i think that
     * might be pretty expensive to do for the text array,
     * since it would have to compare every line of every story
     * until it found the one that matched. since we already know
     * the index, that seems wasteful.
     */
    if (i == 0)
    {
	Story_titles = Story_titles[1..];
	Story_info = Story_info[1..];
	Story_text = Story_text[1..];
    }
    else if (i == sizeof(Story_titles))
    {
	--i;
	Story_titles = Story_titles[..i];
	Story_info = Story_info[..i];
	Story_text = Story_text[..i];
    }
    else
    {
	j = i + 1;
	--i;
	Story_titles = Story_titles[0..i] + Story_titles[j..];
	Story_info = Story_info[0..i] + Story_info[j..];
	Story_text = Story_text[0..i] + Story_text[j..];
    }
    --Nstories;
    write("You erase the story '"+title+"' from your book.\n");

    save_object(TELLERS_DIR + Owner);

    return 1;
} /* erase_story */

/*
 * Function name: measure_story
 * Description  : Measures the time the story will take to tell
 * Arguments    : string title - the story to measure
 * Returns      : int 1/0 successful/not
 */
public int
measure_story(string title)
{
    int	i, j, tmpint;
    float t = 0.0, tmpfloat;
    string final, tmpstr;

    if (!strlen(title))
    {
	NF0("Measure which story?\n");
    }

    if (sscanf(title, "'%s'", tmpstr))
    {
	title = tmpstr;
    }

    if ((i = member_array(title, Story_titles)) < 0)
    {
	NF0("There is no story named '"+title+"' to measure.\n");
    }

    for (j = sizeof(Story_text[i]) - 1; j >= 0; j--)
    {
        if (sscanf(Story_text[i][j], "=%f", tmpfloat))
            t += tmpfloat;
        else if (sscanf(Story_text[i][j], "=%d", tmpint))
            t += itof(tmpint);
        else if (Story_text[i][j] == "=")
            t += 3.0;
    }

    if (t < 1.0)
        final = "barely any time at all";
    else
        final = ("/lib/time"->convtime(ftoi(t)));

    write(title + " will take " + final + " to tell.\n");
    return 1;
}

/*
 * Function name:	find_story
 * Description	:	find story in book
 * Arguments	:	string title -- title we're looking for
 * Returns	:	int -- index of story. -1 if not found.
 */
public int
find_story(string title)
{
    if (strlen(title))
    {
	return member_array(LOW(title), Story_titles);
    }
    return -1;
} /* find_story */


/*
 * Function name:	tell_story
 * Description	:	tell a story
 * Arguments	:	string arg -- presumably the story name
 * Returns	:	1 if we know the story, 0 if not
 */
public int
tell_story(string title)
{
    int		i,
		n;
    string	tmpstr;

    if (!strlen(title))
    {
	NF0("Tell what?\n");
    }

    if (Story_alarm)
    {
	NF0("You are already telling a story.\n");
    }

    if (sscanf(title, "'%s'", tmpstr))
    {
	title = tmpstr;
    }

    if ((i = member_array(title, Story_titles)) < 0)
    {
	NF0("The storybook does not contain the story '"+title+"'\n");
    }

    if (!(n = sizeof(Story_text[i])))
    {
	NF0("Unfortunately, the story '"+title+"' seems to have been "+
	    "expunged.\n");
    }

    write("You begin spinning the tale of '"+title+"'. (You will see what "+
	"the audience sees)\n");
    say(QCTNAME(TP)+" begins spinning the tale of '"+title+"'.\n");

    Story_alarm = set_alarm(2.0, 0.0, &tell_story_alarm(i, 0, n));
    return 1;
} /* tell_story */


/*
 * Function name:	tell_story_alarm
 * Description	:	do the actual storytelling
 * Arguments	:	int index -- index of this story
 *			int count -- where we are in the story's text
 *			int nsections -- size of the story's text
 */
public void
tell_story_alarm(int index, int count, int nsections)
{
    float	delay;
    int		finished;
    string	line,
		lineknown,
		lineunknown,
		met,
		nonmet;
    object	save_tp,
		teller = ENV(),
		room = ENV(teller),
		*players;

    Story_alarm = 0;
    if (nsections <= 0 ||
	count >= nsections)
    {
	return;
    }

    /* called from alarm -- need to set this_player() to the
     * storyteller so that write/say works.
     */
    save_tp = this_player();
    set_this_player(teller);

    players = FILTER_PLAYERS(all_inventory(ENV(teller)));
    met = teller->query_name();
    nonmet = "The "+teller->query_nonmet_name();

    while (!finished &&
	   count < nsections)
    {
	/* we have to do some tricky stuff to get met and nonmet
	 * embedded names to come out right ... there may be a
	 * better way to do this.
	 */
	line = Story_text[index][count];
	switch (line[0..0])
	{
	case EMOTE_PROC:
	    line = line[1..];
	    lineknown = met+process_name_known(line, teller)+"\n";
	    lineunknown = nonmet+process_name_unknown(line, teller)+"\n";
	    players->catch_msg(({lineknown, lineunknown, ""}), teller);
	    break;
	case EMOTE:
	    tell_room(room, QCTNAME(teller)+line[1..]+"\n");
	    break;
        case NEWLINE:
            tell_room("\n");
            break;

/* Remove the ability to use atmospheric messages
	case ATMOS_PROC:
	    line = line[1..];
	    lineknown = process_name_known(line, teller)+"\n";
	    lineunknown = process_name_unknown(line, teller)+"\n";
	    players->catch_msg(({lineknown, lineunknown, ""}), teller);
	    break;
	case ATMOS:
	    tell_room(room, line[1..] + "\n");
	    break; */

	case ALARM:
	    if (!sscanf(line, ALARM+"%f", delay))
	    {
		delay = DEFAULT_ALARM;
	    }
	    finished = 1;
	    break;
	}
	++count;
    }

    if (count < nsections)
    {
	Story_alarm = set_alarm(delay, 0.0,
	    &tell_story_alarm(index, count, nsections));
    }
    else
    {
        Story_alarm = set_alarm(2.0, 0.0, &give_the_end_message(teller));
    }

    set_this_player(save_tp);
} /* tell_story_alarm */


public void
give_the_end_message(object teller)
{
    tell_room(ENV(teller), QCTNAME(teller)+" concludes "+POSSESSIVE(teller)+
	" story.\n", teller);
    teller->catch_tell("You finish telling your story.\n");
    remove_alarm(Story_alarm);
    Story_alarm = 0;
}

/*
 * Function name:	process_name_known
 * Description	:	replace STR_NAME with teller's name
 * Arguments	:	string line -- the line of text to process
 * Returns	:	string -- the line with all name codes
 *			processed.
 */
public string
process_name_known(string line, object teller)
{
    string	*data,
		replace;
    int		i, n;

    n = sizeof(data = explode(line, STR_NAME));
    if (n > 1)
    {
	line = implode(data, teller->query_name());
    }
    return CAP(line);
} /* process_name_known */


/*
 * Function name:	process_name_unknown
 * Description	:	replace STR_NAME with teller's nonmet name
 * Arguments	:	string line -- the line of text to process
 * Returns	:	string -- the line with all name codes
 *			processed.
 */
public string
process_name_unknown(string line, object teller)
{
    string	*data,
		replace;
    int		i, n;

    n = sizeof(data = explode(line, STR_NAME));
    if (n > 1)
    {
	line = implode(data, "the "+teller->query_nonmet_name());
    }
    return CAP(line);
} /* process_name_unknown */


/*
 * Function name:	stop_story
 * Description	:	stop telling a story
 * Arguments	:	string arg  -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
stop_story(string arg)
{
    string	*stop_what = ({ "spinning", "telling", "story" });

    /* stop telling [the] [story]
     * stop [the] story
     */
    if (!arg ||
	!parse_command(LOW(arg), ({}), "[the] %p [the] [story]", stop_what))
    {
	return 0;
    }
    if (!Story_alarm)
    {
	write("You are not telling a story just now.\n");
    }
    else
    {
	remove_alarm(Story_alarm);
	Story_alarm = 0;
	write("You stop telling the story.\n");
	SAY(" suddenly falls silent.");
    }
    return 1;
} /* stop_story */
