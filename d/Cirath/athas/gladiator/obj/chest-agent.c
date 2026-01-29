/*
 * This object is given to players that own some objects that are presently
 * logged by gladiator-chest logger engine. Its purpose is to catch
 * linkdying/reviving, and quitting of a player. It does not shadow the
 * player, it just reports the events the player object calls in it.
 * 
 * Valen, Feb 2003
 */

inherit "/std/object";

#include <files.h>
#include <macros.h>

#include "defs.h"

static string owner = "Nobody";

/*
 * Set all properties to make the object as invisible as possible
 */

public void
create_object(void)
{
    set_name("_chest_logger_agent_");
    set_short("chest logger agent");
    set_long("You should never see this.\n");
    set_no_show();
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

/*
 * This function is supposed to set name of the owner, when the object
 * enters a player. It is then used when calling the reporting functions.
 */
 
public void
enter_env(object to, object from)
{
    if(to && IS_PLAYER_OBJECT(to))
        owner = capitalize(to->query_real_name());
    ::enter_env(to, from);
}

/*
 * This function is called when player carrying this object linkdies/revives,
 * we just report the fact to the logger.
 */

public void
linkdeath_hook(object who, int ld)
{
    CHEST_LOGGER->report_linkdeath(owner, ld);
}

/*
 * We use remove_object function to know when the player is destructed,
 * that is most likely caused by quitting the game.
 */

public void
remove_object(void)
{
    if(!IS_CLONE) return;
    CHEST_LOGGER->report_quit(owner);
    ::remove_object();
}

/*
 * This is dug up from the mudlib - when a living dies, all objects in
 * its inventory have this property added. We use that to detect death
 * of our guinea pig.
 */

public void
add_prop_obj_o_looted_in_room()
{
    CHEST_LOGGER->report_death(owner);
    /* Never destruct an item in an add-prop handler! Use an alarm. */
    set_alarm(0.0, 0.0, remove_object);
}
