inherit "/d/Krynn/guilds/knights/obj/std_rack";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

#include <filter_funs.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <files.h>
#include <wa_types.h>

#define GLOW_RACK_LOG   ("/d/Krynn/guilds/knights/log/glow_rack_log")


int Allow_misc=0;
int Allow_armour=0;
int Allow_weapon=0;
int Allow_glowing=0;
int Allow_nonglowing=0;


/*
 * Function name: prevent_enter
 * Description:   limited items allowed
 */
public int
prevent_enter(object ob)
{
    if (!Allow_glowing && (ob->check_recoverable() ||
        strlen(ob->query_auto_load())))
    {
        return 5;
    }

    if (!Allow_nonglowing && !ob->check_recoverable() &&
        !strlen(ob->query_auto_load()))
    {
        return 5;
    }

    if (!Allow_armour && ob->check_armour())
    {
        return 5;
    }

    if (!Allow_weapon && ob->check_weapon())
    {
        return 5;
    }

    if (!Allow_misc && !ob->check_weapon() && !ob->check_armour())
    {
        return 5;
    }

    return 0;
}

public void set_allow_weapon(int i)
{
    Allow_weapon=i;
}

public void set_allow_armour(int i)
{
    Allow_armour=i;
}

public void set_allow_misc(int i)
{
    Allow_misc=i;
}

public void set_allow_glowing(int i)
{
    Allow_glowing=i;
}

public void set_allow_nonglowing(int i)
{
    Allow_nonglowing=i;
}




/*
* Function name: enter_inv
* Description:   Called when objects enter this container or when an
*                object has just changed its weight/volume/light status.
* Arguments:     ob: The object that just entered this inventory
*                from: The object from which it came.
*/
public void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);

	if (from == this_object())
	{
		return;
	}


        if (from && this_player()) 
            write_file(GLOW_RACK_LOG, this_player()->query_name()
                    + " puts " + ob->query_short() + " into the rack"
                    + " (" + ctime(time()) + ").\n");

	// Step 4. Add add_rack_entry to enter_inv
	add_rack_entry(ob);
}



/*
* Function name: leave_inv
* Description:   Called when objects leave this container or when an
*                object is about to change its weight/volume/light status.
* Arguments:     ob: The object that just left this inventory.
*                to: Where it went.
*/
public void
leave_inv(object ob, object to)
{
	::leave_inv(ob, to);

	if (to == this_object() || !objectp(to))
	{
		// Not actually leaving this container, just return
		return;
	}

	write_file(GLOW_RACK_LOG, this_player()->query_name()
	+ " takes " + ob->query_short() + " from the rack"
	+ " (" + ctime(time()) + ").\n");

	// Step 5. Add remove_rack_entry to leave_inv
	remove_rack_entry(ob);
}


nomask void
create_container()
{
    if(!IS_CLONE)
        return;

    add_prop(OBJ_M_NO_GET, "You are unable to take that.\n");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT,99999999);
    add_prop(CONT_I_MAX_VOLUME,99999999);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);

	set_enable_logging(0);
	set_enable_recovery(1);

	init_database();
	set_alarm(0.0, 0.0, &recover_objects_from_database());

    set_no_show_composite(1);

}

