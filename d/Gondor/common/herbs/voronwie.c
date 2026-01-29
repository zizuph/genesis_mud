/*
 * Modified from Tuo
 *
 * Varian 2015
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("fern");
    set_adj(({"yellow", "brittle",}));
    set_short("brittle yellow fern");
    set_pshort("brittle yellow fern");
    set_herb_name("voronwie");
    set_id_long(BSN("This is a piece of Voronwie, a fern that often " +
        "grows near heavily wooded areas. This yellowish fern is rather " +
        "fragile and brittle, crumbling very easily each time you handle " +
        "it. Old legends suggest that in contrast to its physical " +
        "appearance, eating the leaves of this rare fern will grant you " +
        "remarkable endurance.")); 
    set_unid_long(BSN("This yellowish fern is very delicate and brittle, " +
        "crumbling between your fingers whenever you handle it."));
    set_ingest_verb("eat");
    set_id_diff(51);
    set_find_diff(7);
    set_effect(HERB_ENHANCING, "con", 35);
    set_decay_time(1800);
    set_herb_value(589);
}
