inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("bracers");
  set_short("nomad steel bracers");
  set_long("These bracers are made of steel and painted "+
           "red, the favourite colour of the cirathian "+
           "nomads that lives in the desert.\n");
  set_adj("steel");
  add_adj("nomad");

  set_ac(10);
  set_am(({ 0, 0, 0}));
  set_at(A_ARMS);
}
