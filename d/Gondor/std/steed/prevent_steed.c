/*
   prevent_steed.c
   
   Module to prevent steeds from boarding ships.

   Fysix@Genesis, October 1997
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

// Globals
static int No_steed_allowed;

/* Function name: set_no_allow_steed
 * Description:   Allow steeds on this ship?
 * Arguments:     int 1 don't allow them, 0 allow them
 */
public void
set_no_allow_steed(int i)
{   
    No_steed_allowed = i;
}

/* Function name: query_steed_allowed
 * Description:   Are steeds allowed on this ship?
 * Returns:       int 1 if they are allowed
 */
public int
query_steed_allowed()
{
    return !No_steed_allowed;
}

// Prevent steeds from boarding the ship
public int
query_prevent_board_ship(object player)
{
object steed, captain;

    steed = player->query_prop(LIVE_O_STEED);

    // Check if steeds are allowed on this ship
    if (!objectp(steed) || !No_steed_allowed)
        return 0;
        
    if (objectp(captain = this_object()->query_captain()))
    {
        tell_room(environment(),
            QCTNAME(captain) + " scowls menacingly " +
            "at " + QTNAME(this_player()) + " and blocks " +
            this_player()->query_possessive() + " way.\n",
            this_player());
        write(capitalize(captain->query_the_name(this_player())) +
         	" scowls at you.\n");
        captain->command("say Your " + steed->query_race() +
            " is not allowed on this " + this_object()->short() + ", " +
            this_player()->query_nonmet_name() + ".");
    }
    else
    {
        write("A ship officer prevents you from boarding the "+
            this_object()->short() + ".\n");
        tell_room(environment(), QCNAME(this_player()) + " tries to "+
            "board the " + this_object()->short() + ", but is prevented.\n",
            this_player());
    }
    return 1;
}
