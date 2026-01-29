inherit "/std/herb";

#include <herb.h>

create_herb()
{
  set_name("carrot");
  set_adj("black");
  set_short("black carrot");
  set_id_long("This is a carrot-like root. It's black and is "+
              "called gizsha. It has a good taste and has some "+
              "healing powers. It is easily misplaced with its "+
              "relative wizsha which tastes bad and is not good "+
              "for the health. The gizsha root grows in the jungles "+
              "of eastern Athas.\n");
  set_unid_long("It looks like a carrot, except it's black.\n");
  set_herb_name("gizsha");
  set_find_diff(6);
  set_id_diff(40);
  set_dryable();
  set_ingest_verb("eat");
  set_herb_value(600);
  set_decay_time(500);
  set_amount(5);
  set_effect(HERB_HEALING,"hp",300);
}
