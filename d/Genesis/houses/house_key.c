
#include "./defs.h"
#include <composite.h>
#include <macros.h>

inherit "/std/key";

private string house_name;

public void set_house_name(string name)
{
	house_name = name;
}

public string query_house_name()
{
	return house_name;
}

public int is_owner(object player)
{
    mapping details = HOUSE_MANAGER->get_house_details(house_name);
  
    if (mappingp(details))
    {
        if (details[KEY_OWNER] == player->query_real_name())
	    {
		    return 1;
        }
    }
    return 0;
}

public void
create_key()
{
    ::create_key();

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_I_WEIGHT,  1);
    add_prop(OBJ_I_VALUE,   0);
}

/*
 * Function name: enter_env
 * Description  : Mask enter_env to remove the key if the key shouldn't
 *                be with this player. Allows wizards to clone keys.
 * Arguments    : object to - the destination
 *                object from - where it came from
 */

public int
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!is_owner(to))
    {
        to->catch_tell("Oops! That " + short() + " isn't yours! " +
          "It has been taken away for safe keeping!\n");
        set_alarm(0.3, 0.0, &remove_object());

        return 0;
    }

    return 1;
}

public void init_arg(string arg)
{
    // No arguments expected.
}

public string
query_auto_load()
{
    return (MASTER + ":");
}
