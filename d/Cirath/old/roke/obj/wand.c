/*
 * wand.c
 *
 * Used in npc/refnas.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* wand of healing */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/wand";

#include "/d/Cirath/roke/lib/wand.h"
#include <stdproperties.h>

void
create_wand()
{
    set_name("wand");
    add_name("stick");
    set_adj("strange");
    add_adj("wooden");
    add_adj("healing");

    add_prop("refnas_e_en_riktig_man_banka_gurka_det_kan_han", 1); //FIXA

    set_short("strange wooden stick");
    set_long("A grey stick. It looks a little mysterious.\n");
    set_id_long("This is a wand of healing.\n");
    set_id_short("wand of healing");

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);

    set_charges(10);

    set_charge_value(50);

    set_wand_type(WAND_HEAL);
    set_wand_effect(40);

    set_ident_limit(25);
}
