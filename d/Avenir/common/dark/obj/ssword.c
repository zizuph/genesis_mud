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
    set_name("sword");
    add_name("shortsword");
    set_adj(({ "black", "short" }));
    set_short("black shortsword");
    set_pshort("black shortswords");
    set_long("A black blade with a bone hilt, bearing an emblem of a chimera.\n" );

    set_default_weapon(36, 36, W_SWORD, W_IMPALE| W_SLASH, W_ANYH, 0);
}
