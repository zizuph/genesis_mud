/*
 * The base of one of the Armies in the War of the Lance
 *
 * The idea is basically to provide a nice interface for the army
 * setup.
 */
#pragma no_clone
#pragma strict_types

#include <composite.h>
#include <macros.h>
#include "warfare.h"

/* !!! All vars that should not be saved MUST be static !!! */

static string army_name;  /* What are we called ? */

static mapping units;     /* What units can we recruit ? */
static int tax,           /* How heavily do we tax the people */
    alignment;            /* Are we nice or bad? */

static float recruit_mod;   /* What's our recruit modifier */

/* These vars are saved over armageddon */
public int funds,         /* GOLD! */
    recruits;             /* How many recruits do we have pending? */
mapping recruited_units;  /* Total number of units that have been recruited
                           * during this war. */

public void
configure_army()
{
    /* MASK */
}

nomask void
create()
{
    setuid();
    seteuid(getuid());
    
    army_name = "Undefined";
    tax = 100; /* 100% default */
    recruit_mod = 1.0; /* 1.0 default */
    
    units = ([ ]);
    recruited_units = ([ ]);
    configure_army();

    if (file_size(MASTER + ".o") > 0)
	restore_object(MASTER);
}

/*
 * A new war is to be started.
 */
public void
start_war()
{
    recruits = 0;
    recruited_units = ([ ]);
}

public void
save()
{
    save_object(MASTER);
}

public void
set_army_name(string str)
{
    army_name = str;
}

public string
query_army_name()
{
    return army_name;
}

public void
set_recruit_modifier(float f)
{
    recruit_mod = f;
}

public int
query_alignment()
{
    return alignment;
}

/* 
 *  1 - good
 *  0 - neutral
 * -1 - evil
 */
public int
set_alignment(int i)
{
    alignment = i;
}

/*
 * Mask this if you want to give the army more recruits in
 * a specific area
 */
public float
query_recruit_modifier(string area)
{
    return recruit_mod;
}

/*
 * Function Name: add_unit
 * Description  : Add a unit for this army.
 * Arguments    : string - the name of the unit
 *                string - the file to clone
 *                int - the cost of the unit in copper
 *                function - access function
 */
public varargs void
add_unit(string name, string file, int cost, function acs)
{
    units[name] = ({ file, cost, acs });
}

/*
 * Function Name: query_unit
 */
public string
query_unit_file(string name)
{
    return units[name][0];
}

/*
 * The base price of a unit
 */
public int
query_unit_price(string name)
{
    return units[name][1];
}

public int
query_recruit_price(string unit, string area)
{
    int price;
    string aob;
    
    if (!(aob = ARMYMASTER->query_area(area)))
	return 0;

    price = ftoi(UNIT_PRICE(itof(query_unit_price(unit)),
	itof(aob->query_unit_count(unit))));
    
    return price;
}

/*
 * Gives all the units which are recruitable in a certain area.
 *
 * If the show_recruited flag is set we return those already in
 * the area even if we can't recruit more of them.
 */
public varargs string *
query_recruitable_units(string area, int show_recruited)
{
    function fun;
    string *idx, *res, aob;
    int k;

    aob = ARMYMASTER->query_area(area);
    res = ({ });
    idx = m_indexes(units);
    k = sizeof(idx);

    while (k--)
    {
	fun = units[idx[k]][2];

	if (!(show_recruited && aob->query_unit_count(idx[k])) &&
	    (fun && !fun(area, idx[k])))
	{
	    continue;
	}
	
	res += ({ idx[k] });
    }
    return res;
}

public void
set_funds(int i)
{
    funds = i;
}

public void
add_funds(int i)
{
    funds += i;
}

public int
query_funds()
{
    return funds;
}

/*
 * How heavily do we tax the people ?
 * Gives an int, 100 is the default. 
 */
public int
query_tax()
{
    return tax;
}

/*
 * recruits
 *
 * mostly called from the master.
 */
public int
add_recruits(int i)
{
    recruits += i;
}

public int
query_recruits()
{
    return recruits;
}

/*
 * Attempt to recruit a unit, called from a command.
 * We should set notify fail and return 1/0 correctly.
 */
public varargs int
recruit_unit(string area, string unit, int count = 1, int silent = 0)
{
    string aob;

    if (!(aob = ARMYMASTER->query_area(area)))
    {
	notify_fail("There is no area called the " + area + ".\n");
	return 0;
    }

    if (aob->query_controller() != army_name)
    {
	notify_fail("The " + area + " is not under your control!\n");
	return 0;
    }
    
    if (member_array(unit, query_recruitable_units(area)) < 0)
    {
	if (aob->query_unit_count(unit) > 0)
	{
	    notify_fail("You can't recruit any more " + LANG_PWORD(unit) +
		" currently.\n");
	    return 0;
	}
	notify_fail("There is no such unit recruitable for the " +
	    area + ".\n");
	return 0;
    }
    
    if (recruits < count)
    {
	notify_fail("You do not have enough recruits to recruit.\n");
	return 0;
    }

    if (query_funds() < (query_recruit_price(unit, area) * count))
    {
	notify_fail("You do not have enough funds to recruit.\n");
	return 0;
    }
    
    if (!recruited_units[unit])
	recruited_units[unit] = 0;
    
    recruited_units[unit] += count;
    recruits -= count;
    /* This will be wrong */
    add_funds(-(query_recruit_price(unit, area) * count));
    
    aob->add_unit(unit, count);
    
    if (!silent)
        write("You recruit " + LANG_WNUM(count) + " " +
            (count > 1 ? LANG_PWORD(unit) : unit) +
            " for the " + area + ".\n");
    return 1;
}

public varargs void
conquer(string area, string from, object player)
{
    if (objectp(player))
    {
	player->catch_tell("You conquer the " + area + " in the name of the " +
	    army_name + " from the " + from + ".\n");
    }
}

/*
 * Some default unit filters
 */

/*
 * Unit can't be recruited to this area 
 */ 
public int
invalid_area(string area, mixed m)
{
    if (stringp(m))
	return !(area == m);
    if (pointerp(m))
	return !(member_array(area, m) >= 0);
    return 0;
}

/*
 * Unit can only be recruited in a specific area.
 */
public int
valid_area(string area, mixed m)
{
    if (stringp(m))
	return (area == m);
    if (pointerp(m))
	return (member_array(area, m) >= 0);
    return 0;
}

/*
 * The total amount of units of this type may not exceed x% in the
 * area. 
 */ 
public int
satisfy_area_percentage(string area, string unit, int percent)
{
    string aob;
    
    aob = ARMYMASTER->query_area(area);

    if ((aob->query_unit_count(unit) * 100) / (aob->query_unit_count() + 1) >
	percent)
	return 0;
    return 1;
}

/*
 * Unit can't be manually recruited.
 */
public int
block(string area)
{
    return 1;
}

/*
 * Stat Object
 *
 * Gives some info to a wizard stating the object.
 */
public string
stat_object()
{
    string ret, *idx;
    string *areas;

    int i, k;
    
    ret = army_name + "\n";
    ret += sprintf("  Funds: %10d Recruits: %4d\n", query_funds(),
	query_recruits());

    areas = ARMYMASTER->query_areas_of_army(army_name);

    ret += "Areas: ";
    if (sizeof(areas))
        ret += COMPOSITE_WORDS(areas) + "\n";
    else
        ret += "None\n";

    idx = sort_array(m_indexes(recruited_units));
    k = sizeof(idx);
    i = -1;

    ret += " Total Recruit Count:\n";
    while (++i < k)
    {
	ret += sprintf("   %s: %d\n", idx[i], recruited_units[idx[i]]);
    }
    ret += "\n";
    return ret;
}


