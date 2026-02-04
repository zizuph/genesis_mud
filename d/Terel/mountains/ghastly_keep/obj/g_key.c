/*
 *  /d/Terel/mountains/ghastly_keep/obj/g_key.c
 *
 * Copper-plated key.
 *
 *  Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */
inherit "/std/object";

#include "../defs.h";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("key");
    add_name("_gkeep_chest_key");
    set_adj("copper");
    add_adj("plated");

    set_short("copper-plated key");

    set_long("This looks like an ordinary key, plated with copper.\n");

    add_prop(OBJ_I_VALUE, 50);
    add_prop("_key_i_no_keyring", 1);

}
