/*
 *  /d/Terel/mountains/ghastly_keep/obj/g_spyglass_obj.c
 *
 *  Ghostly spyglass.
 *
 *  Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"

#define HOUR	3600
#define LIFE	itof(HOUR + random(HOUR * 2))

void
create_object()
{
    seteuid(getuid());

    set_name("_ghastly_spyglass_obj");
    set_long("_ghastly_spyglass_obj.\n");

    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_I_VALUE,   0);

    set_no_show();
    set_alarm(LIFE, 0.0, remove_object);
}
