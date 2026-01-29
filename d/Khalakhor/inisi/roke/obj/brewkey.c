/*
 * brewkey.c
 *
 * Used in nyreese/red_pub.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/key";

#include <stdproperties.h>

void
create_key()
{
    set_name("key");
    add_name("cadu_beerkey");
    set_adj("metal");
    set_long("It appears to be the key to some kind of tap.\n");

    add_prop(OBJ_I_VALUE, 200);
}
