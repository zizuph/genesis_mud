/* 
 * Black Rush - Coastal herb, no eating value.
 * Finwe, January 17, 2009
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
    set_name("grass");
    set_adj(({"stout", "sharp-pointed"}));
    set_herb_name("black rush");
    set_short("stout sharp-pointed grass");
    set_pshort("stout sharp-pointed grasses");
    set_ingest_verb("eat");
    set_unid_long("This grass is grayish-green to black and grows along seashores.\n");
    set_id_long("This is grass is from a Black Rush plant. The grass is actually a leaf that has grown so tightly round that it appears to be a stem. The stem tips are sharp-pointed.\n");
    set_herb_value(400);
    set_id_diff(15);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
