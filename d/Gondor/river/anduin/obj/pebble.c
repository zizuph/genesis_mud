/*
 * /d/Gondor/river/anduin/obj/pebble.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * Just a simple pebble.
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>		/* for NORMAL_ACCESS */
#include <language.h>		/* for LANG_WNUM */
#include <macros.h>		/* for QTNAME*	*/
#include <stdproperties.h>	/* for OBJ_I_*	*/
#include <wa_types.h>		/* for A_?_HAND */
#include "/d/Gondor/defs.h"

public void	create_object();
public string	long_desc();
public void	init();
public int	rub_pebble(string arg);
public int	toss_pebble(string arg);


/*
 * Function name:	create_object
 * Description	:	set up the pebble
 */
public void
create_object()
{
    set_name( ({ "pebble", "stone", "rock" }) );
    set_adj( ({ "small", "brown" }) );
    set_long(long_desc);

    add_prop(OBJ_I_WEIGHT, 28);	/* 1 oz */
    add_prop(OBJ_I_VOLUME, 16);	/* 1 cubic inch */
    add_prop(OBJ_I_VALUE, 0);
} /* create_object */


/*
 * Function name:	long_desc
 * Description	:	VBFC for pebble long -- if bare hand,
 *			notice that is cool to touch
 * Returns	:	string -- the desc
 */
public string
long_desc()
{
    object	tp = TP;
    string	desc = "The pebble is light brown, and about an inch wide.";

    if (ENV() == tp &&
	(!objectp(tp->query_armour(A_R_HAND)) ||
         !objectp(tp->query_armour(A_L_HAND))))
    {
	desc += " It feels smooth and cool to the touch.";
    }
    return BSN(desc);
} /* long_desc */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    ::init();
    add_action(rub_pebble,	"rub");
    add_action(rub_pebble,	"touch");
    add_action(rub_pebble,	"feel");
    add_action(toss_pebble,	"toss");
    add_action(toss_pebble,	"throw");
} /* init */


/*
 * Function name:	rub_pebble
 * Description	:	respond to attempts to touch etc
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 */
public int
rub_pebble(string arg)
{
    object	*targets,
		tp = TP;

    if (!strlen(arg) ||
	!parse_command(LOW(arg), (all_inventory(tp) + all_inventory(ENV(tp))),
		       "%i", targets) ||
	!sizeof(targets = NORMAL_ACCESS(targets, 0, 0)) ||
	targets[0] != TO)
    {
	NF0(CAP(QVB)+" what?\n");
    }
    if (ENV() == tp)
    {
	write("You rub the small brown pebble.\n");
	SAY(" rubs a small pebble.");
    }
    else
    {
	write("You stoop and rub the small brown pebble.\n");
	SAY(" stoops and rubs the small pebble.");
    }
    if (!objectp(tp->query_armour(A_R_HAND)) ||
        !objectp(tp->query_armour(A_L_HAND)))
    {
	write("It is smooth and pleasantly cool to the touch.\n");
    }
    return 1;
} /* rub_pebble */


/*
 * Function name:	toss_pebble
 * Description	:	respond to attempts to toss/throw
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 */
public int
toss_pebble(string arg)
{
    object	*items, 
		*targets,
		tp = TP,
		env = ENV(tp);
    string	tmpstr,
		vb = QVB;
    int		s;

    if (!strlen(arg) ||
	!parse_command(LOW(arg), all_inventory(tp), "%i %s", items, tmpstr) ||
	!sizeof(items = NORMAL_ACCESS(items, 0, 0)) ||
	items[0] != TO)
    {
	NF0(CAP(vb)+" what?\n");
    }
    if (strlen(tmpstr) &&
	tmpstr != "away" &&
	(!parse_command(tmpstr, all_inventory(env), "'at' %l", targets) ||
	 !(s = sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))))
    {
	NF0(CAP(vb)+" pebble at whom?\n");
    }
    switch (s)
    {
    case 0:
	tmpstr = (env->query_prop(ROOM_I_INSIDE) ? "floor." : "ground.");
	WRITE("You toss the pebble away. It lands on the "+tmpstr);
	SAY(" tosses a pebble away. It lands on the "+tmpstr);
	break;
    case 1:
	tmpstr = ". It bounces harmlessly off and lands on the "+
	    (env->query_prop(ROOM_I_INSIDE) ? "floor.\n" : "ground.\n");
	tp->catch_msg("You toss the pebble at "+QTNAME(targets[0])+tmpstr);
	targets[0]->catch_msg(QCTNAME(tp)+" tosses a pebble at you"+tmpstr);
	tell_room(env,
	    QCTNAME(tp)+" tosses a pebble at "+QTNAME(targets[0])+tmpstr,
	    ({ tp, targets[0] }) );
	break;
    default:
	NFN0("You cannot "+vb+" the pebble at "+LANG_WNUM(s)+
	    " people at once.");
	break;
    }
    move(env, 1);
    return 1;
} /* toss_pebble */
