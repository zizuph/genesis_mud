/*
 * Disarm Spell Weapon Shadow
 *
 * This is the weapon shadow for the disarm spell, naro libo makil.
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/unfinished/disarm_weapon_sh";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define DISARM_SPELL_CANNOT_WIELD   ("_disarm_spell_cannot_wield")

#define DEBUG(x)	     find_player("arman")->catch_msg("[Disarm] " + x + "\n")

public object            oldwf;

public varargs string
short(object for_obj)
{
    return ("uncorporal " + shadow_who->short(for_obj));
}

string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "It seems to be in an uncorporal form, battling to return from "
        + "the realm of Shadows!\n");
}

public void
initialize_shadow()
{
    oldwf = query_shadow_who()->query_wf();
    query_shadow_who()->set_wf(this_object());
}

public void
remove_disarm_shadow()
{
    object weapon = query_shadow_who();
    object target = environment(weapon);
    target->remove_prop(DISARM_SPELL_CANNOT_WIELD);

    if (objectp(target))
    {
        if(!target->query_ghost())
        {
            target->catch_tell("Your " +weapon->short()+ " returns " +
                "from the realm of Shadow!\n");  
            tell_room(environment(target), QCTPNAME(target) + " "
                + weapon->short()+ " returns from the realm of Shadow!\n", 
                ({ target }));
        }
    }
         
    if (objectp(target))
    {
        // If no other weapon has been rewielded, rewield if in possession
        if(!sizeof(target->query_weapon(-1)) && present(weapon, target))
           target->command("$wield " + OB_NAME(weapon));
    } 

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
        tell_room(environment(owner), QCTNAME(owner) + " tries to "
            + "re-wield " +owner->query_possessive()+ " "
            + weapon->short() + ", but " +owner->query_possessive()
            + " hands pass through it like smoke!\n", 
            ({ owner }));
        return "The " +weapon->short()+ " is uncorporal, " +
             "stuck in the realm of Shadows! Your hands pass " +
             "through it as if it were smoke!\n"; 
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


