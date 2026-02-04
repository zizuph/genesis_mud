/*
 * kob_lair_pit.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "include/cave_defs.h"

inherit KOB_LAIR_PATH + "default_kob_lair";

/*
 * Function name: create_room
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void 
create_room()
{
    ::create_room();
    set_short("Deep pit");
    set_long("A deep pit with rough cut walls. Spikes and stakes "
      + "half embedded in the ground point upward to savagely " 
      + "damage those who fall.\n");
 
    reset_room();
}

/*
 * Function name: init
 * Description  : add room actions for player
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    add_action("climb_up", "climb");
    ::init();
}

/*
 * Function name: climb_up
 * Description  : Move the player out of the pit
 * Arguments    : n/a
 * Returns      : 1 success/0 not found
 */
public int
climb_up(string text)
{
    if (text == "up" || text == "out")
    {
        object player = this_player();
        tell_room(environment(player), player->query_name() + " climbs " +
        "up out of the hole.\n", player);
        player->catch_tell("You climb out of the hole.\n"); 
        player->move(KOB_LAIR_PATH + "kob_lair_a03");
        return 1;
    }
    return 0;
}