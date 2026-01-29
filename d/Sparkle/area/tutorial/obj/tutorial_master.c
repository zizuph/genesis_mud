/*
 *  /d/Sparkle/area/tutorial/obj/tutorial_master.c
 *
 *  This is the master file for the tutorial. It keeps track of which
 *  chapters of the tutorial have been read by players.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 *      Special thanks to: Raven and Mercade
 */
#pragma strict_types
#pragma no_clone

#include "../defs.h"

inherit "/std/object";

#include <std.h>

/* prototypes */
public void        create_object();
public void        test_members();
public void        remove_player(string player);
public void        set_tutorial(string player, int chapter_num);
public void        clear_tutorial(string player, int chapter_num);
public int         query_tutorial(string player, int chapter_num);
public void        store_data();
public void        restore_data();

/* global variables */
private mapping        Read_Signs = ([ ]);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());

    restore_data();
    test_members();
} /* create_object */


/*
 * Function name:        test_members
 * Description  :        see if the members in the array still exist
 *                       as players in the game. If they do not, remove
 *                       them from the mapping.
 *
 * Special thanks to Mercade for creating this function.
 */
public void
test_members()
{
    string *names = m_indices(Read_Signs);

    foreach(string name: names)
    {
        if (!(SECURITY->exist_player(name)))
        {
            m_delkey(Read_Signs, name);
        }
    }

    store_data();
} /* test_members */


/*
 * Function name:        remove_player
 * Description  :        remove a player when they leave the tutorial
 *                       or are no longer in existence
 * Arguments    :        string player - the playername index
 */
public void
remove_player(string player)
{
    m_delkey(Read_Signs, player);

    store_data();
} /* remove_player */

/*
 * Function name: rename_player
 * Description  : If a player is renamed, update the index.
 * Arguments    : string oldname - old name of the player.
 *                string newname - new name of the player.
 */
public void
rename_player(string oldname, string newname)
{
    if (Read_Signs[oldname])
    {
	Read_Signs[newname] = Read_Signs[oldname];
        store_data();
    }
}

/*
 * Function name:        set_tutorial
 * Description  :        set the bit for having completed some aspect
 *                       of the tutorial
 * Arguments    :        string player - the player name,
 *                       int chapter_num  - the chapter number
 */
public void
set_tutorial(string player, int chapter_num)
{
    if (!Read_Signs[player])
    {
	Read_Signs[player] = "";
    }

    Read_Signs[player] = efun::set_bit(Read_Signs[player], chapter_num);

    store_data();
} /* set_tutorial */


/*
 * Function name:        clear_tutorial
 * Description  :        clear the bit for having completed some aspect
 *                       of the tutorial
 * Arguments    :        string player - the player name,
 *                       int chapter_num  - the chapter number
 */
public void
clear_tutorial(string player, int chapter_num)
{
    if (!Read_Signs[player])
	return;

    Read_Signs[player] = efun::clear_bit(Read_Signs[player], chapter_num);

    store_data();
} /* clear_tutorial */


/*
 * Function name:        query_tutorial
 * Description  :        see if the bit is set for having completed
 *                       this aspect of the tutorial (signs mostly)
 * Arguments    :        string player - the player name,
 *                       int chapter_num  - the chapter number
 * Returns      :        int 1 - read,
 *                       int 0 - unread
 */
public int
query_tutorial(string player, int chapter_num)
{
    if (!Read_Signs[player])
    {
	return 0;
    }

    return efun::test_bit(Read_Signs[player], chapter_num);
} /* query_tutorial */


/*
 * Function name:        store_data
 * Description  :        write the current values to a save file
 */
public void
store_data()
{
    save_object(SAVE_FILE);
} /* store_data */


/*
 * Function name:        restore_data
 * Description  :        restore the values from a save file
 */
public void
restore_data()
{
    restore_object(SAVE_FILE);

    if (!mappingp(Read_Signs))
    {
        Read_Signs = ([ ]);
    }
} /* restore_data */
