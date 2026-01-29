/*
 *  faerun/underdark/upper/menzo/sorcere/obj/health_drain_cloud.c
 *
 *  A cloud, created when a player tries to pick a lock and failed.
 *
 *  Created by Midnight, 8-4-2004
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
    add_adj( ({ "thick", "purple" }) );

    set_short("thick purple gas");
    set_long("A thick purple gas has filled the room and a sour smell " +
             "fills your nostrils. It seems to stream out " +
             "from the key hole of the weirdwood door and hangs heavily " +
             "in the air around you.\n");

    add_prop(OBJ_M_NO_GET, "Your hands pass straight through the purple gas.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 1000000);
}

/*
 * Function name: do_health_drain
 * Description  : We drain the health here
 */
void do_health_drain()
{
    object *obs;

    // Find the players in our inventory
    obs = FILTER_LIVE(all_inventory(environment(this_object())));
    obs->catch_msg("As you inhale the purple gas you feel it is getting " +
        "very hard and painful to breathe and you feel less healthy.\n");
    obs->heal_hp(-150);
}

/*
 * Function name: remove_cloud
 * Description  : Called when we leave the environment
 */
void remove_cloud()
{
    tell_room(environment(this_object()), 
        "The cloud of purple gas disperses.\n");
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
    tell_room(to, "A cloud of thick purple gas suddenly " +
                  "streams out from the keyhole of the weirwood door " +
                  "and fills the room.\n");
    set_alarm(1.0, 5.0, do_health_drain);
    set_alarm(21.0, 0.0, remove_cloud);
}

