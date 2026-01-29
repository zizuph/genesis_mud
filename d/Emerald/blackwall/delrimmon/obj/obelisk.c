/*
 *  /d/Emerald/blackwall/delrimmon/obj/obelisk.c
 *
 *  This obelisk was created by the Darklings and placed beside
 *  their tower beneath Del Rimmon. Formandil and Maeltar chose
 *  to keep it there, for it proved useful to them as well.
 *
 *  Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/obelisk";

/* prototypes */
public void        create_obelisk();
public int         search_obelisk(string arg);
public void        init();


/*
 * Function name:        create_obelisk
 * Description  :        set up the obelisk
 */
public void
create_obelisk()
{
    set_destination("/d/Emerald/blackwall/delrimmon/lakeside/sw_wood3b");
} /* create_obelisk */


/*
 * Function name:        search_obelisk
 * Description  :        allow the player to search the obelisk, thereby
 *                       touching it
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
search_obelisk(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle the notify_fail */
    }

    if (!parse_command(arg, ({}),
        "[the] [black] 'obelisk'"))
    {
        return 0; /* again, mudlib handles it */
    }

    write("As begin to thoroughly examine the obelisk, your hand"
        + " brushes against its black surface.\n");
    this_player()->command("$touch obelisk");
    if (this_player()->query_wiz_level())
    {
        write("Normally, we would have the player touch the obelisk"
            + " using command. Since you are a wizard, that will not"
            + " work. Simply type 'touch obelisk' yourself.\n");
    }

    return 1;
} /* search_obelisk */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(search_obelisk, "search");
} /* init */
