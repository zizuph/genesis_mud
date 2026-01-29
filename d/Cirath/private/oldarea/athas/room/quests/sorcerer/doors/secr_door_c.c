inherit "/std/door";

#include <macros.h>
#include "/d/Roke/common/defs.h"

create_door()
{
    set_door_id("black_door");

    set_pass_command(({"e","east"}));

    set_open_command(({"pull"}));
    set_close_command(({"push"}));

    set_door_name(({"torch"}));

    set_door_desc(BSS("This torch is bolted to the wall, though it seems "+
		"to be loose, you cannot, with all your powers, get it out of "+
		"the stand. When you tried to pull it, you noticed that "+
		"the whole stand is loose, but still not so loose you can just "+
		"pick it down from the wall.\n"));

    set_other_room(CELL_D+"black_magi_room");

    set_open_desc(BSS("You are in a small hallway, dimly lit by a small "+
		"torch, now pulled a bit out. There are cracks in the wall "+
		"and there is small streams of water flowing silently down "+
		"towards the floor. The wall have been moved a bit out, "+
		"revealing a secret passage east.\n"));

    set_closed_desc(BSS("You are in a small hallway, dimly lit by a small "+
		"torch. There are cracks in the walls, and small streams of "+
		"water flowing silently towards the floor.\n"));

    set_fail_pass("There is no obvious exit east.");
    set_open_mess(({"moves a part of the wall out, and reveals a passage in that direction.\n","The secret door opens.\n"}));
    set_close_mess(({"pushes the wall back, closing the passage in that direction.\n","The secret door closes.\n"}));

    set_open(0);
    set_locked(0);

}

/*
 * Function name: open_door
 * Description:   Open the door.
 * Arguments:	  arg - arguments given
 */
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
	else
	{
	write(BSS("You pull the torch, and when you do so, you notice the "+
		"the wall pulling a bit out, creating an exit east.\n"));
	    say(QCTNAME(this_player()) + " " + check_call(open_mess[0]),
		this_player());
	    do_open_door("");
	    other_door->do_open_door(check_call(open_mess[1]));
	}
    }
    else
	write(check_call(fail_open[0]));

    return 1;
}

void
do_open_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc(check_call(open_desc));
    if (strlen(mess))
	tell_room(env, mess);
    open_status = 1;
}

/*
 * Function name: close_door
 * Description:   Close the door.
 * Arguments:	  arg - arguments given
 */
int
close_door(string arg)
{
    if (member_array(arg, door_name) < 0)
	return 0;

    if (!other_door)
	load_other_door();

    if (open_status)
    {
	write(BSS("When you push the torch, the wall slowly closes back to "+
		"close the exit east again.\n"));
	say(QCTNAME(this_player()) + " " +
		check_call(close_mess[0]), this_player());
	do_close_door("");
	other_door->do_close_door(check_call(close_mess[1]));
    }
    else
	write(check_call(fail_close));

    return 1;
}

void
do_close_door(string mess)
{
    object env;

    env = environment(this_object());
    env->change_my_desc(check_call(closed_desc));
    if (strlen(mess))
	tell_room(env, mess);
    open_status = 0;
}
