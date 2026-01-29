/*
 *  /d/Emerald/blackwall/delrimmon/npc/catapult_orc.c
 *
 *  These orcs will happen to notice the breaking catapult, and will
 *  run off to find and guard the arm when it appears on the shoreline.
 *
 *  Coded by Gorboth, May 1997
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/npc/del_rimmon_orc.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon_orc();
public void    add_blackwall_emotes();

/*
 * Function name:        create_del_rimmon_orc
 * Description  :        set up the npc
 */
public void
create_del_rimmon_orc()
{
    Chief = 1;

    add_name("_catapult_orc");

} /* create_del_rimmon_orc */

/*
 * Function name:        add_blackwall_emotes
 * Description  :        we redefine the function to add specific
 *                       emotes for these npcs only
 */
public void
add_blackwall_emotes()
{
    set_chat_time(10 + random(10));
    add_chat("But where did it come from?");
    add_chat("Who cares? We found it, why tell anyone else?");
    add_chat("I say we tell Akugla. He'll roast us if we don't!");
    add_chat("Since when do we care what the others think?");
    add_chat("Akugla ought to know about this!");
    add_chat("So what? Do you want to go tell him? Then go!");
    add_chat("It looks old... old and broken!");
    add_chat("Might make a good club, actually.");
    add_chat("I say we take it for ourselves.");
    add_chat("Maybe it belongs to one of the others... but who'd"
           + " want something like this?");
    add_chat("I'm telling you fools... Akugla would want to know!");
    add_chat("Shut up about Akugla then!");
} /* add_blackwall_emotes */
