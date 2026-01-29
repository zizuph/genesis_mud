inherit "/std/herb";
#include "/sys/herb.h"
 
create_herb()
{
  set_name("flower");
  set_short("small red flower");
  set_herb_name("loyol");
  set_id_long("This is a loyol, rare herb that can be found " +
    "only in Emerald. It's magical and used in brewing " +
    "potions very often, but eating it can poison you.\n");
  set_unid_long("A small red flower, that you never " +
    "seen before.\n");
  set_ingest_verb("eat");
  set_id_diff(20);
  set_find_diff(7);
  set_effect(HERB_POISONING,"herb",30);
  set_decay_time(4000);
  set_herb_value(500);
}
