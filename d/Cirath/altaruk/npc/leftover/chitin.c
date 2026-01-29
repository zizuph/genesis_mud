/*
 * /d/Cirath/altaruk/npc/leftover/chitin.c
 *
 * Heap item for special leftover to
 * /d/Cirath/altaruk/npc/mekillot.c and
 * mekillot_tame.c
 *
 * Azazel 2002
 */
#pragma strict_types

#include <stdproperties.h>

inherit "/std/object";

void
create_object()
{

    set_name("chitin");
    add_adj("mekillot");
    set_long("This is the torn and bloody remains of a mekillot" +
        " chitin. It dosent look edible. Maybe someone can make" +
        " something usefull from it.\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, random(100) + 400);
    add_prop(OBJ_I_VOLUME, random(100) + 400);
}
