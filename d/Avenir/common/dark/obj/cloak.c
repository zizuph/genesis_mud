/*
 * A black cloak, suitable for a assassin. Shinto 980730
 *
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour(void)
{
    set_name("cloak");
    set_adj(({"black"}));
    set_short("black cloak");
    set_pshort("black cloaks");
    set_long("It's a black cloak with grey linings.\n");

    set_default_armour(10, A_ROBE, ({ -2, 0, 2}), 0);
}
