/* /d/Shire/common/herbs/obj/master_bundle.c
*
*
* by Palmer, Feb 2003
*
* The bundle master object that keeps track of bundle's decay times.
* It is loaded from /d/Shire/domain_links.c
*
* After reboot it loads the mapping for the recovering bundles to query.
* It deletes old bundles, in case someone didn't login after reboot.
*
* See /d/Shire/common/herbs/obj/wrap.c for info
*
* To see what bundles are in memory use:
*    Call mbundle show_bundles
*
* Mapping keys are: playername*timestamp*random_int
*
* Why the random integer? If someone wraps two bundles within
* a second, both keys would be the same.
*
*/

#pragma strict_types

inherit "/std/object.c";

#include "../defs.h"
#include <macros.h>
#include "/sys/stdproperties.h"

#define MAP_FILE "/d/Shire/common/herbs/obj/nbundle_map"
#define MAX_TIME 1382400
/* TEMPORARY: Increased time to 9 days due to test of 1 week recovery - Palmer */
/* MAX_TIME is oldest time for bundles in seconds before it is deleted (2 days) */

    
    
/* Function Prototypes */
public int create_object();
public void add_bundle(string key, string herb_file, int *decays);
public void remove_bundle(string key);
public void show_bundles();
nomask private void restore_bundles();
public int clear_old_bundles();
public int query_time(string key);

/* Globals */
mapping Bundles = ([ ]);


public int
create_object()
{
    set_name("mbundle");
    set_short("mbundle");

    setuid();
    seteuid(getuid());

    restore_bundles();
    
    // Lets do this a couple hours after reboot to be nice.
    set_alarm(7200.0, 0.0, clear_old_bundles);
}


/*
 * Function name: clear_old_bundles
 *
 * Description  : Clears old bundles that were never restored after reboot
 *
 * Arguments: 
 * Returns: 1/0
 */
public int
clear_old_bundles()
{
    int ktime, i, n, now;
    string *keys;
    mapping new_bundles = ([ ]);
    mixed vals;
    
    now = time();
    
    keys = m_indices(Bundles);
    vals = m_values(Bundles);
    
    n = sizeof(keys);
    
    for (i = 0; i < n; i++)
    {
        ktime = atoi(query_time(keys[i]));
        if (now - ktime < MAX_TIME)
        {
            new_bundles += ([keys[i]:vals[i]]);
        }
    }
    
    save_map(new_bundles, MAP_FILE);
    restore_bundles();
    
    return 1;
}


/*
 * Function name: query_file
 *
 * Description  : Get herb file name
 *
 * Arguments: string - key
 * Returns: string - file name
 */
public string
query_file(string key)
{
    string file;
    
    file = Bundles[key][0];
    
    return file;
}


/*
 * Function name: query_decays
 *
 * Description  : Get herb decays
 *
 * Arguments: string - key
 * Returns: mixed - decay times
 */
public mixed
query_decays(string key)
{
    int *decays;
    
    decays = Bundles[key][1];
    
    return decays;
}


/*
 * Function name: query_time
 *
 * Description  : Get time of bundle's creation
 *
 * Arguments: 
 * Returns: int - time
 */
public int
query_time(string key)
{
    string name;
    int time, garbage;
    
    sscanf(key, "%s*%s*%s", name, time, garbage);
    return time;
}

/*
 * Function name : restore_bundles
 * Description   : restores the bundle mapping from disk
 */
nomask private void
restore_bundles()
{
    Bundles = restore_map(MAP_FILE);
    if (!mappingp(Bundles))
        Bundles = ([ ]);
}


/*
 * Function name: show_bundles
 *
 * Description  : Dumps bundle mapping for debugging purposes
 *
 * Arguments: none
 * Returns: write() output of mapping
 */
public void
show_bundles()
{
    dump_mapping(Bundles, "\t");
}


/*
 * Function name: add_bundle
 *
 * Description  : Add bundle info to mapping when someone wraps
 *                     a bundle of herbs.
 *
 * Arguments: string player, string herb_file, int time, int *decays
 * Returns: none
 */
public void
add_bundle(string key, string herb_file, int *decays)
{
    Bundles += ([key:({herb_file, decays})]);
    save_map(Bundles, MAP_FILE);
}

/*
 * Function name: remove_one_herb
 *
 * Description  : Remove single herb, used when used in spell component
 *
 * Arguments: string - Key
 * Returns: none
 */
public void
remove_one_herb(string key)
{
    int n, *decays;
    string herb_file;
    
    herb_file = query_file(key);
    decays = query_decays(key);
    n = sizeof(decays);
    
    decays = decays[0..0] + decays[1..n-2];
    Bundles = m_delete(Bundles, key);
    add_bundle(key, herb_file, decays);
}
 

/*
 * Function name: remove_bundle
 *
 * Description  : Remove bundle info from mapping when someone
 *                      unwraps a bundle.
 *
 * Arguments: none
 * Returns: none
 */
public void
remove_bundle(string key)
{
    Bundles = m_delete(Bundles, key);
    save_map(Bundles, MAP_FILE);
}
 
