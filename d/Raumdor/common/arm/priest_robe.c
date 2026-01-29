#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    set_name("robe");
    set_adj("white");
    set_short("white robe");
    set_long(
      "This is the white robe like one worn by a priest. The collar is flat " +
      "and tight around the neck, while rippling cloth drapes around the " +
      "feet.\n");
    set_ac(10);
    set_at(A_ROBE);
}
