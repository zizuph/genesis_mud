/*
 * /d/Gondor/ithilien/forest/corpse.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/std/container";

#include "/sys/stdproperties.h"

#define BS(message)	break_string(message, 75)

public void
create_container()
{
    set_name("corpse");
    add_name( ({ "orc","corpse of an orc" }) );
    set_short("corpse of an orc");
    set_pshort("corpses of orcs");
    set_long(BS(
	"This dead body of an orc has begun to rot away. An old "+
	"scar disfigures the orc's face, and a few fingers are missing from "+
	"his right hand, but these injuries clearly were received long ago. "+
	"There are no visible signs that explain the orc's demise.\n"));
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_WEIGHT, 65000);
    add_prop(CONT_I_VOLUME, 80000);
    add_prop(CONT_I_MAX_WEIGHT, 65000);
    add_prop(CONT_I_MAX_VOLUME, 80000);
}
