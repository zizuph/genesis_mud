/*
 * Key inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/fort_hall_key.c
 *
 * Varian 2016
 */

#pragma strict_types

inherit "/std/key";

#include "../../defs.h"

void
create_key()
{
    set_name("key");
    set_adj(({"dirty", "old"}));
    set_short("dirty old key");
    set_long("This key is made of iron, although that is hard to see at " +
        "first as it is covered in a layer of dirt and grime. Aside from " +
        "being old and dirty, the key appears to be in good condition.\n");
    set_key("cairandros_fort_hall");
}