/*
 *  /d/Genesis/imbuement2/obj/recoverer.c
 *
 *  This item is recovered by a player instead of the actual item.
 *  It clones and configures the actual item, then destructs.
 *
 *  2010/09/16 Lavellan
 *
 *  Modifications:
 *    January 30, 2016 - Added query_imbuement_id to help identify which
 *                       imbuement entry this object originally came from.
 *   December 20, 2018 - Fixed a bad bug with the weight of recovered
 *                       imbues. - Cotillion
 *
 */
#pragma strict_types

inherit "/std/object";

#include "../imbuement.h"
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
public mixed 
init_recover(string arg)
{
    string recs, *rec;
//    TELL_G("Arg: " + arg);
//    TELL_G("Recover: " + IMBUE_MASTER->get_recover(atoi(arg)));
    IMBUE_LOGGER->log_shadow(atoi(arg), 0, "Recovering " +
        file_name(calling_object()) + " " +
        (IS_PLAYER_OBJECT(calling_object()) ?
        calling_object()->query_real_name() :
        file_name(calling_object())));
    id = atoi(arg);
    recs = IMBUE_GENERATOR->get_recover(id);
    if (!recs)
    {
        IMBUE_LOGGER->log("bad_recover", (IS_PLAYER_OBJECT(calling_object()) ?
            calling_object()->query_real_name() :
            file_name(calling_object())) + " failed to recover " + arg + " " +
            this_player()->query_real_name());
        // Set a property on this recoverer object so that we can inform the callers
        // that there was a problem with this imbuement.
        add_prop("_imbuement_missing", 1);
        set_alarm(0.0, 0.0, remove_object);
        return 1;
    }
    rec = explode(recs, ":");
    obj = clone_object(rec[0]);

    if (sizeof(rec) > 1)
        obj->init_recover(rec[1]);

    add_prop(OBJ_I_WEIGHT, obj->query_prop(OBJ_I_WEIGHT));
    add_prop("_recovered_obj", obj);

    IMBUE_GENERATOR->reimbue(obj, atoi(arg));
    set_short(obj->short());
    set_long(obj->long());

    return obj;
} /* init_recover */


/*
 * Function name:        enter_env
 * Description  :        mov
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest,old);
    if (obj) {
        set_alarm(0.0, 0.0, &replace());
    }
} /* enter_env */


/*
 * Function name:        replace
 * Description  :        Replace this object with real item
 */
public void
replace()
{
    /* This is not a nice solution, but this entire setup is not stable */
    obj->add_prop("auction_id", query_prop("auction_id"));

    if (!(environment(obj)))
    {
        obj->move(environment(), 1);
    }
    obj = 0;
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
    return RECOVER_OBJ + ":" + id;
} /* query_recover */

/*
 * Function:    query_imbuement_id
 * Description: Returns the value of the "id" field, which is the
 *              actual imbuement id used by the imbuement generator
 *              and imbuement master. Note that this is set in
 *              init_recover.
 */
public int
query_imbuement_id()
{
    return id;
}
