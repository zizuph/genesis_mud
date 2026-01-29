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

mapping Vampires_weapon_selection;

mapping Vampires_thirst_gauge;

mapping Vampires_resilience_gauge;

mapping Vampires_main_special;

mapping Vampires_occ_ability_1;

mapping Vampires_occ_ability_2;

mapping Vampires_occ_ability_3;

mapping Vampires_occ_ability_4;

mapping Vampires_occ_ability_5;

mapping Vampires_occ_ability_6;

mapping Vampires_occ_ability_7;

mapping Vampires_occ_ability_8;

mapping Vampires_occ_ability_progenitor;

mapping Vampires_gauge;

mapping Vampires_rank;

mapping Vampires_reputation;

mapping Vampirespawn_timer;

mapping Vampires_seeker;

mapping Thrall_pool;

mapping Vamp_blessed;

mapping Vamp_title;

mapping Vamp_agent;

mapping Vamp_pathprog;







public int
query_vamp_blessed(string real_name)
{
    return Vamp_blessed[lower_case(real_name)];
}


public void
set_vamp_blessed(string real_name, int blessed)
{
    Vamp_blessed = restore_map(VAMP_PROG);
    Vamp_blessed[lower_case(real_name)] = blessed;
    save_map(Vamp_blessed, VAMP_BLESSED);
}


public void
clean_vamp_blessed(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vamp_blessed[real_name])
    {
        Vamp_blessed = m_delete(Vamp_blessed, real_name);
        save_map(Vamp_blessed, VAMP_BLESSED);
    }
}










public int
query_vamp_pathprogression(string real_name)
{
    return Vamp_pathprog[lower_case(real_name)];
}


public void
set_vamp_pathprogression(string real_name, int vampprog_nr)
{
    Vamp_pathprog = restore_map(VAMP_PROG);
    Vamp_pathprog[lower_case(real_name)] = vampprog_nr;
    save_map(Vamp_pathprog, VAMP_PROG);
}


public void
clean_vamp_pathprogression(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vamp_pathprog[real_name])
    {
        Vamp_pathprog = m_delete(Vamp_pathprog, real_name);
        save_map(Vamp_pathprog, VAMP_PROG);
    }
}


public int
query_vamp_agent(string real_name)
{
    return Vamp_agent[lower_case(real_name)];
}


public void
set_vamp_agent(string real_name, int vampagent_nr)
{
    Vamp_agent = restore_map(VAMP_AGENT);
    Vamp_agent[lower_case(real_name)] = vampagent_nr;
    save_map(Vamp_agent, VAMP_AGENT);
}


public void
clean_vamp_agent(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vamp_agent[real_name])
    {
        Vamp_agent = m_delete(Vamp_agent, real_name);
        save_map(Vamp_agent, VAMP_AGENT);
    }
}


public int
query_vamp_title(string real_name)
{
    return Vamp_title[lower_case(real_name)];
}


public void
set_vamp_title(string real_name, int vamptitle_nr)
{
    Vamp_title = restore_map(VAMP_TITLE);
    Vamp_title[lower_case(real_name)] = vamptitle_nr;
    save_map(Vamp_title, VAMP_TITLE);
}


public void
clean_vamp_title(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vamp_title[real_name])
    {
        Vamp_title = m_delete(Vamp_title, real_name);
        save_map(Vamp_title, VAMP_TITLE);
    }
}


// Tracking Immportalitypoint-worth of a thrall
public int
query_thrall_pool(string real_name)
{
    return Thrall_pool[lower_case(real_name)];
}


public void
set_thrall_pool(string real_name, int thrallpool_nr)
{
    Thrall_pool = restore_map(THRALL_POOL);
    Thrall_pool[lower_case(real_name)] = thrallpool_nr;
    save_map(Thrall_pool, THRALL_POOL);
}


public void
clean_thrall_pool(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Thrall_pool[real_name])
    {
        Thrall_pool = m_delete(Thrall_pool, real_name);
        save_map(Thrall_pool, THRALL_POOL);
    }
}


public int
query_vampire_reputation(string real_name)
{
    return Vampires_reputation[lower_case(real_name)];
}


public void
set_vampire_reputation(string real_name, int vamprep_nr)
{
    Vampires_reputation = restore_map(VAMPIRES_REP);
    Vampires_reputation[lower_case(real_name)] = vamprep_nr;
    save_map(Vampires_reputation, VAMPIRES_REP);
}


public void
clean_vampire_reputation(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_reputation[real_name])
    {
        Vampires_reputation = m_delete(Vampires_reputation, real_name);
        save_map(Vampires_reputation, VAMPIRES_REP);
    }
}


// This part is for the questpath, or the progresspath
// in order to be flagged for joining the vampires.
public int
query_vampire_seeker(string real_name)
{
    return Vampires_seeker[lower_case(real_name)];
}


public void
set_vampires_seeker(string real_name, int vampireseeker_nr)
{
    Vampires_seeker = restore_map(VAMPIRES_SEEKER);
    Vampires_seeker[lower_case(real_name)] = vampireseeker_nr;
    save_map(Vampires_seeker, VAMPIRES_SEEKER);
}


public void
clean_vampires_seeker(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_seeker[real_name])
    {
        Vampires_seeker = m_delete(Vampires_seeker, real_name);
        save_map(Vampires_seeker, VAMPIRES_SEEKER);
    }
}

public int
query_vampirespawn_timer(string real_name)
{
    return Vampirespawn_timer[lower_case(real_name)];
}


public void
set_vampirespawn_timer(string real_name, int vampireseeker_nr)
{
    Vampirespawn_timer = restore_map(VAMPIRESPAWN_TIMER);
    Vampirespawn_timer[lower_case(real_name)] = vampireseeker_nr;
    save_map(Vampirespawn_timer, VAMPIRESPAWN_TIMER);
}


public void
clean_vampirespawn_timer(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampirespawn_timer[real_name])
    {
        Vampirespawn_timer = m_delete(Vampirespawn_timer, real_name);
        save_map(Vampirespawn_timer, VAMPIRESPAWN_TIMER);
    }
}


public int
query_weaponskill_selection(string real_name)
{
    return Vampires_weapon_selection[lower_case(real_name)];
}


public void
set_weaponskill_selection(string real_name, int vampireselection_nr)
{
    Vampires_weapon_selection = restore_map(VAMPIRES_WEAPON_SELECTION);
    Vampires_weapon_selection[lower_case(real_name)] = vampireselection_nr;
    save_map(Vampires_weapon_selection, VAMPIRES_WEAPON_SELECTION);
}


public void
clean_weaponskill_selection(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_weapon_selection[real_name])
    {
        Vampires_weapon_selection = m_delete(Vampires_weapon_selection, 
        real_name);
        save_map(Vampires_weapon_selection, VAMPIRES_WEAPON_SELECTION);
    }
}


public int
query_vampires_rank(string real_name)
{
    return Vampires_rank[lower_case(real_name)];
}


public void
set_vampires_rank(string real_name, int vampiresrank_nr)
{
    Vampires_rank = restore_map(VAMPIRES_RANK);
    Vampires_rank[lower_case(real_name)] = vampiresrank_nr;
    save_map(Vampires_rank, VAMPIRES_RANK);
}


public void
clean_vampires_rank(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_rank[real_name])
    {
        Vampires_rank = m_delete(Vampires_rank, real_name);
        save_map(Vampires_rank, VAMPIRES_RANK);
    }
}


public int
query_vampire_main_special(string real_name)
{
    return Vampires_main_special[lower_case(real_name)];
}


public void
set_vampire_main_special(string real_name, int selection)
{
    Vampires_main_special = restore_map(VAMP_MAIN_SPECIAL_MAPPING);
    Vampires_main_special[lower_case(real_name)] = selection;
    save_map(Vampires_main_special, VAMP_MAIN_SPECIAL_MAPPING);
}


public void
clean_vampire_main_special(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_main_special[real_name])
    {
        Vampires_main_special = m_delete(Vampires_main_special, real_name);
        save_map(Vampires_main_special, VAMP_MAIN_SPECIAL_MAPPING);
    }
}


public int
query_vampire_ability_occ_1(string real_name)
{
    return Vampires_occ_ability_1[lower_case(real_name)];
}


public void
set_vampire_ability_occ_1(string real_name, int selection)
{
    Vampires_occ_ability_1 = restore_map(VAMP_OCC_ABILITY_1_MAPPING);
    Vampires_occ_ability_1[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_1, VAMP_OCC_ABILITY_1_MAPPING);
}


public void
clean_vampire_ability_occ_1(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_1[real_name])
    {
        Vampires_occ_ability_1 = m_delete(Vampires_occ_ability_1, real_name);
        save_map(Vampires_occ_ability_1, VAMP_OCC_ABILITY_1_MAPPING);
    }
}


public int
query_vampire_ability_occ_2(string real_name)
{
    return Vampires_occ_ability_2[lower_case(real_name)];
}


public void
set_vampire_ability_occ_2(string real_name, int selection)
{
    Vampires_occ_ability_2 = restore_map(VAMP_OCC_ABILITY_2_MAPPING);
    Vampires_occ_ability_2[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_2, VAMP_OCC_ABILITY_2_MAPPING);
}


public void
clean_vampire_ability_occ_2(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_2[real_name])
    {
        Vampires_occ_ability_2 = m_delete(Vampires_occ_ability_2, real_name);
        save_map(Vampires_occ_ability_2, VAMP_OCC_ABILITY_2_MAPPING);
    }
}


public int
query_vampire_ability_occ_3(string real_name)
{
    return Vampires_occ_ability_3[lower_case(real_name)];
}


public void
set_vampire_ability_occ_3(string real_name, int selection)
{
    Vampires_occ_ability_3 = restore_map(VAMP_OCC_ABILITY_3_MAPPING);
    Vampires_occ_ability_3[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_3, VAMP_OCC_ABILITY_3_MAPPING);
}


public void
clean_vampire_ability_occ_3(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_3[real_name])
    {
        Vampires_occ_ability_3 = m_delete(Vampires_occ_ability_3, real_name);
        save_map(Vampires_occ_ability_3, VAMP_OCC_ABILITY_3_MAPPING);
    }
}


public int
query_vampire_ability_occ_4(string real_name)
{
    return Vampires_occ_ability_4[lower_case(real_name)];
}


public void
set_vampire_ability_occ_4(string real_name, int selection)
{
    Vampires_occ_ability_4 = restore_map(VAMP_OCC_ABILITY_4_MAPPING);
    Vampires_occ_ability_4[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_4, VAMP_OCC_ABILITY_4_MAPPING);
}


public void
clean_vampire_ability_occ_4(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_4[real_name])
    {
        Vampires_occ_ability_4 = m_delete(Vampires_occ_ability_4, real_name);
        save_map(Vampires_occ_ability_4, VAMP_OCC_ABILITY_4_MAPPING);
    }
}


public int
query_vampire_ability_occ_5(string real_name)
{
    return Vampires_occ_ability_5[lower_case(real_name)];
}


public void
set_vampire_ability_occ_5(string real_name, int selection)
{
    Vampires_occ_ability_5 = restore_map(VAMP_OCC_ABILITY_5_MAPPING);
    Vampires_occ_ability_5[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_5, VAMP_OCC_ABILITY_5_MAPPING);
}


public void
clean_vampire_ability_occ_5(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_5[real_name])
    {
        Vampires_occ_ability_5 = m_delete(Vampires_occ_ability_5, real_name);
        save_map(Vampires_occ_ability_5, VAMP_OCC_ABILITY_5_MAPPING);
    }
}


public int
query_vampire_ability_occ_6(string real_name)
{
    return Vampires_occ_ability_6[lower_case(real_name)];
}


public void
set_vampire_ability_occ_6(string real_name, int selection)
{
    Vampires_occ_ability_6 = restore_map(VAMP_OCC_ABILITY_6_MAPPING);
    Vampires_occ_ability_6[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_6, VAMP_OCC_ABILITY_6_MAPPING);
}


public void
clean_vampire_ability_occ_6(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_6[real_name])
    {
        Vampires_occ_ability_6 = m_delete(Vampires_occ_ability_6, real_name);
        save_map(Vampires_occ_ability_6, VAMP_OCC_ABILITY_6_MAPPING);
    }
}


public int
query_vampire_ability_occ_7(string real_name)
{
    return Vampires_occ_ability_7[lower_case(real_name)];
}


public void
set_vampire_ability_occ_7(string real_name, int selection)
{
    Vampires_occ_ability_7 = restore_map(VAMP_OCC_ABILITY_7_MAPPING);
    Vampires_occ_ability_7[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_7, VAMP_OCC_ABILITY_7_MAPPING);
}


public void
clean_vampire_ability_occ_7(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_7[real_name])
    {
        Vampires_occ_ability_7 = m_delete(Vampires_occ_ability_7, real_name);
        save_map(Vampires_occ_ability_7, VAMP_OCC_ABILITY_7_MAPPING);
    }
}


public int
query_vampire_ability_occ_8(string real_name)
{
    return Vampires_occ_ability_8[lower_case(real_name)];
}


public void
set_vampire_ability_occ_8(string real_name, int selection)
{
    Vampires_occ_ability_8 = restore_map(VAMP_OCC_ABILITY_8_MAPPING);
    Vampires_occ_ability_8[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_8, VAMP_OCC_ABILITY_8_MAPPING);
}


public void
clean_vampire_ability_occ_8(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_8[real_name])
    {
        Vampires_occ_ability_8 = m_delete(Vampires_occ_ability_8, real_name);
        save_map(Vampires_occ_ability_8, VAMP_OCC_ABILITY_8_MAPPING);
    }
}


public int
query_vampire_ability_occ_progenitor(string real_name)
{
    return Vampires_occ_ability_progenitor[lower_case(real_name)];
}


public void
set_vampire_ability_occ_progenitor(string real_name, int selection)
{
    Vampires_occ_ability_progenitor = restore_map(VAMP_OCC_ABILITY_PROGENITOR_MAPPING);
    Vampires_occ_ability_progenitor[lower_case(real_name)] = selection;
    save_map(Vampires_occ_ability_progenitor, VAMP_OCC_ABILITY_PROGENITOR_MAPPING);
}


public void
clean_vampire_ability_occ_progenitor(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_occ_ability_progenitor[real_name])
    {
        Vampires_occ_ability_progenitor = m_delete(Vampires_occ_ability_progenitor, real_name);
        save_map(Vampires_occ_ability_progenitor, VAMP_OCC_ABILITY_PROGENITOR_MAPPING);
    }
}


public int
query_vampires_gauge(string real_name)
{
    return Vampires_gauge[lower_case(real_name)];
}


public void
set_vampires_gauge(string real_name, int selection)
{
    Vampires_gauge = restore_map(VAMPIRES_GAUGE);
    Vampires_gauge[lower_case(real_name)] = selection;
    save_map(Vampires_gauge, VAMPIRES_GAUGE);
}


public void
clean_vampires_gauge(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_gauge[real_name])
    {
        Vampires_gauge = m_delete(Vampires_gauge, real_name);
        save_map(Vampires_gauge, VAMPIRES_GAUGE);
    }
}


public int
query_thirst_gauge(string real_name)
{
    return Vampires_thirst_gauge[lower_case(real_name)];
}


public void
set_thirst_gauge(string real_name, int selection)
{
    Vampires_thirst_gauge = restore_map(VAMPIRES_THIRST_GAUGE);
    Vampires_thirst_gauge[lower_case(real_name)] = selection;
    save_map(Vampires_thirst_gauge, VAMPIRES_THIRST_GAUGE);
}


public void
clean_thirst_gauge(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_thirst_gauge[real_name])
    {
        Vampires_thirst_gauge = m_delete(Vampires_thirst_gauge, real_name);
        save_map(Vampires_thirst_gauge, VAMPIRES_THIRST_GAUGE);
    }
}


public int
query_vampires_resilience(string real_name)
{
    return Vampires_resilience_gauge[lower_case(real_name)];
}


public void
set_vampires_resilience(string real_name, int selection)
{
    Vampires_resilience_gauge = restore_map(VAMPIRES_RESILIENCE_GAUGE);
    Vampires_resilience_gauge[lower_case(real_name)] = selection;
    save_map(Vampires_resilience_gauge, VAMPIRES_RESILIENCE_GAUGE);
}


public void
clean_vampires_resilience(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Vampires_resilience_gauge[real_name])
    {
        Vampires_resilience_gauge = m_delete(Vampires_resilience_gauge, real_name);
        save_map(Vampires_resilience_gauge, VAMPIRES_RESILIENCE_GAUGE);
    }
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    Vampires_weapon_selection = restore_map(VAMPIRES_WEAPON_SELECTION);

    Vampires_resilience_gauge = restore_map(VAMPIRES_RESILIENCE_GAUGE);
    
    Vampires_thirst_gauge = restore_map(VAMPIRES_THIRST_GAUGE);
    
    Vampires_main_special = restore_map(VAMP_MAIN_SPECIAL_MAPPING);
    
    Vampires_occ_ability_1 = restore_map(VAMP_OCC_ABILITY_1_MAPPING);

    Vampires_occ_ability_2 = restore_map(VAMP_OCC_ABILITY_2_MAPPING);

    Vampires_occ_ability_3 = restore_map(VAMP_OCC_ABILITY_3_MAPPING);
    
    Vampires_occ_ability_4 = restore_map(VAMP_OCC_ABILITY_4_MAPPING);

    Vampires_occ_ability_5 = restore_map(VAMP_OCC_ABILITY_5_MAPPING);
    
    Vampires_occ_ability_6 = restore_map(VAMP_OCC_ABILITY_6_MAPPING);
    
    Vampires_occ_ability_7 = restore_map(VAMP_OCC_ABILITY_7_MAPPING);
    
    Vampires_occ_ability_8 = restore_map(VAMP_OCC_ABILITY_8_MAPPING);

    Vampires_occ_ability_progenitor = restore_map(VAMP_OCC_ABILITY_PROGENITOR_MAPPING);;
    
    Vampires_gauge= restore_map(VAMPIRES_GAUGE);
    
    Vampires_rank = restore_map(VAMPIRES_RANK);
    
    Vampirespawn_timer = restore_map(VAMPIRESPAWN_TIMER);
    
    Vampires_reputation = restore_map(VAMPIRES_REP);
    
    
    // Seekers
    Vampires_seeker = restore_map(VAMPIRES_SEEKER);
    
    // Imm points, thralls
    Thrall_pool = restore_map(THRALL_POOL);   
    
    Vamp_blessed = restore_map(VAMP_BLESSED);
    
    Vamp_title = restore_map(VAMP_TITLE);
         
    Vamp_agent = restore_map(VAMP_AGENT);
    
    Vamp_pathprog = restore_map(VAMP_PROG);
}
