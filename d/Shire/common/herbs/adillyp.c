/*
 * adillyp weed (freshwater grass)
 * This herb grows in water and very wet areas.  It is always meant
 * to be moist.  NEVER add a call to set_dryable to this file!
 */

inherit "/std/herb.c";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "/sys/herb.h"

create_herb()
{
  set_adj(({"wet", "brown"}));
  set_name("weed");
  add_prop(OBJ_I_WEIGHT, 5);
  add_prop(OBJ_I_VOLUME, 2);
  
  set_ingest_verb("eat");
  set_short("river weed");
  set_herb_name("adillyp weed");
  set_id_long("The freshwater herb adillyp is uncommon indeed.  " +
        "It is rumored that it is a quite healthy food.  " +
        "However, it is much better known for its horrible " +
        "taste.\n");
    set_unid_long("This is a freshwater weed.\n");
  set_herb_value(175);
  set_find_diff(2);
  set_id_diff(15);
  set_effect(HERB_ENHANCING,"con",12);
  set_decay_time(600);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) {  init_herb_recover(arg);  }
