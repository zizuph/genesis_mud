/*
 * /d/Gondor/minas/quest/wallsafe_key.c
 *
 * Modification history:
 *
 * 29-March-98, Gnadnar:	add no-keyring prop
 */

#pragma strict_types

inherit "/std/key";

#include "/d/Gondor/defs.h"

void
create_key()
{
    add_name("Gimilzors_wallsafe_key");
    set_adj("steel");
    add_adj("small");
    set_short("small steel key");
    set_long(BSN(
       "This small steel key has a very intricate keybit. "
     + "It looks too slender to fit in an ordinary doorlock."));
    set_key("Gimilzors_wallsafe_key");
}
