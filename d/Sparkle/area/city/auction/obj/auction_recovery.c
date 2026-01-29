/*
 *  /d/Sparkle/area/city/auction/obj/auction_recovery.c
 *
 *  This item is recovered by a player instead of the actual item.
 *  It clones and configures the actual item, then destructs.
 *  
 *  2010/09/16 Lavellan
 *  2016/01/09 Britanica
 */
#pragma strict_types

inherit "/std/object";

#include "../defs.h"
#include <stdproperties.h>
#include <files.h>

/* Global Variables */
public object           obj;
public int              id;

/* Prototypes */
public void             create_object();
public void             init_recover(string arg);
//public void             enter_env(object dest, object old);
public string           query_recover();
public void             replace();


/*
 * Function name:        create_object
 * Description  :        set up
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());
    set_name("_recoverer");
    set_long("It's not quite ready yet.\n");
} /* create_object */


/*
 * Function name:        init_recover
 * Description  :        clone object
 */
public void
init_recover(string arg)
{
    id = atoi(arg);
    obj = AUCTION_DATA_STORE->get_auction_item("" + id, 1);
    if (objectp(obj))
    {
        set_short(obj->short());
        set_long(obj->long());
    }
    else
    {
        write("Recovery failed, item lost in Armageddon.\n");
        remove_object();
    }
} /* init_recover */


/*
 * Function name:        enter_env
 * Description  :        mov
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest,old);
    if (obj)
        replace();
} /* enter_env */


/*
 * Function name:        replace
 * Description  :        Replace this object with real item
 */
public void
replace()
{
    obj->move(environment(), 1);
    remove_object();
} /* replace */


/*
 * Function name: query_recover
 * Description:   Return recover string for anything cloning us
 * Returns:       Recover string for recoverer, not item
 */
public string
query_recover()
{
    return AUCTION_RECOVER + ":" + id;
} /* query_recover */