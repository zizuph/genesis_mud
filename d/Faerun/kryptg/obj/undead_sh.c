
inherit "/std/shadow";

#include <stdproperties.h>

#define UNDEAD_SUBLOC "undead_subloc"

public mixed query_prop(string prop)
{
    mixed result=shadow_who->query_prop(prop);
    if (prop==LIVE_I_UNDEAD && !result)
    {
        return 1;
    }
    return result;
}

public void remove_undead_shadow()
{
    shadow_who->catch_msg("You feel yourself returning to a more "+
    "natural state.\n");
    shadow_who->remove_subloc(UNDEAD_SUBLOC);
    remove_shadow();
}

/*
 * Function name: shadow_me
 * Description  : Called from object to make us shadow it.
 * Arguments    : mixed to_shadow - either a string or object. If it is
 *                a string, use find_player to find the player to shadow.
 * Returns      : int - True if shadowed.
 */
public varargs int
shadow_me(mixed to_shadow)
{
    int result=::shadow_me(to_shadow);
    
    if (result)
    {
        set_alarm(180.0,0.0,remove_undead_shadow);
        to_shadow->catch_msg("You feel different, as if the life "+
        "was drained out of you.\n");
        to_shadow->add_subloc(UNDEAD_SUBLOC,this_object());
    }
    return result;
    
}

public string show_subloc(string subloc, object on, object for_obj)
{
    if (subloc==UNDEAD_SUBLOC)
    {
        if (on==for_obj)
        {
            return "You are looking a little pale.\n";
        }
        return capitalize(for_obj->query_pronoun())+" is looking "+
        "a little pale.\n";
    }
}

