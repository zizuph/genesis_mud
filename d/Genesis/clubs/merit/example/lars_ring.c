/* File         : /d/Genesis/clubs/reward_example/lars_ring.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : February 20, 1999
 * Purpose      : This is the item to be found for completion of the 
 *                inaugural "personal club" reward.
 * Related Files: /d/Genesis/clubs/reward_example/
 * Comments     : 
 * Modifications:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

/*
 * Function name: create_object
 * Description  : Create and configure the object.
 */

public void
create_object()
{
    set_name("ring");
    add_name("_ring_of_Lars_");
    set_adj("signet");
    add_adj(({"Lars","metal","platinum","glowing"}));
    set_short("signet ring");
    set_pshort("signet rings");

    set_long("This platinum ring glows a faint blue. Etched into " +
        "the outer band of metal are reversed letters which would " +
        "spell 'L A R S' if imprinted upon wax. The inner band of " +
        "the ring contains some small script.\n");

    add_item(({"script","small script"}), "@@read_script");
    add_cmd_item(({"script", "small script"}), "read", "@@read_script");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET, "@@get_log"); //Only interested in who gets it.
    add_prop(OBJ_M_NO_GIVE, 1);

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(OBJ_I_VALUE, 134444);
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_WEIGHT, 20);

    config_wearable_item(A_R_FINGER, 1, 1, this_player());
    /* From wearable_item.c, a handy configure */

    seteuid(getuid());
}

/*
 * Function name: read_script
 * Description  : Makes read and exa work the same way.
 * Returns      : A string to the player.
 */

public string
read_script()
{

    return "Please contact Teth if found. If he's not available, " +
           "worry not, for he will know who has found the ring.\n";

}

/*
 * Function name: get_log
 * Description  : Logs the receipt of this item.
 * Returns      : 0, allowing reception.
 */

public int
get_log()
{
    write_file("/d/Genesis/clubs/reward_example/getlog",
        this_player()->query_name() + " picked up the ring of Lars. " +
        ctime(time())+".\n");

    return 0;
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);
    /* This is necessary for proper wear/remove functionality. */
}

/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
