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
    set_name("shield");
    set_adj("black-horned");
    set_short("black-horned shield");
    set_long("A strange round black shield with spiked "+
        "horns protruding around its edges.\n");

    set_default_armour(18, A_SHIELD, 0, 0);
}
