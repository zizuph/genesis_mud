inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("greaves");
  set_short("nomad steel greaves");
  set_long("These greaves are made of red-painted steel. "+
           "The colour red is holy to the nomad warriors "+
           "that lives in the desert of Cirath.\n");
  set_adj("steel");
  add_adj("nomad");

  set_ac(10);
  set_am(({ 0, 0, 0}));
  set_at(A_LEGS);
}
