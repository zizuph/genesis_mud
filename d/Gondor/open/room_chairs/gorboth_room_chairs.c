/*
 * /d/Gondor/open/room_chairs/room_chairs.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * This object provides seating (chair, couch, desk, ...) for a room.
 *
 * The ideas and much of the code are based on Mercade's 
 * workroom -- thanks, Mercade!!
 *
 * See /d/Gondor/open/room_chairs/room_chairs.doc for documentation,
 * and /d/Gondor/open/room_chairs/room_chairs_example.c for an example.
 *
 * N.B. I take the easy approach to deciding if the player is seated -- just
 * examine the LIVE_S_SITTING prop.  I believe this is safe, and it's
 * quicker than looking at the occupants of every chair.
 *
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

/* indices for chair data */
#define	I_PATTERN	0
#define	I_CAPACITY	1
#define	I_OCCUPANTS	2
#define	I_PREP		3

static mapping Room_chairs = ([]);
/*
 * the mapping is indexed by the chair name (first arg to add_chair()).
 * each chair in the mapping is an array of:
 *	parse pattern	e.g., "[down] [on] / [in] [the] [comfy] 'chair'"
 *	capacity	1 for a chair, > 1 for couch/bench/...
 *	occupants	array of living objects sitting in this chair
 *	prep		e.g., "at", "on", "in"
 *
 * can customize the "you-sit"/"foo-sits" msgs by masking do_sit_msgs()
 * and "you-stand"/"foo-stands" by masking do_stand_msgs(). 
 */

static int	Did_exit_desc,
                Chair_mentioned, /* is chair mentioned in room desc? */
		No_sitting_in_desc;
static string	Exit_desc;


/* prototypes */
public void		init_room_chairs();
public void		leave_inv_room_chairs(object ob, object dest);
public int		add_chair(string name, string parse_pat,
				  int capacity, string prep, int mentioned);
public int		remove_chair(string name);
public mapping		query_room_chairs();
public string		sitting_on_chair(string name, object for_obj,
					 int namesonly, int definite);
public int		do_sit(string arg);
public int		do_stand(string arg);
public void		stand_up(object tp, string name, int domsg);
public object		*query_occupants(string name);
public string		show_subloc(string subloc, object pl, object for_obj);
public void		do_sit_msgs(object pl, string prep, string name);
public void		do_stand_msgs(object pl, string name);
public int		check_sitting();
public int		no_hide(string arg);
public string		exits_description();
public string		my_exits_description();
public void		set_no_sitting_in_desc(int i);
public int		query_no_sitting_in_desc();



/*
 * Function name:	init_room_chairs
 * Description	:	add player verbs
 */
public void
init_room_chairs()
{
    add_action(do_sit,   "sit");
    add_action(do_stand, "stand");
    add_action(do_stand, "rise");
    add_action(no_hide,  "hide");
    if (this_player()->query_wiz_level())
    {
	add_action(no_hide,  "invis");
    }
} /* init_room_chairs */


/*
 * Function name:	query_room_chairs
 * Description	:	dump the chairs ...
 * Returns	:	mapping -- the chairs info
 */
public mapping
query_room_chairs()
{
    return Room_chairs;
} /* query_room_chairs */


/*
 * Function name:	add_chair
 * Description	:	add a "chair" (couch, desk, ...) to the set of
 *			things-upon-which-one-may-sit
 * Arguments	:	string name --	the name of this chair. must be
 *					unique for this room.
 *			string parse_pat -- a pattern for use with
 *				            parse_command() (e.g., 
 *			     "[down] [on] / [in] [the] [red] [wooden] 'chair'")
 *			int capacity -- how many people can sit here
 *				        default is 1
 *			string prep -- the preposition to use.
 *				       default is "on"
 * Returns	:	1 on success, 0 if bad args
 *
 * N.B. the name will be used in messages, so "comfy blue chair" is
 * better than "chair".
 */
public int
add_chair(string name, string parse_pat, int capacity = 1, string prep = "on", int mentioned = 1)
{
    if (strlen(name) &&
	strlen(parse_pat))
    {
	Room_chairs[name] = ({ parse_pat, capacity, ({}), prep });
        Chair_mentioned = mentioned;
	return 1;
    }
    return 0;
} /* add_chair */


/*
 * Function name:	remove_chair
 * Description	:	remove a chair from the list of things-upon
 *			-which-one-may-sit
 * Arguments	:	string name -- the name of the chair
 * Returns	:	1 on success, 0 if chair not found
 */
public int
remove_chair(string name)
{
    if (strlen(name) &&
	pointerp(Room_chairs[name]))
    {
	m_delete(Room_chairs, name);
	return 1;
    }
    return 0;
} /* remove_chair */



/*
 * Function name:	sitting_on_chair
 * Description	:	describe who's on the chair.
 * Arguments	:	string name -- the chair name
 *			object for_obj -- who's doing the looking
 *			int namesonly -- if true, returns only
 *				the names of occupants, suitably
 *				formatted, + " is" or " are"
 *                      int definite -- if true, we use a
 *                                     definite article when
 *                                     we modify the ledge name
 * Returns	:	string -- the desc of the occupants
 *
 * N.B. if namesonly is false, the returned string will have an ending
 * newline. if namesonly is true, it will not. it follows that if you
 * want to embed info about who's sitting on what in the middle of 
 * other text, you set namesonly to true and append your own location
 * string (e.g., " at the desk.").
 */
public string
sitting_on_chair(string name, object for_obj, int namesonly, int definite = 1)
{
    mixed	*chairptr;
    object	*occupants,
		*others;
    int		i,
		s;
    string	*names,
                 desc,
                 my_art;

    my_art = (definite ? " the " : " a ");

    if (!strlen(name) ||
	!pointerp(chairptr = Room_chairs[name]) ||
        !(s = sizeof(occupants = chairptr[I_OCCUPANTS])))
    {
	return "";
    }

    if (!objectp(for_obj))
    {
	for_obj = this_player();
    }

    if (s == 1)
    {
	if (occupants[0] != for_obj) 
	{
	    desc =  occupants[0]->query_Art_name(for_obj) + " is";
	}
	else
	{
	    desc = "You are";
	}
    }
    else
    {
	if ((i = member_array(for_obj, occupants)) < 0)
	{
	    names = occupants->query_art_name(for_obj);
	}
	else
	{
	    others = exclude_array(occupants, i, i);
	    names = others->query_art_name(for_obj)  +  ({ "you" });
	}
	desc =  capitalize(COMPOSITE_WORDS(names)) + " are";
    }

    if (!namesonly)
	desc += " sitting " + chairptr[I_PREP] + my_art + name + ".\n";
    return desc;
} /* sitting_on_chair */


/*
 * Function name:	do_sit
 * Description	:	handle attempts to sit down
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    mixed	*indices,
		*chairptr;
    object	*occupants,
		tp = this_player();
    int		cap,
		i,
		nchairs,
		s;

    if (strlen(tp->query_prop(LIVE_S_SITTING)))
    {
	notify_fail("You are already seated.\n");
	return 0;
    }

    if (tp->query_prop(OBJ_I_HIDE) ||
	tp->query_prop(OBJ_I_INVIS) ||
        tp->query_invis())
    {
	write(break_string("You decide not to sit, since that would " +
	      "probably reveal your presence.", 75) + "\n");
	return 1;
    }

    indices = m_indices(Room_chairs);
    if (!(nchairs = sizeof(indices)))
    {
	notify_fail("Sit on what?\n");
	return 0;
    }

    s = strlen(arg);
    for (i = 0; i < nchairs; ++i)
    {
	chairptr = Room_chairs[indices[i]];
	if (!s ||
	    arg == "down" ||
	    arg == indices[i] ||
	    parse_command(arg, ({}), chairptr[I_PATTERN]))
	{
	    /* matched a chair ... is there room? */
	    occupants = chairptr[I_OCCUPANTS];
	    if (sizeof(occupants) < chairptr[I_CAPACITY])
	    {
		tp->set_no_show_composite(1);
    		tp->add_subloc(SITTING_S_SUBLOC, this_object());
		tp->add_prop(LIVE_S_SITTING, indices[i]);
		chairptr[I_OCCUPANTS] += ({ tp });
		do_sit_msgs(tp, chairptr[I_PREP], indices[i]);
		return 1;
	    }
	    /* cannot say "the <name> is full", because
	     * we don't know whether it should be "is full"
	     * or "are full".
	     */
	    notify_fail("There's no room for you " + chairptr[I_PREP] +
		" the " + indices[i] + ".\n");
	    return 0;
	}
    }
    notify_fail("Sit on what?\n");
    return 0;
} /* do_sit */

/*
 * Function name:	do_stand
 * Description	:	handle attempts to stand up
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * in the interests of simpler parsing, only accept "stand/rise" and
 * "stand/rise up". if you do "stand up from the chair", you lose.
 */
public int
do_stand(string arg)
{
    string	name,
		vb;

    if (strlen(arg) &&
	arg != "up")
    {
	vb = capitalize(query_verb());
    	notify_fail(vb + " what? " + vb + " up, perhaps?\n");
	return 0;
    }
    if (!strlen(name = this_player()->query_prop(LIVE_S_SITTING)))
    {
	notify_fail("You are not seated.\n");
	return 0;
    }

    stand_up(this_player(), name, 1);
    return 1;
} /* do_stand */


/*
 * Function name:	stand_up
 * Description	:	handle the actual bookkeeping of standing
 * Arguments	:	object tp -- the person to stand
 *			string name -- name of the chair 
 *			int domsg -- if true, you-stand msgs will be written
 *
 * this function is separate from do_stand() so that we may force players
 * to stand up without doing the you-stand msgs.  the "Foo leaves west."
 * message will have been written before leave_inv() is called, and it 
 * looks silly to issue a "Foo stands up." afterwards.
 */
public void
stand_up(object tp, string name, int domsg)
{
    mixed	*chairptr;

    tp->unset_no_show_composite();
    tp->remove_subloc(SITTING_S_SUBLOC);
    tp->remove_prop(LIVE_S_SITTING);

    if (domsg)
    {
	do_stand_msgs(tp, name);
    }

    if (pointerp(chairptr = Room_chairs[name]))
    {
    	chairptr[I_OCCUPANTS] -= ({ tp });
    }
    else
    {
	/* eeks. now what? well, let's see if it ever happens. */
	CHAIRS_LOG_ERR("no chair '" + name + "' for " +
	    tp->query_name() + ".\n");
    }
} /* stand_up */


/*
 * Function name:	query_occupants
 * Description	:	returns occupants of a particular chair
 * Arguments	:	string name -- chair name
 * Returns	:	object * -- array of occupants
 */
public object *
query_occupants(string name)
{
    mixed	*chairptr;
    if (pointerp(chairptr = Room_chairs[name]))
    {
    	return chairptr[I_OCCUPANTS];
    }
    return ({});
} /* query_occupants */


/*
 * Function name:	show_subloc
 * Description	:	generate "foo is sitting ..." msg
 *			for living's desc.
 * Arguments	:	string subloc -- the subloc
 *			object pl -- the player
 *			object for_obj -- who's doing the looking
 * Returns	:	string -- the "is sitting" msg
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string	name;
    mixed	*chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
	return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = Room_chairs[name]))
    {
	if (for_obj != pl)
	{
	    return capitalize(pl->query_pronoun()) + " is sitting " +
		chairptr[I_PREP] + " the " + name + ".\n";
	}
	return "You are sitting " + chairptr[I_PREP] + " the " +
	    name + ".\n";
    }
    return "";
} /* show_subloc */


/*
 * Function name:	do_sit_msgs
 * Description	:	do the you-sit and foo-sits msgs
 * Arguments	:	object pl -- the person who's sitting
 *			string prep -- the preposition
 *			string name -- the name of the chair
 *
 * this function exists to provide a convenient hook for
 * inheriting rooms to roll their own messages.
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You sit down " + prep + " the " + name + ".\n");
    say(QCTNAME(this_player()) + " sits down " + prep + " the " +
	name + ".\n");
} /* do_sit_msgs */


/*
 * Function name:	do_stand_msgs
 * Description	:	do the you-stand and foo-stands msgs
 * Arguments	:	object pl -- the person who's standing
 *			string name -- the name of the chair
 *
 * this function exists to provide a convenient hook for
 * inheriting rooms to roll their own messages.
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up.\n");
    say(QCTNAME(this_player()) + " stands up.\n");
} /* do_stand_msgs */


/*
 * Function name:	check_sitting
 * Description	:	have players stand up before leaving
 * Returns	:	0 (always)
 *
 * this routine is intended to be used as the 3rd (efunc) argument
 * to add_exit().  it will issue "you stand up"/"Foo stands up" 
 * msgs for normal exits.  
 *
 * this is separate from leave_inv() handling because by the
 * time leave_inv() is called, the "Foo leaves <dir>." message
 * has already been displayed.  at that point, it's too late to 
 * do "Foo stands up."
 */
public int
check_sitting()
{
    string	chairname = this_player()->query_prop(LIVE_S_SITTING);

    if (strlen(chairname))
    {
	stand_up(this_player(), chairname, 1);
    }
    return 0;
} /* check_sitting */


/*
 * Function name:	leave_inv_room_chairs
 * Description	:	have departing (teleporting) players stand up
 * Arguments	:	object ob -- the departing ob
 *			object dest -- destination
 *
 * This catches players who leave by quitting, teleporting, going netdead ...
 * N.B. we don't do "you-stand"/"foo-stands" msgs here, because the
 * "foo leaves" msg has already been written.
 */
public void
leave_inv_room_chairs(object ob, object dest)
{
    string	chairname,
		vb = query_verb();

    if (living(ob) &&
	vb != "In" &&
	vb != "At")
    {
	/* paranoia, but i want to be sure no invisible obs leave */
	ob->unset_no_show_composite();
	if (strlen(chairname = ob->query_prop(LIVE_S_SITTING)))
	{
	    stand_up(ob, chairname, 0);
	}
    }
} /* leave_inv_room_chairs */


/*
 * Function name:	no_hide
 * Description	:	block attempts to hide/go invis while seated
 * Arguments	:	string arg -- unused
 * Returns	:	1 if player is seated (and so cannot hide);
 *			0 if player is standing.
 *
 * nothing i can do about them quaffing an invis potion while seated :-(
 */
public int
no_hide(string arg)
{
    if (strlen(this_player()->query_prop(LIVE_S_SITTING)))
    {
	write("It's too difficult to " + query_verb() +
	    " while you're seated.\n");
	return 1;
    }
    return 0;
} /* no_hide */


/*
 * Function name:	exits_description
 * Description	:	mask parent to describe seated after the exits
 *			description.
 * Returns	:	string -- exits + seated desc
 */
public string
exits_description()
{
    mixed	*nonob;
    string	desc,
		*chairnames;
    int		s;
    object	tp = this_player();

    if (Did_exit_desc)
    {
	if (strlen(Exit_desc))
	{
	    desc = Exit_desc;
	}
	else
	{
	    desc = my_exits_description();
	}
    }
    else
    {
	/* first time called.  if there is no VBFC to determine
	 * whether an exit is obvious, then we can construct the 
	 * exits desc once and reuse it.
	 */
	Did_exit_desc = 1;
	s = sizeof(nonob = this_object()->query_non_obvious_exits());
	while (s-- > 0)
	{
	    if (!intp(nonob[s]))
	    {
		break;	/* while */
	    }
	}
	desc = my_exits_description();
	if (s < 0)
	{
	    Exit_desc = desc;
	}
    }

    if (!No_sitting_in_desc)
    {
        /* if anyone is seated, apppend desc to exits desc */
        s = sizeof(chairnames = m_indices(Room_chairs));
        while ( s-- > 0)
        {
            desc += sitting_on_chair(chairnames[s], tp, 0,
                                     Chair_mentioned);
        }
    }
    return desc;
} /* exits_description */


/*
 * Function name:	my_exits_description
 * Description	:	generate the exits desc 
 * Returns	:	string -- exits desc
 *
 * N.B. if i could figure out how to call exits_description()
 *      in the base room inherited by the room which also inherits
 *      this file, then i wouldn't need this routine.
 */
public string
my_exits_description()
{
    string	*exits;
    int		size;

    exits = this_object()->query_obvious_exits();

    switch(size = sizeof(exits))
    {
    case 0:
	return "";

    case 1:
	return "There is one obvious exit: " + exits[0] + ".\n";

    default:
	return break_string(("There are " + LANG_WNUM(size) +
	    " obvious exits: " + COMPOSITE_WORDS(exits) + "."), 75) + "\n";
    }
} /* my_exits_description */


public void	set_no_sitting_in_desc(int i)	{ No_sitting_in_desc = i; }
public int	query_no_sitting_in_desc()	{ return No_sitting_in_desc; }
