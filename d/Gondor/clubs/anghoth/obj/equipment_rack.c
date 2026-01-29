/*
 *   A rack for equipment storage.
 *
 *  /d/Gondor/clubs/anghoth/obj/equipment_rack.c
 *
 *  Eowul, April 30, 2009
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/guild_rack";

#include <stdproperties.h>

void
create_rack()
{
    set_short("equipment rack");
    set_name("rack");
    set_adj("equipment");
    set_long("This massive equipment rack is set deeply into the wall. "
       + "Countless hooks, chains and straps line its interior for "
       + "effective ordering and storage of various equipment "
       + "types.\n");

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 2000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
}

