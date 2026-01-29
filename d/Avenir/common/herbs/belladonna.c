// file name: /d/Avenir/common/herbs/nightshade.c
// creator(s): Ilyian
// last update: 29 April, 1995
// purpose: Nasty flower that decreases hp
// note:
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_herb_name("belladonna");
  set_name("flower");
  set_short("black velvety flower");
  add_name("herb");
  add_pname("herbs");
  add_name("_this_is_nightshade_");
  set_adj("black");
  add_adj("velvety");
  set_id_long("This thin black flower (Atropa belladonna) is known "+
     "simply as Belladonna. The petals are so dark a purple as to "+
     "appear black, but they lighten to royal purple near the base. "+
     "This flower grows on a long greenish stem that curls downward "+
     "in a spiral. It can be found in warm, dry areas. It is deadly "+
     "poison if ingested.\n");
  set_unid_long("This is a thin black flower with a long greenish "+
     "stem that curls downwards in a spiral. The petals are so dark "+
     "a purple as to appear black, but they lighten to royal purple "+
     "near the base.\n");
  set_ingest_verb("eat");
  set_id_diff(35);
  set_find_diff(3);
  set_effect(HERB_HEALING,"hp",-1000);  // I said it was deadly...
  set_decay_time(200);
  set_herb_value(200);
}
