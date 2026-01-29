/* created by Aridor 04/01/94
 * updated by Milan 15.6.2000
 *  - typecasting
 *  - function type vars code
 *  - bugfixes
 *
 * Fixed by Stralle @ Genesis 000919
 *
 * Cotillion could not keep his hands away - 030621
 *   - fixed resistance checks
 *   - rewrote damage calculations
 *   - fixed movement in maprooms
 *
 * Navarre October 2006, added prop to prevent from sinking in water.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

object *victims;
int remove_time;

#define EXIT_ROOM 0
#define EXIT_DIR  1
#define EXIT_BLOCK  2

#ifndef KRYNN_LOG
#define KRYNN_LOG(x)  do { seteuid(getuid()); \
              write_file("/d/Krynn/log/events", ctime(time()) + ": " + x + \
                  "\n"); } while(0)
#endif 

#define OBJ_I_FLOAT "_obj_i_float"

/* prototypes */
void drift();
void dissolve();
void hurt_everyone_around();

void
create_object()
{
    set_name("clouds");
    add_name("cloud");
    set_adj("dark");
    set_short("Dark clouds are hanging in the air");
    set_long("The clouds look very menacing and hang very low, " +
        "but even though it is not raining you feel the " +
        "air crackling with energy.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200000);
    add_prop(OBJ_M_NO_GET, "You cannot reach the clouds.\n");
    add_prop(OBJ_I_HAS_FIRE, 10);
    add_prop(OBJ_I_LIGHT, 3);
    add_prop(OBJ_I_RES_ACID, 100);
    add_prop(OBJ_I_RES_WATER, 100);
    add_prop(OBJ_I_RES_FIRE, 10);
    add_prop(OBJ_I_FLOAT, 1); // Added to prevent sinking in water
    
    remove_time = 135 + random(30);

    setuid();
    seteuid(getuid());
}

/*
 * Drift makes us move. 
 */
void
drift()
{
    int i, k;
    string exit, fun, area, my_exit, how;
    mixed rooms, exits;

    exits = environment()->query_exit();
    rooms = ({ });


    if ((k = sizeof(exits)) < 3)
	return;
    
    /* We must find out what the actual path of the exits are since
     * some of them can be very special */

    while (k)
    {
        exit = 0;

        /* It's an ordinary exit, no VBFC */
	if (!exits[EXIT_BLOCK])
	    exit = exits[EXIT_ROOM];	
	/* Cursed VBFC, might be an areahandler room */
	else if (stringp(exits[EXIT_BLOCK]))
	{
	    if (sscanf(exits[EXIT_BLOCK], "@@%s:%s|%s@@", 
		fun, area, my_exit) != 3)
            {
                exits = exits[3..];
                k -= 3;
		continue;
            }
	    
	    if (fun == "enter_map")
	    {
		/* Nothing we can do about this one right now, it wants to
		 * move a living. */
	    }
	    else if (fun == "move_in_map")
	    {
		exit = area->query_room(my_exit);
	    } else {
		/* Let's try the exit even if there is other vbfc */
		exit = exits[EXIT_ROOM];
	    }
	}
	else if (functionp(exits[EXIT_BLOCK]))
	{
	    /* We ignore this case for now, We'll see if it breaks. */
	    exit = exits[EXIT_ROOM];
	}

	/* This is our check for now, it has to be a file */
        
        if (stringp(exit)) 
        {
            if (exit[-2..-1] != ".c")
                exit += ".c";
            
            if (file_size(exit) > 0)
            {
                rooms += ({ ({ exit, exits[EXIT_DIR] }) });
            }
        }

	exits = exits[3..];
	k -= 3;
    }
    
    /* All rooms were broken somehow */
    if (!sizeof(rooms))
	return;

    k = random(sizeof(rooms));
    exit = rooms[k][0];
    how = rooms[k][1];
    
    if (LOAD_ERR(exit) || !exit->query_prop(ROOM_I_IS))
    {
	KRYNN_LOG("Unable to move cloud to: " + exit + " from " + 
	    file_name(environment()));
	return;
    }
    
    tell_room(E(TO),"The clouds drift " + how + ".\n");
    
    move(find_object(exit));
	
    tell_room(E(TO),"A dark and menacing looking cloud " +
	"drifts in.\n");
    
    set_alarm(itof(random(10) + 12), 0.0, drift);
}

void
dissolve()
{
    tell_room(E(TO), 
        "The clouds drift around and slowly vanish into thin air.\n");
    remove_object();
}

void
hurt_player(object player)
{
    int res, dam;
    object co;
    string str;

    /* Pure luck? */
    if (random(100) < 20)
        return;
    
    /* It's supposed to be pretty unlikely that one dies from 
     * these lightning strikes. This is accomplished by using a 
     * dam value of max the amount of hp the player has left / 2 */
    dam = min(player->query_hp() / 2, 150);
    dam = max(dam, 30);
    dam = random(dam);

    /* Electricity and fire resistance helps, we add since we are nice */
    res = player->query_magic_res(MAGIC_I_RES_ELECTRICITY) + 
	player->query_magic_res(MAGIC_I_RES_FIRE);
    res = min(res, 100);
    if (res > random(100))
        return;

    dam -= dam * res / 100;

    /* If a specific set of prefered victims is set, hurt others less */
    if (sizeof(victims) && member_array(player, victims) < 0)
        dam /= 3;

    /* Hurt it! */
    player->heal_hp(-dam);
    
    if (dam > 0)
    {
        switch (dam)
        {
        case 0..20:
            str = "a little ";
            break;
        case 21..50:
            str = "partly ";
            break;
        case 51..100:
            str = "badly ";
            break;
        default:
            str = "very badly ";
            break;
        }

        tell_object(player, "You are hit and " + str + "burnt.\n");
    }
    
    tell_room(E(player), QCTNAME(player) + " was struck by lightning.\n",
        player);
    
    co = player->query_combat_object();
    co->cb_add_panic(dam / 4);
    co->cb_may_panic("north");
    
    if (!player->query_ghost() && player->query_hp() <= 0)
        player->do_die(TO);
}

void
hurt_everyone_around()
{
    object *things;
    
    if (!objectp(E(TO)))
    {
	set_alarm(0.0, 0.0, remove_object);
	return;
    }


    tell_room(E(TO), "Lightning strikes down from the clouds.\n");
    
    /* Kill em! */
    things = all_inventory(E(TO));
    things = filter(things, living);
    map(things, hurt_player);
    
    set_alarm(itof(random(6) + 3), 0.0, hurt_everyone_around);
}

void
set_my_victims(object *whos)
{
    victims = whos;
}

int
set_remove_time(int i)
{
    remove_time = i;
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(from))
    {
        set_alarm(itof(remove_time), 0.0, dissolve);
        set_alarm(itof(random(10) + 12),  0.0, drift);
        set_alarm(itof(random(4) + 8),    0.0, hurt_everyone_around);
    }
}
