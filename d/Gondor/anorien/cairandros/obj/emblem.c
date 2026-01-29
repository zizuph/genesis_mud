/*
 * /d/Gondor/anorien/cairandros/obj/emblem.c
 * A mostly invisble emblem that hangs inside the fort of Cair Andros.
 * - Important, because when seeing this emblem, soldiers of Cair Andros
 *   will keep hunting. Otherwise, away from the emblem they grow bored
 *   and leave
 * Varian 2016
 */

inherit "/std/object";
#include <stdproperties.h>

void
create_object()

{
    set_name("emblem");
    set_short("white emblem");
    set_pshort("white emblemss");
    set_long("This is a small emblem of a white tree, almost entirely " +
        "invisible and hanging on the wall of the fortress.\n");

    /*add_prop(OBJ_I_INVIS, 1);*/
    set_no_show();
}