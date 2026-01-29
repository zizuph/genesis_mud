/*
 * A glass jar to carry herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * Mercade, 23 November 1993; changed from container to /std/receptacle
 * Olorin, 12 November 1996: changed to use /lib/keep.c
 * Khail, Feb 14, 1997: changed to fix the message and weight
 *        losing bugs, caused by attempts to put in non-herbs.
 * Mercade, 21 May 2004: removed decay protection.
 */
#pragma strict_types

inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

/* Identify it as herb jar only when filled. */
string
short_func()
{
    if (sizeof(all_inventory()))
    {
        return "herb jar";
    }
    return "glass jar";
}

/* Identify it as herb jar only when filled. */
string
pshort_func()
{
    if (sizeof(all_inventory()))
    {
        return "herb jars";
    }
    return "glass jars";
}

/* Constructor. */
public void
create_container()
{
    set_name("jar");
    add_name("herbjar");
    set_adj( ({ "glass", "herb", }) );
    set_short(short_func);
    set_pshort(pshort_func);
    set_long("This is a glass jar for storing herbs.\n");
    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_RIGID,         1);
    add_prop(CONT_I_TRANSP,        1);
    add_prop(CONT_I_WEIGHT,      200);
    add_prop(CONT_I_VOLUME,      200);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(OBJ_I_VALUE,         48);

    /* Some herbs are spell components */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    set_keep(1);
}

/* Only allow herbs to be inserted. */
public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the "+query_name()+".\n");
        return 1;
    }
    return 0;
}

/* Necessary for recovering the keep value. */
public string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

/* Necessary for recovering the keep value. */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
}
