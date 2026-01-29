#pragma strict_types

#include "defs.h"
inherit TBASE;

#define CAVEIN	(TUNNEL + "tunnel6")

public int alarm;


public varargs string
cavein_status(string where = get_north())
{
    return CAVEIN->cavein_status(south);
}

public int
try_south(void)
{
#ifdef TUNNEL_CAVE_IN
    if (CAVEIN->query_amount_left())
    {
	write("The way to the "+ get_south() +
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
    add_item(({"ground","floor"}),
	"It is smooth and worn. Scattered about the ground are piles "+
	"of rocks and stone, the result of a cave-in.\n");
    add_item(({"rubble", "rocks", "stones", "pile", "cavein"}),
	"@@cavein_status@@\n");

    northern("tunnel8");
    southern("tunnel6", try_south);
}

#ifdef TUNNEL_CAVE_IN
public int
reduce_rubble(int how_much)
{
    return CAVEIN->reduce_rubble(how_much);
}

public int
query_amount_left(void)
{
    return CAVEIN->query_amount_left();
}

private void
done_moving(object who)
{
    string msg = "You finish clearing away some of the rubble";

    alarm = 0;

    if (!reduce_rubble(random((who->query_stat(SS_STR) / 10))))
	msg += ", making the tunnel passable to the "+ get_south();

    TP->add_fatigue(-100);
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
