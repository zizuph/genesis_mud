/*
 * Kelp, a very useful general-purpose herb.
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "/sys/stdproperties.h"

create_herb()
{
   set_name(({"kelp", "seaweed"}));
   set_short("strand of seaweed");
   set_herb_name("kelp");
   set_id_long();
   set_unid_long("This is a strand of brownish-green seaweed.\n");
   set_id_diff(10);
   set_find_diff(1);
   set_effect(HERB_ENHANCING, "dis", 5);
// ^ It's like eating a live frog.  Nothing worse can happen to you all day.
   set_decay_time(1800);
   set_herb_value(410);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_VALUE, 37);
}
query_recover() { return MASTER + ":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
