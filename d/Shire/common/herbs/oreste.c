/*
 *  Oreste berry, adapted from the evendim grass.
 *  Coded by Qualar           
 */

inherit "/std/herb.c";
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/defs.h"
#include "/sys/herb.h"

create_herb()
{
  set_adj(({"red"}));
  set_name("berry");
  set_pname("berries");
  add_name("berry");
  add_prop(OBJ_I_WEIGHT, 20);
  add_prop(OBJ_I_VOLUME, 20);

  set_ingest_verb("eat");
  set_short("red berry");
  set_herb_name("oreste");
  set_id_long("The oreste berry can be found in many fields and " +
        "is said to endow strength to whomever eats it. Nonetheless, " +
        "it is said to be dangerous when too many are eaten. The " +
        "berry looks fierce and juicy.\n");
  set_unid_long("This is a fierce, juicy, red berry\n");
  set_herb_value(400);
  set_find_diff(4);
  set_id_diff(20);
  set_effect(HERB_ENHANCING,"str",15);
  set_decay_time(500);
}
query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }

