/*
 * Common functions supporting SoHM and WoHS spells
 */

#define PROT_SPELL_OBJ(x, y)  (SOHM_SPELLS + "protect_" + x)->has_spell_object(y) 

public int
minor_at_will_rotation_check(object caster)
{
     int rotation_no = 0;
     object acid_arrow = find_object(SOHM_SPELLS + "acid_arrow");
     object ballistic_spray = find_object(SOHM_SPELLS + "ballistic_spray");
     object fire_dart = find_object(SOHM_SPELLS + "fire_dart");
     object magic_missile = find_object(SOHM_SPELLS + "magic_missile");
     object prismatic_spray = find_object(SOHM_SPELLS + "prismatic_spray");
     object ice_shard = find_object(SOHM_SPELLS + "ice_shard");

    if (objectp(acid_arrow))
    {
        if(acid_arrow->query_ability_in_cooldown(caster))
           rotation_no += 1;

        // DEBUG("Rotation number acid arrow: " +rotation_no+ ".");
    }

    if (objectp(ballistic_spray))
    {
        if(ballistic_spray->query_ability_in_cooldown(caster))
           rotation_no += 1;

        // DEBUG("Rotation number ballistic_spray: " +rotation_no+ ".");
    }

    if (objectp(fire_dart))
    {
        if(fire_dart->query_ability_in_cooldown(caster))
           rotation_no += 1;

        // DEBUG("Rotation number fire_dart: " +rotation_no+ ".");
    }

    if (objectp(magic_missile))
    {
        if(magic_missile->query_ability_in_cooldown(caster))
           rotation_no += 1;

        // DEBUG("Rotation number magic_missile: " +rotation_no+ ".");
    }

    if (objectp(prismatic_spray))
    {
        if(prismatic_spray->query_ability_in_cooldown(caster))
           rotation_no += 1;

        // DEBUG("Rotation number prismatic_spray: " +rotation_no+ ".");
    }

    if (objectp(ice_shard))
    {
        if(ice_shard->query_ability_in_cooldown(caster))
           rotation_no += 1;

        // DEBUG("Rotation number ice_shard: " +rotation_no+ ".");
    }

    // DEBUG("Total rotation number: " +rotation_no+ ".");

    return rotation_no;   
}

/* This function counts the number of maintained spells of a specific
 * spell level that provides combat aid. 
 */

public int
query_maintained_defensive_caid_spells(object caster, string spell_level)
{
    int num;

    object * effects = caster->query_prop("_live_o_maintained_effects");
    string caster_name = caster->query_real_name();

    switch(spell_level)
    {
        case "minor":
            num = 0;
            if("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(caster))
                num++;
            if("/d/Krynn/guilds/sohm/spells/featherweight"->has_spell_object(caster))
                num++;
        break;

        case "lesser":
            num = 0;
            if("/d/Krynn/guilds/sohm/spells/blur"->has_spell_object(caster))
                num++;
            if("/d/Krynn/guilds/sohm/spells/mage_strength"->has_spell_object(caster))
                num++;
            if(caster->query_prop("_sohm_enchant_weapon_active"))
                num++;
            if(caster->query_has_shadow_veil_shadow())
                num++;
            if(PROT_SPELL_OBJ("fire", caster))
                num++;
            if(PROT_SPELL_OBJ("lightning", caster))
                num++;
            if(PROT_SPELL_OBJ("poison", caster))
                num++;
            if(PROT_SPELL_OBJ("acid", caster))
                num++; 
            if(PROT_SPELL_OBJ("cold", caster))
                num++;
            if(caster->query_prop("_sohm_flaming_fist_effect"))
                num++;
        break;

        case "greater":
            num = 0;
            if("/d/Krynn/guilds/sohm/spells/haste"->has_spell_object(caster))
                num++;
            if("/d/Krynn/guilds/sohm/spells/stoneskin"->has_spell_object(caster))
                num++;
            if("/d/Krynn/guilds/sohm/spells/portents_and_omens"->has_spell_object(caster))
                num++;
            if(caster->query_prop("_sohm_retributive_ward_effect"))
                num++;
        break;

        case "advanced":
            num = 0;
            if("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(caster))
                num++;
            if(PROT_SPELL_OBJ("magic", caster))
                num++;
        break;

        default:
            num = 0;
        break;
    }

    // DEBUG("Number of " +spell_level+ " spells active on " +caster_name+ ": " +num+ ".");

    return num;
}

/* This function checks for spells that leverage the same combat aid, namely
 * the greater spells dominate and gravity, and the advanced spells GMS,
 * protect from magic and arcane vulnerability.
 */
public string
query_restricted_advanced_spells(object caster, mixed * targets)
{
    // Dominate spell active
    object *target;

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_sohm_dominate())))
    {   
        if (target[0]->query_sohm_active())
            return "dominate";
    }

    if("/d/Krynn/guilds/sohm/spells/dominate"->has_spell_object(caster))
        return "dominate"; 
    if(caster->query_prop("_sohm_gravity_active"))
        return "gravity";
    if("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(caster))
        return "greater magic shield";
    if(PROT_SPELL_OBJ("magic", caster))
        return "protection from magic";
    if(caster->query_prop("_wohs_plythusuiaerl_active"))
        return "vulnerability to magic";

    return "";
}


