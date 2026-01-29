/*
 * This room is cloned for each person using the outer stairs
 * to enter / leave the Ziggurat.
 *
 *  Revisions:
 *  	Lucius, Jun 2017: Fixed non-player auto-follow "pets" from
 *  			  behaving oddly.
 */
#pragma strict_types

#include "zigg.h"
#include <config.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

/* From /d/Genesis/obj/statue.c */
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

#define TICK     2.0
#define TICKS    (6 + random(5))
#define FATIGUE  -3

inherit "/std/room";

private static int goodbye;
private static object player;
private static string dir, dest;

public string
block_dir(void)
{
    return "You are too busy "+ dir +"ing the stairs!\n";
}

public string
get_dir(void)	{ return dir; }

public void
create_room(void)
{
    setuid();
    seteuid(geteuid());

    /* XXX improve */
    set_short("outer stairway of the Ziggurat");
    set_long("You are @@get_dir@@ing the outer stairs of the Ziggurat.\n");

    /* XXX add items */

    /* All of sybarus is inside. */
    add_prop(ROOM_I_INSIDE, 1);
    /* No magic props. */
    add_prop(ROOM_M_NO_MAGIC, block_dir);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, block_dir);
    /* No teleport props. */
    add_prop(ROOM_M_NO_TELEPORT, block_dir);
    add_prop(ROOM_M_NO_TELEPORT_TO, block_dir);
    add_prop(ROOM_M_NO_TELEPORT_FROM, block_dir);
}

private void
spammage(int count)
{
    int cost;

    /* Counting down to extinction. */
    if (goodbye)
	return;

    /* Fail-safe */
    if (!present(player))
    {
	set_alarm(1.0, 0.0, remove_object);
	return;
    }

    /* Descending is less taxing. */
    if (dir == "ascend")
	cost = FATIGUE;
    else
	cost = (FATIGUE / 2);

    /* The steps are exhaustive. */
    player->add_fatigue(cost);

    /* At destination. */
    if (count >= TICKS)
    {
	tell_room(TO, "You finally "+ dir +" the last of the steps.\n");

	/* In case of failure... */
	if (player->move_living("M", dest, 1, 0))
	{
	    tell_room(TO, "There was a problem moving you.\n"+
		"Try link-dying for a minute to reset your location.\n");
	}
	else
	{
	    tell_room(dest, QCTNAME(player) +" arrives "+ dir +"ing "+
		"the outer Ziggurat steps.\n", player, player);
	}

	return;
    }

    /* We are treading steps, whee! */
    tell_room(TO, one_of_list(({
	"You climb "+ (dir == "ascend" ? "up" : "down") +" more steps.\n",
	"Even more steps pass under your feet.\n",
	"Refreshing spray from a small waterfall to your "+
	    one_of_list(({"left", "right"})) +" cools your skin.\n",
	"You climb and climb until your legs "+
	    one_of_list(({"shake with fatigue", "feel like jelly",
	      "burn with the effort", "feel heavy with exhaustion"})) +".\n",
	"Sweat trickles down your sides as you trudge "+ 
	    (dir == "ascend" ? "upward" : "downward") +".\n",
	"The "+ (dir == "ascend" ? "top" : "bottom") +" seems only a little "+
	    "closer as you begin to feel out of breath.\n",
	"You "+ dir +" past tiered gardens with "+ one_of_list(({
	    "colorful flowers","redolent blossoms","beautiful fruit trees",
	    "surprisingly tall trees", "creatively clipped bushes"})) +".\n",
	"You catch the scent of "+ one_of_list(({"roses", "lavender",
	    "lilies", "olive trees", "fresh clipped grass",
	    "honeysuckle"})) +" as you continue "+
	    (dir == "ascend" ? "upward" : "downward") +".\n",
	"The sound of your feet treading against the stone lulls you "+
	    "with its steady rhythm.\n",
    })));

    /* More steps ahead (or below). */
    set_alarm(TICK, 0.0, &spammage(++count));
}

private void
bounce(object ob)
{
    if (!present(ob))
	return;

    object room = (ZIG_RL1 + "landing")->get_this_object();
    /* Heaps will be the death of me someday.... */
    string str, name = (living(ob) ? QCTNAME(ob) : ob->num_heap() ?
	CAP(ob->short()) : CAP(LANG_ADDART(ob->short())));

    if (ob->num_heap() > 1)
	str = " go ";
    else
	str = " goes ";

    tell_room(TO, name + str +"bouncing down the stairs and comes "+
	"to a stop at the landing.\n", ob, ob);

    if (living(ob))
    {
	str = " arrives ";
	ob->move_living("M", room, 1, 1);
    }
    else
    {
	ob->move(room);

	if (ob->num_heap() > 1)
	    str = " arrive ";
	else
	    str = " arrives ";
    }

    tell_room(room, name + str + "bouncing down the Ziggurat "+
	"stairs.\n", 0, ob);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob))
    {
	set_alarm(0.5, 0.0, &bounce(ob));
	return;
    }

    if (!IS_CLONE)
	return;

    if (!query_interactive(ob))
	return;

    if (file_name(from) == (ZIG_RL1 + "landing"))
    {
	dir = "ascend";
	dest = (ZIG_RL1 + "entrance");
    }
    else
    {
	dir = "descend";
	dest = (ZIG_RL1 + "landing");
    }

    player = ob;
    set_alarm(TICK, 0.0, &spammage(1));
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    /* This is a cloned room that gets destroyed when left.
     * If a player linkdies here, have them recover at the landing.
     */
    if (living(ob) && objectp(to) && file_name(to) == OWN_STATUE)
    {
	ob->add_prop(PLAYER_S_LD_IN_ROOM, ZIG_RL1 + "landing");
	goodbye = set_alarm(5.0, 0.0, remove_object);
	return;
    }

    /* Non-players return here.
     * Comes after linkdeath check because players are no longer
     * interactive at this point if linkdead.
     */
    if (!query_interactive(ob))
	return;

    goodbye = set_alarm(5.0, 0.0, remove_object);
}
