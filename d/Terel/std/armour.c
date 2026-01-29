/*
 *  /d/Terel/std/armour.c
 *
 *  The standard armour object of Terel.
 *
 *  Torm, Sept 98
 *
 *  Modified by Lilith, July 2008
 *  - Removed the feature making armours unwearable based on race
 *  - Admin is trying to make game more playable, not less. Items
 *    which discriminate against players in such ways as this one
 *    did are being discouraged.
 *
 * Modified by ?, March 25 2010
 *
 * Modified by Lavellan, July 11 2011
 *  - Removed unnecessary nomask for wear()
 *
 * Lucius, 2021-03
 *  - Really remove the armour size check.
 */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Terel/include/Terel.h"

//** prototypes **//
static nomask void set_armour_size(int i);
public void create_terel_armour();
public mixed wear_terel_armour(object o);
public int query_armour_size();

//** global variables **//
private int gArmourSize;


/*
 * Function name: query_armour_size
 * Description  : informs us about the size of this armour
 * Returns      : int - the armour size
 */

public int
query_armour_size() { return gArmourSize; }

/*
 * Function name: set_armour_size
 * Description  : Sets the size of who can wear this armour
 * Arguments    : int i - the size we want
 */

static nomask void
set_armour_size(int i) { gArmourSize = i; }


/*
 * Function name: create_terel_armour
 * Description  : Use this function to set the name, description, 
 *                armour type, armour size, etc.
 */

public void
create_terel_armour()
{
}


/*
 * Function name: create_armour
 * Description  : Allows for centralized control over all
 *                armours inheriting this object. You cannot
 *                redefine this function, instead use
 *                create_terel_armour.
 */

public nomask void
create_armour()
{
    set_name("_std_terel_armour");
    set_pname("_std_terel_armours");
    set_af(TO);
    set_armour_size(MEDIUM); // our default size
    add_name("armour");
    add_pname("armours");
    create_terel_armour();
}


/*
 * Function name: wear
 * Description  : This function might be called when someone 
 *                tries to wear this armour. You cannot redefine
 *                this function, instead use wear_terel_armour.
 * Arguments   : object obj - The armour we want to wear.
 * Returns         : int  0 - The armour can be worn normally.
 *                 1 - The armour can be worn, but print no messages.
 *                -1 - The armour can't be worn, use default messages.
 *                 string - The armour can't be worn, use this message.
 */

public mixed
wear(object obj)
{
#if 0
    int race_size = RACE_SIZE_TRACKER->query_race_size(TP->query_race_name());

    if (gArmourSize & race_size)
        return wear_terel_armour(obj);

    return "The "+TO->query_short()+" does not fit properly on you.\n";
#else
        return wear_terel_armour(obj);
#endif
}


/*
 * Function name: wear_terel_armour
 * Description  : This function might be called when someone tries to 
 *                wear this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int 0 - The armour can be worn normally.
 *                1 - The armour can be worn, but print no messages.
 *               -1 - The armour can't be worn, use default messages.
 *                string - Armour can't be worn, use this message.
 */

public mixed
wear_terel_armour(object obj)
{
    return 0;
}


/*
 * function name: init_recover
 * description  : recovers armour size and other info for this armour.  
 * arguments    : string s - variables to be recovered
 */

public void
init_recover(string s)
{
    string armour_vars, junk;
    int armour_size;

    setuid(); seteuid(getuid());

    sscanf(s, "%s#TAS#%d#%s", junk, armour_size, armour_vars);
    set_armour_size(armour_size);
    armour_vars = "#" + armour_vars;
    ::init_arm_recover(armour_vars);
}


/*
 * function name: query_recover
 * description  : lets us know all variables this armour will recover
 * returns      : a string of the variables to be recovered
 */

public string
query_recover() 
{ 
    return MASTER+":#TAS#"+gArmourSize+query_arm_recover();
}
