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
#include <language.h>

#include "warfare.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* !!! All vars that should not be saved MUST be static !!! */

static string area_name,       /* What are we called ? */
    default_controller,        /* Army controlling area by default */
    cob;                       /* Path to controlling army */
static mapping cloned_units;   /* Units already parked in the area */
static object *actual_units;   /*The actual units*/
static int recruit_base, tax_base; 
static string *excluded_rooms = EXCLUDED_ROOMS;

/* SAVED VARS */

string controller;      /* Army Currently Controlling Area */
mapping units;          /* Units assigned to this area */
string *rooms;          /* The rooms of the area */
int conquer_time;       /* When was this area last conquered? */ 
mixed *conquests;       /* The Areas conquest history */

public void set_controller(string str);
public string query_default_controller();
public void reward_item(object player, string area_name, string old_army);

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

    /* Remove any newly excluded rooms */
    rooms -= excluded_rooms; 

    if (!controller)
        set_controller(query_default_controller());
    
    set_controller(controller);
    
    this_object()->populate_warfare_area();
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
 * Called when you want to re-populate the warfare rooms,
 * such as after a reboot and the war re-starts.
 */
public void
populate_warfare_area()
{
    object *ob;
    ob = map(rooms, find_object);
    ob -= ({ 0 });

    foreach(object room: ob)
    {
        object *npcs = filter(room->query_room_npc(), objectp);
        
        if (pointerp(npcs))
            actual_units += npcs;
    }

    /* Dont spawn NPCs during peace. */
    if (ARMYMASTER->query_peace())
        return;
    
    // WARFARE_DEBUG("Populating the warfare area");
    /* We just want 10 units in each area to begin with after load */
    for(int value = sizeof(actual_units); value < 10; value++)
    {
        object cloned;
        
        /* Create an NPC */
        if (!objectp(cloned = this_object()->clone_unit(1)))
            break;
        
        /* Verify that there are legitimate rooms in the area. */
        foreach(object room: ob)
        {
            if (room->add_room_npc(cloned))
                break;
        }
    }
}

/*
 * Called when you want to de-populate the warfare rooms,
 * such as when the war ends.
 */
public void
depopulate_warfare_area()
{
    object *ob;
    
    ob = map(rooms, find_object);
    ob -= ({ 0 });

    // WARFARE_DEBUG("De-populate warfare area called (2)");
    
    foreach(object room: ob)
    {
        object *npcs = room->query_room_npc();
        room->remove_room_npc(npcs);
        
        if (pointerp(npcs))
            actual_units -= npcs;
        
        tell_room(room, "\nThe War of the Lance has ended!\n\n",
            ({ }), 0);
    }
    
    if (sizeof(actual_units))
        actual_units->remove_object();
    
    actual_units -= ({ 0 });
}

/*
 * Called when a new war starts, should reset
 * most stuff to default state.
 */
public void
start_war()
{
    if (calling_function() != "load_areas")
    {
        units = ([ ]);
        cloned_units = ([ ]);
        conquests = ({ });
        actual_units = ({ });
        object *ob;
    
        ob = map(rooms, find_object);
        ob -= ({ 0 });
        
        foreach(object room: ob)
        {
            tell_room(room, "\nWar has returned to Krynn! Prepare yourself!"
            + "\n\n", ({ }), 0);
        }
        
        set_controller(default_controller);
        conquer_time = time();
    }
    
    set_alarm(1.0, 0.0, &populate_warfare_area());
    //populate_warfare_area();
}

/* Called when we are ending or resetting the war.
 */
public void
stop_war()
{
    set_alarm(1.0, 0.0, &depopulate_warfare_area());
    WARFARE_DEBUG("Ending the war");
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
 *
 * Arguments:   (int) push - forces a clone instead of taking spare units.
 */
public varargs object
clone_unit(int push = 0)
{
    string unitName = cob->get_unit_for_area(area_name);
    object ob;
    
    if (!stringp(unitName))
    {
        WAR_LOG("Didn't get a unitName while trying to clone for "+area_name);
        return 0;
    }

    actual_units -= ({ 0 });
    // Check if we have any spare units by filtering out environment
    object *spare_units;
    if (!push && sizeof(spare_units = filter(actual_units, intp @ environment)))
        return spare_units[0];
    
    string file = cob->query_unit_file(unitName);

    WAR_LOG(area_name+" Cloning: " + unitName + " (" + file + ")");

    ob = clone_object(file);

    if (!objectp(ob))
    {
    	WAR_LOG("Error cloning " + file + " (" + unitName + ")");
        return 0;
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
        WAR_LOG("Error cloning " + file + " (" + arr[k] + ")");
    
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
    // Don't add rooms that shouldn't be added
    if (member_array(room, excluded_rooms) > -1)
	return;

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
public string *
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

    //WARFARE_DEBUG("i: " + i);

    while (i--)
    {
        if (!environment(actual_units[i]))
            continue;
        
        //If they're not in a valid room, remove them
        if (!wildmatch("/d/Krynn/*", file_name(environment(actual_units[i]))) &&
            !wildmatch("/d/Ansalon/*", file_name(environment(actual_units[i]))))
        {
            units_to_remove += ({ actual_units[i] });
        }

    }

    if (sizeof(units_to_remove))
        units_to_remove->remove_object();
    
    actual_units -= ({ 0 });
}
/*
 * Someone wishes to conquer us!
 *
 */
varargs public int
conquer(string army, object player)
{
    int k, *idx, score;

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
    
/*
    //60 * 60 = 3600 in an hour * 2 = 7200 seconds in 2 hours
    if ((conquer_time + 7200) > time())
    {
	notify_fail("This area has been recently taken over. You must wait a "+
        "while before attempting to conquer the " + area_name + ".\n");
	return 0;
    }
*/
    clean_up_actual_units();

/*
    foreach(mixed war_unit: actual_units)
    {
        if(!objectp(war_unit))
            actual_units -= ({ war_unit });
    }
*/

    if (pointerp(actual_units) && sizeof(actual_units))
    {
        // WARFARE_DEBUG("Sizeof actual_units pre remove: " +sizeof(actual_units) + ".");

        // Remove dead units.
        actual_units -= ({ 0 });

        int left = sizeof(actual_units);
        string est = "an unknown amount";

        // WARFARE_DEBUG("Sizeof actual_units post remove: " +sizeof(actual_units) + ".");
        
        switch (left) {
            case 1..20:
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

        if(left)
        {
            notify_fail("You cannot conquer the " + area_name + " as it does not "
            + "yet seem to be completely cleared of enemies. There are still signs "
            + "of " + est + " of enemies remaining.\n");
            return 0;
        }
    }

    if (WAR_CLUB_ADMIN->query_time_attacked_own_army(player))
    {
        int last_attacked;
        last_attacked = WAR_CLUB_ADMIN->query_time_attacked_own_army(player);

        // if a member has attacked their own troops within the last 24
        // hours, the troops don't come to their conquest call.
        if( (last_attacked + 86400) > time())
        {
	    notify_fail("No troops come to your call to conquer " +
                "this area, likely because they are distrustful after " +
                "you attacked them in the last 24 hours! You may have " +
                "to wait a while before they will answer any of your " +
                "claims of conquest.\n");
	    return 0;
        }
    }    
   
    old_army = controller;
    set_controller(army);

    CONQ_LOG(area_name + " " + old_army + " -> " + controller + " (" +
	(objectp(player) ? player->query_real_name() : "auto") + ")");

    units = ([ ]);
    cloned_units = ([ ]);
    actual_units->remove_object();
    
    score = time() - conquer_time;
    
    conquer_time = time();
    conquests += ({ time(), controller, old_army, player->query_real_name() });
    
    WAR_LOG(area_name + " " + old_army + " -> " + controller + " (" +
	(objectp(player) ? player->query_real_name() : "auto") + ")");

    send_debug_message("warfare", area_name + " " + old_army + " -> "
    + controller + " (" + (objectp(player) ? player->query_real_name() : "auto")
    + ")", "/d/Krynn/common/warfare/war_conq.log");
    
     /* This writes messages */
    ARMYMASTER->query_army(army)->conquer(area_name, old_army, player);
    
    /* Call the reward hook */
    player->reward_warfare_conquest(area_name, controller, old_army);

    reward_item(player, area_name, old_army);

    // If part of warfare club, add to conquest counter.
    if (WAR_CLUB_ADMIN->query_is_member(player))
        WAR_CLUB_ADMIN->player_conquer_location(player, area_name, score,
                                                army, old_army);

    /*
     * Might have to be rewritten depending on eval cost
     * We do this after message printing since it might runtime.
     */
    ob = map(rooms, find_object);
    ob -= ({ 0 });
    ob->conquer_update(area_name, controller, old_army);

    // Add npcs to counter insta-conquering
    populate_warfare_area();

    return 1;
}

//Called when a player conquers an area, give them some loot
public void
reward_item(object player, string area_name, string old_army)
{
    if (!player)
        return 0;

    int coin_size;
    object gem;
    string gem_string;
    string * gems;
    string gem_type = WARFARE_GEM_CUT[random(4)];

    // WARFARE_DEBUG("Area: " +area_name+ ", old army: " +old_army);
    // object re = ARMYMASTER->reward_item(player);

    if (member_array(area_name, TOP_TIER_AREAS) > -1)
    {
        WARFARE_DEBUG("Top tier reward called");
        coin_size = 25 + random(20);
        gems = KRYNN_WAR_GEM_TIER2_SPAWN[gem_type];
    }
    else
    {
        coin_size = 15 + random(10);
        gems = KRYNN_WAR_GEM_TIER1_SPAWN[gem_type];
    }

    object re = clone_object(REWARDS_PATH + "krynn_steel_coin");
    re->set_heap_size(coin_size);
    gem_string = ONE_OF(gems);
    gem = clone_object(gem_string);

    if (!re)
        return 0;

    re->move(player);
    gem->move(player);

    old_army = WARFARE_ARMIES_NAMES[old_army];

    player->catch_msg("As the " +old_army+ " flee the battlefield, " +
        "you recover " +re->short()+ " and " +LANG_ASHORT(gem)+ 
        " as spoils of war!\n");
        
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
