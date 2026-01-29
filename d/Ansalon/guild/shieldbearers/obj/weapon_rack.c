/*
 * Shieldbearer Weapon Rack
 */
 
inherit "/d/Genesis/specials/guilds/objs/weapon_rack";

#include <stdproperties.h>

void
create_rack()
{
    set_adj("large");
    set_adj("weapon");
    set_short("weapon rack");
    set_long("This large rack, skillfully crafted " 
        + "from a dark wood native to these areas, "
        + "is used by shieldbearers to store their "
        + "weapons for later use. See <rackhelp> for "
        + "instructions on how to use it.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,0);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_MAX_WEIGHT, 90000000);
    add_prop(CONT_I_MAX_VOLUME, 90000000);
}

public void
init()
{
    ::init();
    add_action(do_help, "rackhelp");
}

/*
 * Function:    hook_prepend_describe_contents
 * Description: Allows one to customize the text that goes above the
 *              listing of the contents in the rack object.
 */
public void
hook_prepend_describe_contents(object for_obj, object * obarr)
{
}

/*
 * Function:    hook_append_describe_contents
 * Description: Allows one to customize the text that goes after the
 *              listing of the contents in the rack object.
 */
public void
hook_append_describe_contents(object for_obj, object * obarr)
{
}
