/* 
 * oede - Cures health and fatigue. For this reason, it's set to be difficult 
 * to find and only in limited areas in temperate areas
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
    set_adj(({"broad", "golden"}));
    set_herb_name("oede");
    set_short("broad golden leaf");
    set_pshort("broad golden leaves");
    set_ingest_verb("eat");
    set_unid_long("This is a  broad golden leaf. The leaf is circular and has thin veins.\n");
    set_id_long("This is a leaf from an Oede bush. It is one of the most prized herbs for its healing abilities. According to common folklore, it can cure many aliments and is sought by many herbalists.\n");
    set_herb_value(2592); /* 1.5 plats */
    set_id_diff(50);
    set_find_diff(10);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_HEALING,"hp",50);
    add_effect(HERB_HEALING,"fatigue",30);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
