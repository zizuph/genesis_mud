/*
 *  /d/Genesis/imbuement2/obj/recoverer.c
 *
 *  This item is recovered by a player instead of the actual item.
 *  It clones and configures the actual item, then destructs.
 *  
 *  2010/09/16 Lavellan
 */
#pragma strict_types

inherit "/std/object";
#include "../imbuement.h"
#include <stdproperties.h>

/* Global Variables */
public object           obj;

/* Prototypes */
public void             create_object();
public void             init_recover(string arg);
public void             enter_env(object dest, object old);


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
} /* create_object */


/*
 * Function name:        init_recover
 * Description  :        clone object
 */
public void
init_recover(string arg)
{
    string recs, *rec;
//    TELL_G("Arg: " + arg);
//    TELL_G("Recover: " + IMBUE_MASTER->get_recover(atoi(arg)));
    recs = IMBUE_GENERATOR->get_recover(atoi(arg));
    rec = explode(recs, ":");
    obj = clone_object(rec[0]);
    obj->init_recover(rec[1]);
    set_short(obj->short());
    add_prop(OBJ_I_WEIGHT, obj->query_prop(OBJ_I_WEIGHT));
    IMBUE_GENERATOR->reimbue(obj, atoi(arg));
    obj->move(environment(),1);
} /* init_recover */


/*
 * Function name:        enter_env
 * Description  :        mov
 */
public void
enter_env(object dest, object old)
{
    obj->move(environment(), 1);
    remove_object();
}