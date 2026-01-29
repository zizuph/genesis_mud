 /*
  * elidross.c
  *
  * modified from tuo.c by Elessar
  * Teth, Feb.10/96
  */

#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"blue", "pale", "delicate"}));
    set_herb_name("elidross");
    set_short("delicate pale blue flower");
    set_pshort("delicate pale blue flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("inhale");
    set_unid_long("This is a delicate pale blue flower, probably " +
        "picked in a north temperate forest.\n");
    set_id_long(BSN("This flower has several names. It is given the " +
        "name elidross by the common folk, which originated from the " +
        "Silvanesti E'li D'ross. A rough translation results in the " +
        "other common name, Paladine's Tears. The flower is " +
        "said to have been first discovered after the Cataclysm. This " +
        "wildflower is native to north temperate climes. It is most " +
        "often found growing in a vertical mat between two trees, " +
        "clinging to the trunks. The small blue flowers appear to " +
        "sparkle like teardrops when the light catches them, hence the " +
        "name. Inhaling it is rumoured to prevent certain types " +
        "of inaction."));
    set_herb_value(565);
    set_id_diff(36);
    set_find_diff(8);
    set_effect(HERB_CURING,"kapak_saliva",51);
    set_decay_time(2000);
    set_amount(1);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
