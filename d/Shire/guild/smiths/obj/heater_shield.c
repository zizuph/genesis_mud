/*
 * /d/Shire/guild/smiths/heater_shield.c
 *
 * Palmer - Aug 2006
 * Based on std_smith_armour
 */

#pragma strict_types;


inherit "/std/armour.c";
inherit "/lib/keep.c";

#include "/d/Shire/guild/smiths/smiths.h"
#include "/d/Shire/defs.h"


//************** Global Variables ********//
static string Recover_str;
static string Forger;
static string ForgeName;

//************** Prototypes **************//
public string query_forger();
public string query_forgeName();
public string query_recover_str();
public void set_forger(string s);
public void set_forgeName(string s);
public void set_recover_str(string s);
public void set_state(string s);


string
query_forgeName() 
{
    return ForgeName;
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}

void
set_forgeName(string s) { ForgeName = s; }

/*
 * function name: set_state
 * description  : changes the state flag of this object indicating
 *                the type of adjective shadow in use
 * arguments    : string s - the state to change to
 */

public void
set_state(string s)
{
    set_recover_str("#SMA#" + TO->query_ac() + "#" + query_forgeName() +
        "#" + s + "#" + query_forger() + "#");    
}


/*
 * function name: set_forger
 * description  : sets the name of the player who forged this armour
 * arguments    : string s - name of the forger
 */

public void 
set_forger(string s) 
{ 
    Forger = lower_case(s);
}


/*
 * function name: query_forger
 * description  : lets us know who forged this armour
 * returns      : string - name of the player who forged this armour
 */

public string
query_forger()
{ 
    return Forger;
}


/*
 * function name: set_recover_str
 * description  : sets the recover string for this armour
 * arguments    : string s - a string of variables we want this 
 *                armour to recover via query_recover()
 */

public void
set_recover_str(string s)
{ 
    Recover_str = s; 
}


/*
 * function name: query_recover_str
 * description  : lets us know what variables we will recover from
 *                this armour
 */

public string
query_recover_str() 
{
    return Recover_str;
}


/*
 * function name: init_recover
 * description  : recovers variables and sets the recover string
 *                for this armour. calls the manager object to
 *                initialize this armour after a reboot 
 * arguments    : string s - variables to be recovered
 */

public void
init_recover(string s)
{
    string init_arm_rec_str,
           junk,
           armour_name,
           state,
           forger;
    int    ac;

    FIXEUID

    sscanf(s, "%s#SMA#%d#%s#%s#%s#%s", junk, ac, armour_name,
        state, forger, init_arm_rec_str);
    set_recover_str("#SMA#" + ac + "#" + armour_name + "#" + state + "#" + 
                    forger + "#");
    if (!objectp(find_object(MANAGER)))
        MANAGER->load_object();

    MANAGER->init_smith_armour(ac, armour_name, TO, state, forger);
    ::init_arm_recover(init_arm_rec_str);
}


/*
 * function name: query_recover
 * description  : lets us know all variables this armour will recover
 * returns      : a string of the variables to be recovered
 */

public string
query_recover()
{
    return MASTER + ":" + Recover_str + query_arm_recover(); 
}


