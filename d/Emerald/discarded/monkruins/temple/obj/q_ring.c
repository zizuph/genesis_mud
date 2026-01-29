/* temple/obj/q_ring.c is cloned by temple/obj/shovel.c */
inherit "/std/armour.c";
 
#include "/sys/wa_types.h"
#include "/d/Emerald/defs.h"
 
create_armour()
{
  seteuid(getuid(this_object()));
  set_name("ring");
  add_name("_abbot_quest_ring_");
  set_adj("gold");
  set_adj("ruby");
  set_short("gold ring");
  set_long("This is a golden ring with a large ruby set into it. "+
           "Intricate ornaments cover the golden surface, and the "+
           "gem sparkles, as you turn the ring to examine it "+
           "thoroughly. You sense an aura of holiness surrounding "+
           "this artifact.\n");
  set_ac(2);
  set_at(A_ANY_FINGER);
  set_am(({0,0,0}));
 
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VALUE,1000+random(400));
  add_prop(OBJ_M_NO_SELL,"This is much too valuable to sell.\n");
}
