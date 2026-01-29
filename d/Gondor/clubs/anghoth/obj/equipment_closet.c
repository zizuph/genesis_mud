/*
 *   A closet for equipment storage.
 *
 *  /d/Gondor/clubs/anghoth/obj/equipment_closet.c
 *
 *  Alto, 18 August 2002
 *
 */
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_container()
{
    set_short("concealed closet");
    set_name("closet");
    set_adj("concealed");
    add_adj(({"hidden", "small"}));
    set_long("This small closet was constructed to avoid notice. It looks like it "
         + "could be used to store almost anything.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The closet built into the wall itself and cannot "
        + "be taken.\n");
    add_prop(OBJ_I_VOLUME,      100000);
    add_prop(OBJ_I_WEIGHT,      100000);
    add_prop(CONT_I_VOLUME,     200000);
    add_prop(CONT_I_WEIGHT,     200000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

}

