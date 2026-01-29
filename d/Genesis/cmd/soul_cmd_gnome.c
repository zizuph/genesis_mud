/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

/*
 * /d/Genesis/cmd/soul_cmd_gnome.c
 *
 * This is the soul command object for Gnome. 
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/cmd/soul";

#include <cmdparse.h>
#include <files.h>
#include <stdproperties.h>

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 *
 * This function is outcommented while there are no special commands in it.
 */
mapping
query_cmdlist()
{
    /* We add rsay here because rsay is now in the speech soul. */
    return ::query_cmdlist() +
        ([
           "rsay":"rsay",
        ]);
}

/* **************************************************************************
 * Here follows the actual functions. Please add new functions in the 
 * same order as in the function name list.
 * **************************************************************************/

/* **************************************************************************
 * rsay - gnomish speech.
 */

/*
 * Function name: rsay_to
 * Description  : This function is called whenever the player starts his
 *                say-string with 'to'. This usually indicates that the
 *                player wants to say something to some people in particular.
 *                All others will still hear it though.
 * Arguments    : string str - the text to say (not including 'to').
 * Returns      : int 1/0 - success/failure.
 */
public int
rsay_to(string str)
{
    object *oblist;
    string say_string;
    string to_string;

    /* We must parse the lower case of the string 'str' since parse_command
     * does not find capitalized player names, so it would not trigger on
     * "say to Mercade Greetings!" However, since we want to keep the
     * capitals in the said text, we store the original text in the variable
     * 'say_string' and use that later.
     */
    say_string = str;
    if (!parse_command(lower_case(str), environment(this_player()),
        "[the] %l %s", oblist, str))
    {
        return 0;
    }

    oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player(), 0 });
    if (!sizeof(oblist) ||
        !strlen(str))
    {
        return 0;
    }

    to_string = extract(say_string, 0, (strlen(say_string) - strlen(str) - 1));
    say_string = extract(say_string, -(strlen(str)));
    say_string = implode(map(explode(say_string, " "), capitalize), "");

    /* We need to do this so that people don't write their own VBFC. */
    while(wildmatch("*@@*", say_string))
    {
        say_string = implode(explode(say_string, "@@"), "#");
    }

    return CMD_LIVE_SPEECH->remote_rsay_to((to_string + say_string));
}

int
rsay(string str)
{
    mixed tmp;

    if (!strlen(str))
    {
        notify_fail("Say what in your racial tongue?\n");
        return 0;
    }

    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot speak.\n");
        return 1;
    }

    /* This is a test for the command 'rsay to'. If it fails, we just default
     * to the normal rsay.
     */
    if (wildmatch("to *", str))
    {
        if (rsay_to(extract(str, 3)))
        {
            return 1;
        }
    }

    str = implode(map(explode(str, " "), capitalize), "");

    /* We need to do this so that people don't write their own VBFC. */
    while(wildmatch("*@@*", str))
    {
        str = implode(explode(str, "@@"), "#");
    }

    return CMD_LIVE_SPEECH->say_text(str);
}
