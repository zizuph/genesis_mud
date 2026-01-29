inherit "/std/door";
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_door()
{
    set_door_id("celldoor");

    set_pass_command(({"d","down"}));

    set_door_name(({"fireplace","fireplace"}));

	set_other_room(CELL_D+"celstair1");

    set_lock_command("lock");
    set_unlock_command("unlock");
    set_open_command("move");
    set_close_command("push");
    
    set_open_desc(BSS("The fireplace has been moved slightly out "+
		  "making a passage behind it. There is now an extra exit "+
		  "down from here, and you wonder how a house like this can "+
	       "a cellar. There is a sitting room to the north, a library to "+
		"the east, and a set of stairs leading up.\n"));
    set_closed_desc(BSS("There is a sitting room to the north, a library "+
			"to the east, and a set of stairs leading up.\n"));
    set_fail_pass("There is no obvious exit down.\n");

    set_open_mess(({"moves the fireplace a little bit out, causing an opening "+
		    "to appere in its place.\n","The secret door opens.\n"}));
    set_close_mess(({"pushes the fireplace back in place, concealing the "+
			 "hole behind it.\n","The secret door is closed.\n"}));

    set_unlock_mess(({"does something to the fireplace, and you can "+
		  "hear a soft 'click'.\n","You hear a soft 'click' from the "+
		  "secret door.\n"}));
    set_lock_mess(({"does something to the fireplace, and you hear a "+
		"harsh 'click'.\n","You hear a harsh 'click' from the secret door.\n"}));

    set_open(0);
    set_locked(1);
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
	    write(BSS("You move the fireplace a bit out, and when "+
		      "you hear the sounds, you become a bit scared "+
		      "about someone hearing you, but noone seemed "+
		      "to do so.\n"));
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
	write(BSS("You push with all your powers, and manage to push the "+
		"fireplace back in its place.\n"));
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

/*
 * Function name: lock_door
 * Description:   Lock the door.
 * Arguments:	  arg - arguments given
 */
int
lock_door(string arg)
{
    if (!lock_procedure(arg))
	return 0;

    if (!other_door)
	load_other_door();

    if (!lock_status)
    {
	if (open_status)
	    write(check_call(fail_lock[1]));
	else
	{
	write(BSS("You insert the key in the hole, and turns it. When "+
		"you do so, you hear a harsh 'click' from the hole.\n"));
	    say(QCTNAME(this_player()) + " " +
		check_call(lock_mess[0]), this_player());
	    do_lock_door("");
	    other_door->do_lock_door(check_call(lock_mess[1]));
	}
    }
    else
	write(check_call(fail_lock[0]));

    return 1;
}

void
do_lock_door(string mess)
{
    if (strlen(mess))
	tell_room(environment(this_object()), mess);
    lock_status = 1;
}

/*
 * Function name: unlock_door
 * Description:   Unlock the door.
 * Arguments:	  arg - arguments given
 */
int
unlock_door(string arg)
{
    if (!lock_procedure(arg))
	return 0;

    if (!other_door)
	load_other_door();

    if (lock_status)
    {
	write(BSS("As you insert the key in the hole and turns it, you "+
		"hear a soft 'click', indicating that the lock is unlocked.\n"));
	say(QCTNAME(this_player()) + " " + check_call(unlock_mess[0]),
	    this_player());
	do_unlock_door("");
	other_door->do_unlock_door(check_call(unlock_mess[1]));
    }
    else
	write(check_call(fail_unlock));

    return 1;
}

void
do_unlock_door(string mess)
{
    if (strlen(mess))
	tell_room(environment(this_object()), mess);
    lock_status = 0;
}
