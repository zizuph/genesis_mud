/*
 *  /d/Earthsea/gont/sewers/obj/dam.c
 *
 *  A barricade made at the bottom of the sewers.
 *  Supposed to appear to be the block that stops items in its
 *  room. Made a container as a quirk, so players can stash stuff
 *  in it.
 *
 *  Adapted by Aeg from fountain_pool.c. 
 *  All credit goes to Gorboth.
 */
#pragma strict_types

#include "../defs.h"
inherit "/std/container";

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>


/* Prototpyes */
public void        create_container();
public void        init();
public void        describe_contents(object for_obj, object *obarr);


/*
 * Function name:        create_container
 * Description  :        set up the object
 */
public void
create_container()
{
    set_name("heap");
    add_name("dam_heap");

    set_short("makeshift dam at the lowpoint of the sewer");
    set_long("The makeshift dam seems to be solidly constructed, "
      + "but it seems that you might be able to toss things in this "
      + "heap.\n");

    add_prop(CONT_I_MAX_VOLUME, 50000000);
    add_prop(CONT_I_VOLUME,     10000000);
    add_prop(CONT_I_WEIGHT,     10000000);
    add_prop(CONT_I_MAX_WEIGHT, 50000000);

    /* We don't want this to appear as an extra item in room
     * descriptions. Rather, it will be up to individual rooms that have
     * such dams to indicate that this is present somehow.
     */
    set_no_show_composite(1);

    setuid();
    seteuid(getuid());
} /* create_container */
    
    
    
/*
 * Function name:        drop_stuff
 * Description  :        allow the player to drop stuff in the dam.
 * Arguments    :        string arg -- what the player typed
 * Returns      :        1 -- success, 0 -- failure
 *
 */
public int
drop_stuff(string arg)
{
    mixed   fail;
    object  drop_ob;
    int     heap_true = 0;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o [in] [into] [to] [the] [makeshift] "
      + " 'heap'", drop_ob))
    {
        return 0;
    }

    if (drop_ob->query_no_show_composite())
    {
        return 0;
    }

    if (drop_ob->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail("You cannot throw the " + drop_ob->short()
                 + " away.\n");
        return 0;
    }

    if (IS_HEAP_OBJECT(drop_ob))
    {
        heap_true = 1;
        drop_ob->split_heap(1);
    }

    if (!drop_ob->move(this_object()))
    {
        write("You toss "
          + ((heap_true) ? drop_ob->short() : "the " + drop_ob->short())
          + " into the heap of the makeshift dam.\n");
          say(QCTNAME(this_player()) + " does something to the makeshift "
          + "dam.\n");

        if (heap_true)
        {
            drop_ob->restore_heap();
        }

        write_file(SEWER_LOG_DIR + "dam",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " put " + ((heap_true) ? drop_ob->short() :
           LANG_ADDART(drop_ob->short())) + " into the heap.\n");

        return 1; /* success! */
    }

    /* We get here if for some reason the move failed. We'll assume
     * that the fountain is too full, and thus we'll instead have it
     * land on the ground.
     */

    write("You toss "
      + ((heap_true) ? drop_ob->short() : "the " + drop_ob->short())
      + " into the heap,"
      + " but there is so much stuff piling up, that"
      + " it bounces off and lands at your feet instead.\n");
    say(QCTNAME(this_player()) + " tosses "
      + ((heap_true) ? drop_ob->short() : LANG_ADDART(drop_ob->short()))
      + " into the heap, but it"
      + " bounces off all the junk and lands instead on"
      + " the ground.\n");

    drop_ob->move(environment(this_object()));

    if (heap_true)
    {
        drop_ob->restore_heap();
    }

    return 1;
} /* drop_stuff */


/*
 * Function name:        init
 * Description  :        add some actions for the player
 */
public void
init()
{
    ::init();

    add_action(drop_stuff, "toss");
    add_action(drop_stuff, "drop");
    add_action(drop_stuff, "put");
    add_action(drop_stuff, "throw");

} /* init */


/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 *
 * We don't want the standard empty messages for containers applied
 * to this pool, so we mask the function from /std/container.c.
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(this_object()->show_sublocs(for_obj));

    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("You see " + COMPOSITE_DEAD(obarr)
          + " and many other items in the heap of the makeshift "
          + "dam.\n");
    }
    } /* describe_contents */
    