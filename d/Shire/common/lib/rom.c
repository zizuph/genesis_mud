inherit "/d/Shire/common/lib/room";

#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

//Prototypes
int sunlight();


/*
 * Global variables.
 */

int my_exit_desc_mode;	/* Want my exit description way? */
mixed *room_alias;	/* The aliases for commands.	 */


/*
 * Function name:   set_short_dirs
 * Arguments:	    set [default = 1] - set short dirs.
 * Description:     Sets the special short-direction format, as well as
 *		    the indented form of the long exit description.
 */
varargs void
set_short_dirs(int set = 1)
{
    my_exit_desc_mode = 1;
}

/*
 * Function name:   create_room
 * Description:     Sets this room to a normal room, and calls create_rom().
 */
nomask void
create_room()
{
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop("_room_i_sunlight",sunlight);

    set_short_dirs();

    TO->create_rom();


    //    if (my_exit_desc_mode)
    //	set_noshow_obvious(1);
}

int
sunlight()
{
    return "/d/Shire/std/room"->query_sunlight();
}

/*
 * Function name:   reset_room
 * Description:     Calls reset_rom()
 */
reset_room() {
    TO->reset_rom();
}

/*
 * Function name:   set_long
 * Arguments:	    str     - string for add_items.
 * Description:     Strips trailing newline and adds a space if needed.
 */
void
set_long(string str)
{
    /*
	if (str[-1..-1]=="\n")
	    str = str[0..-2]+" ";

	else if(str[-1..-1]!=" ")
	    str += " ";
    */
    ::set_long(str+"@@query_extra@@");
}

/*
 * Function name:   query_extra
 * Description:     Can be used for special outputs. Called from vbfc in long.
 */
string
query_extra()
{
    return "";
}

/*
 * Function name:   break_it
 * Description:     breaks a string into a string array on the newlines.
 * Returns:	    Array of lines.
 */
string
break_it(string in, int dist)
{
    return break_string(in, dist);
}

/*
 * Function name:   my_break_string
 * Description:     Similar to break_string, but fixes newline-chars.
 */
varargs string
my_break_string(string str, int dis = 70)
{
    string *exp;
    string *brk;

    exp = explode(str, "\n");

    if (sizeof(exp) == 1)
	return break_string(str, dis);

    brk = map(exp, "break_it", TO, dis);

    return (str[0..0]=="\n"?"\n":"")
    + implode(brk, "\n")
    + (str[-1..-1]=="\n"?"\n":"");
}


/*
 * Function name:   MASKED long()
 * Description:     Handles the indentanation of room exits.
 */
varargs public mixed
long(string sob)
{

    //    if (strlen(sob))
    //	return ::long(sob)+ "\n";
    /*
	if (!my_exit_desc_mode)
	    return ::long() + "\n";

	if (!sizeof(room_exits))
	    return my_break_string(::long())
		 + "\nThere are no obvious exits.\n";
	else

	    return my_break_string(::long())
		 + "\n"+exits_description();
    */
    return ::long(sob);
}

#define DIR  ([	"north":"n", "south":"s", "east":"e", "west":"w",\
		"northeast":"ne", "northwest":"nw",\
		"southeast":"se", "southwest":"sw",\
		"up":"u", "down":"d" ])

string
direction(string dir)
{
    //    return DIR[check_call(dir)];
}

/*
 * Function name:   MASKED short()
 * Description:     Describes the short description.
 *		    It will give a direction path on the form:
 *		    A room (n,e,s,w).
 */
string
short()
{

    string *exits = query_exit_cmds();

    //    if (!my_exit_desc_mode)

    return ::short();
    /*
	if (!sizeof(exits))
	   return CAP(check_call(obj_short)) + " (No exits)";

	return check_call(obj_short)
	     + " (" + implode(map(exits, "direction", TO), ",") + ")";
    */
}
