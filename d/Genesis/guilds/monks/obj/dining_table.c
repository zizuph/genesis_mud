/*
 * File:     dining_table
 * Created:  Cirion, 1998.05.29
 * Purpose:  table for the monk's dining hall
 * Modification Log:
 *    Cirion, 1998.06.07: changed it to an inheritable module,
 *        simplified this instance of it.
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>
#include <filter_funs.h>
inherit MONK_OBJ + "table";
inherit MONKLIB;

string
table_long ()
{
    return "This massive table is made from dark redwood. It "
        + "extends the entire length of the dining hall, and "
        + "arranged neatly around the table are " + LANG_WNUM (m_member_count ())
        + " sturdy wooden chairs. The surface of the table is scarred "
        + "and stained from countless meals and celebrations over the "
        + "years.\n";
}

void
create_table()
{
    set_name("table");
    add_name("dining_table");
    set_adj(({"heavy","redwood","red","massive","wood"}));
    set_short("massive redwood table");
    set_long(table_long);
    set_describe_prefix(" Dominating the room is a massive redwood dining "
        + "table");

}

