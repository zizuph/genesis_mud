inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("helmet");
  set_short("nomad helmet");
  set_long(break_string(
           "This is the type of helmet that the "+
           "nomads populating the cirathian desert "+
           "use. It is made of iron and has a leather "+
           "visor to protect the eyes from the sun and "+
           "the nose from sand.\n",60));
  set_adj("nomad");

  set_ac(10);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

}