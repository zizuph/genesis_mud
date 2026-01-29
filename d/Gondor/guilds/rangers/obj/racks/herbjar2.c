/*
 * A glass jar to carry herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * /Mercade, 23 November 1993; changed from container to /std/receptacle
 * Olorin, 12 November 1996: changed to use /lib/keep.c
 * Khail, Feb 14, 1997: changed to fix the message and weight
 *        losing bugs, caused by attempts to put in non-herbs.
 * Gwyneth, 3/24/02, altered to allow sorting. Do not use this copy
 * for anything but being glued to the floor in the Ranger equipment
 * rooms!
 * ?   , 17 May 2004: previous update?
 * Lavellan, 29 October 2010: changed to use new saving rack system
 */
#include "../../rangers.h"
//#include <stdproperties.h>
#include <macros.h>
#pragma no_clone

inherit RANGERS_OBJ + "herbjar";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

public void
create_container()
{
    ::create_container();

    /* Do not remove this. It's needed for sorting purposes. */
    add_name("herb_storage_jar");

    add_prop(OBJ_M_NO_GET, "It's glued to the floor.\n");

    if (!IS_CLONE)
    {
        return;
    }

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database());
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from == this_object())
    {
        return;
    }

    add_rack_entry(ob);
}


public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to == this_object() || !objectp(to))
    {
        return;
    }

    remove_rack_entry(ob);
}