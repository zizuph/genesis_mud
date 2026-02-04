 /*
  * mint.c
  *
  * modified from tuo.c by Elessar
  * Olorin, April 1993
  */
inherit "/std/herb";
#include "/sys/herb.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_herb()
{
  set_name("leaves");
  add_name("leaf");
  add_name("spice");
  add_name("_spice");
  set_adj("handful");
  set_adj("of");
  set_adj("narrow");
  set_adj("sharply");
  set_adj("toothed");
  set_herb_name("catmint");
  set_short("handful of narrow sharply toothed leaves");
  set_pshort("handfuls of narrow sharply toothed leaves");
  set_ingest_verb("eat");
  set_unid_long(BS("This is a handful of narrow sharply toothed fragant leaves. \n"));
  set_id_long(BS("This is a handful of mint leaves. Mint (Mentha piperita) is a fragant, square-stemmed perennial herb " +
    "of the mint family growing in north temperate zones. It grows to a height of one to three feet. The smooth branchy " +
    "stems bear narrow, sharply toothed leaves that are dotted with minute oil glands. The purplish and occasionally " +
    "white flowers grow in dense clusters. Leaves, stem, and roots contain aromatic oils, the leaves are used to flavour " +
    "dishes.\n"));
  set_herb_value(random(50));
  set_id_diff(10);
  set_find_diff(2);
  set_effect(HERB_HEALING,"fatigue",1);
  set_decay_time(5000);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
