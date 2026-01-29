/* 
 * bee balm - Cures fatigue
 * Finwe, January 2009
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
    set_name("leaves");
    set_adj(({"sprig of", "green"}));
    set_herb_name("bee balm");
    set_short("sprig of green leaves");
    set_pshort("sprigs of green leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a sprig of soft, downy leaves. It is green and smells of lemons.\n");
    set_id_long("This is a sprig of Bee Balm. It's a member of the Mint family and also known as Lemon Balm. The leaves are soft and triangular shaped. It smells like lemons and is thought to lift the spirits when eaten.\n");
    set_herb_value(( 4 * 50) + (50 * 50)/4 );
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
    TP->catch_msg("Your breathing slows down as a calm feeling descends on you.\n");
}
