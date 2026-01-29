/* File         : /d/Khalakhor/guilds/lore/obj/soul.c
 * Creator      : Teth@Genesis
 * Date         : Dec 29, 2001
 * Purpose      : This is the command soul of the Lore Seekers.
 * Related Files:
 * Comments     :
 * Modifications:
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../local.h"
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/skills.h"

public void identify(object obj);

public int
query_cmd_soul()
{
    return 1;
}

public string
get_soul_id()
{
    return "Seekers of An Seann Firinne";
}



varargs int
light_fail(string str)
{
    string s;

    if (!strlen(str))
        str = query_verb() + " things";
    if (!stringp(s = environment(this_player())->query_prop(ROOM_S_DARK_MSG)))
        notify_fail("It is too dark to " + str + ".\n");
    else
        notify_fail(s + " " + str + ".\n");
    return 0;
}

/*
 * Function name: get_lore_info
 * Description:   Return a string describing the lore information
 *                of an item, up to a certain level.
 * Arguments:     object target - the item to identify
 *                int max_level - the level of info you want
 *                (see OBJ_AM_LORE_INFO)
 * Returns:       the description
 */
public string
get_lore_info(object target, int max_level)
{
    mixed *info;
    int level, i;
    string desc, msg = "";

    info = target->query_prop(OBJ_AM_LORE_INFO);

    for (i = 0; i < (sizeof(info) - 1); i += 2)
    {
        if (intp(info[i]))
	{
            level = info[i];
            desc  = info[i + 1];
	}
        else if (intp(info[i + 1]))
	{
            level = info[i + 1];
            desc  = info[i];
	}
        else
	{
            break;
	}

        if (level <= max_level)
	{
            msg += desc;
	}
    }

    return msg;
}

/*
 * Function name: identify
 * Description:   Evaluate how well the player knows an object
 * Arguments:     int result      - the player's lore skill
 */
public void
identify(object obj)
{
    string msg;
    int result;

    result = this_player()->query_skill(SS_KHALAKHOR_LORE);

    msg = get_lore_info(obj, result);

    if (strlen(msg))
    {
        this_player()->catch_tell(msg);
    }
    else
    {
        this_player()->catch_tell("You fail to recall any lore.\n");
    }

}


/***********************************************************************
* The list of verbs and functions. Please add new in alphabetical order.
***********************************************************************/

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([
      "sfhelp":    "do_help",
      "sfstudy":   "do_lore"
           ]);
}


/********************* help ********************************************/
int
do_help(string str)
{
    string subject, filename;

    if (!str)
	return 0;

	if (sscanf(str, "sfhelp %s", subject) != 1)
		return 0;


    filename = HELP_DIR + subject;
    if (file_size(filename) > 0)
    {
	setuid();
	seteuid(getuid());
	cat(filename);
	return 1;
    }
    notify_fail("No help on that subject I'm afraid.\n");
    return 0;
}

/********************* lore ********************************************/
int
do_lore(string str)
{
    object *ob;
    int i;

    if (CAN_SEE_IN_ROOM(this_player()) <= 0)
        return light_fail("study");

    notify_fail("Study what?\n");
    if (!stringp(str))
        return 0;

    ob = FIND_STR_IN_OBJECT(str, this_player());
    if (sizeof(ob) == 0)
        ob = FIND_STR_IN_OBJECT(str, environment(this_player()));

    if (sizeof(ob) == 0)
        return 0;

    for (i = 0; i < sizeof(ob); i++)
    {
        if (living(ob[i]))
            write("You study " + ob[i]->query_the_name(this_player()) +
                " carefully.\n");
        else
            write("You study " + LANG_THESHORT(ob[i]) + " carefully.\n");
        identify(ob[i]);
    }

    return 1;
}

