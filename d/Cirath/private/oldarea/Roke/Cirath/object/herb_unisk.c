inherit "/std/herb";

#include <herb.h>

create_herb()
{
  set_name("leaf");
  set_adj("light-green");
  set_short("light-green leaf");
  set_id_long("This leaf comes from the unisk tree. It has "+
              "sharp edges and looks hairy. The colour is "+
              "light-green. The unisk tree grows in the jungles "+
              "of eastern Athas and if eaten, it affects the mana "+
              "in a rather negative way.\n");
  set_unid_long("It's a small leaf with sharp edges.\n");
  set_herb_name("unisk");
  set_find_diff(3);
  set_id_diff(40);
  set_dryable();
  set_ingest_verb("eat");
  set_herb_value(0);
  set_decay_time(300);
  set_amount(5);
  set_effect(HERB_HEALING,"mana",-500);
}
