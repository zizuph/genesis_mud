inherit "/std/herb";

#include <herb.h>

create_herb()
{
  set_name("flower");
  set_adj("red-speckled");
  add_adj("white");
  set_short("white red-speckled flower");
  set_id_long("This flower is caller Iunora. It's known having "+
                "some powers in mana healing if chewing it. Iunora "+
                " usually grows in "+
                "very humid ground, preferably in jungle areas. The "+
                 "flower can be found on the island of Athas.\n");
  set_unid_long("A pretty white flower with red dots on it.\n");
  set_herb_name("iunora");
  set_find_diff(6);
  set_id_diff(40);
  set_dryable();
  set_ingest_verb("chew");
  set_herb_value(40);
  set_decay_time(500);
  set_amount(5);
  set_effect(HERB_HEALING,"mana",300);
}
