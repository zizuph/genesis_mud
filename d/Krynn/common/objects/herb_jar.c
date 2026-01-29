/*
 * A glass jar to carry herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * /Mercade, 23 November 1993; changed from container to /std/receptacle
 * Olorin, 12 November 1996: changed to use /lib/keep.c
 * Teth, Jan 15 1997: changed slightly for Krynn purposes
 * Khail, Feb 14, 1997: changed to fix the message and weight
 * losing bugs, caused by attempts to put in non-herbs.
 * Mercade, 21 May 2004; removed decay routines.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public mixed
check_insert()
{
    int i;
    object *arr;

    for (i = 0; i < 10; i++)
    {
        if (!objectp(calling_object(-i)))
            break;
        if (calling_object(-i) == TO)
        {
            arr = ({calling_object(-(i+1))});
            if (function_exists("set_herb_name", arr[0]) != "/std/herb")
                return "You can only put herbs in the jar.\n";
        }
    }

    return 0;
}

void
create_container()
{
    set_name("jar");
    set_pname("jars");
    set_adj("glass");

    set_short("@@short_func");
    set_pshort("glass jars");
    set_long("This is a glass jar for storing herbs.\n");

    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_TRANSP,1);

    add_prop(CONT_I_WEIGHT,200);
    add_prop(CONT_I_VOLUME,200);
    add_prop(CONT_I_MAX_WEIGHT,3000);
    add_prop(CONT_I_MAX_VOLUME,3000);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    add_prop(OBJ_I_VALUE,48);

    add_prop(CONT_M_NO_INS, VBFC_ME("check_insert"));

    set_keep(1);
}

string
short_func()
{
    if (sizeof(all_inventory(this_object())) >= 1)
        return "herb jar";
    return "glass jar";
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

