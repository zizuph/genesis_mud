/*
 *    Terel blind object, based on examples from Gondor and Krynn,
 *    thanks Navarre, Tomas,
 *     - Udana
 *
 * Modifications:
 * October 2009 - Changed to use LIVE_I_BLIND since the global darkness
 *                properties were changed. (Petros)
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#define BLIND_SUBLOC "_stick_blind_subloc"

/* time before the blindness is removed. */
int duration = 0;
// Alarm that will actuall remove the blindness object
int alarm_id = 0;

public int
query_is_terel_blind_object()
{
    return 1;
}

void
create_object()
{
    set_name("_terel_blind_object");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    
    set_no_show();
}

public void 
set_time(int i)
{
    duration = i; 
}

public void
add_time(int i)
{
    mixed alarm_info = get_alarm(alarm_id);
    // We check the existing alarm and add to the duration.
    if (!alarm_info)
    {
        // If there's no existing alarm, just go ahead and
        // add to the duration variable.
        duration += i;
        return;
    }
    
    float time_remaining = alarm_info[2];
    time_remaining += itof(i);
    remove_alarm(alarm_id);
    alarm_id = set_alarm(time_remaining, 0.0, remove_object);
}

public float
query_time_remaining()
{
    mixed alarm_info = get_alarm(alarm_id);
    // We check the existing alarm and add to the duration.
    if (!alarm_info)
    {
        return 0;
    }
    
    return alarm_info[2];
}

/* returns 1 if it really has removed the blind */
public void 
remove_object()
{
    object player = E(this_object());

    // Sanity Check. If not in a living, don't do anything special.
    if (!living(player))
    {
        ::remove_object();
        return;
    }
    
    player->remove_subloc(BLIND_SUBLOC);
    player->dec_prop(LIVE_I_BLIND);
    if (!player->query_prop(LIVE_I_BLIND))
    {
        // If a player is no longer blinded, we display messages to indicate
        // this to them and others.
        player->catch_msg("You blink few times, and slowly regain your "
            + "sight.\n");
        tell_room(E(player), QCTPNAME(player) + " blinks few times, and "
            + "seems to be able to see again!\n", player);
    }
    
    ::remove_object();
    return;
}

public void
enter_env(object to, object from)
{
    object * blind_objects;
    object player = to;
    
    blind_objects = filter(all_inventory(player), 
        &->query_is_terel_blind_object());
    blind_objects -= ({ this_object() });
    if (sizeof(blind_objects))
    {
        // Since there's already a blind object, we simply remove this
        // object. You can't blind someone more than they already are.
        player->inc_prop(LIVE_I_BLIND); // remove_object has a decrement
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
            
    ::enter_env(to, from);

    player->catch_msg("Being accustomed to darkness for so long, you are "
        + "blinded by this sudden light!\n");
    tell_room(E(player), QCTNAME(player) + " covers " + player->query_possessive() 
        + " eyes and winces in pain!\n", player);
    player->add_subloc(BLIND_SUBLOC,TO);
    player->inc_prop(LIVE_I_BLIND);
    alarm_id = set_alarm(itof(duration), 0.0, remove_object);
}

string show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if (for_obj == carrier)
        str = "All you see is bunch of red dots, dancing in front of your eyes.\n";
    else str = capitalize(carrier->query_pronoun()) + " seems to have some problem with "
        + carrier->query_possessive() + " eyes.\n";
    return str;
}

