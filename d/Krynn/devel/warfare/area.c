/*
 * The base of one of the Areas in the War of the Lance
 *
 * The idea is basically to provide a nice interface for the area
 * setup.
 */
#pragma no_clone
#pragma strict_types

#include <macros.h>

#include "warfare.h"

/* !!! All vars that should not be saved MUST be static !!! */

static string area_name,       /* What are we called ? */
    default_controller,        /* Army controlling area by default */
    cob;                       /* Path to controlling army */
static mapping cloned_units;   /* Units already parked in the area */
static int recruit_base, tax_base; 

/* SAVED VARS */

string controller;      /* Army Currently Controlling Area */
mapping units;          /* Units assigned to this area */
string *rooms;          /* The rooms of the area */
int conquer_time;       /* When was this area last conquered? */ 

public void set_controller(string str);


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

    tax_base = DEFAULT_TAX_BASE;
    recruit_base = DEFAULT_RECRUIT_BASE;
    
    configure_area();

    if (file_size(MASTER + ".o") > 0)
	restore_object(MASTER);

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
	LOG("Default Controller Does Not Exist (" + controller + ")");
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
 *
 * Randomize from availible units. We randomize a bit which unit
 * gets picked depending on how many of it's kind are recruited.
 * Beats the old way.
 */
public object
clone_unit()
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
    
    LOG("Cloning: " + arr[k] + " (" + file + ")");


    if (!cloned_units[arr[k]])
	cloned_units[arr[k]] = 0;
    
    cloned_units[arr[k]]++;
    
    ob = clone_object(file);
    if (!objectp(ob))
    {
	LOG("Error cloning " + file + " (" + arr[k] + ")");
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
 * Count the number of rooms
 */
public int
count_rooms()
{
    return sizeof(rooms);
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
    
    /* We require 30 minutes between two conquests of the same area */
    if ((conquer_time + 18) > time())
    {
	notify_fail("There are already reinforcements on the way. You are " +
	    "unable to conquer the " + area_name + ".\n");
	return 0;
    }
    
    if (query_unit_count() > 0)
    {
	notify_fail("The " + area_name +
	    " doesn't seem to be completely cleared of enemies " +
	    "yet, or there are still reinforcements on the way. You " +
	    "are unable to conquer the territory.\n");
	return 0;
    }
    
    old_army = controller;
    set_controller(army);
    
    units = ([ ]);
    cloned_units = ([ ]);
    
    conquer_time = time();
    
    LOG(area_name + " " + old_army + " -> " + controller + " (" +
	(objectp(player) ? player->query_real_name() : "auto") + ")");

     /* This writes messages */
    ARMYMASTER->query_army(army)->conquer(area_name, old_army, player);
    
    /* Call the reward hook */
    player->reward_warfare_conquest(player, area_name, controller, old_army);

    /*
     * Might have to be rewritten depending on eval cost
     * We do this after message printing since it might runtime.
     */
    ob = map(rooms, find_object);
    ob -= ({ 0 });
    ob->conquer_update(area_name, controller, old_army);
    return 1;
}




