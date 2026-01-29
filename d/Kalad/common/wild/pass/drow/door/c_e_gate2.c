// file name:        /d/Kalad/common/wild/pass/drow/c_e_gate2.c
// creator(s):       
// revision history: Denis, Nov'96: Moved to Avenir.
// purpose:          Exterior of the entrance gate to Undraeth.
// note:             
// bug(s):           
// to-do:            
/*
 * Repatriating to Kalad and
 * removing references to Avenir code.
 *	- Lucius, June 2017
 */
# pragma strict_types
#include "/d/Kalad/defs.h"
# include <macros.h>
# include <stdproperties.h>
inherit "/std/door";

void
create_door()
{
    set_door_id("cegate");
    set_pass_command(({ "sw", "southwest" }));
    set_door_name(({ "black adamantine gate", "black gate", 
	"adamantine gate", "gate" }));
    set_name("gate");
    set_other_room(CPASS(drow/d1));
    set_fail_pass("The black adamantine gate is closed!\n");
    set_open(0); /* Closed by default */
    set_str(180);
    set_door_desc("A massive gate fashioned entirely from black adamantine "+
      "metal. The gate's surface has been so flawlessly crafted that it "+
      "acts as a gigantic black mirror, reflecting everything within this "+
      "passage. So ingenious is its design, that it molds perfectly with the "+
      "surrounding rock, making it appear as if it were a smooth extension "+
      "of the passage itself.\n");
    write("For a moment, you feel a twinge of nervousness...but the sensation "+
      "soon fades.\n");
}

public void
gates_move(string dir)
{
    if (!other_door)
	load_other_door();

    if (dir == "open")
    {
	TO->do_open_door("Someone says: Abban, khaless nau uss "+
	  "mzild taga dosstan.\n" + "Someone opens the black "+
	  "adamantine gate.\n");
	other_door->do_open_door("The black adamantine gate opens.\n");
    }
    else if (dir == "close")
    {
	TO->do_close_door("Someone says: Abban, Quarvalsharess tlu "+
	  "malla; jal ultrinnan zhah xundus.\n" + "Someone closes "+
	  "the black adamantine gate.\n");
	other_door->do_close_door("The black adamantine gate closes.\n");
    }
}

int
hear_dsay(string str)
{
    if ((TP->query_race_name() != "drow") ||
	(TP->query_skill(SS_LANGUAGE) < 15))
	return 0;
    if (!strlen(str))
	return 0;
    if (str == "open" || str == "Open")
    {
	set_alarm(0.0, 0.0, &gates_move("open"));
	return 0;
    }
    if (str == "close" || str == "Close")
    {
	set_alarm(0.0, 0.0, &gates_move("close"));
	return 0;
    }
    else
	return 0;
}

void
init()
{
    ::init();
    add_action(hear_dsay, "dsay");
}

int
pass_door(string arg)
{
    if (!other_door)
	load_other_door();

    if (open_status)
	return 0;
    else
	write(check_call(fail_pass));
    return 1;
}

int
open_door(string arg)
{
    if (member_array(arg, door_name) < 0)
	return 0;

    if (!other_door)
	load_other_door();

    if (!open_status)
    {
	if (lock_status)
	    write(check_call(fail_open[1]));
	else if (this_player()->query_stat(SS_STR) < open_str)
	    notify_fail("You lack the strength needed.\n");
	else
	{
	    write("Ok.\n");
	    say(QCTNAME(this_player()) + " " + check_call(open_mess[0]),
	      this_player());
	    do_open_door("");
	    other_door->do_open_door(check_call(open_mess[1]));
	    notify_fail("");
	}
    }
    else
	notify_fail(check_call(fail_open[0]));
    return 0;
}

