/*
 * Item Database Handler
 *
 * This listener is called by the item registry whenever a new item
 * is cloned. This particular handler will call the AoB item database
 * and ensure that every item in the game is tracked in the database.
 *
 * Created by Petros, November 2009
 */

#pragma strict_types

#include <macros.h>
#include <files.h>

#define AOB_ITEM_DATABASE   "/d/Genesis/ateam/aob/magic_hunter/item_database"

public void
create()
{
    setuid();
    seteuid(getuid());
    
    // Register with the callback.
    LISTENER_ADD(MASTER);
}

/* 
 * Function:    notify_new_object
 * Description: This is called by the registry whenever there is a new
 *              object. We do all the processing here.
 */
public varargs void
notify_new_object(object obj)
{
    AOB_ITEM_DATABASE->investigate(obj);
}
