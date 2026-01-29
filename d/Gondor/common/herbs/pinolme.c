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
    set_name("berry");
    set_adj(({"hard", "green",}));
    set_short("hard green berry");
    set_pshort("hard green berries");
    set_herb_name("pinolme");
    set_id_long(BSN("This is the Pinolme berry. Pinolme is a hard, green " +
        "berry that is found in and around northern forests. It is rumoured " +
        "to be a favourite snack for many elders of the Silvan elves.")); 
    set_unid_long(BSN("This small green berry is much harder than you " +
        "would have expected. You suspect it is probably poisonous."));
    set_ingest_verb("eat");
    set_id_diff(45);
    set_find_diff(4);
    set_effect(HERB_ENHANCING, "wis", 55);
    set_decay_time(1800);
    set_herb_value(644);
}
