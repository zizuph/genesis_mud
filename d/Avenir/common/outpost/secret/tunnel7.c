/*
 * Revisions:
 * 	Lucius, Jun 2017: Fixup 'clear' messages.
 *
 */
#include "outpost.h"
inherit OUTPOST +"secret/tunnel_base";

#define CAVEIN		(OUTPOST +"secret/tunnel6")


string
cavein_status()
{
    return CAVEIN->cavein_status();
}

void
create_room()
{
		IN_IN; // not in flux zone.
    set_short("irregular tunnel");
    set_short("small irregular tunnel");

    add_exit("tunnel6", "south", VBFC_ME("try_south"));
    add_exit("../fort6", "north");

    set_long(VBFC_ME("cavein_status") + " It is warm and dry here "+
      "and the walls are very close. There are little puffs and "+
      "trails of dust everywhere, reminding you that the stone "+
      "is not stable and there may be another cave-in at any "+
      "moment. There are sounds of activity coming from the "+
      "north, and a faint warm breeze blows in from the south.\n");
    add_item(({ "wall", "walls" }), "The walls are rough and "+
      "jagged in places, illustrating that this is a natural "+
      "tunnel.\n");
    add_item("ceiling","The ceiling of the tunnel jagged in places.\n");
    add_item(({"ground","floor"}), "It is uneven. Scattered "+
      "about the ground are piles of rocks and stone, the result "+
      "of a cave-in.\n");
    add_item(({"rubble", "rocks", "stones", "pile", "cavein"}), 
      VBFC_ME("cavein_status") +"\n");

    add_prop(ROOM_I_LIGHT,  1);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

int
reduce_rubble(int how_much)
{
    return CAVEIN->reduce_rubble(how_much);
}

int
query_amount_left()
{
    return CAVEIN->query_amount_left();
}

void
done_moving(object who)
{
    string msg = "You finish clearing away some of the rubble";

    TP->add_fatigue(-50);

    if (reduce_rubble(random((who->query_stat(SS_STR) / 10))) <= 0)
    {
	SCROLLING_LOG(ENTR_LOG, capitalize(who->query_real_name()) +
	  " cleared the rubble and opened the back exit.");
	msg += ", making the tunnel passable at last";
    }

    TP->catch_tell(msg + ".\n");
}    

void
start_moving()
{
    int tim;
    object obj;

    tim = 20 + random(10);

    set_alarm(itof(tim), 0.0, &done_moving(TP));

    obj = clone_object("/std/paralyze");
    obj->set_remove_time(tim);
    obj->set_stop_object(TO);
    obj->move(TP, 1);

}

int
do_move(string str)
{
    NFVB;
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "[away] [the] 'stone' / 'rubble' / 'stones' / 'rocks'"))
	return 0;

    if (!(CAVEIN->query_amount_left()))
    {
	write("The passage is clear, so that is not necessary.\n");
	return 1;
    }

    if (TP->query_fatigue() < 100 && TP->query_fatigue() < TP->query_max_fatigue())
    {
	write("You are too tired to try to move any more of the rubble.\n");
	return 1;
    }

    write("You begin moving aside the rocks and stones.\n");
    say(QCTNAME(TP) + " begins moving aside the rocks and stones.\n");
    start_moving();
    return 1;
}

int
try_south()
{
    if (CAVEIN->query_amount_left())
    {
	if (present(TP))
	    write("The way to the south is blocked by the rubble.\n");
	return 1;
    }

    return 0;
}

void
init()
{
    ::init();

    add_action(do_move, "move");
    add_action(do_move, "clear");
    add_action(do_move, "sort");
    add_action(do_move, "dig");
}
