/*
 * Stun/slow special for dwarven guild
 *
 * Idea from dragon fear coded by Erine & Jeremiah.
 * 
 * Coded   : 4/97 by Arman
 * Modified: 16.08.2003 by Blizzard
* 01.07.2005 Louie - Remove stun upon remove_object()
 */

inherit  "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int         time = 20;

object      victim;

public void
create_object() 
{
    seteuid(getuid());
    set_name("dwarven_special_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

/*
init()
{
    ::init();
}
*/

public void
remove_slam(object victim)
{
    object vict = victim; 

    victim->remove_stun();
    
    vict->catch_msg("You feel you have recovered from " +
        "the slam attack.\n");
    tell_room(E(vict), QCTNAME(vict) + " seems to have " +
        "recovered from the slam attack.\n", victim, TO);

    remove_object();
}

public int
set_slam_effect_time(int stun_time)
{
    time = stun_time;
}

public int
query_slam_time()
{
    return time;
}

public void
do_slam()
{
    victim->add_stun();

    set_alarm(itof(time), 0.0, &remove_slam(victim) );

    time = 0;
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if( !objectp(to) )
    {
	remove_object();
	return;
    }

    if( !living(to) )
    {
	remove_object();
	return;
    }

    victim = to;
    do_slam();
}

public int
remove_object()
{
    if (victim)
        victim->remove_stun();

    ::remove_object();
}
