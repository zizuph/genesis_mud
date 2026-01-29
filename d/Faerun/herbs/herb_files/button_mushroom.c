/* 
 * button mushroom - Has little health value
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
    add_name("button");
    set_adj(({"small", "white"}));
    set_herb_name("button mushroom");
    set_short("small white mushroom");
    set_pshort("small white mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a small white mushroom.\n");
    set_id_long("This small, white mushroom is a Button mushroom. The cap is plump and creme colored and the the stem is thick. It is found growing in meadows and grasslands. It is a younger version of the common Portabello mushroom.\n");
    set_herb_value(( 4 * 5) + (5 * 5)/4 );
    set_id_diff(25);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",5);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
