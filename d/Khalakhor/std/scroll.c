/*
 * /d/Khalakhor/std/scroll.c      
 *
 * A standard object that can be both read, and mread :)
 *
 * set_scroll_file(string file) - Will connect a file to the read command
 * 
 *  Borrowed from /std/scroll updated and redone since there is no plans for
 *  it to be done there... just because the std is out of date doesn't mean we 
 *  have to use it ;)
 *
 *  Igneous  October 27th, 1998
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

/*
 * Global variables.
 */
static string gScroll_file;

/*
 * Function name: create_khalakhor_scroll
 * description  : Create the scroll. You should redefine this function if
 *                you want to create the scroll.
 */
void
create_khalakhor_scroll()
{
    set_name("scroll");
    set_adj(({"yellowed", "ancient"}));
    set_short("ancient yellowed scroll");
    set_long("An empty scroll, no use to either read or mread it.\n");
}

/*
 * Function name: create_object
 * Description  : Create the object. You must define the function
 *                create_khalakhor_scroll() to define the scroll.
 */
nomask void
create_object()
{
    add_prop(OBJ_I_WEIGHT, 10); /* 10 g */
    add_prop(OBJ_I_VOLUME, 10); /* 10 ml */
    remove_prop(OBJ_I_VALUE); /* 0 copper */

    create_khalakhor_scroll();
}

/*
 * Function name: set_scroll_file
 * Description  : Set the file to list when player reads this.
 * Arguments    : string file - the filename.
 */
public void
set_scroll_file(string file)
{
    gScroll_file = file;
}

/*
 * Function name: query_scroll_file
 * Description  : Query what file is connected to read command
 * Returns      : string - the filename.
 */
string
query_scroll_file()
{
    return gScroll_file;
}

/*
 * Function name: command_read
 * Description  : The is the command which is called when person
 *                tries to read the scroll
 * Returns      : int    1 success 
 *                string failure message.
 */
mixed
command_read(int more_flag)
{
    int fsz;

    seteuid(getuid(this_object()));

    say(QCTNAME(this_player()) + " reads the " + short() + ".\n");

    if ((fsz = file_size(gScroll_file)) == -1)
        return "The "+short()+" is too damaged to read.\n";

    if ((!more_flag) && (fsz < 4000))
    {
        this_player()->cat(read_file(gScroll_file));
    }
    else
    {
	if (fsz >= 50000)
	{
            return "The words on the "+short()+" are too difficult to decifer.\n";
	}
        this_player()->more(read_file(gScroll_file));
    }
    return 1;
}

/*
 * Function name: reset_scroll
 * Description  : Define this function if you want the scroll to reset at
 *                a certain interval and do not forget to call the function
 *                enable_reset() to initialize the reset-process.
 */
void
reset_scroll()
{
}

/*
 * Function name: reset_object
 * Description  : Reset the scroll. You may not mask this function so you
 *                have to define the function reset_scroll in your scroll.
 */
nomask void
reset_object()
{
    reset_scroll();
}


