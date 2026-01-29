/*
 * /d/Cirath/altaruk/npc/leftover/claw.c
 *
 * Heap item for special leftover to
 * /d/Cirath/altaruk/npc/erdlu_tame.c,
 * erdlu_steed.c and erdlu_wild.c
 *
 * Azazel 2002
 */
#pragma strict_types

#include <stdproperties.h>

inherit "/std/object";

void
create_object()
{

    set_name("claw");
    add_adj("erdlu");
    set_long("This is the torn and bloody remains of a erdlu" +
        " claw. It dosent look edible. Maybe someone can make" +
        " something usefull from it.\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, random(30) + 50);
    add_prop(OBJ_I_VOLUME, random(30) + 50);
}
