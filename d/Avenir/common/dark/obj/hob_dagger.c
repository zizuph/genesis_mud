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
    set_adj("stone");
    set_short("stone dagger");
    set_pshort("stone daggers");
    set_long("A large sharp stone dagger.\n");

    set_default_weapon(15, 15, W_KNIFE, W_IMPALE, W_ANYH, 0);
}
