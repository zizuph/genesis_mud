/*
   /d/Kalad/std/dirt.c

   Standard Kalad dirt object.

   Replacement of the old dirty exit in Kalad. This may be a pool
   of mud where players can fall into.

   Fysix@Genesis, Jan 1998
 */
#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Kalad/sys/properties.h"
#include "/d/Kalad/sys/files.h"

// Globals
static int  Chance,        // What's the chance of stepping into the
// dirt?
Dirtiness;     // How dirty does a living get when he
// steps into this dirt object?

// --- Set and query functions --------------------------------------

/* Function name: set_dirtiness
 * Description:   Set how dirty this object is.
 *                Note: this may be a negative number.
 * Arguments:     int
 */
public void
set_dirtiness(int i)
{
    Dirtiness = i;
}

/* Function name: query_dirtiness
 * Description:   How dirty is this object?
 * Returns:       int
 */
public int
query_dirtiness()
{
    return Dirtiness;
}

/* Function name: set_chance
 * Description:   Set the chance of getting dirty when someone enters
 *                the environment.
 * Arguments:     int 0-100
 */
public void
set_chance(int i)
{
    if (Chance >= 0 && Chance <= 100)
	Chance = i;
}

/* Function name: query_chance
 * Description:   What is the chance of getting dirty when someone
 *                enters the environment?
 * Returns:       int 0-100
 */
public int
query_chance()
{
    return Chance;
}

// --- Other functions -------------------------------------------------

/* Function name: create_dirt
 * Description:   Dirt creation function
 */
public void
create_dirt()
{
}

public nomask void
create_object()
{
    set_name("dirt");
    add_name("pile");
    set_long("This is a pile of dirt.\n");

    set_dirtiness(1); // dirtiness will increase with 1 when
    // stepping into this dirt
    set_chance(10);   // 10% chance of stepping into this dirt

    add_prop(OBJ_I_NO_GET, 1);

    set_no_show_composite(1);  // don't show

    setuid();
    seteuid(getuid());

    create_dirt();
}

/* Function name: hook_step_into_dirt_msg
 * Description:   A hook for giving a message when a player steps
 *                into this dirt.
 * Arguments:     object living
 */
public void
hook_step_into_dirt_msg(object living)
{
    living->catch_tell("You didn't look very well and you " +
      "stepped into some dirt.\n");
    tell_room(environment(),
      QCTNAME(living) + " steps into some dirt.\n", living);
}

/* Function name: make_dirty
 * Description:   Make a player dirty after he walked somewhere.
 *                Called from enter_inv.
 * Arguments:     object player
 */
public void
make_dirty(object living)
{
    object o;

    if (environment(this_object()) != environment(living))
	return;

    // If riding a steed, make the steed dirty
    if (!(o = living->query_prop(LIVE_O_STEED)))
	o = living;

    hook_step_into_dirt_msg(o);
    o->add_prop(LIVE_I_DIRTY, o->query_prop(LIVE_I_DIRTY) +
      Dirtiness);

    // Clone the dirt object if it wasn't there yet
    if (!present(DIRTY_OBJECT_ID, living))
	clone_object(DIRTY_OBJECT)->move(living, 1);
}

/* Function name: notify_living_entered
 * Description:   This function is called when a living enters
 *                the environment. The player is made dirty
 *                with query_chance % probability.
 * Arguments:     object living
 */
public void
notify_living_entered(object living)
{
    if (random(100) <= Chance)
	// Use an alarm to make sure players steps into the dirt
	// after he has glanced.
	set_alarm(0.1, 0.0, &make_dirty(living));
}

// When a living enters the environment give a call
// to notify_living_entered
void
init()
{
    ::init();
    notify_living_entered(this_player());
}

// Add some extra wizard info
public string
stat_object()
{
    string str;

    // Describe dirtiness
    str += "Dirtiness: " + sprintf("%d\n", Dirtiness) +
    "Chance: " + sprintf("%d\n", Chance);

    return ::stat_object() + str;
}
