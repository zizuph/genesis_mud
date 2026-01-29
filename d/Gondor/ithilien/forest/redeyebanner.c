/*
 * /d/Gondor/ithilien/forest/redeyebanner.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/std/object";
#include "/sys/stdproperties.h"

#define BS(message)	break_string(message, 75)

public void
create_object()
{
    set_name("banner");
    add_name("_red_eye_banner_from_camp_");
    add_name("flag");
    set_adj("large");
    add_adj("black");
    set_long(BS("This large black banner has a lidless eye embroidered in red "+
    "in the center. It is the symbol of the orcs from Mordor.\n"));
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,2500);
}
