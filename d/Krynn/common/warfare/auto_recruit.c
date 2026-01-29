/*
 * Simple Auto Recruitment Module
 *
 * It will keep track of how many units have been recruited each hour
 * the last few hours. How many it will recruit depends on the losses
 * the last hours. 
 *
 * Ideally conquerors should be forced to push hard for atleast a few 
 * hours before conquering an area. 
 *
 * NOTE: This file is obsolete! It doesn't appear to do anything anymore.
 */
#include "warfare.h"
#include "/d/Krynn/common/defs.h"


static int max_recruit = 20, /* Max recruited at a time */ 
    conquer_goal = 30;      /* How many should be killed before we allow a 
			      * conquer */  
//prototype
public void populate_area(string area, int count);

/*
 * Recruit units for this amount of funds for the area 
 */
static int
recruit_area(string area, int funds, int recruits)
{
    mapping data = ([ ]);
    int size, price, cost, count, base, tmp, *value;
    string *units, unit, aob;
    
    aob = ARMYMASTER->query_area(area);
    //units = this_object()->query_recruitable_units(area, 1);

    // Whats the ideal amount of units to recruit in one go? 
    /*
    count = conquer_goal - ((time() - aob->query_conquer_time()) / 86400) * 8;
    count = max(count, 12);

    count = min(count, recruits);
    */

    //We recruit 1/20th the max amount of recruits.  This means it
    //would take us 20 cycles (cycle = 600 seconds) to become fully stocked
//CHANGED by Louie since I dropped the max count to 30, so only by half
    count = conquer_goal / 2;

    //If we don't have enough recruits to meet even that
    //count = min(count, recruits);

    // We don't want thousands of units in an area - cap it
    count = min(count, conquer_goal - aob->query_unit_count_cloned());
    
    //populate 
    populate_area(area, count);

    if (count <= 0)
    {
        WAR_LOG("No recruit for: " + area);
        return 0;
    }

    // Loop through all the units and check how many units of this kind we
    // can afford 
    /*
    size = sizeof(units);
    while (size--)
    {
        unit = units[size];
        tmp = 0;
        cost = 0;
        base = aob->query_unit_count(unit);

        while (cost < funds)
        {
            tmp += 1;
            cost += ftoi(UNIT_PRICE(itof(this_object()->query_unit_price(unit)),
                itof(base + tmp)));            
            
        }
        
        if (tmp > 0)
            tmp -= 1;

        if (!tmp)
            continue;

        data[unit] = tmp;
    }
    
    value = m_values(data);
    size = sizeof(value);
    tmp = 0;
    while (size--)
    {
        tmp += value[size];
    }
    
    value = m_values(data);
    size = sizeof(value);
    

    WAR_LOG("Recruiting for: " + area);
    
    if (!tmp)
    {
        WAR_LOG(" - No funds");
        return 0;
    }
    // All these calculations are absolutely insane 

    units = m_indexes(data);
    size = sizeof(units);
    tmp /= size;

    while (size--)
    {
        unit = units[size];
        data[unit] /= sizeof(units);
        data[unit] = count * data[unit] / tmp;
        
        if (data[unit] < 1)
            continue;
        
        WAR_LOG("  " + unit + "  - " + data[unit]);
        this_object()->recruit_unit(area, unit, data[unit], 1);
    }
    */

}

/*
 * Clone enough units to hit the cap for the area, if possible.
 * Randomly distribute
 */
public void
populate_area(string area, int count)
{
    //We don't do this anymore, this is just a safety catch
    return;
    //end safety catch
    string aob = ARMYMASTER->query_area(area);
    int current_npcs, clone_count,max_npcs_for_area;
    string room_to_pop, *area_rooms, potential_room;
    object ob;

    if (!aob)
        return;

    current_npcs = aob->query_unit_count_cloned(0);
    //max_npcs_for_area = aob->count_rooms();

    //Only save 15 random rooms to clone to each time
    area_rooms = ({ });
    for (int b = 0; b < 16; ) {
        potential_room = ONE_OF(aob->query_rooms());

        if (find_object(potential_room)) {
           area_rooms += ({ potential_room });
           b++;
        }
    }

    area_rooms -= ({ 0 });
    
    //Only clone up to "count" npcs per area
    clone_count = 0;
    while (current_npcs < conquer_goal && clone_count < count)
    {
        current_npcs++;
        clone_count++;

	    ob = ARMYMASTER->clone_new_npc(area);

	    if (ob)
	    {
            room_to_pop = ONE_OF(area_rooms);

	        ob->move_living("north",room_to_pop);
	    } else {
    	    /* No npcs recruited */
	        break;
	    }
    }

    WAR_LOG(area+" cloned "+clone_count+" units.");
}

/*
 * We don't need to do this at the moment - the rooms reset and then
 * clone units from Armymaster as needed.  We don't use funds or
 * anything
 */
public void
auto_recruit()
{
    //Just return since we don't do anything
    return;
    //end just return

    string *areas = ARMYMASTER->query_areas_of_army(this_object()->
	query_army_name());
    
    WAR_LOG("Auto Recruiting for: " + this_object()->query_army_name());
    
    /* If they have no areas .. */
    if (!sizeof(areas))
        return;
    
    int i = sizeof(areas);

    while (i--) {
        recruit_area(areas[i],0,0);
    }

    //map(areas,
    //    &recruit_area(,0,0));
    
    /*
    map(areas, 
        &recruit_area(,
            min(this_object()->query_funds() / sizeof(areas), 200000),
            this_object()->query_recruits() / sizeof(areas)));
    */
}
