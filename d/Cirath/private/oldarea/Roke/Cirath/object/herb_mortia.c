inherit "/std/herb";

#include <herb.h>
#include "/d/Roke/Cirath/defs.h"

create_herb()
{
  set_name("flower");
  set_adj("yellowish");
  set_short("yellowish flower");
  set_id_long("This flower is call mortia. It's a very pretty "+
              "flower, but extremely poisonous to eat. The "+
              "mortia flower grows where it can find much water "+
              "and not too much light.\n");
  set_unid_long("This must be one of the most beautiful flowers "+
                "you've ever seen.\n");
  set_herb_name("mortia");
  set_find_diff(4);
  set_id_diff(50);
  set_dryable();
  set_ingest_verb("eat");
  set_herb_value(40);
  set_decay_time(500);
  set_amount(5);
  set_effect(HERB_HEALING,"mana",300);
  set_poison_file(OBJ+"herb_poison");
  set_effect(HERB_POISONING);
  seteuid(getuid());
}
