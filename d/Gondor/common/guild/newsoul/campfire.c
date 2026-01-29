/*
 * /d/Gondor/common/guild/soul/campfire.h
 *
 * With this command the Gondorian Rangers can nake a campfire in the
 * open. The command requires that the player is in an outside-room, and
 * will drain 5 manapoints for gathering firewood.
 *
 * Elessar, May 1992.
 */

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define RANGER_IS_GATHERING_FIREWOOD   "_ranger_i_is_gathering_firewood"

/*
 * Function name: gather_firewood
 * Description  : After a little delay, this function is called since it
 *                takes time to gather firewood. Note that since we are
 *                called by an alarm, this_player() is not known.
 * Arguments    : object player - the player gathering firewood.
 *                int    mana   - the mana of the player at the time the
 *                                player starts searching since it can be
 *                                regained by time.
 */
static void
gather_firewood(object player, int mana)
{
    int    burn_time;
    object firewood;
    string new = "";

    if (!objectp(player))
    {
	return 0;
    }

    player->remove_prop(RANGER_IS_GATHERING_FIREWOOD);

    if (mana < 10)
    {
	tell_object(player, "You are too mentally exhausted, you can't " +
	    "concentrate enough to find any firewood!\n");
	return;
    }

    /* The time the fire will last depends on the players skill in finding
     * firewood (the hunting skill) as well as his average stats, + 50 free.
     * Total possible maximum is a fire lasting 850 ticks.
     */
    burn_time = (player->query_skill(SS_HUNTING) * 3) +
	((player->query_average_stats() / 10) * 50) + 50;

    if (mana < 20)
    {
 	burn_time = ((burn_time * mana) / 20);
    }

    player->add_mana(-5);

    firewood = present("campfire", environment(player));

    /* If there already is a campfire in the room that was burnt down,
     * destruct it and add to the message displayed to the people.
     */
    if (firewood->query_burnt_down())
    {
	new = "new ";
	firewood->remove_object();
    }

    /* ... but if it is still burning, add wood to it. */
    if (objectp(firewood))
    {
	tell_object(player, "You gather some more firewood, and throw it " +
	    "on the campfire.\n");
	tell_room(environment(player), QCTNAME(player) +
	    " gathers some more firewood, adding to the campfire.\n", player);

	firewood->add_burn_time(burn_time / 2);
	return;
    }

    tell_object(player, "You gather some firewood and stack it up to make a " +
	new + "campfire.\n");
    tell_room(environment(player), QCTNAME(player) +
	" gathers some firewood to make a " + new + "campfire.\n", player);

    setuid();
    seteuid(getuid());

    firewood = clone_object("/d/Gondor/common/guild/obj/firewood");
    firewood->move(environment(player), 1);
    firewood->set_burn_time(burn_time);
}

/*
 * Function name: try_gather
 * Description  : When a ranger wants to gather some firewood, this function
 *                is called.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
try_gather(string str)
{
    int speed;

    if ((str != "wood") && (str != "firewood"))
    {
	NFN0("Gather what?"):
    }

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
	write("You can only gather firewood out in the open.\n");
	return 1;
    }

    if (this_player()->query_prop(RANGER_IS_GATHERING_FIREWOOD))
    {
	write("But you are already searching for firewood!\n");
	return 1;
    }

    write("You start searching for firewood for a campfire.\n");
    say(QCTNAME(this_player())+" starts searching for firewood.\n");

    this_player()->add_prop(RANGER_IS_GATHERING_FIREWOOD, 1);

    speed = this_player()->query_skill(SS_HUNTING);
    speed = (55 - (MAX(speed, 90) / 2));
    set_alarm(itof(speed), 0.0, "gather_firewood", this_player(),
	this_player()->query_mana());

    return 1;
}
