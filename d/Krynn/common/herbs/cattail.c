 /*
  * cattail.c
  *
  * modified from tuo.c by Elessar
  * Teth, Feb 06, 1996
  */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("root");
    set_adj(({"thick", "brown"}));
    set_herb_name("cattail");
    set_short("thick brown root");
    set_pshort("thick brown roots");
    set_pname(({"roots", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long("This thick brown root probably anchored a tall " +
        "grass-like plant with sharp leaves.\n");
    set_id_long(BSN("This is the thick brown root of cattail. Cattail " +
        "(Typha latifolia) is a tall grass-like plant with slender " +
        "leaves and a club-like inflorescence that is found in ponds and " +
        "still waters. The root is used as a foodstuff."));
    set_herb_value(70);
    set_id_diff(10);
    set_find_diff(2);
    set_effect(HERB_HEALING,"fatigue",2);
    set_decay_time(10000);
    set_dryable();
    set_amount(50);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
