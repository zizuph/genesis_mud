/*
 * kob_lair_a02.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "ss_types.h"
#include "stdproperties.h"
#include "include/cave_defs.h"
#include "tasks.h"

inherit KOB_LAIR_PATH + "default_kob_lair";

int trap_set;
int trap_found;

public int remove_trap(string text);

/*
 * Function name: create_room
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void 
create_room()
{
    ::create_room();

    set_long("A dark narrow tunnel travelling north to south through " 
      + "the cave system. The smell in the air can only be described " 
      + "as vile. Small rocks litter the floor.\n");
    
    add_exit(KOB_LAIR_PATH + "kob_lair_a01", "north", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a03", "south", "@@trigger_trap");

    add_item(({"trap", "hole", "crossbolt trap", 
               "crossbow trap", "bolt trap"}
               ), "@@trap_desc");
    
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT, 0);
    
    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Resets the rooms trap
 * Arguments    : n/a
 * Returns      : n/a
 */
public void 
reset_room()
{
    trap_set = 1;
    trap_found = 0;
}

/*
 * Function name: do_search
 * Description  : Handle custom searching
 * Arguments    : object searcher - Player searching
 *                string str - Search Target
 * Returns      : string - description of trap if found
 */
public string do_search(object searcher, string str)
{
    if (str == "here for traps" || str == "here")
    {
        if (searcher->resolve_task(TASK_EASY, SS_FR_TRAP) > 0)
        {
            if (trap_set)
            {
                trap_found = 1;
                return "You find a crossbolt trap which is triggered " 
                  + "by travelling south.\n";
            }
            else
            {
                return "You find a hole in the wall attached to a " 
                  + "trigger.  The trap is inactive.\n";
            }
        }
    }
    return 0;
}

/*
 * Function name: trigger_trap
 * Description  : Handle player triggering the trap
 * Arguments    : n/a
 * Returns      : 1 for success, 0 for no action
 */
public int trigger_trap()
{
    object player = this_player();
    if (trap_set)
    {
        player->catch_tell("You hear a sharp click as you step.\n");
        if (present(player))
        {
            if (player->resolve_task(TASK_DIFFICULT, SS_ACROBAT) <= 0)
            {
                int damage = player->query_max_hp() / 10;
                player->heal_hp(-damage);
                tell_room(environment(player), player->query_name() 
                  + " is hit by a wooden cross bolt.\n", player);
                player->catch_tell("A wooden bolt hits you in the " 
                  + "chest.\n");
            }
            else
            {
                tell_room(environment(player), player->query_name() 
                  + " performs an acrobatic roll to avoid a trap.  A " 
                  + "wooden bolt flies across the room and shatters "
                  + "against the cave wall.\n", player);
                player->catch_tell("You perform an acrobatic roll to "
                  + "avoid a wooden bolt launched from near wall.  The " 
                  + "bolt shatters against the far wall.\n");
            }
        }
        trap_set = 0;
        return 1;
    }
    return 0;
}

/*
 * Function name: trap_desc
 * Description  : VBFC
 * Arguments    : n/a
 * Returns      : string - trap description if found
 */
public string 
trap_desc()
{
    if (!trap_found)
    {
        return 0;
    }
    if (trap_set)
    {
        return "You find a crossbolt trap which is triggered by " 
          + "travelling south.\n";
    }
    else
    {
        return "You find a hole in the wall attached to a trigger. " 
          + "The trap is inactive.\n";
    }
}

/*
 * Function name: init
 * Description  : add remove and disarm actions to player
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(remove_trap,"remove");
    add_action(remove_trap,"disarm");
}

/*
 * Function name: remove_trap
 * Description  : Player attempts to disarm the trap
 * Arguments    : string text - target to attempt disarm 
 * Returns      : 1 success, 0 failure
 */
public int remove_trap(string text)
{
    if (parse_command(text, this_player(), " [crossbolt] [bolt] 'trap'"))
    {
        if (trap_found)
        {
            if (this_player()->resolve_task(TASK_ROUTINE, SS_FR_TRAP) > 0)
            {
                if (trap_set)
                {
                    trap_set = 0;
                    this_player()->catch_tell("You disarm the crossbolt " 
                      + "trap.\n");
                }
                else
                {
                    this_player()->catch_tell("The trap has already "
                      + "been sprung.\n");
                }
                return 1;
            }
            else
            {
                set_alarm(2.0, 0.0, trigger_trap);
                this_player()->catch_tell("You accidentally trigger " 
                  + "the trap.\n");
                return 1;
            }
        }
    }
    return 0;
}
