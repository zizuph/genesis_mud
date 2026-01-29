/*
 * Priest of Takhisis Slow Object
 *
 * This object if cloned makes the container of this object slower.
 *
 * Created by Petros, November 2011
 */

#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>
#include <files.h>
#include <ss_types.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public float    duration;
public int      Slowness = 140; // Average for PoT is 140

// Prototypes
public void     start_slow_effects(object player);
public void     remove_slow_effects(object player);

// Defines
#define SLOW_EFFECT   ("/d/Ansalon/guild/pot/spells/obj/pslow")

public void
set_slow_duration(float seconds)
{
    duration = seconds;
}

public float
query_slow_duration()
{
    return duration;
}

public void
set_slowness(int slowness)
{
    Slowness = slowness;
}

public int
query_slowness()
{
    return Slowness;
}

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("pot_slow_object");
    set_short("hidden priests of takhisis slow object");
    set_long("Players should not see this object.\n");

    set_no_show();
    set_slow_duration(300.00);  
    set_slowness(140);  
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
public void
enter_env(object to, object from)
{
    object * others;
    
    ::enter_env(to, from);
    
    // Make sure that we cannot have more than
    // one of these objects
    others = filter(all_inventory(to), &->id("pot_slow_object"));
    others -= ({ this_object() });
    if (sizeof(others))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    if (to != from && IS_LIVING_OBJECT(to))
    {
        start_slow_effects(to);
    }
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
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (old != dest && IS_LIVING_OBJECT(old))
    {
        remove_slow_effects(old);
    }
}

private void
restart_effect(object player)
{
    start_slow_effects(player);
}

private void
end_effect(object player)
{
    remove_slow_effects(player);
    // Restart the effect in 5 seconds (simulating a second casting)
    set_alarm(5.0, 0.0, &restart_effect(player));
}

public void
start_slow_effects(object player)
{
    setuid();
    seteuid(getuid());
    player->dec_prop(LIVE_I_QUICKNESS, Slowness);
    player->query_combat_object()->cb_update_speed();
    // Remove this object after the specified duration
    set_alarm(duration, 0.0, &end_effect(player));
}

public void
remove_slow_effects(object player)
{
    setuid();
    seteuid(getuid());
    player->inc_prop(LIVE_I_QUICKNESS, Slowness);
    player->query_combat_object()->cb_update_speed();
}

