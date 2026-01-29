/*
 * Valerian - This herb heals panic
 * /d/Faerun/herbs/herb_files/valerian.c
 * Finwe, Jan 2009
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb";

#define EFFECT 50
void
create_herb()
{
    set_name("root");
    set_adj(({"angular", "tuberous"}));
    set_herb_name("valerian");
    set_short("angular tuberous root");
    set_pshort("angular tuberous roots");
    set_ingest_verb("eat");
    set_unid_long("This is an angular tuberous root. It is yellow-brown and smells musty.\n");
    set_id_long("This is the root of a Valerian. The yellow-brown, tuberous rootstock produces a hollow, angular, furrowed stem with deeply dissected leaves each bearing 7-10 pairs of lance-shaped leaflets. The root is often used to cure those with anxiety when eaten.\n");
    set_herb_value(1000);
    set_id_diff(50);
    set_find_diff(6);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_SPECIAL,"panic",EFFECT);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }


void
special_effect()
{
    if ((effects[1] != "panic") || (TP->query_panic() <= 0))
    {
        write("You do not feel any effect.\n");
        return;
    }

    TP->add_panic(-EFFECT);
    TP->catch_msg("You feel more calm and relaxed, and less panicky.\n");
}
