/*
 * This file is included in Minor At Will spells to limit the number of 
 * at will spells on rotation to three.
 * Created by Arman, Dec 2017
 *
 * Ice shard added Dec 2020
 */
 

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

