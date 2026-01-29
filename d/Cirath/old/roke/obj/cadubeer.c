/*
 * cadubeer.c
 *
 * Used in nyreese/cadu_inn.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle 921113 */

#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include "defs.h"
#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(540);       /* a pint */
    set_alco_amount(50);
    set_long("This is a pint of the world famous Cadu beer, the most " +
             "refreshing and relaxing beer ever made.\n");
    set_name("beer");
    set_adj("excellent");
    set_short("cadu beer");
    set_pshort("cadu beers");
    add_name("cadubeer");

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 600);
}

void
special_effect(int amnt)
{
    seteuid(getuid());

    if (!present("drunk", this_player()))
        clone_object(ROKEDIR + "obj/drunk")->move(this_player());
}
