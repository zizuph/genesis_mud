/*
 * Key inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/storse_key.c
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
    set_adj(({"thick", "iron"}));
    set_short("thick iron key");
    set_long("This key is rather thick and crafted from iron. The key is " +
        "well made, and it was probably designed for somewhere very " +
        "and secure.\n");
    set_key("cairandros_storage_se");
}