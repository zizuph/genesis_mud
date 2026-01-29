/*
 * pot.c
 *
 * Used in npc/ddealer.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* some pot - to smoke :) */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include "defs.h"
#include <herb.h>
#include <macros.h>

int i = 0;

void
create_herb()
{
    set_ingest_verb("smoke");

    set_name("grass");
    set_short("brown grass");
    set_adj("brown");

    add_name("herb");
    add_name("leaf");

    set_herb_name("pot");

    set_unid_long("Some brown grass.\n");
    set_id_long("This is some high-quality pot, well suited for smoking.\n");

    set_herb_value(100);

    set_id_diff(3);

    set_find_diff(1);

    set_effect(HERB_SPECIAL, "", 0);
}

void
special_effect()
{
    object g;

    write("As you smoke the grass you are filled with a feeling of peace " +
          "and tranquility. You are also getting pleasantly intoxicated.\n");

    TP->drink_alco(50);

    seteuid(getuid());

    g = clone_object(ROKEDIR + "obj/potpoison");
    g->move(TP, 1);
    g->start_poison();
}
