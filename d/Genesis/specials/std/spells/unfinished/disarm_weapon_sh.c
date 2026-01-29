/*
 * Disarm Spell Weapon Shadow
 *
 * This is the weapon shadow for the disarm spell.
 *
 * Created by Arman, Oct 2017.
 */
#pragma strict_types

inherit "/std/shadow";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define DISARM_SPELL_CANNOT_WIELD   ("_disarm_spell_cannot_wield")

#define DEBUG(x)	     find_player("arman")->catch_msg("[Disarm] " + x + "\n")

public object            oldwf;

public void
initialize_shadow()
{
    oldwf = query_shadow_who()->query_wf();
    query_shadow_who()->set_wf(this_object());
}

public void
remove_disarm_shadow()
{
    query_shadow_who()->set_wf(oldwf);
    remove_shadow();
}

public mixed
wield(object what)
{
    object weapon = query_shadow_who();
    object owner = environment(weapon);

    if (owner->query_prop(DISARM_SPELL_CANNOT_WIELD))
    {
        return "The " +weapon->short()+ " is still magically " +
             "superheated and it cannot be wielded.\n"; 
    }
    else
        return weapon->wield(weapon);
}

public void
dispel_disarm_spell_shadow(int time)
{
    float dispel_time = itof(time);

    set_alarm(dispel_time, 0.0, &remove_disarm_shadow());
}


