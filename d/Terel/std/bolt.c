/*
 * bolt.c
 *
 * This is the base for all kinds of bolts that are
 * shot with xbows. Inherit this class if you want to
 * create your own kind of bolts.
 *
 * Since bolt is a heap object your need to give
 * it an unique id with set_projectile_id() or else it
 * might be absorbed by other heaps of bolts.
 *
 * See /doc/examples/weapons/black_feathered_arrow.c
 * for an example of an arrow.
 */

#pragma strict_types

inherit "/std/projectile";

#include <stdproperties.h>

/*

 * Description  : Constructor. Use this constructor to create bolt type
 *                projectiles.
 */

public void
create_bolt()
{
  return;
}


/*
 * Function name: get_projectile_long
 * Description  : Use this function to return the proper long description
 *                of this bolt.
 *
 * Arguments    : string str     - the pseudo-item to describe. This is an
 *                                 item added with add_item. If this is 0, it
 *                                 will return the description of the whole
 *                                 object.
 *                object for_obj - the object trying to get the long.

 * Returns      : string         - the description of the object or
 *                                 pseudo-item.
 */

string
get_projectile_long(string str, object for_obj, int num)
{
    return "The bolt" +
        ((num == 1) ? " is" : "s are") + " unusually plain.\n";
}


/*
 * Function name: create_projectile
 * Description  : Constructor. This sets some internal state of the bolt
 *                Mask create_bolt instead if you want to create a bolt.
 */

public nomask void
create_projectile()
{
    set_name("bolt");

    add_prop(HEAP_I_UNIT_WEIGHT, 42);
    add_prop(HEAP_I_UNIT_VOLUME, 40);
    add_prop(HEAP_I_UNIT_VALUE, 20);
    set_hit(40);
    set_pen(40);
    set_heap_size(12);
    set_projectile_id("plain_bolt");
    create_bolt();
}


/*
 * Function name: is_bolt
 * Description  : A function that indentifies this projectile as a bolt
 *                type projectile.
 *
 * Returns      : (int) 1 - Since this is a bolt.
 */

public nomask int
is_bolt()
{
    return 1;
}
