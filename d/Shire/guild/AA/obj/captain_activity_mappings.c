/*
 * Guild manager, mappings
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "/d/Shire/guild/AA/guild.h";

#define CAPTAIN_ACTIVE_GAUGE  ("/d/Shire/guild/AA/save_files/captain_activity_gauge")
#define CAPTAIN_REJOIN_COOLDOWN  ("/d/Shire/guild/AA/save_files/captain_rejoin_cooldown")

void create();

// Captain activity Gauge
mapping captain_activity_gauge;

// Captain rejoin cooldown
mapping captain_rejoin_cooldown;


// Activity mappings
public int
query_captain_activity_gauge(string real_name)
{
    return captain_activity_gauge[lower_case(real_name)];
}


public void
set_captain_activity_gauge(string real_name, int selection)
{
    captain_activity_gauge = restore_map(CAPTAIN_ACTIVE_GAUGE);
    captain_activity_gauge[lower_case(real_name)] = selection;
    save_map(captain_activity_gauge, CAPTAIN_ACTIVE_GAUGE);
}


public void
clean_captain_activity_gauge(string real_name)
{
    real_name = lower_case(real_name);
    
    if(captain_activity_gauge[real_name])
    {
        captain_activity_gauge = m_delete(captain_activity_gauge, real_name);
        save_map(captain_activity_gauge, CAPTAIN_ACTIVE_GAUGE);
    }
}


// Activity mappings
public int
query_captain_rejoin_cooldown(string real_name)
{
    return captain_rejoin_cooldown[lower_case(real_name)];
}


public void
set_captain_rejoin_cooldown(string real_name, int selection)
{
    captain_rejoin_cooldown = restore_map(CAPTAIN_REJOIN_COOLDOWN);
    captain_rejoin_cooldown[lower_case(real_name)] = selection;
    save_map(captain_rejoin_cooldown, CAPTAIN_REJOIN_COOLDOWN);
}


public void
clean_captain_rejoin_cooldown(string real_name)
{
    real_name = lower_case(real_name);
    
    if(captain_rejoin_cooldown[real_name])
    {
        captain_rejoin_cooldown = m_delete(captain_rejoin_cooldown, real_name);
        save_map(captain_rejoin_cooldown, CAPTAIN_REJOIN_COOLDOWN);
    }
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
	// Captain activity gauge.
    captain_activity_gauge = restore_map(CAPTAIN_ACTIVE_GAUGE);
    
    // Captain rejoin cooldown.
    captain_rejoin_cooldown = restore_map(CAPTAIN_REJOIN_COOLDOWN);
}
