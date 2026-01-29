/*
 * Item Recovery Database Library
 *
 * Stores information about the items managed by this container. This
 * allows the container to recover the items as much as possible in the
 * state that they were in before.
 *
 * To use this library, you will need to do the following:
 *  1. inherit this library in your object
 *  2. Set the options of whether you want to enable logging or recovery in the object creation function.
 *
 *     setuid();
 *     seteuid(getuid());
 *
 *     if (!IS_CLONE)
 *     {
 *         return;
 *     }
 *
 *     set_enable_logging(0);
 *     set_enable_recovery(1);
 *
 *  3. Call the initialization routines in the object creation function
 *
 *     init_database();
 *     set_alarm(0.0, 0.0, &recover_objects_from_database());
 *
 *  4. Call add_rack_entry in the enter_inv of the object
 *  5. Call remove_rack_entry in the leave_inv of the object
 *
 * For an example of all these steps, please see:
 *   /d/Genesis/specials/lib/examples/recover_rack.c
 *
 * By default, this library stores the data file in the same directory
 * as the master object, and appends _data to the name. For example,
 * rack.c would have a data file called rack_data.o.
 *
 * Note: A saveable rack should only have one instance. If you clone
 *       more than one instance, the results will be undefined.
 *
 * Created by Petros, October 2010
 *
 * Revisions:
 * 	Lucius, September, 2017: Added basic check to add_rack_entry
 * 	        and remove_rack_entry to prevent duplication from
 * 	        improperly coded racks.
 *
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <filepath.h>
#include <files.h>

inherit "/d/Genesis/specials/lib/database_lib";

// Defines
#define RECOVERY_INTERVAL     0.1
#define OBJ_I_IGNORE_RECOVERY "_obj_i_ignore_recovery"
#define OBJ_I_TEST_ARMAGEDDON_ACTIVE  "_obj_i_test_armageddon_active"
#define OBJ_I_DO_NO_RESTORE           "_obj_i_do_not_restore"
#define AUTOSAVE_MASTER               "/d/Genesis/specials/lib/autosave_rack_master"

// Global Variables
public int          bEnableLogging = 0;  // Logging is off by default.
public int          bEnableRecovery = 1; // Recovery is on by default


static int queue_alarm;
static function *itemActionQueue = ({ }); // A list of actions to perform

/*
 * Function:    set_enable_logging
 * Description: Allows someone to set whether logging will be
 *              enabled or not. If logging is set, then all events
 *              will get logged in the log file.
 */
public void
set_enable_logging(int bEnable)
{
    if (bEnable != 0)
    {
        bEnableLogging = 1;
    }
    else
    {
        bEnableLogging = 0;
    }
}

/*
 * Function:    set_enable_recovery
 * Description: Allows someone to toggle whether recovery should
 *              be active or not.
 */
public void
set_enable_recovery(int bEnable)
{
    if (bEnable != 0)
    {
        bEnableRecovery = 1;
    }
    else
    {
        bEnableRecovery = 0;
    }
}

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return MASTER_OB(this_object()) + "_data";
}

/*
 * Function:    query_log_file
 * Description: This is the log file that will get written to
 *              whenever there are changes in the database.
 */
public string
query_log_file()
{
    if (!bEnableLogging)
    {
        return 0; // returning 0 means that we don't log to disk.
    }
    return MASTER_OB(this_object()) + "_log.txt";
}

/*
 * Function:    init_database
 * Description: This function initializes all the columns for the
 *              database. It should be called during the creation of
 *              the container. It must be called before calling
 *              restore_objects_from_database().
 */
public void
init_database()
{
    ::init_database();

    add_column("instance"); // actual object in rack
    add_column("file");     // master object file name
    add_column("recover_type");   // none (0), recover (1), autoload (2)
    add_column("recover_string"); // string to pass to init function
    add_column("recoverable");    // currently recoverable or not
    add_column("armageddon"); // if set, item will be recovered according to Armageddon rules.

    setuid();
    seteuid(getuid());

    // Last step of initializing is to register with the autosave rack master
    if (AUTOSAVE_MASTER->add_saving_rack_entry(this_object()))
    {
        send_debug_message("item_recovery_lib", "Successfully added saving "
            + "rack to the master.");
    }
    else
    {
        send_debug_message("item_recovery_lib", "Failed to add saving "
            + "rack to the master.");
    }
}

/*
 * Function:    is_valid_rack_item
 * Description: A function used to determine whether we will keep a
 *              rack entry for this item.
 */
public int
is_valid_rack_item(object obj)
{
    if (!objectp(obj))
    {
        return 0;
    }

    // We don't allow living objects to be cloned again. We may
    // change this for messengers in the future.
    if (IS_LIVING_OBJECT(obj) || obj->query_prop(OBJ_I_DO_NO_RESTORE))
    {
        return 0;
    }

    return 1;
}

/*
 * Function:    populate_row_entry
 * Description: Takes in an existing row entry and populates it with the
 *              values for the object.
 */
public void
populate_row_entry(object obj, mapping entry)
{
    string file, recover_string;
    int recover_type, recoverable;

    file = MASTER_OB(obj);
    recover_type = 0;
    recoverable = 0;
    if (function_exists("query_recover", obj))
    {
        recover_type = 1;
        recover_string = obj->query_recover();
        if (obj->check_recoverable())
        {
            recoverable = 1;
        }
    }
    else if (function_exists("query_auto_load", obj))
    {
        recover_type = 2;
        recover_string = obj->query_auto_load();
    }

    if (!mappingp(entry))
    {
        entry = ([ ]);
    }
    entry["instance"] = obj;
    entry["file"] = file;
    entry["recover_type"] = recover_type;
    entry["recover_string"] = recover_string;
    entry["recoverable"] = recoverable;
    entry["armageddon"] = 0;
}


/* Process the pending additions, removals or updates in order */
static void
process_queue() {
    int i, chunk = 100;

    queue_alarm = 0;

    for (; i < sizeof(itemActionQueue) && i < chunk; i++) {
        function f = itemActionQueue[i];
        f();
    }

    if (i < sizeof(itemActionQueue)) {
        itemActionQueue = itemActionQueue[i..];
        queue_alarm = set_alarm(0.0, 0.0, &process_queue());
    } else {
        itemActionQueue = ({ });
    }
}


static void
queue_items(object obj, function callback)
{
    itemActionQueue += ({ papplyv(callback, ({ obj, file_name(obj) })) });

    foreach (object item: all_inventory(obj))
    {
        itemActionQueue += ({ papplyv(callback, ({ item, file_name(item) })) });
    }

    send_debug_message("item_recovery_lib_detail", sprintf("queue: %O", itemActionQueue));

    if (!queue_alarm) 
        queue_alarm = set_alarm(0.0, 0.0, &process_queue());
}

static void
add_rack_item(object ob, string file)
{
    mapping entry = ([ ]);

    if (!objectp(ob))
        return;

    foreach (mixed row: m_rows)
    {
        if (row["instance"] == ob)
        {
            send_debug_message("item_recovery_lib", sprintf("add_item: Item already exists! %O", ob));
            return;
        }
    }


    populate_row_entry(ob, entry);
    add_or_update_row(entry);
}


static void
update_rack_item(object ob, string file)
{
    if (!objectp(ob))
        return;

    foreach (mixed row: m_rows)
    {
        if (row["instance"] == ob)
        {
            populate_row_entry(ob, row);
            return;
        }
    }
}

/*
 * Function:    add_rack_entry
 * Description: This adds the entry for the object into the database,
 *              allowing it to be restored at a later time.
 *              This function should be called inside the container's
 *              enter_inv.
 */
public int
add_rack_entry(object obj)
{
    if (!is_valid_rack_item(obj))
    {
        // Can't add an invalid object
        send_debug_message("item_recovery_lib", "add_rack_entry(): Invalid object " + file_name(obj));
        return 0;
    }


    /* This catches heap merging and turns them into an update */
    if (environment(obj) && environment(obj) != this_object())
    {
        if (environment(environment(obj)) == this_object())
        {
            queue_items(environment(obj), update_rack_item);
            return 1;
        }
    }

    queue_items(obj, add_rack_item);
    return 1;
}

static void
remove_rack_item(object ob, string name)
{
    mixed *deleted = filter(m_rows, &operator(==)(, ob) @ &operator([])(, "instance"));

    if (sizeof(deleted) > 0) {
        m_rows -= deleted;
    } else {
        send_debug_message("item_recovery_lib", sprintf("remove_item(): Item to remove not found: %O / %O", ob, name));
    }
}


/*
 * Function:    remove_rack_entry
 * Description: This function should be called by the container's
 *              leave_inv function. It will remove the object from
 *              the database, so that it won't be restored.
 */
public int
remove_rack_entry(object obj)
{
    if (!is_valid_rack_item(obj))
    {
        return 0;
    }

    queue_items(obj, remove_rack_item);
    return 1;
}

public int
clear_all_rows()
{
    m_rows = ({ });
    itemActionQueue = ({ });
    save_data();
}

/*
 * Function:    post_process_recovered_object
 * Description: Allows someone to override this and post process the object
 *              once it's been created (autoload and/or recover)
 * Arguments:   obj - the object that was recovered/loaded
 *              row - the entire row that contains all the data
 */
public void
post_process_recovered_object(object obj, mixed * row)
{
}

static object
clone_recover_object(string entry, function init)
{
    string file, argument;

    if (!stringp(entry) || !strlen(entry))
        return 0;

    if (sscanf(entry, "%s:%s", file, argument) != 2)
    {
        file = entry;
        argument = 0;
    }

    /* Don't print messages to random players */
    set_this_player(0);

    object ob;
    catch(ob = clone_object(file));
    if (!objectp(ob))
    {
        return 0;
    }

    /* Note that we don't check for strlen() since we also want to call
     * init_recover() if the format is 'filename:'.
     */
    if (stringp(argument) && functionp(init))
    {
        /*
         * Call the provided init function
         * If init returns true the object is removed. If the return value is
         * an object that object is return instead, allowing recovered items to
         * be replaced.
         */
        mixed ret;

        try {
            if (ret = init(ob, argument))
            {
                ob->remove_object();

                if (objectp(ret)) {
                    return ret;
                }

                return 0;
            }
        } catch (mixed ex) {
            ob->remove_object();
            return 0;
        }
    }

    return ob;
}


/*
 * Function:    slow_recover_objects
 * Description: This function is called by recover_objects_from_database
 *              to recover each object. This is normally called by alarm
 *              so that objects will not exceed eval_cost for containers
 *              with lots of objects to restore.
 */
public nomask void
slow_recover_objects(mixed * current_rows, object rack)
{
    string file, arg;

    if (!bEnableRecovery || !objectp(rack) || !sizeof(current_rows))
    {
        return;
    }

    mixed row = current_rows[0];
    if (sizeof(current_rows) > 1)
    {
        // We keep looping until we finish loading all the objects
        set_alarm(RECOVERY_INTERVAL, 0.0, &slow_recover_objects(current_rows[1..], rack));
    }

    if (objectp(row["instance"]))
    {
        // Object already exists. We don't need to recover it.
        send_debug_message("item_recovery_lib", "Did not recover " + row["file"]
            + " because it already exists.", query_log_file());
        m_rows += ({ row });
        save_data();
        return;
    }


    function init;
    string type;
    switch (row["recover_type"])
    {
        case 0:
            break;
        case 1: // init_recover
            init = &->init_recover();
            type = " using recovery";
            break;
        case 2: // init_arg
            init = &->init_arg();
            type = " using autoload";
            break;
    }

    object obj = clone_recover_object(row["recover_string"], init);

    if (!objectp(obj))
    {
        // Couldn't properly create the object.
        send_debug_message("item_recovery_lib", "Could not recover " + 
            row["recover_string"], query_log_file());
        return;
    }

    string log_message = "Restoring " + row["recover_string"] + type;

    // Apply the previous recoverable state
    if (row["armageddon"])
    {
        // After an Armageddon, we allow the item_recovery_handler to set
        // the glow rates, rather than setting it based on what it was
        // before.
        log_message += " after Armageddon.";
    }
    else
    {
        // We want to set the ignore recovery property so that the item recovery
        // handler doesn't improperly reset the recovery flag
        obj->add_prop(OBJ_I_IGNORE_RECOVERY, 1);
        if (row["recoverable"])
        {
            obj->set_may_recover();
            log_message += " and making it glow.";
        }
        else
        {
            obj->set_may_not_recover();
            log_message += " and making it not glow.";
        }
    }

    if (strlen(query_log_file()))
    {
        send_debug_message("item_recovery_lib", log_message, query_log_file());
    }

    // Move the cloned object to the rack
    if (obj->move(rack) != 0)
    {
        // failed to move the item to the rack. Try to move it into
        // the environment of the rack object.
        obj->move(environment(rack));
    }

    // Call a post-processing function so that inheriting objects can
    // do their own additional work on the object.
    post_process_recovered_object(obj, row);
}

/*
 * Function:    recover_objects_from_database
 * Description: This function should be called after init_database to
 *              restore all the saved objects from disk.
 */
public void
recover_objects_from_database()
{
    object obj;
    string file, arg;

    if (bEnableRecovery)
    {
        // We control the logging of the messages using bEnableRecovery
        // flag, but we still move forward with the bookkeeping for all the
        // database rows.
        send_debug_message("item_recovery_lib", "Recovering " + sizeof(m_rows)
            + " object(s).", query_log_file());
    }
    mixed * current_rows = m_rows;
    mixed * remaining_rows = ({ });
    clear_all_rows(); // clear and save so no one else will recover these objects

    set_alarm(RECOVERY_INTERVAL, 0.0, &slow_recover_objects(current_rows, this_object()));
}

/*
 * Function:    check_for_armageddon
 * Description: This function needs to be called in the remove_object
 *              of the container so that we can properly remove
 *              non-saving items during Armageddon. We definitely don't
 *              want non-saving items to come back the next Armageddon.
 *              For crashes, however, we do keep the non-recoverable
 *              items.
 */
public void
check_for_armageddon()
{
    if (!IS_CLONE)
    {
        return;
    }

    // We need to check if we are being destructed during Armageddon. If so,
    // we need to remove all the non-recoverable objects.
    if ((ARMAGEDDON->shutdown_active() && !ARMAGEDDON->query_manual_reboot())
        || this_object()->query_prop(OBJ_I_TEST_ARMAGEDDON_ACTIVE))
    {
        mixed * glowing_rows = ({ });
        foreach (mixed row : m_rows)
        {
            if (row["recover_type"] == 2 || row["recoverable"] == 1)
            {
                row["armageddon"] = 1; // set the armageddon bit so that glow rates will be controlled by the item_recovery_handler
                glowing_rows += ({ row });
            }
        }
        send_debug_message("item_recovery_lib", "Out of " + sizeof(m_rows)
            + " objects, saving " + sizeof(glowing_rows) + " glowing "
            + "objects during Armageddon.", query_log_file());
        m_rows = glowing_rows;
        save_data();
    }
    else
    {
        mixed * updated_rows = ({ });
        foreach (mixed row : m_rows)
        {
            row["armageddon"] = 0;
            updated_rows += ({ row });
        }
        m_rows = updated_rows;
        save_data();
    }
}

/*
 * Function:    refresh_database
 * Description: Sometimes, due to runtime errors, the database entries can
 *              get out of whack compared to the actual contents of the object.
 *              We have a function here that will clear all the rows and
 *              refresh them so that it's back in sync again.
 */
public void
refresh_database()
{
    // First clear everything
    clear_all_rows();
    map(all_inventory(this_object()), add_rack_entry);
}

public void
remove_object()
{
    save_data();
    // We call destruct here on purpose. The only alternative is
    // to force every recovery rack to override remove_object. We
    // do this here for convenience.
    // Because it calls destruct() directly, all normal things done
    // through remove_object() will be ignored.
    destruct();
}
