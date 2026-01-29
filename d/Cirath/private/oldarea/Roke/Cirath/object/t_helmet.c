inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include <stdproperties.h>
void
create_armour()

{
  set_name("helmet");
  set_short("dirty helmet");
  set_long(break_string(
           "The helmet is made of iron and has a thick layer of dirt on it. "+
           "It ought to be polished!\n",60));
  set_adj("dirty");

  set_ac(15);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,1000);
}