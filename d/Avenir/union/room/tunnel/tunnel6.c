/*
 * Revised:
 *
 *   Lucius Aug 2011: Removed the cave-in bits. There is not enough
 *                    active players to keep this in check and still
 *                    be fun unless done veeerrryyy slowly over time
 *                    and then what is the point?
 */
#pragma strict_types

#include "defs.h"
inherit TBASE;

#define SAVE		save_object(TUNNEL + "cavein")
#define RESTORE 	restore_object(TUNNEL + "cavein")

public int alarm, next_cavein, amount_left;


public void
reset_room(void)
{
#ifdef TUNNEL_CAVE_IN
    if (time() > next_cavein)
    {
	amount_left += 5 + random(15);
	next_cavein = time() + (60 * 60 * 60) + (random(3) * 60 * 60 * 60);
	SAVE;
    }
#endif
}

public varargs string
cavein_status(string where = get_north())
{
    switch(amount_left)
    {
    case 0:
	return "Some piles of rocks and rubble lie strewn about the "+
	    "ground, as if there had been a cavein some time ago. The "+
	    "rubble has been cleared aside, allowing passage through "+
	    "to the " + where + ".";
    case 1..10:
	return "A large pile of rocks and rubble blocks the passage to "+
	    "the " + where + ". Most of it has been cleared away, but "+
	    "the tunnel is still unpassable.";
    case 11..20:
	return "A large pile of rocks and rubble blocks the passage "+
	    "to the " + where + ". Although some if it has been cleared "+
	    "away, the stone is still piled high high enough to "+
	    "completely block the passage.";
    default:
	return "A massive pile of rocks and rubble blocks the passage "+
	    "to the " + where + ", the result of a cave-in. The stone "+
	    "is piled high, completely blocking the passage.";
    }
}

public int
try_north(void)
{
#ifdef TUNNEL_CAVE_IN
    if (amount_left)
    {
	write("The way to the " + get_north() +
	    " is blocked by the rubble.\n");
	return 1;
    }
#endif
    return 0;
}

public void
tunnel_room(void)
{
    set_short("warm tunnel");

    set_long("@@cavein_status@@ " + LDESC + "The air here is hot and "+
	"dry, moved by a strong wind that blows down from the "+
	"@@get_north@@.\n");

    add_item(({ "wall", "walls" }),
	"The walls are smooth and undecorated.\n");
    add_item(({"ground","floor"}), "It is smooth and worn. Scattered "+
	"about the ground are piles of rocks and stone, the result "+
	"of a cave-in.\n");
    add_item(({"rubble", "rocks", "stones", "pile", "cavein"}),
	"@@cavein_status@@\n");

    southern("tunnel5");
    northern("tunnel7", try_north);

#ifdef TUNNEL_CAVE_IN
    RESTORE;
    reset_room();
#endif
}

#ifdef TUNNEL_CAVE_IN
public int
reduce_rubble(int how_much)
{
    amount_left -= how_much;

    if (amount_left < 0)
	amount_left = 0;

    SAVE;
    return amount_left;
}

public int
query_amount_left(void)
{
    return amount_left;
}

private void
done_moving(object who)
{
    string msg = "You finish clearing away some of the rubble";

    alarm = 0;

    if (!reduce_rubble(random((who->query_stat(SS_STR) / 10))))
	msg += ", making the tunnel passable to the "+ get_north();

    TP->add_fatigue(-50);
    TP->catch_tell(msg + ".\n");
}

private void
start_moving(void)
{
    int when = 20 + random(10);
    object obj = clone_object("/std/paralyze");

    obj->set_remove_time(when);
    obj->set_stop_object(TO);
    obj->move(TP, 1);

    alarm = set_alarm(itof(when), 0.0, &done_moving(TP));
}

public int
do_move(string str)
{
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "[away] [the] 'stone' / 'rubble' / 'stones' / 'rocks' / 'pile'"))
    {
	return NF(CAP(query_verb()) +" what? The rubble perhaps?\n");
    }

    if (!amount_left)
    {
	write("The passage is clear, so that is not necessary.\n");
	return 1;
    }

    if (alarm)
    {
	write("Someone else is already doing that and there is "+
	    "room enough for one.\n");
	return 1;
    }

    if (TP->query_fatigue() < 100 &&
	TP->query_fatigue() < TP->query_max_fatigue())
    {
	write("You are too tired to try to move any more of the rubble.\n");
	return 1;
    }

    write("You begin moving aside the rocks and stones.\n");
    say(QCTNAME(TP) +" begins moving aside the rocks and stones.\n");

    start_moving();
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(do_move, "move");
    add_action(do_move, "clear");
}
#endif
