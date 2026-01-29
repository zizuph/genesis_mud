/*
 *  faerun/underdark/upper/menzo/sorcere/obj/second_master_door.c
 *
 *  The door used on the second floor. Create an instance of it, and call
 *  the configure_ground_door function.
 *
 *  Created by Midnight, 1-3-2004
 */

inherit "/std/door";
inherit "/d/Genesis/lib/trap";

#include "defs.h"

/*
 * Function name: create_door
 * Description  : Construct our door
 */
void create_door()
{
    // We are closed by default
    set_open(0);
    set_locked(1);
    set_lock_command("lock");
    set_lock_name("lock");
    set_key("_bogus_key_for_menzo_sorcere");
    set_unlock_command("unlock");

    set_pick(20);
    set_trapped(1);

    set_door_desc("This sturdy looking door is constructed out of " +
                  "natural untreated weirwood. A dancing light of " +
                  "fairie fire dances across the doors natural surface. " +
                  "Weirwoood is a rare and highly prized type of wood " +
                  "and it can only be ignigted or consumed by magical fire.\n" +
                  "@@trap_desc@@");
}

/*
 * Function name: reset_trapped_door
 * Description  : Close the door, lock it, and set the trap
 */
void reset_trapped_door()
{
    set_open(0);
    set_locked(1);
    set_trapped(1);

    if(!other_door)
	    load_other_door();

    // Reset the trap on the other side
    other_door->set_trapped(1);
}

/*
 * Function name: spring trap
 * Description:   This function is called when the trap is sprung.
 * Arguments:     object who - the person who sprung the trap
 */
public void
spring_trap(object who)
{
    object ob;

    if (!query_trapped())
        return;

    // Create the cloud
    seteuid(getuid());
    ob = clone_object(SOR_OBJ_DIR + "health_drain_cloud");
    ob->move(environment(who));

    /* Disable the trap now that it has been sprung */
    set_trapped(0);
}

/*
 * Function name: do_pick_lock
 * Description:   Here we pick the lock, redefine this function if you want
 *		          something to happen, like a trap or something.
 * Arguments:	  skill - randomized picking skill of player
 *		          pick  - how difficult to pick the lock
 */
void
do_pick_lock(int skill, int pick)
{
    // Call the original function
    ::do_pick_lock(skill, pick);

    // See if we want the trap to go off
    if(skill <= pick)
    {
        // Fifty/fifty chance of hitting the lock
        if(random(2))
            spring_trap(this_player());
    }
}


/*
 * Function name: configure_ground_door
 * Description  : Set up this door
 * Arguments    : direction - in which direction do we pass through this 
 *              :       door, use full names, such as west, southwest etc
 *              : door id - the id of the door, sould be the same as in the
 *              :       other room
 *              : other_side - the other side of this door
 */
void configure_ground_door(string direction, string door_id, 
    string other_side)
{
    mapping directions = ([ "west" : ({ "w", "west" }), 
                            "east" : ({ "e", "east" }),
                            "south" : ({ "s", "south" }),
                            "north" : ({ "n", "north" }),
                            "northeast" : ({ "ne", "northeast" }),
                            "southeast" : ({ "se", "southeast" }),
                            "northwest" : ({ "nw", "northwest" }),
                            "southwest" : ({ "sw", "southwest" }) ]);
    mixed   direction_names;

    // Find the right direction
    if(member_array(direction, m_indexes(directions)) != -1)
        direction_names = directions[direction];
    else
        direction_names = ({ direction });

    // Configure the door
    set_door_name(({"weirwood door", "door", direction + " door"}));
    set_door_id(door_id);
    set_pass_command(direction_names);
    set_other_room(other_side);
}

/*
 * Function name: init
 * Description  : Add commands
 */
void init()
{
    ::init();
    init_trap();
}