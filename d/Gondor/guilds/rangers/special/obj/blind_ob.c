/*
 * /d/Gondor/guilds/rangers/special/obj/blind_ob.c
 *
 * This is an object that is cloned into a player to blind him for some time.
 * It is used with the "brawl" command of the Gondorian Rangers.
 *
 * Originally coded by Lord Elessar Telcontar
 *
 * Revision history:
 *
 * /Mercade, 17 November 1993, recoded and enhanced, solved the killing prob
 * July 2001, Gwyneth: Added a $ to the kill command and changed to OB_NAME
 *                     Tidied up and moved
 * May 2004, Gwyneth, updated
 * Mars 2009, Cotillion: Changed to LIVE_I_BLIND
 */
 
#include "/d/Genesis/specials/local.h"; 
 
inherit BLIND_OBJ_BASE;

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define BLIND_SUBLOC "ranger_blind_subloc"


public object find_other_ranger_blind(object* effects)
{
    foreach(object effect : effects)
    {
        if (effect->is_ranger_blind() &&
            effect != this_object())
        {
            return effect;
        }
    }
    return 0;
}

public int is_ranger_blind()
{
    return 1;
}

public void
hook_blind_begin(object actor, object target, object *effects)
{
    int busy_hands = 0;
    string how;
    
    if (actor->query_weapon(W_BOTH))
        busy_hands = 1;
    else if (actor->query_weapon(W_RIGHT) && actor->query_weapon(W_LEFT))
        busy_hands = 1;

    if (busy_hands)
        how = "kick";
    else
        how = "throw";
    
    // blinded may be from a non-ranger ability, so we will filter for
    // other sand for various messages.
    if (find_other_ranger_blind(effects))
    {
        write("You successfully " + how + " some more sand in the eyes of " +
            target->query_the_name(actor) + ". " +
            capitalize(target->query_pronoun()) + " is still blinded!\n");
        tell_room(environment(actor), QCTNAME(actor) + " manages " +
            "to " + how + " some more sand into the already blinded " +
            "eyes of " + QTNAME(target) + "!\n", ({ target, actor }), );
    }
    else
    {
        target->add_subloc(BLIND_SUBLOC, this_object());
        write("You successfully " + how + " a shower " + "of sand into " +
            "the eyes of " + target->query_the_name(actor) + ". " +
            capitalize(target->query_pronoun(actor)) + " looks blinded!\n");

        if (busy_hands)
            how = " kicks at the dusty ground,";
        else
            how = " jerks " + actor->query_possessive() + " hand up,";

        tell_room(environment(actor), QCTNAME(actor) + " suddenly" +
            how + " sending a shower of sand into the eyes of " +
            QTNAME(target) + "!\n", ({ actor, target }), );

        // The target is already blinded when this is called, so we do not
        // have the description of the one doing the blinding like the
        // old effect.
        target->catch_tell("You scream loudly as a shower of sand hits " +
            "your eyes! You are blinded!\n");
    }
} 

public void
hook_blind_ended(object actor, object target, object *effects)
{

    if (!objectp(target) || target->query_ghost() || !living(target))
        return;

    if (target->query_hp() <= 0)
        return;
        
    // blinded may be from a non-ranger ability, so we will filter for
    // other sand for various messages.
    object other_blind = find_other_ranger_blind(effects);
    
    if (!other_blind)
    {
        target->remove_subloc(BLIND_SUBLOC);
        target->catch_tell("You finally manage to clear your eyes of sand, " +
            "and are able to see again!\n");

        if (target->query_humanoid())
        {
            tell_room(environment(target), QCTNAME(target) + " rubs " + 
                target->query_possessive() + " eyes, and seems to have " +
                "cleared them of sand!\n", target);
        }
        else
        { 
            tell_room(environment(target), QCTNAME(target) + " shakes " + 
                target->query_possessive() + " head vigorously to clear " + 
                target->query_possessive() + " eyes of sand!\n", target);
        }
    }
    else
    {
        target->catch_tell("You clear some of the sand from your eyes, but " +
            "are still blinded.\n");
        // Hand off the subloc to the remaining blind.
        target->add_subloc(BLIND_SUBLOC, other_blind);
    }
            
} /* hook_blind_ended */

public void hook_blind_failed(object actor, object target)
{
    write("You attempt to blind " +
        target->query_the_name(actor) + ", " +
        "but " + target->query_pronoun() + 
        " is too focused on your brawling.\n");
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != BLIND_SUBLOC)
    {
        return "";
    }

    if (for_obj == carrier)
    {
        str = "You have trouble looking, since your eyes are filled " +
            "with sand!\n";
    }
    else
    {
        str = capitalize(carrier->query_pronoun()) + " is desperately " +
            "trying to get sand out of " + carrier->query_possessive() + 
            " eyes!\n";
    }

    return str;
}
