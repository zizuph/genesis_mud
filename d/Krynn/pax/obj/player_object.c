/* 
 * This is the player object, all players in Pax Tharkas should have one,
 * or certain events will not occur.
 *
 * 950401 by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit  "/std/object";

void
create_object()
{
    set_name(({"player object", "_pax_player_"}));

    set_no_show();

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

nomask public void
enter_env(object to, object from)
{
    if ((IS_PAXPLAYER(to) != TO) || !query_ip_number(to))
	remove_object();

    PAXMASTER->add_player(to->query_real_name());

    ::enter_env(to, from);
}

nomask public void
leave_env(object from, object to)
{
    if (from)
	if (query_ip_number(from))
	    PAXMASTER->remove_player(from->query_real_name());

    ::leave_env(from, to);
}
