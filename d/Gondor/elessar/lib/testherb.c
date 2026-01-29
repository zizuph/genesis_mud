inherit "/d/Gondor/elessar/lib/herb";
#include "/d/Gondor/elessar/lib/herb_types.h"

create_herb()
{
  set_name("berry");
  set_short("little blue berry");
  set_herb_name("attanar");
  set_id_long("This blue berry is an example of the Attanar herb species.\n"+
    "It can be eaten, and will heal hit-points.\n");
  set_unid_long("This blue berry looks like an ordinary berry. You don't know\n"+
    "what it's for.\n");
  set_ingest_verb("eat");
  set_id_diff(35);
  set_find_diff(4);
  set_effect(HERB_HEALING,"hp",-400);
  set_decay_time(450);
  set_herb_value(1050);
}
