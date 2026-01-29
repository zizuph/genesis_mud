/*
 * /std/rock.c
 *
 * This is the base for all kinds of rocks that are
 * shot with bows. Inherit this class if you want to
 * create your own kind of rocks.
 *
 * Since /std/rock is a heap object your need to give
 * it an unique id with set_projectile_id() or else it
 * might be absorbed by other heaps of rocks.
 *
 * See /doc/examples/weapons/black_feathered_rock.c
 * for an example of an rock.
 */

#pragma strict_types

inherit "/std/projectile";

#include <stdproperties.h>

/*
 * Function name: create_rock
 * Description  : Constructor. Use this constructor to create rock type
 *                projectiles.
 */

public void
create_rock()
{
  return;
}


/*
 * Function name: get_projectile_long
 * Description  : Use this function to return the proper long description
 *                of this rock.
 *                
 * Arguments    : string str     - the pseudo-item to describe. This is an
 *                                 item added with add_item. If this is 0, it
 *                                 will return the description of the whole
 *                                 object.
 *                object for_obj - the object trying to get the long.
 *                int num        - The number of rocks in this stack.
 * Returns      : string         - the description of the object or
 *                                 pseudo-item.
 */

string
get_projectile_long(string str, object for_obj, int num)
{
    return "The rock" + 
        ((num == 1) ? " is" : "s are") + " unusually plain.\n";
}


/*
 * Function name: create_projectile
 * Description  : Constructor. This sets some internal state of the rock
 *                Mask create_rock instead if you want to create an
 *                rock.
 */

public nomask void
create_projectile()
{
    set_name("rock");

    add_prop(HEAP_I_UNIT_WEIGHT, 22);
    add_prop(HEAP_I_UNIT_VOLUME, 26);
    add_prop(HEAP_I_UNIT_VALUE, 20);
    set_hit(40);
    set_pen(40);
    set_heap_size(12);
    set_projectile_id("plain_rock");
    create_rock();
}


/*
 * Function name: is_rock
 * Description  : A function that indentifies this projectile as an rock
 *                type projectile.
 *
 * Returns      : (int) 1 - Since this is an rock.
 */

public nomask int
is_rock()
{
    return 1;
}
