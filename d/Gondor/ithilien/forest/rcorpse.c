/*
 * /d/Gondor/ithilien/forest/rcorpse.c
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
    add_name( ({ "human", "corpse of a human" }) );
    set_short("corpse of a human");
    set_pshort("corpses of humans");
    set_long(BS(
	"This is the dead body of a tall human. He has been dead for "+
	"a long time, but he must have suffered enormously before he died. "+
	"The man was tall and well-built, but now his body looks badly "+
	"tortured and mauled. His stomach has been torn open, and a hand "+
	"is missing.\n"));
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_WEIGHT, 87000);
    add_prop(CONT_I_VOLUME, 90000);
    add_prop(CONT_I_MAX_WEIGHT, 87000);
    add_prop(CONT_I_MAX_VOLUME, 90000);
}
