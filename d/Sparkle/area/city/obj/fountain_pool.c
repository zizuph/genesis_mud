/*
 *  /d/Sparkle/area/city/obj/fountain_pool.c
 *
 *  A pool of water that rests within a basin of a fountain. Players can
 *  drink from them or toss things (such as coins) into them.
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
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
public int         do_drink(string str);
public void        init();
public void        describe_contents(object for_obj, object *obarr);


/*
 * Function name:        create_container
 * Description  :        set up the object
 */
public void
create_container()
{
    set_name("pool");

    set_short("pool at the base of the fountain");
    set_long("A pool fills the basin at the base of the fountain,"
      + " catching the water as it falls.\n");

    add_prop(CONT_I_MAX_VOLUME, 50000000);
    add_prop(CONT_I_VOLUME,     10000000);
    add_prop(CONT_I_WEIGHT,     10000000);
    add_prop(CONT_I_MAX_WEIGHT, 50000000);

    /* We don't want this to appear as an extra item in room
     * descriptions. Rather, it will be up to individual rooms that have
     * such fountains to indicate that this is present somehow.
     */
    set_no_show_composite(1);

    setuid();
    seteuid(getuid());
} /* create_container */


/*
 * Function name:        do_drink
 * Description  :        let players drink from the fountain
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'fountain' / 'basin' [from] [the]"
      + " [basin] [of] [the] [fountain]"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("People nearby peer curiously at you as you dip your hand"
             + " in the basin and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You seem to have drunk your fill.\n");
    }
    else
    {
        write("People nearby peer curiously at you as you dip your hand"
             + " in the basin and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the"
        + " fountain.\n");

    return 1;
} /* do_drink */


/*
 * Function name:        drop_stuff
 * Description  :        allow the player to drop stuff off of the
 *                       cliff ledge.
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
        "[the] %o [in] [into] [to] [the] [beautiful] [central]"
      + " 'pool' / 'fountain' / 'basin' [of] [the] [fountain]", drop_ob))
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
          + " into the fountain"
          + " where it sinks with a splash into the pool.\n");
        say(QCTNAME(this_player()) + " tosses "
          + ((heap_true) ? drop_ob->short() :
           LANG_ADDART(drop_ob->short())) + " into the fountain.\n");

        if (heap_true)
        {
            drop_ob->restore_heap();
        }

        write_file(LOG_DIR + "fountain",
            TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_real_name()) 
          + " tossed " + ((heap_true) ? drop_ob->short() :
           LANG_ADDART(drop_ob->short())) + " into the fountain.\n");

        return 1; /* success! */
    }

    /* We get here if for some reason the move failed. We'll assume
     * that the fountain is too full, and thus we'll instead have it
     * land on the ground.
     */

    write("You toss "
      + ((heap_true) ? drop_ob->short() : "the " + drop_ob->short())
      + " into the fountain,"
      + " but there is so much stuff piling out of the pool, that"
      + " it bounces off and lands at your feet instead.\n");
    say(QCTNAME(this_player()) + " tosses "
      + ((heap_true) ? drop_ob->short() : LANG_ADDART(drop_ob->short()))
      + " into the fountain, but it"
      + " bounces off all the junk in the pool and lands instead on"
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
    add_action(do_drink, "drink");
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
          + " resting at the bottom of the pool.\n");
    }
} /* describe_contents */