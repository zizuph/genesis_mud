inherit "/std/herb";

#include <herb.h>

create_herb()
{
  set_name("carrot");
  set_adj("black");
  set_short("black carrot");
  set_id_long("This is a carrot-like root. It's black and is "+
              "called wizsha. It tastes really bad and are not "+
              "good for the health. It is easily misplaced with its "+
              "relative gizsha which tastes fine and is good "+
              "for the health. The wizsha root grows in the jungles "+
              "of eastern Athas.\n");
  set_unid_long("It looks like a carrot, except it's black.\n");
  set_herb_name("wizsha");
  set_find_diff(5);
  set_id_diff(40);
  set_dryable();
  set_ingest_verb("eat");
  set_herb_value(600);
  set_decay_time(500);
  set_amount(5);
  set_effect(HERB_HEALING,"hp",-500);
}
