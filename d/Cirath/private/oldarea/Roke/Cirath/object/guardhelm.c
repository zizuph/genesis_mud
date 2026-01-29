inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("helmet");
  set_short("large sturdy helmet");
  set_long("This helmet is big and heavy.\n");
  set_adj("sturdy");
  add_adj("large");

  set_ac(15);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

}