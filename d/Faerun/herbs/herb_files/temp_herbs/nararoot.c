/* 
 * nararoot - does nothing. RP wise, female birth
 * control/1 month infertility. For quests or RP.
 * Twire, September 2016
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
    set_name("tuber");
    set_adj(({"black", "woody"}));
    set_herb_name("nararoot");
    set_short("black woody tuber");
    set_pshort("black woody tubers");
    set_ingest_verb("eat");
    set_unid_long("This is a black woody tuber with a licorice-like
    aroma.\n");
    set_id_long("This black woody tuber is known as nararoot, and it can be
    dug up commonly throughout Faerun. It has a very strong, licorice-like
    flavor. It is used for as birth control, as it renders females infertile
    for up to one month if consumed near the begining of a menstrual cycle.
    Though effective if consumed directly, it is often diluted and steeped
    into tea for a more palatable flavor.\n");
    set_herb_value(77);
    set_id_diff(30);
    set_find_diff(2);
    set_decay_time(10000);
    set_dryable();
    set_amount(1);
    
    if(gender=="female")
    {
    return "You feel a subtle numbness in your abdonmen.\n";
    ]
}


string query_recover() { return MASTER + ":"+ query_herb_recover(); }
void   init_recover(string arg) { init_herb_recover(arg); }
