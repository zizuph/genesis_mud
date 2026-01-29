/* 
 * borage - Cures health and fatigue
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
    set_name("leaf");
    set_adj(({"thick", "large"}));
    set_herb_name("borage");
    set_short("thick large leaf");
    set_pshort("thick large leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a thick large leaf. It is covered with fine bristly hair.\n");
    set_id_long("This is a leaf from the plant Borage. It has thick soft stems and large leaves, both of which are covered in fine bristly hairs. When it blooms, the flowers are star-shaped and a vivid sky blue. When the leaf is eaten, it heals the body and leaves you less tired.\n");
    set_herb_value(( 4 * 25) + (25 * 25)/4 );
    set_id_diff(50);
    set_find_diff(6);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",20);
    add_effect(HERB_HEALING,"fatigue",20);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
