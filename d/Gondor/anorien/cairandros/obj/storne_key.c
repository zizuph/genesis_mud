/*
 * Key inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/storne_key.c
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
    set_adj(({"long", "iron"}));
    set_short("long iron key");
    set_long("This key is rather long and crafted from iron. The key is " +
        "well made, and it was probably designed for somewhere very " +
        "and secure.\n");
    set_key("cairandros_storage_ne");
}