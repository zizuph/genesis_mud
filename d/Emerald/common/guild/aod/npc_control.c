/*
 *  /d/Emerald/common/guild/aod/darkling_control.c
 *
 *  This is the room to control a Darkling npc to interact with players.
 *  It allows a wizard (who has permission) to use a Darkling for
 *  thematic purposes in Emerald.
 *
 *  Created February 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <macros.h>             /* for QNAME, etc               */
#include "defs.h"


/* Prototypes */
public void        create_room();
public void        init();
public int         ddtell(string arg);
public int         ddcommand(string arg);
public int         ddsummon(string arg);


/* Global Variables */
public object      Darkling;


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_short("the Darkling control room");
    set_long("This is the NPC Control Room. If you have not been"
      + " invited to be here, you probably should leave. This is a"
      + " room which allows certain wizards to control an npc to"
      + " roleplay with a player.\n\n"
      + "\tCommands:\n\n"

      + "\t<nc [command]>           Send the npc an action command\n"
      + "\t<nbring [name]>          Summon the npc to the location of\n"
      + "\t                         a certain player (can only be done\n"
      + "\t                         once)\n");

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(ddcommand, "nc");
    add_action(ddsummon, "nbring");
} /* init */


/*
 * Function name:        ddtell
 * Description  :        Print a message from a Darkling to a player
 *                       or a room full of players.
 * Arguments    :        string arg - whatever was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
ddtell(string arg)
{
    string   who,
             text;
    object  *occupants,
             old_this_player,
            *targets;

    if (this_player()->query_name() != "Gorboth" ||
        this_player()->query_name() != "Petros")
    {
        notify_fail("You do not have permission to do that.\n");
        return 0;
    }

    notify_fail("Useage: <dtell playername/room text>\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}), "%w %s", who, text))
    {
        return 0;
    }

    if (who == "room")
    {
        if (!objectp(Darkling))
        {
            notify_fail("There must be a Darkling in a room first.\n");
            return 0;
        }

        targets = FILTER_LIVE(all_inventory(environment(Darkling)));

        foreach(object target: targets)
        {
            set_this_player(target);
            DARKLING_TELL(text);
        }

        return 1;
    }

    old_this_player = this_player();
    set_this_player(find_living(who));
    DARKLING_TELL(text);

    set_this_player(old_this_player);

    return 1;
} /* ddtell */


/*
 * Function name:        ddcommand
 * Description  :        send a command to the Darkling, if it has been
 *                       summoned. Fails if no Darkling exists.
 * Arguments    :        string arg - the command for the darkling
 * Returns      :        1 - success, 0 - failure
 */
public int
ddcommand(string arg)
{
    if (!objectp(Darkling))
    {
        notify_fail("There is no Darkling yet to command.\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("What command do you wish to send to the Darkling?\n");
        return 0;
    }

    if (this_player()->query_name() != "Gorboth" &&
        this_player()->query_name() != "Petros")
    {
        notify_fail("You do not have permission to do that.\n");
        return 0;
    }

    write("Command sent.\n");
    Darkling->command(arg);
    return 1;
} /* ddcommand */


/*
 * Function name:        ddsummon
 * Description  :        summon a Darkling and move it to the location
 *                       of a particular player. If the Darkling already
 *                       exists, we don't summon a new one, but rather
 *                       move the old one to a new location.
 * Arguments    :        string arg - Whatever was typed following the
 *                       verb. Typically this will be the name of the
 *                       player to move the Darkling to. However, if the
 *                       argument is instead the word "goodbye" we remove
 *                       the Darkling from the game.
 * Returns      :        int 1 - success, 0 - failure
 */
public int
ddsummon(string arg)
{
    object  player;

    if (this_player()->query_name() != "Gorboth" &&
        this_player()->query_name() != "Petros")
    {
        notify_fail("You do not have permission to do that.\n");
        return 0;
    }

    if (arg == "goodbye")
    {
        if (!objectp(Darkling))
        {
            notify_fail("No Darkling has been summoned!\n");
            return 0;
        }

        tell_room(environment(Darkling),
            "Turning slowly, " + QTNAME(Darkling) + " walks silently"
          + " out of view.\n");
        Darkling->remove_object();
        return 1;
    }

    if (strlen(arg))
    {
        player = find_player(lower_case(arg));
    }
    else
    {
        notify_fail("You must specify a player to move the Darkling"
          + " to, or \"goodbye\" to remove the Darkling from the game.\n");
        return 0;
    }

    if (!objectp(player))
    {
        notify_fail("There is no such player to move the Darkling to!\n");
        return 0;
    }

    if (objectp(Darkling))
    {
        tell_room(environment(Darkling),
            "Smiling slightly, " + QTNAME(Darkling) + " steps around"
          + " a corner, and is gone.\n");
    }
    else
    {
        Darkling = clone_object("/d/Terel/guilds/vamp/npc/isabella");
        write("Summoned.\n");
    }

    tell_room(environment(player),
            QCTNAME(Darkling) + " steps from around a corner.\n");

    Darkling->move_living("M", environment(player), 1, 0);
    write("Moved.\n");
    return 1;
} /* ddsummon */
