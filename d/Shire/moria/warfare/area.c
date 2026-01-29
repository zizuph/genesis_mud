/*
 * The base of one of the Areas in the War of the Lance
 *
 * The idea is basically to provide a nice interface for the area
 * setup.
 *
 * Louie March 2006 - Adding actual_units to stored pointers to the
 * actual cloned units.  This way we don't have to keep track of numbers,
 * which can get out of sync.
 */

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <time.h>

#include "warfare.h"

/* !!! All vars that should not be saved MUST be static !!! */

static string area_name,       /* What are we called ? */
    default_controller,        /* Army controlling area by default */
    cob;                       /* Path to controlling army */
static mapping cloned_units;   /* Units already parked in the area */
static object *actual_units;   /*The actual units*/
static int recruit_base, tax_base; 

/* SAVED VARS */

string controller;      /* Army Currently Controlling Area */
mapping units;          /* Units assigned to this area */
string *rooms;          /* The rooms of the area */
int conquer_time;       /* When was this area last conquered? */ 
mixed *conquests;       /* The Areas conquest history */

public void set_controller(string str);
public string query_default_controller();
public void reward_item(object player);

public void
configure_area()
{
    /* MASK */
}

nomask void
create()
{
    setuid();
    seteuid(getuid());
    
    area_name = "Undefined Area";

    units = ([ ]);
    cloned_units = ([ ]);
    rooms = ({ });
    conquests = ({ });
    actual_units = ({ });
    
    tax_base = DEFAULT_TAX_BASE;
    recruit_base = DEFAULT_RECRUIT_BASE;
    
    configure_area();

    if (file_size(MASTER + ".o") > 0)
	restore_object(MASTER);

    if (!controller)
        set_controller(query_default_controller());
    set_controller(controller);
}

public void
save()
{
    save_object(MASTER);
}

static void
set_area_name(string str)
{
    area_name = str;
}

public string
query_area_name()
{
    return area_name;
}

/* How much tax can be gathered from the area? */
public void
set_tax_base(int i)
{
    tax_base = i;
}

public int
query_tax_base()
{
    return tax_base;
}

/* How many recruits do the area produce? */
public void
set_recruit_base(int i)
{
    recruit_base = i;
}

public int
query_recruit_base()
{
    return recruit_base;
}

/*
 * When was the area conquered?
 */
public int
query_conquer_time()
{
    return conquer_time;
}

/*
 * Who is currently controlling this area?
 */
public string
query_controller()
{
    return controller;
}

public void
set_controller(string str)
{
    controller = str;
    cob = ARMYMASTER->query_army(controller);
    if (!cob)
	WAR_LOG("Default Controller Does Not Exist (" + controller + ")");
}

/*
 * Default Controlling army
 */
static void
set_default_controller(string str)
{
    default_controller = str;
}

public string
query_default_controller()
{
    return default_controller;
}

public mixed
query_conquests()
{
    return conquests + ({ });
}

/*
 * Stuff called from armymaster
 */

/*
 * Called when a new war starts, should reset
 * most stuff to default state.
 */
public void
start_war()
{
    units = ([ ]);
    cloned_units = ([ ]);
    conquests = ({ });
    actual_units = ({ });
    
    set_controller(default_controller);
    conquer_time = time();
}

varargs public void
add_unit(string npc, int count = 1)
{
    if (!units[npc])
    {
	units[npc] = 0;
    }
    
    units[npc] += count;
}

varargs public void
add_cloned_unit(string npc, int count = 1)
{
    if (!cloned_units[npc])
    {
	    cloned_units[npc] = 0;
    }
    
        cloned_units[npc] += count;
}

/* Add an actual unit*/
public void
add_actual_unit(object ob)
{
    if (!actual_units)
    {
        actual_units = ({ });
    }

    if (!ob)
    {
        return;
    }

    actual_units += ({ ob });
}

/* Query actual units */
public mixed
query_actual_units()
{
    return actual_units;
}

/*
 * Remove an npc, it probably died. 
 */
public void
remove_unit(string npc)
{
    if (!units[npc])
	return;

    if (cloned_units[npc] > 0)
	cloned_units[npc]--;
    
    units[npc]--;
}

/*
 * Clone a new unit into the area
 * Called from auto_recruit - no need to determine the number to
 * clone, just clone one!  auto_recruit handles how many.
 */
public object
clone_unit()
{
    string unitName = cob->get_unit_for_area(area_name);
    object ob;
    
    if (!stringp(unitName))
    {
        WAR_LOG("Didn't get a unitName while trying to clone for "+area_name);
        return 0;
    }

    string file = cob->query_unit_file(unitName);

    WAR_LOG(area_name+" Cloning: " + unitName + " (" + file + ")");

    ob = clone_object(file);

    if (!objectp(ob))
    {
    	WAR_LOG("Error cloning " + file + " (" + unitName + ")");
    }

    /* This means that the npc belongs to the war, not which army */
    ob->set_belongs_to_army(unitName);
    
    add_cloned_unit(unitName);
    add_actual_unit(ob);
    
    return ob;

}

/*
 * Clone a new unit into the area
 *
 * Randomize from availible units. We randomize a bit which unit
 * gets picked depending on how many of it's kind are recruited.
 * Beats the old way.
 *
 * Obsoleting in favor of cloning based on a %
 */
public object
clone_unit_old()
{
    object ob;
    int sum, goal, k;
    string *arr, file;

    arr = m_indexes(units);
    k = sizeof(arr);

    while (k--)
	sum += units[arr[k]] - cloned_units[arr[k]];

    /* No units recruited in area */
    if (!sum)
	return 0;
    
    goal = random(sum);
    
    sum = 0;
    k = sizeof(arr);
    while (k--)
    {
	sum += units[arr[k]] - cloned_units[arr[k]];
	if (goal < sum)
	    break;
    }

    /* Strange if this happens */
    if (k < 0)
	return 0;
    
    file = cob->query_unit_file(arr[k]);
    /* This can happen is a unit is removed from the army */
    if (!file)
    {
        units = m_delete(units, arr[k]);
        cloned_units = m_delete(units, arr[k]);
        WAR_LOG("Removed unit: " + arr[k] + " purged from " +
            area_name);
        /* Try again */
        return clone_unit();
    }
    
    
    WAR_LOG("Cloning: " + arr[k] + " (" + file + ")");


    if (!cloned_units[arr[k]])
	cloned_units[arr[k]] = 0;
    
    cloned_units[arr[k]]++;
    
    ob = clone_object(file);
    if (!objectp(ob))
    {
	WAR_LOG("Error cloning " + file + " (" + arr[k] + ")");
    }
    /* This means that the npc belongs to the war, not which army */
    ob->set_belongs_to_army(arr[k]);
    
    return ob;
}

public mapping
query_units()
{
    return units + ([ ]);
}

/*
 * How many units [of this type] have been recruited
 *
 * If npc is unspecified the total amount of units in the area is returned.
 */
public varargs int
query_unit_count(string npc)
{
    string *idx;
    int k, sum; 
    
    if (stringp(npc))
	return units[npc];

    idx = m_indexes(units);
    k = sizeof(idx);
    while (k--)
    {
	sum += units[idx[k]];
    }

    return sum;
}

/*
 * How many are left to clone
 */
public int
query_unit_reserve(string npc)
{
    return units[npc] - cloned_units[npc];
}

/*
 * How many units are currently cloned
 * If no string is given return total count.
 */
public int
query_unit_count_cloned(string npc)
{
    string *idx;
    int k, sum; 
    
    if (stringp(npc))
	return cloned_units[npc];

    idx = m_indexes(cloned_units);
    k = sizeof(idx);
    while (k--)
    {
	sum += cloned_units[idx[k]];
    }

    return sum;
}

/*
 * Add a room to this area.
 */
public void
add_room(string room)
{
    if (member_array(room, rooms) < 0)
	rooms += ({ room });
}

/*
 * Remove a room, not sure why this would happen but ..
 */
public void
remove_room(string room)
{
    rooms -= ({ room });
}

/*
 * Query if a room belongs to this area 
 */
public int
query_room(string room)
{
    return (member_array(room, rooms) >= 0);
}

/*
 * Get the array of rooms
 */
public string*
query_rooms()
{
    return rooms;
}

/*
 * Count the number of rooms
 */
public int
count_rooms()
{
    return sizeof(rooms);
}

/* This makes sure all the actual units are in accessible rooms, npcs,
 * etc
 */
public void
clean_up_actual_units()
{
    int i;
    object *units_to_remove = ({ });

    actual_units -= ({ 0 });
 
    if (!actual_units || !(i = sizeof(actual_units)))
        return;

    while (i--)
    {
        //If they're not in a valid room, remove them
        if (!wildmatch("/d/Krynn/*", file_name(environment(actual_units[i]))) &&
            !wildmatch("/d/Ansalon/*", file_name(environment(actual_units[i]))))
        {
            units_to_remove += ({ actual_units[i] });
        }
    }

    if (sizeof(units_to_remove))
        units_to_remove->remove_object();

}
/*
 * Someone wishes to conquer us!
 *
 */
varargs public int
conquer(string army, object player)
{
    int k, *idx;

    object *ob;
    string old_army;

    if (controller == army)
    {
	notify_fail("Your army is already controlling the " + area_name +
	    ".\n");
	return 0;
    }
    
    /* We require 2 hours between two conquests of the same area */
    /* Sanity check */
    if (conquer_time > time()) 
    {
        conquer_time = time();
    }

    //60 * 60 = 3600 in an hour * 2 = 7200 seconds in 2 hours
    if ((conquer_time + 7200) > time())
    {
	notify_fail("This area has been recently taken over, you must wait a "+
        " while before attempting to conquer the " + area_name + ".\n");
	return 0;
    }
    
    clean_up_actual_units();

    //Changed by Louie Mar 2006 to use actual_units
    //if (query_unit_count_cloned(0) > 3)
    if (actual_units && sizeof(actual_units) > 5)
    {
        //int left = query_unit_count_cloned(0);
        int left = sizeof(actual_units);
        string est = "an unknown amount";
        
        switch (left) {
            case 0..20:
                est = "a tiny group";
                break;
            case 21..50:
                est = "a small band";
                break;
            case 51..100:
                est = "a strong force";
                break;
            case 101..120:
                est = "a large number";
                break;
            case 121..150:
                est = "a huge number";
                break;
            case 151..200:
                est = "a full army";
                break;
            default:
                est = "a full army";
                break;
        }

    notify_fail("You cannot conquer the " + area_name +" as it does "+
        "not yet seem to be completely cleared of enemies.  There are still "+
        "signs of "+ est +" of enemies remaining.\n");
    /*
	notify_fail("The " + area_name +
	    " doesn't seem to be completely cleared of enemies " +
	    "yet, or there are still reinforcements on the way. You " +
	    "are unable to conquer the territory.\n");
    */
	return 0;
    }
    
   
    old_army = controller;
    set_controller(army);

    CONQ_LOG(area_name + " " + old_army + " -> " + controller + " (" +
	(objectp(player) ? player->query_real_name() : "auto") + ")");

    units = ([ ]);
    cloned_units = ([ ]);
    actual_units->remove_object();
    
    conquer_time = time();
    conquests += ({ time(), controller, old_army, player->query_real_name() });
    
    WAR_LOG(area_name + " " + old_army + " -> " + controller + " (" +
	(objectp(player) ? player->query_real_name() : "auto") + ")");
    
     /* This writes messages */
    ARMYMASTER->query_army(army)->conquer(area_name, old_army, player);
    
    /* Call the reward hook */
    player->reward_warfare_conquest(area_name, controller, old_army);

    //reward_item(player);

    /*
     * Might have to be rewritten depending on eval cost
     * We do this after message printing since it might runtime.
     */
    ob = map(rooms, find_object);
    ob -= ({ 0 });
    ob->conquer_update(area_name, controller, old_army);
    return 1;
}

//Called when a player conquers an area, give them some loot
public void
reward_item(object player)
{
    if (!player)
        return 0;

    object re = ARMYMASTER->reward_item(player);

    if (!re)
        return 0;

    re->move(player);

    player->catch_msg("Among the spoils of war you find "+
        LANG_ADDART(re->short())+"!\n");
        
}

/*
 * WIZINFO
 */
string
stat_object()
{
    int index, size;
    string *idx;
    string str = "";
    
    str += sprintf("%s (%s)\n", area_name, controller);
    str += sprintf("Area held for: %s\n",  
        CONVTIME(time() - query_conquer_time()));
    
    
    idx = m_indexes(units);
    size = sizeof(idx);
    index = -1;

    if (!size)
    {
        str += "No units recruited.\n";
    }

    while (++index < size)
    {
        str += sprintf("   %16s: %2d units (%d reserve)\n", idx[index],
            query_unit_count(idx[index]), query_unit_reserve(idx[index]));
    }

    str += "\n";
    return str;
}


