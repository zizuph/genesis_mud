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
#include "../guild.h";

void create();

// Guild rank mapping
mapping Assassin_rank;

// Assassination gauge mapping
mapping Assassination_gauge;

// Assassination Council Activity Gauge
mapping Assassination_council_activity_gauge;

// Assassination x-council cooldown countdown
mapping Assassination_xcouncil_activity_cooldown;

mapping Ability1;
mapping Ability2;
mapping Ability3;
mapping Ability4;
mapping Ability5;


public int
query_ability1(string real_name)
{
    return Ability1[lower_case(real_name)];
}


public void
set_ability1(string real_name, int ab1_nr)
{
    Ability1 = restore_map(ABILITY1);
    Ability1[lower_case(real_name)] = ab1_nr;
    save_map(Ability1, ABILITY1);
}


public void
clean_ability1(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Ability1[real_name])
    {
        Ability1 = m_delete(Ability1, real_name);
        save_map(Ability1, ABILITY1);
    }
}


public int
query_ability2(string real_name)
{
    return Ability2[lower_case(real_name)];
}


public void
set_ability2(string real_name, int ab2_nr)
{
    Ability2 = restore_map(ABILITY1);
    Ability2[lower_case(real_name)] = ab2_nr;
    save_map(Ability2, ABILITY2);
}


public void
clean_ability2(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Ability2[real_name])
    {
        Ability2 = m_delete(Ability2, real_name);
        save_map(Ability2, ABILITY2);
    }
}


public int
query_ability3(string real_name)
{
    return Ability3[lower_case(real_name)];
}


public void
set_ability3(string real_name, int ab3_nr)
{
    Ability3 = restore_map(ABILITY3);
    Ability3[lower_case(real_name)] = ab3_nr;
    save_map(Ability3, ABILITY3);
}


public void
clean_ability3(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Ability3[real_name])
    {
        Ability3 = m_delete(Ability3, real_name);
        save_map(Ability3, ABILITY3);
    }
}


public int
query_ability4(string real_name)
{
    return Ability4[lower_case(real_name)];
}


public void
set_ability4(string real_name, int ab4_nr)
{
    Ability4 = restore_map(ABILITY4);
    Ability4[lower_case(real_name)] = ab4_nr;
    save_map(Ability4, ABILITY4);
}


public void
clean_ability4(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Ability1[real_name])
    {
        Ability1 = m_delete(Ability1, real_name);
        save_map(Ability1, ABILITY1);
    }
}


public int
query_ability5(string real_name)
{
    return Ability5[lower_case(real_name)];
}


public void
set_ability5(string real_name, int ab5_nr)
{
    Ability5 = restore_map(ABILITY5);
    Ability5[lower_case(real_name)] = ab5_nr;
    save_map(Ability5, ABILITY5);
}


public void
clean_ability5(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Ability5[real_name])
    {
        Ability5 = m_delete(Ability5, real_name);
        save_map(Ability5, ABILITY5);
    }
}


public int
query_assassin_rank(string real_name)
{
    return Assassin_rank[lower_case(real_name)];
}


public void
set_assassin_rank(string real_name, int assassinrank_nr)
{
    Assassin_rank = restore_map(ASSASSIN_RANK);
    Assassin_rank[lower_case(real_name)] = assassinrank_nr;
    save_map(Assassin_rank, ASSASSIN_RANK);
}


public void
clean_assassin_rank(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Assassin_rank[real_name])
    {
        Assassin_rank = m_delete(Assassin_rank, real_name);
        save_map(Assassin_rank, ASSASSIN_RANK);
    }
}


public int
query_assassin_council_activity_gauge(string real_name)
{
    return Assassination_council_activity_gauge[lower_case(real_name)];
}


public void
set_assassin_council_activity_gauge(string real_name, int selection)
{
    Assassination_council_activity_gauge = restore_map(ASSASSINATION_ACTIV_GAUGE);
    Assassination_council_activity_gauge[lower_case(real_name)] = selection;
    save_map(Assassination_council_activity_gauge, ASSASSINATION_ACTIV_GAUGE);
}


public void
clean_assassin_council_activity_gauge(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Assassination_council_activity_gauge[real_name])
    {
        Assassination_council_activity_gauge = m_delete(Assassination_council_activity_gauge, real_name);
        save_map(Assassination_council_activity_gauge, ASSASSINATION_ACTIV_GAUGE);
    }
}


public int
query_assassin_xcouncil_activity_cooldown(string real_name)
{
    return Assassination_xcouncil_activity_cooldown[lower_case(real_name)];
}


public void
set_assassin_xcouncil_activity_cooldown(string real_name, int selection)
{
    Assassination_xcouncil_activity_cooldown = restore_map(ASSA_XCOUNCIL_COOLDOWN);
    Assassination_xcouncil_activity_cooldown[lower_case(real_name)] = selection;
    save_map(Assassination_xcouncil_activity_cooldown, ASSA_XCOUNCIL_COOLDOWN);
}


public void
clean_assassin_xcouncil_activity_cooldown(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Assassination_xcouncil_activity_cooldown[real_name])
    {
        Assassination_xcouncil_activity_cooldown = m_delete(Assassination_xcouncil_activity_cooldown, real_name);
        save_map(Assassination_xcouncil_activity_cooldown, ASSA_XCOUNCIL_COOLDOWN);
    }
}


public int
query_assassin_gauge(string real_name)
{
    return Assassination_gauge[lower_case(real_name)];
}


public void
set_assassin_gauge(string real_name, int selection)
{
    Assassination_gauge = restore_map(ASSASSINATION_GAUGE);
    Assassination_gauge[lower_case(real_name)] = selection;
    save_map(Assassination_gauge, ASSASSINATION_GAUGE);
}


public void
clean_assassin_gauge(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Assassination_gauge[real_name])
    {
        Assassination_gauge = m_delete(Assassination_gauge, real_name);
        save_map(Assassination_gauge, ASSASSINATION_GAUGE);
    }
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    // Guild rank
    Assassin_rank = restore_map(ASSASSIN_RANK);
    
    // Assassination gauge.
    Assassination_gauge = restore_map(ASSASSINATION_GAUGE);
	
	// Assassination Council activity gauge.
    Assassination_council_activity_gauge = restore_map(ASSASSINATION_ACTIV_GAUGE);
    
    // Assassination x-council cooldown. council-members that idles out can't
    // simply re-assume council positions, keeping guild hostage.
    Assassination_xcouncil_activity_cooldown = restore_map(ASSA_XCOUNCIL_COOLDOWN);
    
    Ability1 = restore_map(ABILITY1);
    Ability2 = restore_map(ABILITY2);
    Ability3 = restore_map(ABILITY3);
    Ability4 = restore_map(ABILITY4);
    Ability5 = restore_map(ABILITY5);
}
