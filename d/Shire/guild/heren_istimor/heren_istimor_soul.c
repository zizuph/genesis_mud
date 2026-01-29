/* /d/Shire/guild/heren_istimor/heren_istimor_soul.c

 Heren Istimor soul 
 occ Illusionist/Enchanter
 by Palmer, January 2003


*/

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "heren_istimor.h"
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>

#define MORE(x)    this_player()->more(read_file(x, 2))



public string
get_soul_id()
{
    return "Heren Istimor";
}

public int
query_cmd_soul()
{
    return 1;
}

public mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([

      "help"        :    "help",
      "hlook"       :    "hlook",
    ]);
}

// Begin Commands:

public int
hlook(string str)
{
    string *dirs, *exits;
    int exit_nbr;
    object room;
    mixed people, things;

    // TODO: Convert n to north, u to up etc.

    // Get array of obvious exits
    dirs = (environment(TP))->query_obvious_exits();

    // Get array of rooms
    exits = (environment(TP))->query_exit_rooms();

    // Check if they are looking in a valid direction.
    exit_nbr = member_array(str, dirs);
    if (exit_nbr == -1)
    {
        if (str != "here")
        {
            write ("Look where?\n");
            all (" looks confused.\n");
            return 1;
        }
    }

    // Find room object matched to exit
    if (str == "here")
        room = environment(TP);
    else
        room = find_object(exits[exit_nbr]);

    // Get array of people in room
    people = FILTER_LIVE(all_inventory(room));
    things = FILTER_DEAD(all_inventory(room));

    write("You look at the '" + str + "' exit:\n");
    all(" looks " + str + ".\n");

    // Show room long description
    write (room->long());

    // Show people, if any
    if (sizeof(people))
    {
         write(COMPOSITE_LIVE(people) + ".\n");
    }

    // Show things on ground, if any
    if (sizeof(things))
    {
         write(COMPOSITE_DEAD(things) + ".\n");
    }

    return 1;
}



int
help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
        case "heren":
            MORE(HEREN_ISTIMOR_HELP + "general");
            TP->catch_tell("And please report any problems you may encounter "+
              "with "+HEREN_ISTIMOR_GUILD_NAME+" to "+
              COMPOSITE_WORDS(map(HEREN_ISTIMOR_GUILD_MASTER, capitalize)) + ".\n");
        break;
        case "heren guild":
            MORE(HEREN_ISTIMOR_HELP + "guild");
        break;
        case "heren emotes":
        case "heren emotions":
            MORE(HEREN_ISTIMOR_HELP + "emotes");
        break;
        case "heren spells":
            MORE(HEREN_ISTIMOR_HELP + "spells");
        break;
        case "heren titles":
            MORE(HEREN_ISTIMOR_HELP + "titles");
        break;
        case "heren news":
            MORE(HEREN_ISTIMOR_HELP + "news");
        break;
        default:
        return 0;
    }
    return 1;
}
