/*
 * Base object for all Shire rooms. It includes the timeroom.c which
 * allows one to do the command 'time' in the Shire. Also, the
 * functions
 *	add_vision, add_neg, add_cmd, add_call and add_tell
 * are included.
 */

inherit "/d/Shire/common/lib/timeroom";

#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

mixed *room_alias;

/*
 * Function name:   add_vision
 * Arguments:	    direction	- As for the add_exit_fun.
 *				  or a rooms file name.
 *		    ids 	- Array of identifying strings.
 *		    descr	- The description text.
 * Description:     Adds a direction in which you can see.
 */
varargs void
add_vision(string dir, mixed ids, string desc)
{
    if (!dir)
	return;

    if (stringp(ids))
	ids = explode(ids, "|");

    if (!sizeof(ids))
	ids = ({});

    if (!strlen(desc))
	desc = "@@describe_room|"+dir+"@@";
    else if(desc[-1..-1]==" ")
	desc += "@@describe_room|"+dir+"@@";
    else
	desc += " @@describe_room|"+dir+"@@";

    add_item(({dir, dir+" exit", dir+"ern exit", "exit "+dir}) + ids,
	desc);
}

/*
 * Function name:   describe_room
 * Arguments:	    direction
 */
string
describe_room(string dir)
{
    object *ob;
    mixed room;
    string str;
    int pos;

    pos = member_array(dir, room_exits);

    if (pos == -1)
    {
	room = dir;
	dir = "in that room";
    }
    else if (pos >= 0 && (pos % 3 == 0))
    {
	dir = "in the " + room_exits[pos+1];
	room = room_exits[pos];
    }
    else
    {
	dir = "in the " + dir;
	room = room_exits[pos-1];
    }

    if (LOAD_ERR(room))
	return "You see nothing special there.";

    room = find_object(room);

    if (!room)
	return "You see nothing special there.";

    if (room->query_prop(OBJ_I_LIGHT) <= 0)
	return "It is dark " + dir + ", so you can't percieve any details.";

    ob = FILTER_CAN_SEE(all_inventory(room), TP);

    if (!sizeof(ob))
	return "You can't see anything special " + dir + ".";

    return CAP(dir) + " you can see: "
	 + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".";
}

string
desc(object ob)
{
    if (living(ob))
	return LANG_ADDART(ob->query_race_name());
    else
	return LANG_ASHORT(ob);
}

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
    room_alias = add_cmd_list(room_alias, ({ action, form, 0, cmd, nf }));
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
    room_alias = add_cmd_list(room_alias, ({ action, form, 1, neg, nf }));
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
    room_alias = add_cmd_list(room_alias, ({ action, form, 2, call, nf }));
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
 *	    "(You) smell[s] the reek of cookies in the air.\n" +
 *	    "{Ah!! Smells wonderful!;(He) smiles as [he] inhales the reek.}\n");
 */
varargs void
add_tell(mixed action, string form, string tell, string nf)
{
    (STAND_LIB + "tell")->load_me();
    room_alias = add_cmd_list(room_alias, ({ action, form, 3, tell, nf }));
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

	if (strlen(elem[4]))
	    notify_fail(elem[4]);
	else
	    notify_fail(CAP(verb) + " what?\n");

	if (strlen(elem[1]) && !parse_command(rest, ({}), elem[1]))
	    continue;

	switch (elem[2])
	{
	    case 0:
		TP->command(elem[3]);
		return 1;
	    case 1:
		write(elem[3]);
		return 1;
	    case 2:
		call_other(TO, elem[3], rest);
		return 1;
	    case 3:
		(STAND_LIB + "tell")->tellem(TP, 0, elem[3], 1);
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
