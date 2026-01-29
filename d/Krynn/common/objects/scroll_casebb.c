/*
 * A scroll case!
 *
 * By Teth, Feb 1997
 * With much help from Khail, to fix the insert object into case
 * bug. :-)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

#define SCROLL_I_FURLED   "_scroll_i_furled"

public int
valid_scroll(object ob)
{
    if (function_exists("set_file", ob) != "/std/scroll")
        return 0;

    if (!ob->query_prop(SCROLL_I_FURLED))
        return 0;

    return 1;
}

public mixed
check_insert()
{
    int i;
    object ob;

    for (i = 0; i < 10; i++)
    {
        if (!objectp(previous_object(-i)))
            break;
        if (previous_object(-i) == this_object())
        {
            ob = previous_object(-(i+1));
            if (valid_scroll(ob))
                return 0;
            else
                return "You may only insert furled scrolls into the case.\n";
        }
    }
    return 0;
}

public void
create_container()
{
    set_name("case");
    set_pname("cases");
    add_name("scrollcase");
    add_pname("scrollcases");
    set_adj(({"scroll","bark","birch","birchbark"}));

    set_short("birchbark scroll case");
    set_pshort("birchbark scroll cases");

    set_long("This is a birchbark scroll case, that offers " +
      "little protection to scrolls.\n");

    set_keep(1);

    add_prop(OBJ_I_VALUE, 30 + (random(114)));

    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(CONT_I_MAX_WEIGHT, 250);
    add_prop(CONT_I_MAX_VOLUME, 250);

    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_M_NO_INS, VBFC_ME("check_insert"));
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
}

public void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
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

