/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour(void)
{
    set_name("boots");
    set_adj("black");
    set_short("pair of black boots");
    set_pshort("pairs of black boots");
    set_long("It is a pair of black boots with grey linings.\n");

    set_default_armour(20, A_FEET, 0, 0);
}
