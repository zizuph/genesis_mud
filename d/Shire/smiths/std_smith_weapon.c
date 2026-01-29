/*
 *  /d/Shire/smiths/sl_final.c
 *
 *  The standard weapon used by the Smiths' Guild
 *
 *  Glaurung 8/97
 */
 
#pragma strict_types;
#pragma save_binary;

inherit "/std/weapon";
inherit "/lib/keep.c";

#include "/d/Shire/smiths/smiths.h"
#include "/d/Shire/defs.h"


//************** Global Variables ********//
static string Recover_str;
static string Forger;
static string ForgeName;

//************** Prototypes **************//
public string query_forger();
public string query_forgeName();
public string query_recover_str();
public void   set_forger(string s);
public void   set_forgeName(string s);
public void   set_recover_str(string s);
public void   set_state(string s);


string
query_forgeName() { return ForgeName; }

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
    if (!stringp(s))
        return;

    set_recover_str("#SMW#"+TO->query_hit()+"#"+TO->query_pen()+"#"+
        query_forgeName()+"#"+s+"#"+query_forger()+"#");
}


/*
 * function name: set_forger
 * description  : sets the name of the player who forged this weapon
 * arguments    : string s - name of the forger
 */

public void 
set_forger(string s) { Forger = lower_case(s); }


/*
 * function name: query_forger
 * description  : lets us know who forged this weapon
 * returns      : string - name of the player who forged this weapon
 */

public string
query_forger() { return Forger; }


/*
 * function name: set_recover_str
 * description  : sets the recover string for this weapon
 * arguments    : string s - a string of variables we want this 
 *                weapon to recover via query_recover()
 */

public void
set_recover_str(string s) { Recover_str = s; }


/*
 * function name: query_recover_str
 * description  : lets us know what variables we will recover from
 *                this weapon
 */

public string
query_recover_str() { return Recover_str; }


/*
 * function name: init_recover
 * description  : recovers variables and sets the recover string
 *                for this weapon. calls the manager object to
 *                initialize this weapon after a reboot 
 * arguments    : string s - variables to be recovered
 */

public void
init_recover(string s)
{
    string init_wep_rec_str,
           junk,
           weapon_name,
           state,
           forger;
    int    hit, pen;

    FIXEUID

    sscanf(s, "%s#SMW#%d#%d#%s#%s#%s#%s", junk, hit, pen,
        weapon_name, state, forger, init_wep_rec_str);
    set_recover_str("#SMW#"+hit+"#"+pen+"#"+weapon_name+
        "#"+state+"#"+forger+"#");
    if (!objectp(find_object(MANAGER)))
        MANAGER->load_object();

    MANAGER->init_smith_weapon(hit,pen,weapon_name,TO,state,forger);
    ::init_wep_recover(init_wep_rec_str);
}
 

/*
 * function name: query_recover
 * description  : lets us know all variables this weapon will recover
 * returns      : a string of the variables to be recovered
 */

public string
query_recover()
{
    return MASTER+":"+Recover_str+query_wep_recover();
}
