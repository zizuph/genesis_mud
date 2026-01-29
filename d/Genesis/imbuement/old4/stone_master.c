/*
 *  /d/Genesis/imbuement/stone_master.c
 *
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
//#include <stdproperties.h>
#include <composite.h>
#include "imbuement.h"
//#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function name:        try_combine
 * Description  :        Allow the player to combine three of the same
 *                       stones together to upgrade to the next level of
 *                       quality.
 * Arguments    :        string arg - What was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
try_combine(string arg)
{
    object  *stones, *matches, newstone;
    string  stonequal, stonetype, stoneshort, upgrade;
    string  *availtype = ({}), *availqual = ({});
    string  *matchtype = ({}), *matchqual = ({});
    mapping types = ([]);
    int     got, num;

    if (!strlen(arg))
    {
        notify_fail("What do you wish to combine?\n");
        return 0;
    }

    if (!wildmatch("*stone*", arg))
    {
        notify_fail("What do you wish to combine?\n");
        return 0;
    }

    if (!wildmatch("*stones*", arg))
    {
        notify_fail("Do you wish to combine some stones?\n");
        return 0;
    }
    
    if (!parse_command("_imbuement_container_stone", this_player(),
        "%i", stones))
    {
        write("You don't have any stones.\n");
        return 1;
    }
    
    if (!objectp(stones[0]))
        stones -= ({stones[0]});

    got = parse_command(arg, stones, "[the] [three] %i [together]", matches);

    if (got)
        if (!objectp(matches[0]))
            matches -= ({matches[0]});

    foreach(object stone: stones)
    {
        stonequal = stone->query_stone_quality();
        stonetype = stone->query_stone_type();
        stoneshort = stonequal + " " + stonetype + "s";
        stonetype += "s";
        num = types[stoneshort];
        types[stoneshort] = ++num;
        if (member_array(stone, matches) >= 0)
        {
            if (member_array(stonetype, matchtype) == -1)
                matchtype += ({stonetype});
            if (matchtype[0] == stonetype)
                if (member_array(stonequal, matchqual) == -1)
                    matchqual += ({stonequal});
        }
        if ((num == 3) && (stonetype != "nullstones") && 
            (stonequal != "glittering"))
        {
            if (member_array(stonetype, availtype) == -1)
                availtype += ({stonetype});
            if (sizeof(matchtype) == 1)
                if (matchtype[0] == stonetype)
                    if (member_array(stonequal, availqual) == -1)
                        availqual += ({stonequal});
        }
    }
/*    dump_array(stones);
    dump_array(matches);
    dump_mapping(types);
    dump_array(availtype);
    dump_array(matchtype);
    dump_array(availqual);
    dump_array(matchqual);*/

    if (!got)
    {
        write("You don't have that. ");
    }

    if ((sizeof(matchtype) == 1) && (matchtype[0] == "nullstones"))
    {
        write("Nullstones may not be combined with one another.\n");
        return 1;
    }

    if (!sizeof(availtype))
    {
        write("You don't have enough of any type of stone.\n");
        return 1;
    }

    if (sizeof(matchtype) != 1)
    {
        write("Which stones do you wish to combine? You have " + 
            COMPOSITE_WORDS(availtype) + " in sufficient quantity.\n");
        return 1;
    }

    if ((sizeof(matchqual) != 1))
    {
        write("You have " + COMPOSITE_WORDS(availqual) + " " + matchtype[0] +
            " in sufficient quantity. Which did you wish to combine?\n");
        return 1;
    }

    stonequal = matchqual[0];
    stonetype = matches[0]->query_stone_type();
    stoneshort = stonequal + " " + stonetype + "s";

    num = types[stoneshort];
    
    if (num < 3)
    {
        write("You need three identical stones to combine them.\n");
        return 1;
    }

    switch(stonequal)
    {
        case "cracked":
            upgrade = "blemished";
            break;
        case "blemished":
            upgrade = "ordinary";
            break;
        case "ordinary":
            upgrade = "unblemished";
            break;
        case "unblemished":
            upgrade = "glittering";
            break;
        case "glittering":
            write("You place three " + stoneshort
              + " together in your hands, but nothing happens.\n");
            return 1;
            break;
    }

    write("You combine "
      + (num == 3 ? "your three " : "three of your ")
      + stoneshort + " together in your hands. As you do, they pulse"
      + " brilliantly for a brief instant and then meld together to create"
//      + " a single " + ((upgrade == "ordinary") ? "" : upgrade) + " "
      + " a single " + upgrade + " "
      + stonetype + ".\n");

    newstone = clone_object(MASTER_OB(matches[0]));
    TELL_G("We cloned the stone.");
    newstone->set_stone_type(stonetype);
    TELL_G("We set the type.");
    newstone->set_stone_quality(upgrade);
    TELL_G("We set the quality.");

    IMBUE_LOGGER->log("stones", capitalize(this_interactive()->
        query_real_name()) + " combined " + matches[0]->short() + "s.");

    IMBUE_LOGGER->log("combinestones", capitalize(this_interactive()->
        query_real_name()) + " combined " + matches[0]->short() + "s.");

    if (newstone->move(this_player(), 1))
    {
        TELL_G("We failed to move it.");
        write("Oops! You dropped the " + newstone->short() + "!\n");
        tell_room(environment(this_player()),
            QCTNAME(this_player()) + " drops something shiny!\n");
        newstone->move(environment(this_player()));
    }
    
    for (num = 0; num < 3; num++)
    {
        matches[num]->remove_object();
    }
/*
    TELL_G("Trying to get rid of the stones.");
    if (stone == this_object())
    {
        TELL_G("The stone was - stone.");
        matches[0]->remove_object();
        TELL_G("Removed matches[0]");
        matches[1]->remove_object();
        TELL_G("Removed matches[1]");
        Stone_Removal = 1;
        set_alarm(0.1, 0.0, remove_object);
        TELL_G("Removed this_object()");
    }

    if (matches[0] == this_object())
    {
        TELL_G("The stone was - matches[0]");
        matches[1]->remove_object();
        stone->remove_object();
        remove_object();
    }

    if (matches[1] == this_object())
    {
        TELL_G("The stone was - matches[1]");
        matches[0]->remove_object();
        stone->remove_object();
        remove_object();
    }

    if (!Stone_Removal)
    {
        TELL_G("The stone was none of them.");
        matches[0]->remove_object();
        matches[1]->remove_object();
        stone->remove_object();
    }
*/
    return 1;
} /* combines_stones */
