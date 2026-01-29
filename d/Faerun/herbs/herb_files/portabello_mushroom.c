/* 
 * portabello mushroom - Has little health value
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
    add_name("portabello");
    set_adj(({"large", "capped"}));
    set_herb_name("portabello");
    set_short("large capped mushroom");
    set_pshort("large capped mushrooms");
    set_ingest_verb("eat");
    set_unid_long("This is a large capped mushroom.\n");
    set_id_long("This is a Portabello mushroom. It is found growing in grasslands and meadows and is the mature version of the Button mushroom. The cap is the size of a small plate and beige colored. The stem is thick and tan.\n");
    set_herb_value(( 4 * 20) + (20 * 20)/4 );
    set_id_diff(25);
    set_find_diff(4);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
