/*
 *  faerun/underdark/upper/menzo/sorcere/obj/mana_drain_cloud.c
 *
 *  A cloud, created when a player tries to pick a lock and failed.
 *
 *  Created by Wully, 15-2-2004
 */

#include <filter_funs.h>
#include <stdproperties.h>

inherit "/std/object";

/*
 * Function name: create_object
 * Description  : Construct the object
 */
void create_object()
{
    set_name("gas");
    add_adj( ({ "sulphur-smelling", "greenish" }) );

    set_short("sulphur-smelling greenish gas");
    set_long("A thick green gas has filled the room and a strong smell " +
             "of sulphur fills your nostrils. It seems to stream out " +
             "from the key hole of the weirwood door and hangs heavily " +
             "in the air around you.\n");

    add_prop(OBJ_M_NO_GET, "Your hands pass straight through the greenish gas.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 1000000);
}

/*
 * Function name: do_mana_drain
 * Description  : We drain the mana here
 */
void do_mana_drain()
{
    object *obs;

    // Find the players in our inventory
    obs = FILTER_LIVE(all_inventory(environment(this_object())));
    obs->catch_msg("As you inhale the greenish gas you feel your mind " +
        "getting clouded and your thoughts less focused.\n");
    obs->add_mana(-300);
}

/*
 * Function name: remove_cloud
 * Description  : Called when we leave the environment
 */
void remove_cloud()
{
    tell_room(environment(this_object()), 
        "The cloud of greenish gas disperses.\n");
    remove_object();
}

/*
 * Function name: enter_env
 * Description  : Called when we enter the environment
 * Arguments    : to, from
 */
void enter_env(object to, object from)
{
    ::enter_env(to, from);
    tell_room(to, "A cloud of sulphur-smelling greenish gas suddenly " +
                  "streams out from the keyhole of the weirwood door " +
                  "and fill the room.\n");
    set_alarm(1.0, 5.0, do_mana_drain);
    set_alarm(21.0, 0.0, remove_cloud);
}

