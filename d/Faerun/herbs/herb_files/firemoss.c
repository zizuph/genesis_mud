/* 
 * firemoss - Underdark herb - Protects against fire
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
    set_name("moss");
    set_adj(({"fluffy", "red"}));
    set_herb_name("firemoss");
    set_short("fluffy red moss");
    set_pshort("fluffy red mosses");
    set_ingest_verb("eat");
    set_unid_long("This is a piece of fluffy red moss.\n");
    set_id_long("This is a piece of Firemoss. It is fluffy and red colored and grows in the Underdark. The piece of moss is believed to protect you against fire.\n");
    set_herb_value(( 4 * 10) + (10 * 10)/4 );
    set_id_diff(30);
    set_find_diff(5);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);

    set_effect(HERB_ENHANCING,"fire",10);
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
