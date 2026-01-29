/*
 * Key inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/fort_key.c
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
    set_adj(({"iron", "black"}));
    set_short("black iron key");
    set_long("This is a key, all black and made from iron. The key is " +
        "well made, and it was probably designed for somewhere very " +
        "and secure. However, it also looks as if the key was left " +
        "abandoned somewhere for years, as it still quite dirty and " +
        "has developed spots of rust.\n");
    set_key("cairandros_fort");
}