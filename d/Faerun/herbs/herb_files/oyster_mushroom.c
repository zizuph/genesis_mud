/* 
 * oyster mushroom - It has basic healing properties
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

void
create_herb()
{
    set_name("mushroom");
    add_name("oyster");
    set_adj(({"large", "fan-like"}));
    set_herb_name("oyster mushroom");
    set_short("large fan-like mushroom");
    set_pshort("large fan-like mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a large fan-like mushroom. It is cream colored and resembles an oyster.\n");
    set_id_long("This is an Oyster mushroom. It is large and grows in forests and is cream colored. The mushroom grows on trees resembles an oyster's shell as it fans outwards.\n");
    set_herb_value(( 4 * 15) + (15 * 15)/4 );
    set_id_diff(30);
    set_find_diff(6);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",15);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
