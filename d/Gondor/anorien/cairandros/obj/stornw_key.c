/*
 * Key inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/stornw_key.c
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
    set_adj(({"small", "grey"}));
    set_short("small grey key");
    set_long("This is small key is dark grey and made from iron. The key is " +
        "well made, and it was probably designed for somewhere very " +
        "and secure.\n");
    set_key("cairandros_storage_nw");
}