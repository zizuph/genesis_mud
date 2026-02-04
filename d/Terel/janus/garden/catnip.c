 /*
  * catnip.c
  *
  * modified from tuo.c by Elessar
  * Olorin, July 1993
  * following a suggestion by Janus of Terel
  */
inherit "/std/herb";
#include "/sys/herb.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_herb()
{
  set_name("flowers");
  add_name("flower");
  add_name("spice");
  add_name("_spice");
  set_adj("handful");
  set_adj("of");
  set_adj("aromatic");
  set_adj("pale");
  set_adj("purplish");
  set_herb_name("catnip");
  set_short("handful of aromatic pale purplish flowers");
  set_pshort("handfuls of aromatic pale purplish flowers");
  set_ingest_verb("eat");
  set_unid_long(BS("This is a handful of aromatic pale purplish flowers. \n"));
  set_id_long(BS(
    "This is a handful of catnip flowers. Catnip (Nepeta cataria) " +
    "is a perennial of the mint family. The branching herb reaches " +
    "a height of three feet. It has downy leaves and terminal racemes " +
    "of pale purplish flowers. All parts of the plant have an aromatic " +
    "odour when crushed, and this odour is particularly attractive " +
    "to cats. \n"));
  set_herb_value(20);
  set_id_diff(10);
  set_find_diff(2);
  set_effect(HERB_HEALING,"fatigue",1);
  set_decay_time(5000);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
