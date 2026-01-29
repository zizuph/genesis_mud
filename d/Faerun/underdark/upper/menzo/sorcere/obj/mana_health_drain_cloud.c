/*
 *  faerun/underdark/upper/menzo/sorcere/obj/mana_health_drain_cloud.c
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
    add_adj( ({ "hazy", "red" }) );

    set_short("hazy red gas");
    set_long("A thick red gas has filled the room and a sour smell " +
             "fills your nostrils. It seems to stream out " +
             "from the key hole of the silver door and hangs heavily " +
             "in the air around you.\n");

    add_prop(OBJ_M_NO_GET, "Your hands pass straight through the red gas.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 1000000);
}

/*
 * Function name: do_drain
 * Description  : We drain the health and mana here
 */
void do_drain()
{
    object *obs;

    // Find the players in our inventory
    obs = FILTER_LIVE(all_inventory(environment(this_object())));
    obs->catch_msg("As you inhale the red gas you feel it is getting " +
        "very hard and painful to breathe and you feel less healthy. Your " +
        "mind is getting clouded and you sense that is very hard to focus your " +
        "thoughts.\n");
    obs->heal_hp(-200);
    obs->add_mana(-300);
}

/*
 * Function name: remove_cloud
 * Description  : Called when we leave the environment
 */
void remove_cloud()
{
    tell_room(environment(this_object()), 
        "The cloud of red gas disperses.\n");
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
    tell_room(to, "A cloud of red gas suddenly " +
                  "streams out from the keyhole of the silver door " +
                  "and fills the room.\n");
    set_alarm(1.0, 5.0, do_drain);
    set_alarm(21.0, 0.0, remove_cloud);
}

