/*
 * A scroll case, based on Teth's
 * /d/Krynn/common/objects/scroll_caseiv.c
 * 
 * Arman, April 2021.
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
    add_name("scrollcase");
    set_pname("cases");
    add_pname("scrollcases");
    set_adj(({"scroll","wax-sealed"}));

    set_short("wax-sealed scroll case");
    set_pshort("wax-sealed scroll cases");

    set_long("This is a scroll case that has been covered in wax, " +
        "likely to protect the contents from exposure to water.\n");

    set_keep(1);

    add_prop(OBJ_I_VALUE, 500 + (random(1000)));

    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(CONT_I_MAX_WEIGHT, 250);
    add_prop(CONT_I_MAX_VOLUME, 250);
    add_prop(CONT_I_CLOSED, 1); 
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

