/*
 * /d/Gondor/river/anduin/lorien2rauros/boulder.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * on boulder near the south end of the portage trail
 *
 * TBD:
 *	let drop things on people below?
 *	let look north & southeast to portage 6 & 8 ?
 *	let 'em jump gap and explore some caves?
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include <composite.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	BELOW		(LORIEN_TO_RAUROS_DIR+"portage7")
#define	LYING_S_SUBLOC	"_lying_s_subloc"

/* assume CONT_I_VOLUME of a normal height & width human 
 * is 70,000 and that the boulder can hold 4 normal humans
 */
#define	MAX_VOLUME	280000

/* prototypes */
public void		create_gondor();
public varargs string	short(object for_obj);
public string		tod_descs();
public string		show_subloc(string subloc, object pl, object for_obj);
public void		init();
public void		enter_inv(object ob, object from);
public void		leave_inv(object ob, object to);
public int		unq_move(string str);
public int		unq_no_move(string str);
public int		climb_down(string arg);
public string		exa_trail();
public int		query_space(object tp);
public int		lie_down(string arg);
public int		stand_up(string arg);
public int		touch_boulder(string arg);


static int	Living_volume;
static object	Below;		/* the room below boulder */


/*
 * Function name:	create_gondor
 * Description	:	set up the boulder
 */
public void
create_gondor()
{
    FIX_EUID;	/* because we may try to load BELOW room */

    set_short("on a boulder");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The massive boulder leans over a narrow trail "+
	"below. Its top is wide enough to hold several people "+
	"comfortably.");

    set_tod_landtype("boulder");
    set_tod_landname("the Emyn Muil");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("portage7", "down", 0, 8, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"south", "southwest", "west", "northwest", }),
	BSN("Yikes! You almost walked off the boulder into thin air!"));

    add_item( ({ "emyn muil" }),
	BSN("The limestone cliffs of the Emyn Muil are swept "+
	    "bare by wind."));
    add_item( ({ "top of boulder", "top", "massive boulder", "boulder", }),
	tod_descs);
    add_item( ({ "other side", "limestone cliff", "limestone cliffs", 
	"weathered cliff", "weathered cliffs", "cliff", "cliffs", }),
	BSN("Weathered cliffs rise on the other side of the trail."));
    add_item( ({ "narrow gap", "gap", }),
	BSN("The gap between the boulder and the cliffs is "+
	    "not very wide -- two people might be able to pass "+
	    "abreast."));

    add_item( ({ "narrow trail", "trail", "below", "down", }),
	exa_trail);

    add_cmd_item( ({ "across gap", "across narrow gap",
	"gap", "narrow gap", }),
	({ "jump", "leap", }),
	BSN("With no room to make a running start, you "+
	    "feel doubtful of your ability to jump across the gap."));

} /* create_gondor */


/*
 * Function name:	short
 * Description	:	mask parent to handle descs of who's lying
 *			on the boulder ourselves.  LIVE_S_EXTRA_SHORT
 *			is crude.
 * Returns	:	string -- the short desc of the boulder
 */
public varargs string
short(object for_obj)
{
    string	desc;
    object	*lying;

    if (!objectp(for_obj))
    {
	for_obj = TP;
    }

    if (!CAN_SEE_IN_ROOM(for_obj))
    {
	return "a dark room";
    }

    desc = ::short(for_obj);

    lying = FILTER_LIVE(all_inventory(TO));
    lying = filter(lying, &->query_no_show_composite());
    lying = filter(lying, &->check_seen(for_obj));
    lying -= ({ for_obj });
    
    switch(sizeof(lying))
    {
    case 0:
	break;
    case 1:
	desc += ".\n"+BS(lying[0]->query_Art_name(TP)+
	    " is lying on the boulder");
	break;
    default:
	lying->unset_no_show_composite();
	desc += ".\n"+BS(CAP(COMPOSITE_LIVE(lying))+
	    " are lying on the boulder");
	lying->set_no_show_composite(1);
	break;
    }
    return desc;
} /* short */


/*
 * Function name:	tod_descs
 * Description	:	mask parent to handle descs of who's lying
 *			on the boulder ourselves.  LIVE_S_EXTRA_SHORT
 *			is crude.
 * Returns	:	string -- the long desc of the boulder
 */
public string
tod_descs()
{
    int		i;
    string	desc,
		exad = query_exa_arg(),
		*names;
    object	*lying,
		tp = TP;

    if (!CAN_SEE_IN_ROOM(tp))
    {
	return "It is too dark to see.\n";
    }

    if (exad != "boulder" &&
	exad != "huge boulder" &&
	exad != "massive boulder")
    {
	desc = ::tod_descs();
    }
    else
    {
#if 0
	exad = "boulder";
#endif
	desc = BSN("The top of the boulder is fairly flat, and of a size "+
	    "to hold several people quite comfortably.");
    }

    lying = FILTER_LIVE(all_inventory(TO));
    lying = filter(lying, &->query_no_show_composite());
    lying = filter(lying, &->check_seen(tp));
#if 0
/* XXX do we want to show ourselve lying when we exa the room? */
    if (exad != "boulder")
    {
	lying -= ({ tp });
    }
#endif
    
    switch (sizeof(lying))
    {
    case 0:
	break;
    case 1:
	if (lying[0] != tp) 
	{
	    desc += BSN(lying[0]->query_Art_name(tp)+
		" is lying on the boulder.");
	}
	else
	{
	    desc += "You are lying on the boulder.\n";
	}
	break;
    default:
	if ((i = member_array(tp, lying)) < 0)
	{
	    names = lying->query_art_name(tp);
	    break;
	}
	else
	{
	    lying = exclude_array(lying, i, i);
	    names = lying->query_art_name(tp)  +  ({ "you" });
	}
	desc = BSN(CAP(COMPOSITE_WORDS(names))+
	    " are lying on the boulder.");
    }
    return desc;
} /* tod_descs */


/*
 * Function name:	show_subloc
 * Description	:	generate "foo is lying ..." msg
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

    if (subloc != LYING_S_SUBLOC)
    {
	return pl->show_subloc(subloc, pl, for_obj);
    }

    if (for_obj != pl)
    {
	return capitalize(pl->query_pronoun())+
	   " is lying on the boulder.\n";
    }
    return "You are lying on the boulder.\n";
} /* show_subloc */


/*
 * Function name:	init
 * Description	:	add verbs to mess with boulder
 */
public void
init()
{
    ::init();
    add_action(climb_down,	"climb");
    add_action(lie_down,	"lie");
    add_action(stand_up,	"stand");
    add_action(touch_boulder,	"touch");
    add_action(touch_boulder,	"feel");
    add_action(touch_boulder,	"rub");
} /* init */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to update volume of livings here
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) &&
	ENV(ob) == TO)
    {
	Living_volume += ob->query_prop(CONT_I_VOLUME);
    }
} /* enter_inv */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to update volume of livings here
 *			and to restore show_composite
 * Arguments	:	object ob -- the leaving object
 *			object to -- its destination
 */
public void
leave_inv(object ob, object to)
{
    if (living(ob))
    {
	ob->unset_no_show_composite();
	ob->remove_subloc(LYING_S_SUBLOC);
    }

    ::leave_inv(ob, to);

    if (living(ob) &&
	ENV(ob) != TO)
    {
	Living_volume -= ob->query_prop(CONT_I_VOLUME);
    }
} /* leave_inv */


/*
 * Function name:	unq_move
 * Description	:	mask parent so player stands up first
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 if blocked
 */
public int
unq_move(string str)
{
    if (TP->query_no_show_composite())
    {
	stand_up("");
    }
    return ::unq_move(str);
} /* unq_move */


/*
 * Function name:	unq_no_move
 * Description	:	mask parent so player stands up first
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	0 -- always
 */
public int
unq_no_move(string str)
{
    if (TP->query_no_show_composite())
    {
	stand_up("");
    }
    return ::unq_no_move(str);
} /* unq_no_move */


/*
 * Function name:	climb_down
 * Description	:	handle attempts to climb down
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	int -- 1 if we understand the arg, 0 if not
 */
public int
climb_down(string arg)
{
    object	tp;
    if (!arg ||
	!parse_command(LOW(arg), ({}),
	    "'down' [from] [the] [huge] / [massive] [boulder]"))
    {
	NF0("Climb where?\n");
    }
    tp = TP;
    if (tp->query_no_show_composite())
    {
	stand_up("");
    }
    if (!tp->query_wiz_level())
    {
	tp->command("$down");	/* so fatigue is added */
    }
    else
    {
	tp->move_living("down", BELOW);
    }
    return 1;
} /* climb_down */


/*
 * Function name:	exa_trail
 * Description	:	describe trail and occupants
 * Returns	:	string -- the description
 */
public string
exa_trail()
{
    object	*on_trail;
    string	desc;


    if (!objectp(Below))
    {
    	BELOW->short();
    	Below = find_object(BELOW);
    }
    on_trail = FILTER_LIVE(all_inventory(Below));
    if (!TP->query_wiz_level())
    {
	/* assume that from this distance, cannot see hidden or invis */
	on_trail = filter(filter(on_trail,
	    &not() @ &->query_prop(OBJ_I_HIDE)),
	    &not() @ &->query_invis());
    }

    desc = "The trail squeezes through a narrow gap "+
	"between boulder and cliff.";

    switch (sizeof(on_trail))
    {
    case 0:
	break;
    case 1:
	desc += " "+on_trail[0]->query_Art_name(TP)+
	    " is standing on the trail.";
	break;
    default:
	desc += " "+CAP(COMPOSITE_LIVE(on_trail))+
	    " are standing on the trail.";
	break;
    }
    return BSN(desc);
} /* exa_trail */


/*
 * Function name:	query_space
 * Description	:	decide if there's space for another person
 * Arguments	:	object tp -- the climber
 * Returns	:	int -- 0 if there's no space, 1 if there is
 */
public int
query_space(object tp)
{
    int		vol = tp->query_prop(CONT_I_VOLUME);

    return ((Living_volume + vol) <= MAX_VOLUME);
} /* query_space */


/*
 * Function name:	lie_down
 * Description	:	handle attempts to lie on the boulder
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
lie_down(string arg)
{
    object	tp;
    if (!strlen(arg) ||
	((arg = LOW(arg)) != "down" &&
	 !parse_command(arg, ({ }),
			"[down] [on] / [upon] [top] [of] [the] "+
			"[huge] / [massive] 'boulder'")))
    {
	NF0("Lie where?\n");
    }
    tp = TP;
    if (tp->query_no_show_composite())
    {
	NF0("You already are lying down.\n");
    }
    switch (tod())
    {
    case "evening":
    case "night":
    case "early morning":
	WRITE("You stretch out and lie down on the boulder, which is "+
	    "cool to the touch.");
	break;

    default:	/* morning, noon, afternoon */
	WRITE("You stretch out and lie down on the boulder, which is "+
	    "pleasantly warm to the touch.");
	break;
    }
    SAY(" lies down on the boulder.");
    tp->set_no_show_composite(1);
    tp->add_subloc(LYING_S_SUBLOC, TO);
    return 1;
} /* lie_down */


/*
 * Function name:	stand_up
 * Description	:	handle attempts to stand up
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * N.B. only call notify_fail if verb is "stand".  if verb is
 * anything else, we were called from unq_move() or unq_no_move().
 */
public int
stand_up(string arg)
{
    object	tp;
    if (strlen(arg) &&
	(arg = LOW(arg)) != "up" &&
	!parse_command(arg, ({ }),
			"[up] [on] / [upon] [top] [of] [the] "+
			"[huge] / [massive] 'boulder'"))
    {
	if (QVB == "stand")
	{
	    notify_fail("Stand where? Stand up, perhaps?\n");
	}
	return 0;
    }
    tp = TP;
    if (!tp->query_no_show_composite())
    {
	if (QVB == "stand")
	{
	    notify_fail("You already are standing.\n");
	}
	return 0;
    }
    write("You stand up.\n");
    SAY(" stands up.");
    tp->unset_no_show_composite();
    tp->remove_subloc(LYING_S_SUBLOC);
    return 1;
} /* stand_up */


/*
 * Function name:	touch_boulder
 * Description	:	handle attempts to touch boulder, since
 *	 		the "lie down" msg mentions touching it.
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
touch_boulder(string arg)
{
    if (strlen(arg) &&
	parse_command(LOW(arg), ({ }),
		      "[the] [huge] / [massive] 'boulder'"))
    {
	switch (tod())
	{
	case "evening":
	case "night":
	case "early morning":
	    write("The boulder is rough, and cool to the touch.\n");
	break;

	default:	/* morning, noon, afternoon */
	    write("The boulder is rough, and warm to the touch.\n");
	break;
	}
	return 1;
    }
    NF0("Touch what?\n");
} /* touch_boulder */
