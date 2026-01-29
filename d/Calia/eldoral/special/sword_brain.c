/*
 * sword_brain.c
 *
 * This object is a 'master brain' that tracks the status of the
 * 'sword in the stone' quest in Eldoral. It's main purpose to that
 * extent is the tracking of the four 'key' columns of the twelve
 * possible, that unlock the sword from the stone.
 *
 * Coded: Khail, Dec 22/96
 *        Uhclem, Feb 26/99 commented a superfluous statement in reset_quest.
 *            The catacomb_hub calls reset_quest in the pedestal, and the
 *            pedestal calls reset_quest here.  The recursion has always
 *            caused a runtime error, but the problem only became apparent
 *            with the long runtimes allowed by the new computer.
 */
#pragma strict_type
#pragma no_clone
#pragma no_inherit

#include "defs.h"

#define CHIMERA    0
#define WARRIOR    1

string *chimera_loc = ({"the chimera's head",
                       "between the chimera's head and right wing",
                       "at the end of the chimera's right wing",
                       "between the chimera's right wing and right foreleg", 
                       "at the end of the chimera's right foreleg",
                       "at the end of the chimera's right hindleg",
                       "within the curl of the chimera's tail",
                       "at the end of the chimera's left hindleg",
                       "at the end of the chimera's left foreleg",
                       "between the chimera's left wing and left foreleg",
                       "at the end of the chimera's left wing",
                       "between the chimera's head and left wing"});
string *warrior_loc = ({"the warrior's head", 
                       "above the warrior's right shoulder",
                       "at the warrior's right elbow",
                       "at the warrior's right hand",
                       "near the warrior's right knee",
                       "beneath the warrior's right foot",
                       "between the warrior's feet",
                       "beneath the warrior's left foot",
                       "near the warrior's left knee",
                       "at the warrior's left hand",
                       "at the warrior's left elbow",
                       "above the warrior's left shoulder"});
/* Formats: wedge_index ranges from 0 to 11, stone_index from 0 to 2.
 * keystones format: keystones = ([wedge_index: stone_index]);
 * marked format:    marked = ({wedge_index....});
 */ 
mapping keystones;
int     *marked;

public void reset_quest();
public void create();
public void set_keystones();

/*
 * Function name: reset_keystones
 * Description  : Resets the keystones mapping.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_keystones()
{
    keystones = ([]);
}

/*
 * Function name: reset_marked
 * Description  : Resets the marked array.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_marked()
{
    marked = ({});
}

/*
 * Function name: reset_quest
 * Description  : Resets keystones mapping, marked array, and
 *                sets a new keystones mapping.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_quest()
{
    reset_keystones();
    reset_marked();
    set_keystones();
//  (RUIN + "catacomb_hub")->reset_quest();    changed by Uhclem
    (RUIN + "skywalk")->reset_quest();
}

/*
 * Function name: create
 * Description  : Things to do upon loading. Makes sure we start
 *                with a fresh keystones mapping.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create()
{
    reset_quest();
}

/*
 * Function name: set_keystones
 * Description  : Attempts to set the keystones mapping. Will only
 *                succeed if the keystones mapping is 0 or ([]).
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
set_keystones()
{
    int i,
        index,
        *seed = ({0,1,2,3,4,5,6,7,8,9,10,11});

  /* Do nothing if the keystones mapping currently has information. */
    if (keystones && m_sizeof(keystones))
        return;

  /* Make sure the keystones mapping is initialized, and pick */
  /* four random indexes and 1 random value for each index. */
    keystones = ([]);
    for (i = 0; i < 4; i++)
    { 
        index = seed[random(sizeof(seed))];   
        keystones[index] = random(3);
        seed -= ({index});
    }
}

/*
 * Function name: query_keystones
 * Description  : Queries the keystones mapping.
 * Arguments    : n/a
 * Returns      : The keystones mapping var.
 */
public mapping
query_keystones()
{
    if (!keystones)
        return ([]);
    else
        return keystones + ([]);
}

/*
 * Function name: translate_keystones
 * Description  : Translates the keystone mapping into an array
 *                of strings describing their locations on either
 *                the chimera or warrior patterns (chimera by
 *                default)
 * Arguments    : Optional integer 1 will use warrior pattern
 *                rather than default chimera.
 * Returns      : An array of strings as described above.
 */  
public varargs string *
translate_keystones(int which = CHIMERA)
{
    int i;
    string *temp,
           *ret;

    if (which == CHIMERA)
        temp = chimera_loc;
    else
        temp = warrior_loc;

    ret = allocate(4);

    for (i = 0; i < m_sizeof(keystones); i++)
    {
        ret[i] = temp[m_indexes(keystones)[i]];
    }

    return ret;
}

/*
 * Function name: valid_locs
 * Description  : Returns an array of strings describing all the valid
 *                locations on either the chimera (default) or warrior
 *                patterns.
 * Arguments    : Optional integer 1 will list warrior locations.
 * Returns      : An array of strings as described above.
 */
public varargs string *
valid_locs(int which = CHIMERA)
{
    if (which == CHIMERA)
        return chimera_loc + ({});
    else
        return warrior_loc + ({});
}

/*
 * Function name: valid_lod
 * Description  : Tests the supplied argument as being valid location.
 * Arguments    : test - A string describing a potential location.
 * Returns      : 0 - Invalid location. 
 *                1 - Valid chimera location.
 *                2 - Valid warrior location.
 */
public int
valid_loc(string test)
{
    if (member_array(test, chimera_loc) >= 0)
        return 1;
    else if (member_array(test, warrior_loc) >= 0)
        return 2;
    else
        return 0;
}

/*
 * Function name: loc_number
 * Description  : Returns the corresponding location number to a
 *                given string location.
 * Arguments    : str - A valid location string.
 * Returns      : An integer describing the index number of 'str'
 *                in the locations arrays. 0 - 11 for chimera
 *                locations, 12 - 23 for warrior locations.
 */
public int
loc_number(string str)
{
    int num,
        arr;

    if ((num = member_array(str, chimera_loc)) >= 0)
        return num;
    if ((num = member_array(str, warrior_loc)) >= 0)
        return num + 12;
}

/*
 * Function name: set_marked
 * Description  : Sets a location to the marked array.
 * Arguments    : i - Integer representation of a location from
 *                    0 to 23.
 * Returns      : n/a
 */
public void
set_marked(int i)
{
    if (member_array(i, m_indexes(keystones)) < 0)
        marked = ({ ({i, random(3)}) });
    else
        marked = ({ ({i, keystones[i]}) });
}

/*
 * Function name: add_marked
 * Description  : Identical to set_marked, only is used to
 *                add additional locations.
 * Arguments    : Same as set_marked()
 * Returns      : n/a
 */
public void
add_marked(int i)
{
    if (!pointerp(marked))
        marked = ({});
    if (member_array(i, m_indexes(keystones)) < 0)
        marked += ({ ({i, random(3)}) });
    else
        marked += ({ ({i, keystones[i]}) });
}        

/*
 * Function name: query_marked
 * Description  : Queries the marked array.
 * Arguments    : n/a
 * Returns      : Contains an integer array of arrays. Each sub-array
 *                contains two numbers. The first is the location
 *                0 to 11, the third is a section of that location 0 to 2.
 */
public int *
query_marked()
{
    if (!marked)
        return ({});
    else
        return marked + ({});
}

/*
 * Function name: translate_locs
 * Description  : Translates a given integer array of locations
 *                into an array of corresponding string descriptions.
 * Arguments    : arr - An array of locations in integer form.
 * Returns      : An array of corresponding strings.
 */
public string *
translate_locs(mixed arr)
{
    int i;
    string *ret;

    if (!sizeof(arr))
        return ({});

    ret = allocate(sizeof(arr));

    for (i = 0; i < sizeof(arr); i++)
    {  
        if (pointerp(arr[i]))
        {
            if (arr[i][0] < 12)
                ret[i] = chimera_loc[arr[i][0]];
            else
                ret[i] = warrior_loc[arr[i][0] - 12];
        }
        else
        {
            if (arr[i] < 12)
                ret[i] = chimera_loc[arr[i]];
            else
                ret[i] = warrior_loc[arr[i]];
        }
    }

    return ret;
}            
