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
    set_name("halberd");
    add_name("polearm");
    set_adj("black");
    set_short("black halberd");
    set_pshort("black halberds");
    set_long("A wicked halberd, fashioned of a black alloy.\n");

    set_default_weapon(39, 35, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH, 0);
}
