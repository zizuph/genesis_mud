inherit "/std/herb";
#include "/sys/herb.h"
 
create_herb()
{
  set_name("flower");
  set_short("thorny black flower");
  set_herb_name("grave flower");
  set_id_long("This is a Grave Flower, the extremely rare herb " +
    "that can be found only on the graves. It has no real use " +
    "though.\n");
  set_unid_long("There is something special in this flower. " +
    "Its view makes you sad, and you turn away your look " +
    "feeling that tears soon appear on your eyes.\n");
  set_ingest_verb("eat");
  set_id_diff(60);
  set_find_diff(3);
  set_decay_time(2200);
  set_herb_value(150);
}
