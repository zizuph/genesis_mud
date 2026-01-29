#pragma strict_types
#pragma no_inherit

inherit "/std/object";
inherit "/lib/wearable_item";

#include "../defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_object()
{
   set_name("pendant");
   add_name(RAID_HUMAN_REWARD);
   set_adj(({ "goblin", "fang" }));
   set_short("goblin fang pendant");
   set_long("A small silver chain with a bloody goblin fang hanging " +
      "from it.\n");
   set_layers(1);
   set_looseness(10);
   set_slots(A_NECK);
   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_M_NO_STEAL, 1);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 150);
   add_prop(OBJ_I_VOLUME, 50);
}

public string
query_auto_load()
{
   return MASTER;
}

public void
leave_env(object from, object to)
{
   ::leave_env(from, to);
   wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
   ::appraise_object(num);
   appraise_wearable_item();
}
