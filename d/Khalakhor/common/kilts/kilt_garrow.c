/*
 * kilt_garrow.c
 *
 * A kilt bearing the tartan of clan garrow.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/d/Khalakhor/std/arm/kilt_base";

public void
create_kilt()
{
    hunting = "green";
    colours = ({"red", "yellow"});
    clan = "Clan Garrow";
}
