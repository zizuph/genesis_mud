/*
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "/sys/stdproperties.h"

create_herb()
{
   set_name(({"_ak_welan_fishliver_oil_","bottle", "oil"}));
   set_adj(({"small", "glass"}));
   set_short("small but heavy glass bottle");
   set_herb_name("fishliver oil");
   set_id_long();
   set_unid_long("This is a bottle of some oily, strong-smelling liquid.\n");
   set_ingest_verb("quaff");
   set_id_diff(10);
   set_find_diff(1);
   set_effect(HERB_ENHANCING,"int", 8); 
   set_decay_time(0);
   set_herb_value(410);
   add_prop(OBJ_I_WEIGHT, 1500);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_VALUE, 37);
}
query_recover() { return MASTER + ":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
