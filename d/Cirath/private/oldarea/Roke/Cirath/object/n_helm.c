inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("helm");
  set_short("nomad steel helm");
  set_long(break_string(
           "This is the type of helme that the "+
           "nomads populating the cirathian desert "+
           "use. It is made of steel and has a "+
           "visor to protect the eyes from the sun and "+
           "the nose from sand. It looks quite crude.\n",60));
  set_adj("nomad");

  set_ac(14);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

}