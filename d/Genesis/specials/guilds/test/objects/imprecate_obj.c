/*
 * Priests of Takhisis Imprecate Object
 *
 * This unique ability allows a Priest of Takhisis to cause the opponent's
 * defence to go gradually from 0 back up to normal over the course of
 * the spell.
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
public object   effect_object;

// Prototypes
public void     start_imprecate_effects(object player);
public void     remove_imprecate_effects(object player);

// Defines
#define IMPRECATE_EFFECT   ("/d/Ansalon/guild/pot/spells/obj/pimprecate")

public void
set_imprecate_duration(float seconds)
{
    duration = seconds;
}

public float
query_imprecate_duration()
{
    return duration;
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

    set_name("pot_imprecate_object");
    set_short("hidden priests of takhisis imprecate object");
    set_long("Players should not see this object.\n");

    set_no_show();
    set_imprecate_duration(42.00);    
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
    others = filter(all_inventory(to), &->id("pot_imprecate_object"));
    others -= ({ this_object() });
    if (sizeof(others))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    if (to != from && IS_LIVING_OBJECT(to))
    {
        start_imprecate_effects(to);
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
        remove_imprecate_effects(old);
    }
}

private void
restart_effect(object player)
{
    start_imprecate_effects(player);
}

private void
end_effect(object player)
{
    // Restart the effect in 5 seconds (simulating a second casting)
    set_alarm(5.0, 0.0, &restart_effect(player));
}

public void
start_imprecate_effects(object player)
{
    setuid();
    seteuid(getuid());
    effect_object = clone_object(IMPRECATE_EFFECT);
    effect_object->set_time(ftoi(query_imprecate_duration()));
    effect_object->set_spell_effect_target(player);
    effect_object->setup_spell_effect();
    // Remove this object after the specified duration
    set_alarm(duration, 0.0, &end_effect(player));
}

public void
remove_imprecate_effects(object player)
{
    setuid();
    seteuid(getuid());
    effect_object->dispell_spell_effect(player);
    effect_object = 0;
}

