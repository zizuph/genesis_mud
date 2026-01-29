/*
 * ob_key.c
 * An obsidian key.
 * Written by Trenix@Genesis, 8-16-93
 *
 */

inherit "/std/key";
#include <stdproperties.h>

create_key()
{
    set_name( ({ "key" }) );
    set_pname( ({ "keys" }) );
    set_adj("black");
    add_adj("obsidian");
    set_short("black obsidian key");
    set_pshort("black obsidian keys");
    set_long("It's a sharp black key carved from an obsidian stone.\n");
    set_key("_trenix_obsidian_key_");
    add_prop(OBJ_I_WEIGHT,15); /* 15 grams */
    add_prop(OBJ_I_VOLUME,10); /* 10 ml    */
    add_prop(OBJ_I_VALUE,24);  /* 2 silver */
}

/* EOF */
