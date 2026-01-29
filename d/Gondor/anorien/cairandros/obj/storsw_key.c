/*
 * Key inside Cair Andros
 * /d/Gondor/anorien/cairandros/obj/storsw_key.c
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
    set_adj(({"bent", "iron"}));
    set_short("bent iron key");
    set_long("This key is made from black iron, but it slightly bent and " +
        "warped somehow. It still looks sturdy enough, and will probably " +
        "still work if you find the matching lock.\n");
    set_key("cairandros_storage_sw");
}