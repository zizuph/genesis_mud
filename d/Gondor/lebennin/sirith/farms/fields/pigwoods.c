/*
 * /d/Gondor/lebennin/sirith/farms/pigwoods.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * This is the pig's "home" room for domove -- if she gets stuck,
 * she comes here. She also comes here briefly after she's been
 * drunk -- call it a hangover. :-)
 *
 * Since this room is not accessible to players, it doesn't do a
 * lot of the usual stuff. It's good enough to pass, in case a
 * player gets here accidentally (which "cannot" happen), but
 * that's all.
 *
 */

#pragma strict_types

#include <stdproperties.h>		/* for OBJ_S_WIZINFO */
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/std/room";

#define		CHECK_EVERY_N	120.0	/* every 2 minutes */

public void	create_gondor();
public void	check_pig(object pig);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("Woods in southern Lebennin.");
    set_long(BSN("Woods in southern Lebennin. The trees are "+
	"crowded by thickly tangled undergrowth."));
    add_exit("track3", "east");
    add_prop(OBJ_S_WIZINFO,
	BSN("This room is not accessible to players. It exists only "+
	"to give the farm pig a tmp holding place."));
} /* create_gondor */

/*
 * Function name:	enter_inv
 * Description	:	after calling parent's enter_inv(),
 *			intercept players and send them back.
 *			if is pig, set alarm to check her status.
 * Arguments	:	object obj - the object entering this room
 *			object from - where it came from
 */
public void
enter_inv(object obj, object from) 
{
    ::enter_inv(obj, from);
    if (!obj->query_npc() &&
	!obj->query_wiz_level())
    {
	tell_object(obj, "Your head spins and for a moment "+
	    "you cannot get your bearings.\n");
	obj->move(from);
    }
    else if (obj->id(PIGNAME))
    {
	DEBUG_LOG("pigwoods: "+file_name(obj)+" from "+
		file_name(from)+"\n");
	/* restrain pig til we can take a look at it */
	obj->set_random_move(600);
	obj->set_restrain_path(PIGWOODS);
	set_alarm(2.0, 0.0, &check_pig(obj));
    }
    return;
} /* enter_inv */


/*
 * Function name:	check_pig
 * Description	:	check pig's health. if good, send back out
 * Arguments	:	object pig
 *
 * pig's hp is slightly reduced at the end of a drunk spell,
 * so she'll rest here briefly.
 */
public void
check_pig(object pig)
{
    if (objectp(pig))
    {
	if (pig->query_hp() == pig->query_max_hp())
	{
	    /* move_pig() will fix restrain path & random move times */
	    PIGSTY->move_pig(TO, 0);
	}
	else
	{
	    set_alarm(CHECK_EVERY_N, 0.0, &check_pig(pig));
	}
    }
} /* check_pig */
