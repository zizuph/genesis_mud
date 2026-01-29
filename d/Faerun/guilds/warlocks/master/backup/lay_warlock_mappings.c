/*
 * Guild manager, mappings
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow

#pragma no_inherit
#pragma strict_types

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "../guild.h";


/* Patrons :  1 = Fiend
              2 = Great Old One
              3 = Archfey
*/            

void create();

// spell mappings
mapping Spell_16_nr;
mapping Spell_17_nr;
mapping Spell_18_nr;
mapping Spell_19_nr;

// Desecration point mapping
mapping Desecration;
mapping Desecration_primer;


public int
query_desecration_power(string real_name)
{
    return Desecration[lower_case(real_name)];
}


public void
set_desecration_power(string real_name, int desecration_nr)
{
    Desecration = restore_map(DESECRATION);
    Desecration[lower_case(real_name)] = desecration_nr;
    save_map(Desecration, DESECRATION);
}


public void
clean_desecration_power(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Desecration[real_name])
    {
        Desecration = m_delete(Desecration, real_name);
        save_map(Desecration, DESECRATION);
    }
}


public int
query_desecration_primer(string real_name)
{
    return Desecration_primer[lower_case(real_name)];
}


public void
set_desecration_primer(string real_name, int desecrationp_nr)
{
    Desecration_primer = restore_map(DESECRATION_PRIMER);
    Desecration_primer[lower_case(real_name)] = desecrationp_nr;
    save_map(Desecration_primer, DESECRATION_PRIMER);
}


public void
clean_desecration_primer(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Desecration_primer[real_name])
    {
        Desecration_primer = m_delete(Desecration_primer, real_name);
        save_map(Desecration_primer, DESECRATION_PRIMER);
    }
}


public int
query_warspell_16(string real_name)
{
    return Spell_16_nr[lower_case(real_name)];
}


public void
set_warspell_16(string real_name, int selection)
{
    Spell_16_nr = restore_map(WAR_SPELL_16);
    Spell_16_nr[lower_case(real_name)] = selection;
    save_map(Spell_16_nr, WAR_SPELL_16);
}


public void
clean_warspell_16(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Spell_16_nr[real_name])
    {
        Spell_16_nr = m_delete(Spell_16_nr, real_name);
        save_map(Spell_16_nr, WAR_SPELL_16);
    }
}


public int
query_warspell_17(string real_name)
{
    return Spell_17_nr[lower_case(real_name)];
}


public void
set_warspell_17(string real_name, int selection)
{
    Spell_17_nr = restore_map(WAR_SPELL_17);
    Spell_17_nr[lower_case(real_name)] = selection;
    save_map(Spell_17_nr, WAR_SPELL_17);
}


public void
clean_warspell_17(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Spell_17_nr[real_name])
    {
        Spell_17_nr = m_delete(Spell_17_nr, real_name);
        save_map(Spell_17_nr, WAR_SPELL_17);
    }
}


public int
query_warspell_18(string real_name)
{
    return Spell_18_nr[lower_case(real_name)];
}


public void
set_warspell_18(string real_name, int selection)
{
    Spell_18_nr = restore_map(WAR_SPELL_18);
    Spell_18_nr[lower_case(real_name)] = selection;
    save_map(Spell_18_nr, WAR_SPELL_18);
}


public void
clean_warspell_18(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Spell_18_nr[real_name])
    {
        Spell_18_nr = m_delete(Spell_18_nr, real_name);
        save_map(Spell_18_nr, WAR_SPELL_18);
    }
}


public int
query_warspell_19(string real_name)
{
    return Spell_19_nr[lower_case(real_name)];
}


public void
set_warspell_19(string real_name, int selection)
{
    Spell_19_nr = restore_map(WAR_SPELL_19);
    Spell_19_nr[lower_case(real_name)] = selection;
    save_map(Spell_19_nr, WAR_SPELL_19);
}


public void
clean_warspell_19(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Spell_19_nr[real_name])
    {
        Spell_19_nr = m_delete(Spell_19_nr, real_name);
        save_map(Spell_19_nr, WAR_SPELL_19);
    }
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    // spell selection lists.
    Spell_16_nr = restore_map(WAR_SPELL_16);
    Spell_17_nr = restore_map(WAR_SPELL_17);
    Spell_18_nr = restore_map(WAR_SPELL_18);
    Spell_19_nr = restore_map(WAR_SPELL_19);
    
    // Desecreation power
    Desecration = restore_map(DESECRATION);
    
    // Desecreation power
    Desecration_primer = restore_map(DESECRATION_PRIMER);
}
