 /*
  * clove.c
  *
  * modified from tuo.c by Elessar
  * Olorin, April 1993
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("bud");
    add_name(({"flower", "spice", "_spice"}));
    set_adj(({"flower", "greenish", "small"}));
    set_herb_name("clove");
    set_short("small greenish flower bud");
    set_pshort("small greenish flower buds");
    set_ingest_verb("eat");
    set_unid_long(BS("This is a small greenish flower bud. It emits an aromatic smell.\n"));
    set_id_long(BS("This is a small greenish flower bud of the clove tree. The clove (Eugenia aromatica) " +
    "is an evergreen tree of the myrtle family native to an island far south of Harad. But it has been " +
    "cultivated in Ithilien for centuries. The flower buds of the clove tree are used to flavour dishes. \n"));

    set_effect(HERB_HEALING, "fatigue", 1);
    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(3600);
    set_herb_value(24);
    set_dryable();
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
