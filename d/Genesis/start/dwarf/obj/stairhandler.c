/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#include "../defs.h"

#define N_STEPS 20	/* Number of steps in each stairway */
#define STAIR_TOP	D_L1 + "stair_top.c"
#define STAIR_BOTTOM	D_L2 + "stair_bottom.c"

static int	esc_charge;	/* Elevator charge */

object	*s_up,			/* Up stair sequence */
	*s_down;		/* Down stair sequence */

static object *load_stairway(string side);
public void move_stairway();
static void move_contents(object source, string dest);

void
init()
{
    esc_charge = 0;
    s_up = 0;
    s_down = 0;
}

int
enter(string dir, string where, object who)
{
    switch (dir)
    {
    case "red":
	if (!pointerp(s_down))
	    s_down = load_stairway(dir);

	switch (where)
	{
	case "top":
	    who->move_living("down the red stairway",
			     s_down[N_STEPS - 1]);
	    break;

	case "bottom":
	default:				/* Bottom by default */
	    who->move_living("up the red stairway", s_down[0]);
	    break;
	}
	break;

    case "blue":
    default:					/* Up by default */
	if (!pointerp(s_up))
	    s_up = load_stairway(dir);

	switch (where)
	{
	case "top":
	    who->move_living("down the blue stairway",
			     s_up[N_STEPS - 1]);
	    break;

	case "bottom":
	default:				/* Bottom by default */
	    who->move_living("up the blue stairway", s_up[0]);
	    break;
	}
	break;
    }
}

static object *
load_stairway(string side)
{
    int i;
    object *ob_list;

    ob_list = allocate(N_STEPS);

    for (i = 0 ; i < N_STEPS ; i++)
    {
	ob_list[i] = clone_object(D_OBJ + "stair_landing");
	ob_list[i]->set_info(side, i + 1);
    }

    return ob_list;
}

public void
move_player(object player, string side, int lnum, string how)
{
    if (--lnum < 0)
    {
	player->move_living(how, STAIR_BOTTOM);
	return;
    }

    if (lnum >= N_STEPS)
    {
	player->move_living(how, STAIR_TOP);
	return;
    }

    switch (side)
    {
    case "blue":
	if (!pointerp(s_up))
	    s_up = load_stairway(side);
	player->move_living(how, s_up[lnum]);
	break;

    case "red":
    default:			      		/* Move down by default */
	if (!pointerp(s_down))
	    s_down = load_stairway(side);
	player->move_living(how, s_down[lnum]);
	break;
    }
}

public void
glance_landing(object player, string side, int lnum)
{
    object room, *list, *live_ob, *dead_ob;

    lnum -= 1;

    switch (side)
    {
    case "blue":
	if (!pointerp(s_up))
	    s_up = load_stairway(side);
	room = s_up[lnum];
	break;

    case "red":
    default:			      		/* Look down by default */
	if (!pointerp(s_down))
	    s_down = load_stairway(side);
	room = s_down[lnum];
	break;
    }

    /*
     * It is dark.
     */
    if (room->query_prop(OBJ_I_LIGHT) <= 0)
    {
	write("A dark room.\n");
	return;
    }
    
    /*
     * Describe the contents.
     */
    list = all_inventory(room);
    live_ob = FILTER_LIVE(list);
    dead_ob = FILTER_DEAD(list);

    if (sizeof(live_ob) && sizeof(dead_ob))
	write (BS(COMPOSITE_LIVE(live_ob) + ", " + COMPOSITE_DEAD(dead_ob) + "\n"));
    else if (sizeof(live_ob))
	write (BS(COMPOSITE_LIVE(live_ob) + "\n"));
    else
	write (BS(COMPOSITE_LIVE(dead_ob) + "\n"));
}

public int
kill_landings()
{
    int i, count;
    
    for (i = 0 ; i < N_STEPS ; i++)
    {
	if (pointerp(s_up))
	{
	    tell_room(s_up[i], BS("A gigant donut appears from nowhere, you fall through the hole...\n"));
	    s_up[i]->remove_object();
	    count++;
	}
	if (pointerp(s_down))
	{
	    tell_room(s_down[i], BS("A gigant donut appears from nowhere, you fall through the hole...\n"));
	    s_down[i]->remove_object();
	    count++;
	}
    }
    s_up = 0;
    s_down = 0;
    return count;
}

void
remove_object()
{
    /*
     * Remove the landings in case of update.
     */
    kill_landings();
}

public int
charge_stair(int charge)
{
    int i;

    esc_charge += charge;
    if (esc_charge <= charge)	/* Stood still before */
    {
	STAIR_TOP->start_escalator();
	STAIR_BOTTOM->start_escalator();
	if (pointerp(s_up))
	    for (i = 0 ; i < N_STEPS ; i++)
		tell_room(s_up[i], BS("The stairway suddenly jerks upwards!\n"));
	if (pointerp(s_down))
	    for (i = 0 ; i < N_STEPS ; i++)
		tell_room(s_down[i], BS("The stairway suddenly jerks downwards!\n"));
	move_stairway();
    }

    return esc_charge;
}

public void
move_stairway()
{
    int i;
    object step;
    int alarm_id;

    alarm_id = set_alarm(1.0, 0.0, move_stairway);
    if (--esc_charge <= 0)
    {
	STAIR_TOP->stop_escalator();
	STAIR_BOTTOM->stop_escalator();
	remove_alarm(alarm_id);
	if (pointerp(s_up))
	    for (i = 0 ; i < N_STEPS ; i++)
		tell_room(s_up[i], BS("The stairway grinds to a sudden stop!\n"));
	if (pointerp(s_down))
	    for (i = 0 ; i < N_STEPS ; i++)
		tell_room(s_down[i], BS("The stairway grinds to a sudden stop!\n"));
	return;
    }
    
    if (pointerp(s_down))
    {
	step = s_down[0];
	for (i = 1 ; i < N_STEPS ; i++)
	{
	    s_down[i - 1] = s_down[i];
	    s_down[i - 1]->set_info(0, i, "downwards");
	}
	move_contents(step, STAIR_BOTTOM);
	s_down[N_STEPS - 1] = step;
	step->set_info(0, N_STEPS);
    }

    if (pointerp(s_up))
    {
	step = s_up[N_STEPS - 1];
	for (i = N_STEPS - 1 ; i > 0 ; i--)
	{
	    s_up[i] = s_up[i - 1];
	    s_up[i]->set_info(0, i + 1);
	}
	move_contents(step, STAIR_TOP);
	s_up[0] = step;
	step->set_info(0, 1);
    }
}

static void
move_contents(object source, string dest)
{
    object *list;
    int i;

    list = all_inventory(source);

    if (sizeof(list) == 0)
	return;

    for (i = 0 ; i < sizeof(list) ; i++)
    {
	if (!living(list[i]))
	{
	    list[i]->move(dest, 1);
	    tell_room(dest, BS(capitalize(COMPOSITE_FILE->desc_same(({ list[i] })) + " bounces off the moving stairway.\n")));
	}
	else
	    list[i]->move_living("stepping off the moving stairway", dest);
    }
}


