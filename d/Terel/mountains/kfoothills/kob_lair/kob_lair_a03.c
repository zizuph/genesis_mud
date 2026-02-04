/*
 * kob_lair_a03.c
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

    set_long("@@long_desc");
    
    add_exit(KOB_LAIR_PATH + "kob_lair_a02", "north", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a04", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a05", "west", "@@trigger_trap");
    
    add_item(({"trap", "hole", "pit", "large hole"}), "@@trap_desc");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT, 0);
    
    add_item(({"dirt", "Soft dirt", "floor"}), "Soft dirt covers most " 
      + "of the floor with bare rock outcrops dotting it.\n");

    add_item(({"rock"}), "You are surrounded by rock as you are in a " 
      + "cave.\n");
      
    add_item(({"rock outcrops", "outcrops", "bare rock"}), "Bulges of "
      + "bare rock rise from the ground dotting the dirt floor.\n");

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
 * Function name: long_desc
 * Description  : VBFC description of room.  Adds trap description if 
 *                not set
 * Arguments    : n/a
 * Returns      : n/a
 */
public string 
long_desc()
{
    string result = "A large cavern stretches from east to west. A " +
    "small tunnel leads off to the north.  A soft dirt covers most " +
    "of the cave with occasional outcrops of bare rock. The walls here " +
    "are uneven with large cracks.  Small rocks litter the floor.\n";
    if (!trap_set)
    {
        result += "There is a large hole in the middle of the room.\n";
    }
    return result;
}

/*
 * Function name: long_desc
 * Description  : VBFC description of trap.  Adds trap description if 
 *                not set or found
 * Arguments    : n/a
 * Returns      : n/a
 */
public string 
trap_desc()
{
    if (!trap_set)
    {
        return "A large pit in the floor.\n";
    }
    else if (trap_found)
    {
        return "A dirt covered tarp covering a obvious pit.\n";
    }
}

/*
 * Function name: trigger_trap
 * Description  : Handle player triggering the trap
 * Arguments    : n/a
 * Returns      : 1 for success, 0 for no action
 */
public int
trigger_trap()
{
    object player = this_player();
    if (trap_set)
    {
        this_player()->catch_tell("As you walk you notice the cave " 
          + "floor is no longer solid rock.\n");
        if (player->resolve_task(TASK_HARD, SS_ACROBAT) > 0)
        {
            int damage = player->query_max_hp()/5;
            player->heal_hp(-damage);
            tell_room(environment(player), "The floor gives way and " 
              + player->query_name() + " falls into the pit.\n", player);
            player->catch_tell("You floor gives way and you fall into a " 
              + "pit and are impaled as you land on spikes.\n");
            set_alarm(0.5, 0.0, &player->move(KOB_LAIR_PATH 
              + "kob_lair_pit"));
        }
        else
        {
            tell_room(environment(player), "The floor gives way and " 
              + player->query_name() + "jumps aside to avoid falling "
              + "into the pit.\n", player);
            player->catch_tell("You jump aside as the floor gives way " 
              + "revealing a large pit.\n");
        }
        trap_set = 0;
        return 1;
    }
}

/*
 * Function name: init
 * Description  : add room actions for player
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    add_action("jump_hole", "jump");
    add_action("enter_hole", "enter");
    add_action("climb_hole", "climb");
    
    add_action(remove_trap,"remove");
    add_action(remove_trap,"disarm");

    ::init();
}

/*
 * Function name: jump_hole
 * Description  : Player jumps into the hole causing the same affect
 *                as if they triggered the trap
 * Arguments    : string text - 'hole'
 * Returns      : 1 success/0 no match
 */
public int
jump_hole(string text)
{
    object player = this_player();
    notify_fail("Jump where?");
    if (parse_command(text, ({ }),
        " [into] [down] 'hole' "))
    {
        int damage = player->query_max_hp()/5;
        player->heal_hp(-damage);
        tell_room(environment(player), player->query_name() + " jumps " 
          + "into the hole.\n", player);
        player->catch_tell("You jump into the hole and are impaled as " 
          + "you land on stakes.\n"); 
        player->move(KOB_LAIR_PATH + "kob_lair_pit");
        return 1;
    }
    return 0;
}

/*
 * Function name: enter_hole
 * Description  : Clarify how the player should enter the hole
 * Arguments    : string text - 'hole'
 * Returns      : 1 success/0 no match
 */
public int
enter_hole(string text)
{
    object player = this_player();
    if (text == "hole" || text == "pit")
    {
        player->catch_tell("Do you wish to jump or climb down the " 
          + "hole?\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: climb_hole
 * Description  : Player carefully climbs down into the pit
 * Arguments    : string text - 'hole'
 * Returns      : 1 success/0 no match
 */
public int 
climb_hole(string text)
{
    object player = this_player();
    if (strlen(text) && parse_command(text, ({ }),
        " [down] [into] [the] 'hole' "))
    {
        tell_room(environment(player), player->query_name() + " climbs " 
          + "down the hole.\n", player);
        player->catch_tell("You carefully climb down into the hole.\n"); 
        player->move(KOB_LAIR_PATH + "kob_lair_pit");
        return 1;
    }
    return 0;
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
                return "You find a pit trap which is triggered by "
                  + "travelling west.\n";
            }
            else
            {
                return "There is a large pit here.\n";
            }
        }
    }
    return 0;
}

/*
 * Function name: remove_trap
 * Description  : Player attempts to disarm the trap
 * Arguments    : string text - target to attempt disarm 
 * Returns      : 1 success, 0 failure
 */
public int remove_trap(string text)
{
    if (parse_command(text, this_player(), " [pit] [hole] 'trap'"))
    {
        if (trap_found)
        {
            if (this_player()->resolve_task(TASK_ROUTINE, SS_FR_TRAP) > 0)
            {
                if (trap_set)
                {
                    trap_set = 0;
                    this_player()->catch_tell("You touch the trap and "
                      + "cause the trap door to open.\n");
                }
                else
                {
                    this_player()->catch_tell("The trap has already " 
                      + "been sprung.\n");
                }
            }
            else
            {
                this_player()->catch_tell("You fail to disarm the trap "
                  + "and almost fall into the pit.\n");
            }
            return 1;
        }
    }
}
