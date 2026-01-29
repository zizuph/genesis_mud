inherit "/std/weapon";

#include "/sys/wa_types.h" 
#include <stdproperties.h>

void create_weapon()
{
  set_name(({"hatchet","_woodcutter_quest_hatchet"}));
  set_adj(({"small","steel"}));
  set_short("small steel hatchet"); 
  set_long("This small hatchet is made of steel. It is apparently the"+
           " tool of a woodcutter.\n");

  set_hit(14);
  set_pen(13);
  set_wt(W_AXE); 
  set_dt(W_SLASH | W_BLUDGEON); 
  set_hands(W_ANYH); 
}
