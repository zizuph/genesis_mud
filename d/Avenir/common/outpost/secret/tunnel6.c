/*
 * Revisions:
 * 	Lilith, Feb 2014: Capped the amt of rubble that can accumulate.
 * 	Lucius, Jun 2017: Fixup 'clear' messages. Fixed shovel check.
 *
 */
#include "outpost.h"
inherit OUTPOST +"secret/tunnel_base";

#define SAVE    save_object("/d/Avenir/common/outpost/rubble")
#define RESTORE	restore_object("/d/Avenir/common/outpost/rubble")


int next_cavein, amount_left;

void
reset_room()
{
    /* Every one to three hours */
    if (time() > next_cavein)
    {
	if (amount_left > 40)
	{	
	    amount_left = 40;
	}	
	else
	{
	    amount_left += 1 + random(2);
	    next_cavein = time() + (3600) + (random(3) * 3600);
	    SAVE;
	}
    }
}

string
cavein_status()
{
    if (amount_left <= 0)
    {
	return "Some piles of rocks and rubble lie strewn about the "
	+ "ground, as if there had been a cave-in some time ago. The "
	+ "rubble has been cleared aside, allowing passage through "
	+ "the tunnel.";
    }

    switch(amount_left)
    {
    case 1..15: return "A large pile of rocks and rubble blocks the "
	+ "passage. Most of it has been cleared away, but the tunnel "
	+ "is still impassable.";
    case 16..30: return "A large pile of rocks and rubble blocks the "
	+ "tunnel at one end. Although some of it has been "
	+ "cleared away, the stone is still piled high enough to "
	+ "completely block it.";
    default: return "A massive pile of rocks and rubble blocks access "
	+ "at one end, the result of a cave-in. As the stone is piled "
	+ "quite high, it will require considerable effort to clear it "
	+ "away.";
    }
}

void
create_room()
{
		IN_IN; // not in flux zone.
    set_short("small irregular tunnel");
    set_long(VBFC_ME("cavein_status") + " It is hot and dry here "+
      "and the walls are very close. There are little puffs and "+
      "trails of dust everywhere, reminding you that the stone "+
      "is not stable and there may be another cave-in at any "+
      "moment.\n");
    add_item(({ "wall", "walls" }), "The walls are rough and "+
      "jagged in places, illustrating that this is a natural "+
      "tunnel.\n");
    add_item("ceiling","The ceiling of the tunnel jagged in places.\n");
    add_item(({"ground","floor"}), "It is uneven. Scattered "+
      "about the ground are piles of rocks and stone, the result "+
      "of a cave-in.\n");
    add_item(({"rubble", "rocks", "stones", "pile", "cavein"}), 
      VBFC_ME("cavein_status") +"\n");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("tunnel7", "north", VBFC_ME("try_north"));
    add_exit("tunnel4", "south", 0, 20);

    setuid();  
    seteuid(getuid());

    RESTORE;

    reset_room();
}

int
reduce_rubble(int how_much)
{
    if (present("shovel", TP))
	how_much *= 3;

    amount_left -= how_much;

    if (amount_left <= 0)
	amount_left = 0;

    SAVE;
    return amount_left;
}

int
query_amount_left()
{
    return amount_left;
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
	msg += ", making the tunnel passable at last.";
	SAVE;
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
    obj->move(this_player(), 1);
}

int
do_move(string str)
{
    NFVB;
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "[away] / [through] [the] 'stone' / 'rubble' / 'stones' / 'rocks' / 'pile' / 'cavein'"))
    {
	return 0;
    }

    if (!amount_left)
    {
	write("The passage is clear, so that is not necessary.\n");
	return 1;
    }

    if (TP->query_fatigue() < 50 && TP->query_fatigue() < TP->query_max_fatigue())
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
try_north()
{
    if (amount_left)
    {
	if (present(TP))
	    write("The way to the north is blocked by the rubble.\n");
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
