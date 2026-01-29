/*
 * Special Attack Functions for different Guilds
 *
 * special_attack is called for every heartbeat on the npc. We specialize
 * the call here for specific guilds.
 *
 * Created by Petros, December 2009
 */

#pragma strict_types

public void
caster_default_cast(string spell_name)
{
    command("cast " + spell_name);
}

/*
 * Function:    caster_default_rules
 * Description: A caster has two types of spells, duration and instant, that
 *              he will cast. The default rules maintain that the duration
 *              spells should be cast first in priority. Then the instant
 *              spells. This will provide one optimal setup for maximizing
 *              both defence and offence.
 */
public void
caster_default_rules(string * duration_spells, string * instant_spells, function fCastFunction = 0)
{    
    if (objectp(query_prop(LIVE_O_CONCENTRATE)))
    {
        // Caster is still casting. Don't do anything.
        return;
    }

    if (!fCastFunction)
    {
        fCastFunction = caster_default_cast;
    }
    
    // First, check all the duration spells and see if the full list
    string * duration_spell_names = map(duration_spells, &->query_spell_name());
    object * maintained_effects = "/d/Genesis/specials/guilds/souls/spell_manager_soul"->query_magic_effects(this_object());
    foreach (string spell_name : duration_spell_names)
    {
        object * matching_effects = filter(maintained_effects, &operator(==)(spell_name) @ &->query_spell_effect_name());
        if (!sizeof(matching_effects))
        {
            // Maintained effect is no longer valid.
            fCastFunction(spell_name);
            return;
        }
    }
    
    // Now, we deal with the instant cast spells    
    foreach (string spell_file : instant_spells)
    {
        float * remaining_times = spell_file->query_ability_remaining_time(this_object());
        if (!sizeof(remaining_times) || remaining_times[0] || remaining_times[1])
        {
            continue;
        }
        // If we get here, it means that we have a spell that is not in cooldown and should
        // be ready to cast.
        fCastFunction(spell_file->query_spell_name());        
    }
}

public void
special_attack_academic(object target)
{
    string * duration_spells = ({ 
        "/d/Calia/guilds/academics/spells/lithodermu",
        });
    string * instant_spells = ({
        "/d/Calia/guilds/academics/spells/cheiropoto",
        "/d/Calia/guilds/academics/spells/hydrokine",
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_academic(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Calia/guilds/academics/spells/lithodermu",
        });
    string * instant_spells = ({
        "/d/Calia/guilds/academics/spells/cheiropoto",
        "/d/Calia/guilds/academics/spells/hydrokine",
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_academic_harm(object target)
{
    string * duration_spells = ({ 
        "/d/Calia/guilds/academics/spells/lithodermu",
        });
    string * instant_spells = ({
        "/d/Calia/guilds/academics/spells/hydrokine",
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_academic_harm(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Calia/guilds/academics/spells/lithodermu",
        });
    string * instant_spells = ({
        "/d/Calia/guilds/academics/spells/hydrokine",
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_academic_at_will(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Calia/guilds/academics/spells/lithodermu",
        });
    string * instant_spells = ({
        "/d/Calia/guilds/academics/spells/cheiropoto",
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_academic_at_will(object target)
{
    string * duration_spells = ({ 
        "/d/Calia/guilds/academics/spells/lithodermu",
        });
    string * instant_spells = ({
        "/d/Calia/guilds/academics/spells/cheiropoto",
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
cast_ew(string spell_name)
{
    command("pray " + spell_name);
}

public void
notify_spell_complete_ew(object spellobj, string arg)
{
    string * duration_spells = ({ 
       
        });
    string * instant_spells = ({
       
        });
    caster_default_rules(duration_spells, instant_spells, cast_ew);
}

public void
cast_ew_schirmo_air(string spell_name)
{
    if (spell_name == "schirmo")
    {
        command("pray schirmo aeria");
        return;
    }
    cast_ew(spell_name);
}

public void
notify_spell_complete_ew_schirmo_air(object spellobj, string arg)
{
    string * duration_spells = ({ 
       "/d/Calia/guilds/elementalists/spells/schirmo",
        });
    string * instant_spells = ({
       
        });
    caster_default_rules(duration_spells, instant_spells, cast_ew_schirmo_air);
}

public void
cast_ew_schirmo_fire(string spell_name)
{
    if (spell_name == "schirmo")
    {
        command("pray schirmo pyros");
        return;
    }
    cast_ew(spell_name);
}

public void
notify_spell_complete_ew_schirmo_fire(object spellobj, string arg)
{
    string * duration_spells = ({ 
       "/d/Calia/guilds/elementalists/spells/schirmo",
        });
    string * instant_spells = ({
       "/d/Calia/guilds/elementalists/spells/floga",                     
        });
    caster_default_rules(duration_spells, instant_spells, cast_ew_schirmo_fire);
}

public void
cast_ew_schirmo_earth(string spell_name)
{
    if (spell_name == "schirmo")
    {
        command("pray schirmo gu");
        return;
    }
    cast_ew(spell_name);
}

public void
notify_spell_complete_ew_schirmo_earth(object spellobj, string arg)
{
    string * duration_spells = ({ 
       "/d/Calia/guilds/elementalists/spells/schirmo",
        });
    string * instant_spells = ({

        });
    caster_default_rules(duration_spells, instant_spells, cast_ew_schirmo_earth);
}

public void
notify_spell_complete_ew_dynami(object spellobj, string arg)
{
    string * duration_spells = ({ 
       "/d/Calia/guilds/elementalists/spells/dynami",       
        });
    string * instant_spells = ({
       
        });
    caster_default_rules(duration_spells, instant_spells, cast_ew);
}

public void
notify_spell_complete_ew_evimero(object spellobj, string arg)
{
    string * duration_spells = ({ 
       "/d/Calia/guilds/elementalists/spells/evimero",       
        });
    string * instant_spells = ({
       
        });
    caster_default_rules(duration_spells, instant_spells, cast_ew);
}

public void
notify_spell_complete_ew_floga(object spellobj, string arg)
{
    string * duration_spells = ({ 
       
        });
    string * instant_spells = ({
       "/d/Calia/guilds/elementalists/spells/floga",       
        });
    caster_default_rules(duration_spells, instant_spells, cast_ew);
}

public void
special_attack_vampire(object target)
{
    command("vflurry head");

    this_object()->add_blood(300);
    object oldtp = this_player();
    set_this_player(this_object());
    "/d/Terel/guilds/vamp/spells/celerity"->do_ability("");
    "/d/Terel/guilds/vamp/spells/sight"->do_ability("");
    set_this_player(oldtp);
}

public void
special_attack_mage(object target)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/narkirisse", // at will
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_mage(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/narkirisse", // at will
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

/*
public void
special_attack_mage(object target)
{
    object weapon = query_weapon(-1);
    if (!weapon[0]->is_narusse_enhanced()) 
    {
        command("cast narusse");
        return;
    }

    float * remaining_times = "/d/Gondor/guilds/morgulmage/spells/narkirisse"->query_ability_remaining_time(this_object());
    if (remaining_times[1] < 1.0)
    {
        command("cast narkirisse");
    }   
}

public void
notify_spell_complete_mage(object spellobj, string arg)
{
    if (!objectp(spellobj) || !strlen(spellobj->query_spell_name()))
    {
        return;
    }

    object weapon = query_weapon(-1);
    if (!weapon[0]->is_narusse_enhanced()) 
    {
        command("cast narusse");
        return;
    }
    
}
*/

public void
special_attack_mage_air(object target)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/dramalgos", // air damage
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_mage_air(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/dramalgos", // air damage
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_mage_harm(object target)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_mage_harm(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_mage_defence(object target)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/ringurth",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/faugoroth", // stun spell
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_mage_defence(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/ringurth",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/faugoroth", // stun spell
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_mage_morthul_ringurth(object target)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/ringurth",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_mage_morthul_ringurth(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/ringurth",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/morthul", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_mage_ringurth_narusse_narkirisse(object target)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/ringurth",
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/narkirisse", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_mage_ringurth_narusse_narkirisse(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Gondor/guilds/morgulmage/spells/ringurth",
        "/d/Gondor/guilds/morgulmage/spells/narusse",
        });
    string * instant_spells = ({
        "/d/Gondor/guilds/morgulmage/spells/narkirisse", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}


public void
special_attack_pot_harm(object target)
{
    string * duration_spells = ({ 
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_pot_harm(object spellobj, string arg)
{
    string * duration_spells = ({ 
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_pot_scourge_bless(object target)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/pscourge", // weaker spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_pot_scourge_bless_hammer(object target)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/phammer",
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/pscourge", // weaker spell
        });
    caster_default_rules(duration_spells, instant_spells);
}


public void
special_attack_pot_harm_bless(object target)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_pot_harm_bless(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
special_attack_pot_harm_bless_hammer(object target)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/phammer",
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_pot_harm_bless_hammer(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/pbless",
        "/d/Ansalon/guild/new_pot/spells/phammer",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}


public void
special_attack_pot_harm_bless_blind_hammer(object target)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/phammer",
        "/d/Ansalon/guild/new_pot/spells/pblind",
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}

public void
notify_spell_complete_pot_harm_bless_blind_hammer(object spellobj, string arg)
{
    string * duration_spells = ({ 
        "/d/Ansalon/guild/new_pot/spells/phammer",
        "/d/Ansalon/guild/new_pot/spells/pblind",
        "/d/Ansalon/guild/new_pot/spells/pbless",
        });
    string * instant_spells = ({
        "/d/Ansalon/guild/new_pot/spells/ptalon", // main harm spell
        });
    caster_default_rules(duration_spells, instant_spells);
}


public void
caster_sohm_cast(string spell_name)
{
    if (spell_name == "levexlaraek")
    {
        // Enchant Weapon needs a target. We assume the npc
        // has a sword.
        command("cast " + spell_name + " sword");
        return;
    }
    // Otherwise, use the default cast
    caster_default_cast(spell_name);
}

public void
special_attack_sohm_defense(object target)
{
    string * duration_spells = ({ 
            "/d/Krynn/guilds/sohm/spells/stoneskin",
            "/d/Krynn/guilds/sohm/spells/enchant_weapon",            
        });
    string * instant_spells = ({
            "/d/Krynn/guilds/sohm/spells/magic_missile", // at will
            "/d/Krynn/guilds/sohm/spells/fire_dart", // at will
            "/d/Krynn/guilds/sohm/spells/acid_arrow", // at will
        });
    caster_default_rules(duration_spells, instant_spells, caster_sohm_cast);
}

public void
notify_spell_complete_sohm_defense(object spellobj, string arg)
{
    string * duration_spells = ({ 
            "/d/Krynn/guilds/sohm/spells/stoneskin",
            "/d/Krynn/guilds/sohm/spells/enchant_weapon",            
            "/d/Krynn/guilds/sohm/spells/protect_fear",            
            "/d/Krynn/guilds/sohm/spells/protect_poison",
        });
    string * instant_spells = ({
            "/d/Krynn/guilds/sohm/spells/magic_missile", // at will
            "/d/Krynn/guilds/sohm/spells/fire_dart", // at will
            "/d/Krynn/guilds/sohm/spells/acid_arrow", // at will
        });
    caster_default_rules(duration_spells, instant_spells, caster_sohm_cast);
}

public void
special_attack_union(string cmd)
{
    if (sizeof(filter(all_inventory(), &->id("knife"))) < 2)
    {
        clone_object("/d/Genesis/specials/guilds/test/weapons/test_knife")->
	    move(this_object(), 1);
    }
    command(cmd);
}

public void
special_attack_union_fling(object target) {
    special_attack_union("fling");
}

public void
special_attack_union_ufling(object target) {
    special_attack_union("ufling");
}

public void
special_attack_union_testfling(object target) {
    special_attack_union("testfling");
}

public void
special_attack_union_testfling_sway(object target) {
    special_attack_union("testfling");
	command("testsway defensively");
}

public void
special_attack_union_testfling_sway_agg(object target) {
    special_attack_union("testfling");
	command("testsway aggressively");
}
