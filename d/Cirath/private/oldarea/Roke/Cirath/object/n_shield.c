inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("shield");
  set_short("nomad steel shield");
  set_long("This is a steel shield with a red stripe crossing "+
           "diagonally over it. It's the type of shield that "+
           "the nomad warriors use.\n");
  set_adj("steel");
  add_adj("nomad");

  set_ac(10);
  set_am(({ -1, 1, 0 }));
  set_at(A_SHIELD);
}
