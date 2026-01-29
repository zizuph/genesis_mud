/*
 * /d/Gondor/ithilien/forest/ring.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/std/armour";

#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

public void
create_armour()
{
    set_name("ring");
    add_name("Ranger_Quest_Ring");
    set_adj("bronze");
    set_adj("little");
    set_short("small bronze ring");
    set_pshort("small bronze rings");
    set_long(BSN("This is a small ring made out of bronze. "+
	"It has an inscription "+
	"on the inside: Leydon, Ranger of Gondor."));
    set_at(A_ANY_FINGER);
    set_ac(1);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_VALUE,60);
}

#if 0
/* "_doing_lost_ranger_quest_" is not used anywhere but here.
 * old code?? gnadnar
 */
public void
enter_env(object dest, object old)
{
    object room;

    ::enter_env(dest, old);
    if ( !interactive(dest) )
	return;

    room = old;
    if ( !room->query_prop(ROOM_I_IS) )
	room = ENV(room);
    if ( room->query_prop("_this_is_the_orc_refuse_") &&
    dest->query_prop("_doing_lost_ranger_quest_") == 1 )
	dest->add_prop("_doing_lost_ranger_quest_", 2);
}
#endif
