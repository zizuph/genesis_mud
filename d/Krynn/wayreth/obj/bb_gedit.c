inherit "/std/board/bb_gedit";
#include <macros.h>
#define GPROMPT() tell_object(ged_user, cprompt)


new_msg()
{
    string lvl_text, name;
    
    ged_user = this_player();
    board_obj = previous_object();

#ifdef CPROMPT
    cprompt = CPROMPT;
#endif

    write("Entering Gedit. Type 'help' or '?' for help.\n");
    input_to("gedit_msg");
    GPROMPT();
}

void
gedit_msg(string str)
{
    string *ret_buf;
    if ((ret_buf = ed_it(str)))
    {
	if (sizeof(ret_buf) == 0 || !strlen(ret_buf[0]))
	{
	    tell_object(ged_user, "No text entered. " +
			"Writing aborted.\n");
	    say(QCTNAME(ged_user) + " aborts writing a book.\n");
	    remove_object();
	}
	else
	{
	    tell_object(ged_user, "Ok.\n");
	    tell_room(environment(ged_user),
		      QCTNAME(ged_user) + " has completed " + "a book.\n",
		      ged_user);
	    board_obj->set_tmp(implode(ret_buf, "\n"));
	    remove_object();
	}
    }
    else
	input_to("gedit_msg");
}
