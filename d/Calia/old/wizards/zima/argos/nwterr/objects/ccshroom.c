/*
 *  A simple, useless, but interesting mushroom. It is a tour object in
 *  Argos
 */
 
inherit "/std/herb.c";
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"
 
create_herb()
{
   set_name(({"_crucicrescent_shroom","mushroom"}));
   set_adj(({"purple","striped"}));
   set_short("striped purple mushroom");
   set_herb_name("crucicrescent");
   set_id_long(break_string(
      "This is a purple mushroom with yellow stripes on its cap. "
    + "One stripe curves along the rim of the roof and looks like "
    + "a moon, while two stripes cross in the center. It is commonly "
    + "found around sheep dung in the pastures of Argos, but has no "
    + "known potencies.\n",60));
   set_unid_long(break_string(
      "This a is purple mushroom with yellow stripes on its cap. "
    + "One stripe curves along the rim of the roof and looks like "
    + "a moon, while two stripes cross in the center. It is commonly "
    + "found around sheep dung and is native to Argos.\n",60));
   set_ingest_verb("eat");
   set_id_diff(100);
   set_find_diff(0);
   set_decay_time(3000);
   set_herb_value(10);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 100);
}
