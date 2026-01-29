/*
 * Simple Auto Recruitment Module
 *
 * It will keep track of how many units have been recruited each hour
 * the last few hours. How many it will recruit depends on the losses
 * the last hours. 
 *
 * Ideally conquerors should be forced to push hard for atleast a few 
 * hours before conquering an area. 
 */
#include "warfare.h"


static int max_recruit = 20, /* Max recruited at a time */ 
    conquer_goal = 200;      /* How many should be killed before we allow a 
			      * conquer */  

/*
 * Recruit units for this amount of funds for the area 
 */
static int
recruit_area(string area, int funds, int recruits)
{
    mapping data = ([ ]);
    int size, price, count, tmp, *value;
    string *units, unit, aob;
    
    aob = ARMYMASTER->query_area(area);
    units = this_object()->query_recruitable_units(area, 1);

    /* Whats the ideal amount of units to recruit? */
    count = conquer_goal - ((time() - aob->query_conquer_time()) / 86400) * 8;
    count = min(count, recruits);
    count = max(5, count);

    if (!count)
    {
        LOG("No recruit for: " + area);
        return 0;
    }

    size = sizeof(units);
    while (size--)
    {
        unit = units[size];
        price = this_object()->query_recruit_price(unit, area);
        data[unit] = funds / price;
    }

    value = m_values(data);
    size = sizeof(value);
    while (size--)
        tmp += value[size];

    LOG("Recruiting for: " + area);
    
    if (!tmp)
    {
        LOG(" - No funds");
        return 0;
    }

    units = m_indexes(data);
    size = sizeof(units);
    while (size--)
    {
        unit = units[size];
        
        data[unit] = count * data[unit] / tmp;

        if (data[unit] < 1)
            continue;
        
        LOG("  " + unit + "  - " + data[unit]);
        this_object()->recruit_unit(area, unit, data[unit], 1);
    }
}

public void
auto_recruit()
{
    string *areas = ARMYMASTER->query_areas_of_army(this_object()->
	query_army_name());
    
    LOG("Auto Recruiting for: " + this_object()->query_army_name());
    
    map(areas, 
        &recruit_area(, this_object()->query_funds() / sizeof(areas), 
        this_object()->query_recruits() / sizeof(areas)));
}
