inherit "/std/armour";
#include "/d/Roke/common/defs.h"
create_armour()
{
 set_name("shirt");
 set_long("This is a shirt made out of tough burlap. It looks "+
  "as though it would offer a little protection.\n");
 set_adj("burlap");
add_adj("rough");

 set_default_armour(7);

}
