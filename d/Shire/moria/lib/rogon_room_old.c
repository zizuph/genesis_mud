#include "../defs.h"

inherit ROOT_ROOM;

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

/*
 * Global variables.
 */

int my_exit_desc_mode;	/* Want my exit description way? */


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
create_room()
{
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    set_short_dirs();

    TO->create_rogon_room();

//    if (my_exit_desc_mode)
//	set_noshow_obvious(1);

}

/*
 * Function name:   reset_room
 * Description:     Calls reset_rom()
 */
reset_room() {
    TO->reset_rogon_room();
}

/*
 * Function name:   set_long
 * Arguments:	    str     - string for add_items.
 * Description:     Strips trailing newline and adds a space if needed.
 */
void
set_long(string str)
{
    if (str[-1..-1]=="\n")
	str = str[0..-2]+" ";

    else if(str[-1..-1]!=" ")
	str += " ";

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
 * Function name:   MASKED long()
 * Description:     Handles the indentanation of room exits.
 */
varargs public mixed
long(string sob)
{
    if (strlen(sob))
	return ::long(sob);

    if (!my_exit_desc_mode)
	return ::long() + "\n";

    if (!sizeof(room_exits))
	return ::long()
	     + "\n    There are no obvious exits.\n";
    else
	return ::long()
	     + "\n    "+exits_description();
}

#define DIR  ([	"north":"n", "south":"s", "east":"e", "west":"w",\
		"northeast":"ne", "northwest":"nw",\
		"southeast":"se", "southwest":"sw",\
		"up":"u", "down":"d" ])

string
direction(string dir)
{
    return DIR[check_call(dir)];
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

    if (!my_exit_desc_mode)
	return ::short();

    if (!sizeof(exits))
       return CAP(check_call(obj_short)) + " (No exits)";

    return check_call(obj_short)
	 + " (" + implode(map(exits, "direction", TO), ",") + ")";
}

#define COM_VERBS 0
#define COM_ARGS  1
#define COM_TYPE  2
#define COM_CMD   3
#define COM_FAIL  4

#define TYPE_CMD  0
#define TYPE_NEG  1
#define TYPE_CALL 2
#define TYPE_TELL 3

mixed *room_alias;

/*
 * Function name:   add_cmd_list
 * Description:     Common routine to add_cmd/call/neg/tell.
 * Arguments:	    list    - list of elements
 *		    elem    - the element
 */
string *
add_cmd_list(string *list, mixed *elem)
{
    int i;

    if (obj_no_change)
	return list;

    if (!pointerp(list))
	list = ({});

    if (pointerp(elem[0]))
    {
	for (i=0; i<sizeof(elem[0]); i++)
	    list = add_cmd_list(list,
		({ elem[0][i], elem[1], elem[2], elem[3], elem[4] }));
	return list;
    }

    list = list + ({ elem });
    return list;
}

/*
 * Function name:   add_cmd
 * Arguments:	    action  - action to add
 *		    form    - string to parse_command
 *		    cmd     - what command to perform
 *		    nf	    - notify_fail message.
 *
 * Description:     This command adds a command which if the arguments
 *		    match with form will call TP->command(command).
 *		    If not, the errmsg will be notified.
 * Examples:
 *	add_cmd("swim", "[into] [in] [the] 'lake' / 'water'", "down", "Swim where?\n");
 *	add_cmd(({"climb", "jump"}), "[up] [the] 'tree' / 'up'", "up");
 */
varargs void
add_cmd(mixed action, string form, string cmd, string nf)
{
    room_alias = add_cmd_list(room_alias, ({ action, form, TYPE_CMD, cmd, nf }));
}

/*
 * Function name:   add_neg
 * Arguments:	    action  - action to add
 *		    form    - string to parse_command
 *		    neg     - The negative string to output.
 *		    nf	    - notify_fail message.
 * Examples:
 *	add_neg("smell", "[reek] [of] 'cookies'", "Ah, smells marvelous!\n");
 */
varargs void
add_neg(mixed action, string form, mixed neg, string nf)
{
    room_alias = add_cmd_list(room_alias, ({ action, form, TYPE_NEG, neg, nf }));
}

/*
 * Function name:   add_call
 * Arguments:	    action  - action to add
 *		    form    - string to parse_command
 *		    call    - the function to call
 *		    nf	    - notify_fail message.
 * Examples:
 *	add_call("smell", "[reek] [of] 'cookies'", "smell_cookies");
 *	.
 *	.
 *
 * int
 * smell_cookies(string arg)
 * {
 *     write("You smell the reek of cookies in the air.\n"
 *	   + "Ah!! Smells wonderful!\n");
 *     say(QCTNAME(TP) + " smells the reek of cookies in the air.\n"
 *	 + QCTNAME(TP) + " smiles as " + HE_SHE(TP) + " inhales the reek.\n");
 *     return 1;
 * }
 *
 */
varargs void
add_call(mixed action, string form, string call, string nf)
{
    room_alias = add_cmd_list(room_alias, ({ action, form, TYPE_CALL, call, nf }));
}

/*
 * Function name:   add_tell
 * Arguments:	    action  - action to add
 *		    form    - string to parse_command
 *		    tell    - What to tell the room (tellem-style)
 *		    nf	    - notify_fail message.
 *
 * Description:     Uses the special tellem style used by Rogon to print
 *		    out messages in the room. See the file
 *		    /d/Shire/common/lib/tell.c for an explanation of
 *		    syntax.
 *
 * Examples:
 *
 *	add_tell("smell", "[reek] [of] 'cookies'",
 *	    "$You $smell the reek of cookies in the air.\n" +
 *	    "${Ah!! Smells wonderful!;$Name smiles as $he inhales the reek.}\n");
 */
varargs void
add_tell(mixed action, string form, string tell, string nf)
{
    TELL_FILE->load_me();
    room_alias = add_cmd_list(room_alias, ({ action, form, TYPE_TELL, tell, nf }));
}

/*
 * Function name:   init
 * Description:     adds the commands in room_alias
 */
init()
{
    int i;
    ::init();

    for (i=0; i<sizeof(room_alias); i++)
	add_action("do_room_alias", room_alias[i][0]);
}

/*
 * Function name:   do_room_alias
 * Arguments:	    rest    - The rest after the verb.
 * Description:     Checks the room_alias variable and acts accordingly.
 */
int
do_room_alias(string rest)
{
    string verb;
    mixed *list;
    mixed *elem;
    int i;

    verb = query_verb();
    list = filter(room_alias, "match_verb", TO, verb);

    if (!sizeof(list))
	return 0;

    if (!strlen(rest))
	rest = "";

    for (i=0; i<sizeof(list); i++)
    {
	elem = list[i];

	if (sizeof(elem) != 5)
	    continue;

	if (strlen(elem[COM_FAIL]))
	    notify_fail(elem[COM_FAIL]);
	else
	    notify_fail(CAP(verb) + " what?\n");

	if (strlen(elem[COM_ARGS]) && !parse_command(rest, ({}), elem[COM_ARGS]))
	    continue;

	switch (elem[COM_TYPE])
	{
	    case TYPE_CMD:
		TP->command(elem[COM_CMD]);
		return 1;
	    case TYPE_NEG:
		write(elem[COM_CMD]);
		return 1;
	    case TYPE_CALL:
		return call_other(TO, elem[COM_CMD], rest);
	    case TYPE_TELL:
		TELL_FILE->tellem(TP, 0, elem[COM_CMD], 1);
		return 1;
	}
    }
    return 0;
}

int
match_verb(mixed elem, string verb)
{
    return elem[0]==verb;
}
