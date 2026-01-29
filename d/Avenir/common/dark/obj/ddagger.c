/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon(void)
{
    set_name("dagger");
    add_name("knife");
    set_adj("bone-hilted");
    set_short("bone-hilted dagger");
    set_pshort("bone-hilted daggers");
    set_long("A black blade with a bone hilt, bearing an emblem of a chimera.\n");

    set_default_weapon(20, 20, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH, 0);
}
