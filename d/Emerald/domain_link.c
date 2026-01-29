/*
 * This file used by the mudlib when the game boots and goes down.
 */

inherit "/std/domain_link";

/*
 * Function name: preload_link
 * Description:   Build a list of objects that should be loaded
 *                before the first player enters the game.
 */
public void
preload_link()
{
//  preload("/d/Emerald/census/census_master");
    preload("/d/Emerald/sys/global/clock");
    preload("/d/Emerald/sys/global/scheduler");
    preload("/d/Emerald/sys/global/faction_handler");
    preload("/d/Emerald/common/guild/vamp/log/manager");
    preload("/d/Emerald/common/guild/vamp/log/lair_manager");
//  preload("/d/Emerald/docks/sparkle/dock");
//  preload("/d/Emerald/docks/faerie/dock");
//  preload("/d/Emerald/docks/terel/dock");
//  preload("/d/Emerald/docks/telberin/dock");
//  preload("/d/Emerald/docks/ship_mgr");
    preload("/d/Emerald/telberin/dock/telberin_dock");
    preload("/d/Emerald/telberin/dock/ferry_dock");

    preload("/d/Emerald/telberin/clone_handler");

    /* These rooms contain the torques set up by Formandil */
    preload("/d/Emerald/blackwall/delrimmon/tomb");
    preload("/d/Emerald/blackwall/delrimmon/lakeside/caves/tower_entry");
    preload("/d/Emerald/blackwall/delrimmon/rath_lookout");
    preload("/d/Emerald/telberin/telberin_lookout");
    preload("/d/Emerald/blackwall/delrimmon/western_plains_lookout");

    preload("/d/Emerald/sys/global/player_id");
    preload("/d/Emerald/common/guild/aod/obj/master");
}
