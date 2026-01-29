/*
 * /d/Gondor/anorien/cairandros/obj/bshelf.c
 *
 * Varian - February, 2020
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/std/container";

#include "../../defs.h"
#include <stdproperties.h>
#include <files.h>
#include "contobjs.c"

public void
create_container()

{
    set_adj("long");
    add_adj("stone");
    set_name("shelf");
    add_name("bookshelf");

    set_short("long stone shelf");
  
    set_long("This shelf is made from the same grey stone that " +
        "you see everywhere else in the fortress of Cair Andros. " +
        "It looks like it was designed to be a bookshelf, but " +
        "moisture seems to have destroyed most, if not all, of " +
        "the books here.\n");

    add_item( ({"books", "books on shelf"}),
        "There appears to be almost nothing legible left here, " +
        "in fact, almost everything you attempt to pick up seems " +
        "to fall apart in your hands.\n");
    
    cont_add_object("/d/Gondor/anorien/cairandros/obj/oldbook");

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);

    reset_object();
}
