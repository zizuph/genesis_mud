/* Quest Helper
 *
 * This is a helper object that allows use of data files to 
 * track quest progress. Quest objects should be derived
 * and wrap these functions in the quest logic to expose
 * functions to the quest actors.
 *
 * Example:
 * 
 * #pragma no_clone
 * inherit "/d/Faerun/std/quest_helper";
 * #define QUEST_GROUP  -1
 * #define QUEST_BIT    -1
 * #define QUEST_FILE   "/d/Faerun/data/sample"
 * 
 * #define STEP_ONE   0
 * #define STEP_ONE_EXP   1000
 * #define FULL_EXP   10000
 * 
 * public void
 * create_object()
 * {
 *     quest_group = QUEST_GROUP;
 *     quest_bit   = QUEST_BIT;
 *     quest_file  = QUEST_FILE;
 *     ::create_object();
 * }
 * 
 * public int
 * check_step_one(object qp)
 * {
 *     return check_quest_step(qp, STEP_ONE);
 * }
 * 
 * public void
 * award_step_one(object qp)
 * {
 *     set_quest_step(qp, STEP_ONE);
 *     qp->add_exp_quest(STEP_ONE_EXP);
 *     QUEST_LOG_FILE("Finished step one.", STEP_ONE_EXP);
 * } 
 * 
 * public void
 * award_full(object qp)
 * {
 *     complete_quest(qp);
 *     qp->add_exp_quest(FULL_EXP);
 *     QUEST_LOG_FILE("Finished The whole quest.", FULL_EXP);
 * } 
 *
 * Uses concepts from /d/Sparkle/area/tutorial/obj/tutorial_master.c
 * Thanks Gorboth
 *
 * Gnim, October 2016
 */
#pragma strict_types
inherit "/std/object";
#include <std.h>  /* required for SECURITY definition. */

#define DEBUGGING
#ifdef DEBUGGING
#define DEBUGGER "gnim"
#define DEBUG(s) find_player(DEBUGGER)->catch_msg("Quest Helper: "+s+"\n")
#else
#define DEBUG(s)
#endif

public void create_object();
public void test_members();
nomask private void restore_quest_map();
nomask private void save_quest_map();

private mapping quest_map = ([]);

// These three need to be set by derived class
int quest_group;
int quest_bit;
string quest_file;

/*
 * Name   : create_object
 * Desc.  :  Object creation should be called after init in derived class
 * Args.  : None
 * Return : None
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());
    restore_quest_map();
    test_members();
}

/*
 * Name   : clears_quest_step
 * Desc.  :  Clears the completed bit in quest file
 * Args.  : player object to be cleared, quest step
 * Return : None
 */
public void
clear_quest_step(object quest_player, int step)
{
    string name = quest_player->query_real_name();

    if(!quest_map[name])
        quest_map[name] = "";

    quest_map[name] = efun::clear_bit(quest_map[name], step);
    save_quest_map();
}

/*
 * Name   : set_quest_step
 * Desc.  :  Sets the completed bit in quest file
 *           adds new players to file as required
 * Args.  : player object to be set, quest step
 * Return : None
 */
public void
set_quest_step(object quest_player, int step)
{
    string name = quest_player->query_real_name();

    if(!quest_map[name])
        quest_map[name] = "";

    quest_map[name] = efun::set_bit(quest_map[name], step);
    save_quest_map();
}

/*
 * Name   : check_quest_step
 * Desc.  :  Check to see if a quest step is completed. If the quest
*            bit is set all steps are "complete"
 * Args.  : player object to be checked, quest step
 * Return : 1 for step completed 0 for not yet completed
 */
public int
check_quest_step(object quest_player, int step)
{
    string name = quest_player->query_real_name();

    DEBUG("Checked the quest step");

    if( (quest_group > 0) && (quest_group < 5) )
        if( (quest_bit > 0) && (quest_bit < 20) )
            if( quest_player->test_bit(quest_group, quest_bit) )
                return 1;

    if(!quest_map[name])
        return 0;

    return efun::test_bit(quest_map[name], step);
}

/*
 * Name   : complete_quest
 * Desc.  :  Used by derived class to set the quest as completed. 
 *           This removes the player from the map and file and sets the assigned quest bit.
 *           If the group/bit is outside of the valid region 0-4/0-19 no bit will be set.
 * Args.  : Player object that should be set.
 * Return : None
 */
public void
complete_quest(object quest_player)
{
    string name = quest_player->query_real_name();

    DEBUG("Completed quest.");

    if( (quest_group > 0) && (quest_group < 5) )
    {
        if( (quest_bit > 0) && (quest_bit < 20) )
        {
            quest_player->set_bit(quest_group, quest_bit);
            m_delkey(quest_map, name);
            save_quest_map();
        }
    }
}

/*
 * Name   : check_quest_file
 * Desc.  :  Helper to check that filename has been set by dervied class
 * Args.  : None
 * Return : file validity (0 no file, 1 good)
 */
nomask private int
check_quest_file()
{
    if (!quest_file || !stringp(quest_file))
    {
        DEBUG("No save file set for quest");
        return 0;
    }

    return 1;
}

/*
 * Name   :  restore_quest_map
 * Desc.  :  Loads map from file into memory map
 * Args.  : None
 * Return : None
 */
nomask private void
restore_quest_map()
{
    if ( !check_quest_file() )
        return;

    quest_map = restore_map(quest_file);
    if (!mappingp(quest_map))
        quest_map = ([ ]);
}

/*
 * Name   : save_quest_map
 * Desc.  : Saves current map to current quest file
 * Args.  : None
 * Return : None
 */
nomask private void
save_quest_map()
{
    if ( !check_quest_file() )
        return;

    save_map(quest_map, quest_file);
}

/*
 * Name   :  test_members
 * Desc.  :  see if the members in the array still exist
 *           as players in the game. If they do not, remove
 *           them from the mapping.
 * Args.  : None
 * Return : None
 * Special thanks to Mercade for creating this function.
 */
public void
test_members()
{
    string *names = m_indices(quest_map);
    foreach(string name: names)
    {
        if (!(SECURITY->exist_player(name)))
        {
            m_delkey(quest_map, name);
        }
    }
    save_quest_map();
}
