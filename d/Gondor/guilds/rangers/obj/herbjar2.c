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
 */
#include "../rangers.h"
#include <stdproperties.h>

inherit RANGERS_OBJ + "herbjar";

public void
create_container()
{
    ::create_container();

    /* Do not remove this. It's needed for sorting purposes. */
    add_name("herb_storage_jar");

    add_prop(OBJ_M_NO_GET, "It's glued to the floor.\n");
}
