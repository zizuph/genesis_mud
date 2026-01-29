/*
 * A glass jar to carry herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * /Mercade, 23 November 1993; changed from container to /std/receptacle
 * Olorin, 12 November 1996: changed to use /lib/keep.c
 * Khail, Feb 14, 1997: changed to fix the message and weight
 *        losing bugs, caused by attempts to put in non-herbs.
 * Gwyneth, Nov 20, 2003: Made putting in and getting out herbs more
 *                        efficient to try to prevent so many runtimes.
 * Tigerlily, March 26, 2004: added ::leave_inv(obj, from); to leave_inv
 * Mercade, 21 May 2004; removed decay related code.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "/d/Gondor/defs.h"

public string  short_func();
public string  pshort_func();

public void
create_container()
{
    set_name("jar");
    add_name("herbjar");
    set_adj( ({ "glass", "herb", }) );
    set_short(short_func);
    set_pshort(pshort_func);
    set_long("This is a glass jar for storing herbs. You can <hsort jar> to " +
      "remove non-glowing herbs.\n");
    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_RIGID,         1);
    add_prop(CONT_I_TRANSP,        1);
    add_prop(CONT_I_WEIGHT,      200);
    add_prop(CONT_I_VOLUME,      200);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(OBJ_I_VALUE,         48);

    /* some herbs are spell components */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    set_keep(1);
}

public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the " + query_name() + ".\n");
        return 1;
    }

    return 0;
}

string
short_func()
{
    if (sizeof(all_inventory(TO)))
        return "herb jar";
    return "glass jar";
}

string
pshort_func()
{
    if (sizeof(all_inventory(TO)))
        return "herb jars";
    return "glass jars";
}

public string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_keep_recover(arg);
}

/*
 * Function name: reject_me
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
int
reject_me(object ob, object env)
{
    if (ob->move(env) == 0) 
    {  
        //write("You remove "+ LANG_THESHORT(ob) +" from " + 
        //    LANG_THESHORT(this_object()) + ".\n"); 
        return 1; 
    } 
    return 0; 
}

/*
 * Function name: check_lasting
 * Description  : check to see if item is recoverable or autoloading
 */
void
check_lasting(object ob, object env)
{
    if (ob->check_recoverable()) 
        return;
    if (ob->query_auto_load())
        return;
    else
        reject_me(ob, env);
}

/*
 * Function name: do_sort
 * Description  : runs inventory through check_lasting.
 */
void
do_sort()
{
    map(all_inventory(this_object()), 
         &check_lasting(,environment(this_object()))); 
}

/*
 * Function name: start_sort
 * Description  : 
 */
int
start_sort(string arg)
{
    object *ob;

    if (!stringp(arg))
    {
        notify_fail("Sort what?\n");
        return 0;
    }
    
    if (!parse_command(arg, deep_inventory(ENV(TP)), "%i", ob))
    {
        notify_fail("Sort what?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);
    if (!sizeof(ob) || ob[0] != TO)
    {
        notify_fail("Sort what?\n");
        return 0;
    }

    do_sort();
    write("You remove non-glowing herbs from the " + short() + ".\n");
    return 1;
}



/* Function name: init
 * Description  : Masks init to add tie and untie verbs.
 */
public void
init()
{
    ::init();
    add_action(start_sort, "hsort");    
}

