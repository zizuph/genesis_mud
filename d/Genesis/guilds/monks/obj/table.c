/*
 * File:     table
 * Created:  Cirion, 1998.06.06
 * Purpose:  inheritable table with some bells and whistles
 * Modification Log:
 *
 */
#pragma strict_types

inherit "/std/container";
#include "defs.h"
#include <composite.h>
#include <filter_funs.h>

string describe_prefix = " Standing in the room is a table";

/*
 * Function name: table_ob_size_sort
 * Description:   Sort function to sort an array
 *                of objects according to the sum of
 *                their size and weight.
 * Arguments:     a - first object to check
 *                b - second object to check
 * Returns:       1 if a is smaller than b
 *                -1 if b is smaller than a
 *                0 if a and b are the same size
 */
int
table_ob_size_sort(object a, object b)
{
    int v1, v2;

    v1 = a->query_prop(OBJ_I_VOLUME);
    v2 = b->query_prop(OBJ_I_VOLUME);

    if(v1 == v2)
        return 0;
    if (v1 < v2)
        return 1;
    if (v1 > v2)
        return -1;
}


/*
 * Function name: table_filter_largest
 * Description:   Filter function to give the largest
 *                objects in an array.
 * Arguments:     obs - the array of objects to check
 *                max - the number of objects to be returned
 * Returns:       The larget 'max' objects from the array,
 *                based on the objects' size and weight.
 */
varargs object *
table_filter_largest(object *obs, int max = 5)
{
    return sort_array(obs, table_ob_size_sort)[0 .. MIN(max, sizeof(obs) - 1)];
}

/*
 * Function name: describe_table
 * Description:   Call this function in a VBFC from the
 *                room that clones the table to show the
 *                external description of the table, along
 *                with the largest x items on the table
 * Returns:       The external description of the table that
 *                will show up in the room.
 */
string
describe_table()
{
    object *stuff;
    string str = describe_prefix;

    stuff = FILTER_DEAD(all_inventory(TO));
    if(!sizeof(stuff))
        return str + ".";
    else if(sizeof(stuff) <= 5)
        return str + ", upon which lies " + COMPOSITE_DEAD(stuff) + ".";
    else
        return str + ", scattered upon which are many things, including "
            + COMPOSITE_DEAD(table_filter_largest(stuff, 5)) + ".";
}

/*
 * Function name: set_describe_prefix
 * Description:   Set the prefix of the table's external
 *                description for the room desc. Prepend it
 *                with a space. Do not end with any puncuation.
 *                E.g.:
 *                set_describe_prefix (" Dominating the room is a "
 *                    + "massive redwood dining table");
 * Arguments:     str - the string that will prefix the description
 *                    of the table
 */
void
set_describe_prefix (string str)
{
    describe_prefix = str;
}

/*
 * Function name: create_table
 * Description:   Call this function to set up the
 *                non-default values for your table.
 */
public void
create_table()
{
    set_name ("table");
}

nomask void
create_container()
{
    if(!IS_CLONE)
        return;

    set_name("table");

    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 1934);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It does not move.\n");

    set_no_show_composite(1);

    create_table();
}


