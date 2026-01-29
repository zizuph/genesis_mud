/*
 *  A small berry
 *               
 */

inherit "/std/herb.c";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/sys/herb.h"

create_herb()
{
  set_name("berry");
  add_name("berry");
  add_prop(OBJ_I_WEIGHT, 5);
  add_prop(OBJ_I_VOLUME, 2);
  
  set_ingest_verb("eat");
  set_herb_name("lianor berry");
  set_short("small purple berry");
    set_adj(({"small", "purple", }));
  set_id_long("This small, purple berry is well known for its " +
        "healing properties. It is said that it closes small " +
        "wounds in a matter of seconds.\n");
  set_unid_long("This is a small, deep purple berry.\n");
  set_herb_value(75);
  set_find_diff(2);
  set_id_diff(3);
  set_effect(HERB_HEALING,"hp",30);
  set_decay_time(1000);
}

query_recover() { return MASTER+":"+query_herb_recover();  }
init_recover(arg) { init_herb_recover(arg); }
