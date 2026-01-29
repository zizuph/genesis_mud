#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_receptacle()
{
    set_short("great chest");
    set_name("chest");
    set_adj("great");
    set_long("This great chest lies in the center of the chamber. Grey bands " +
        "of an unknown metal tightly bind strips of pine together. Black " +
        "tar has been applied to the joints of the strips ensuring an " +
        "airtight seal. ");

    add_prop(OBJ_M_NO_GET, "The chest is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 750000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

}
