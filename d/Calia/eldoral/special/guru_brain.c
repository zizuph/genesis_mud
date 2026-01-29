/*
 * guru_brain.c
 *
 * This file is fairly simple as far as brains go. All it does is
 * remember which tomb currently has the King's Hand gauntlet. The
 * quest is also reset from this object, which happens only when
 * a: the object is first loaded, or
 * b: after the quest has been solved.
 *
 * Khail - Feb 10/97
 * 
 * Revision history: 
 * 15/2/99      Put the time of this reboot as a seed to random() 
 *              when the king is decided. Before, if this code was 
 *              updated and people were questing, the king would  
 *              change, putting the questers at risk from the penalty
 *              for choosing the wrong tomb. 
 *                            -   Maniac
 */
#pragma strict_types

#include <std.h>
#include "defs.h"
#include "../guru_quest.h"

string *crypts = ({RUIN + "crypt_3",
                   RUIN + "crypt_4",
                   RUIN + "crypt_6",
                   RUIN + "crypt_7",
                   RUIN + "crypt_9"});

string *kings = ({"Brahm",
                  "Larylt",
                  "Koth",
                  "Alyndrys",
                  "Beuradyn"});
string king;

/*
 * Function name: query_kings
 * Description  : Queries an array of all the valid names for the
 *                tombs in Eldoral.
 * Argumetns    : n/a
 * Returns      : An array of names as strings.
 */
public void
query_kings()
{
    return kings + ({});
}

/*
 * Function name: set_king
 * Description  : Sets the name of the current tomb which holds 
 *                the King's Hand gauntlet.
 * Arguments    : str - A string, must be one of the available
 *                      names.
 * Returns      : n/a
public void
set_king(string str)
{
    if (!str || !strlen(str))
        return;
    if (member_array(str, kings) < 0)
        return;
    king = str;
}
 */


/*
 * Function name: query_king
 * Description  : Queries the current tomb that contains the
 *                King's Hand gauntlet.
 * Arguments    : n/a
 * Returns      : The name of the current tomb as a string.
 */
public string
query_king()
{
    return king;
}



/*
 * Function name: reset_quest
 * Description  : Resets the current king.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_quest()
{
    setuid();
    seteuid(getuid());
    king = kings[random(sizeof(kings), SECURITY->query_start_time())];
    crypts->reset_crypts();
}


/*
 * Function name: create
 * Description  : Things to do when this object is loaded.
 * ARguments    : n/a
 * Returns      : n/a
 */
public void
create()
{
    reset_quest();
}

