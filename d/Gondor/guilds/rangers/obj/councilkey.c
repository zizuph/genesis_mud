/*
 * /d/Gondor/guild/rangers/obj/councilkey.c
 *
 * The council object that contains all the council related commands.
 *
 * Gwyneth, June 17, 2001
 */
inherit "/std/key";
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <files.h>         // For SECURITY
#include <macros.h>        // For MASTER
#include <std.h>           // For WIZ_ARCH and WIZ_KEEPER
#include <stdproperties.h> // For added props
#include "../rangers.h"    // For MANAGER

/* Prototype */
public int who_gives();

/* Global var */
int gRcommands = 1;

public void
create_key()
{
    ::create_key();

    add_name("_council_key");
    set_adj("gold");
    set_pshort("gold keys");
    set_long("This is the key to the council-room of the Council of " +
        "Rangers. Only the members of the Council are allowed to " +
        "carry this key.\n\nEngraved in very tiny letters, you see the words " +
        "'help rcouncil'.\n");
    set_key("Council_Key");

    /* Add help strings. Council member will get a list of help
       commands by typing in 'help rcouncil' for example. */
    set_help_type(({ "rcouncil" }));

    /* Where are the council help files located? */
    read_help_dir(RANGERS_HELP + "council/");

    /* Only allow Gondorian wizards and ARCH+ to give away a key. */
    add_prop(OBJ_I_NO_DROP, &who_gives());

    /* It's a very small key. */
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_I_WEIGHT,  1);
    add_prop(OBJ_I_VALUE,   0);
}

/*
 * Function name: enter_env
 * Description  : Mask enter_env to remove the key if the key shouldn't
 *                be with this player. Allows wizards to clone keys.
 * Arguments    : object to - the destination
 *                object from - where it came from
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(from))
        return;

    if (!MANAGER->query_is_council(to->query_real_name()))
    {
        to->catch_tell("As soon as your hand touches the gold key, " +
            "the key melts away.\n");
        set_alarm(0.3, 0.0, &remove_object());
    }

    return;
}

/*
 * Function name: who_gives
 * Description  : Only allow wizards of Gondor, arches and keepers to
 *                give away a council key for security purposes.
 * Returns      : 0 if allowed, 1 if not
 */
public int
who_gives()
{
string name = capitalize(this_interactive()->query_real_name());

    if (SECURITY->query_wiz_dom(this_player()->query_real_name()) == "Gondor" || 
        SECURITY->query_guild_is_master(RANGERS_GUILD_NAME, name))
        return 0;

    switch(SECURITY->query_wiz_rank(this_player()->query_real_name()))
    {
    case WIZ_ARCH:
    case WIZ_KEEPER:
        return 0;
    default:
        return 1;
    }
}

/*
 * Function name: query_recover
 * Description  : The key autoloads, so let's not have it recover at
 *                Armageddon, causing multiple sets.
 */
public string
query_recover()
{
    return 0;
}

/*
 * Function name: query_rcommands
 * Description  : Tests if gRcommands is 1 or 0 for command toggling purposes
 * Returns      : int - gRcommands
 */
public int
query_rcommands()
{
    return gRcommands;
}

/*
 * Function name: set_rcommands
 * Description  : Set the global variable gRcommands to 1 or 0.
 *                This variable allows council commands to be
 *                toggled on and off if a command is interfering
 *                with some other command.
 * Arguments    : string str - empty, "on" or "off"
 * Returns      : int 0/1 - failure/success
 */
public int
set_rcommands(string str)
{
    if (!strlen(str))
        gRcommands = !gRcommands;
    else if (lower_case(str) == "on")
        gRcommands = 1;
    else if (lower_case(str) == "off")
        gRcommands = 0;
    else
    {
        notify_fail("Rcommands [on/off]?\n");
        return 0;
    }

    write("You turn your Ranger Council commands " +
        (gRcommands ? "on" : "off") + ".\n");
    return 1;
}

/*
 * Function name: init
 * Description  : Masks init to add commands to the player.
 */
public void
init()
{
    ::init();

    add_action(_help,         "help");
    add_action(set_rcommands, "rcommands");
}
