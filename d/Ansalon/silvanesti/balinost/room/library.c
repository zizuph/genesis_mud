
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_IN;

reset_balinost_room()
{
    return;
}


create_balinost_room()
{
    set_short("Silvanesti Branch of the Gnomes of Genesis Bank");
    set_long("Unfortunately, like most other businesses in the city, "+
      "the bank is closed.  It looks to have been closed, however, "+
      "for much longer than any of the other places.  Apparently "+
      "it hasn't been used since the Cataclysm.  The gnomes running "+
      "the bank were allowed to stay in the city until then because "+
      "their business was a boon to the city.  Once the fiery mountain "+
      "landed upon Istar, the elves demanded that the gnomes return "+
      "to Mount Nevermind.\n");

    add_exit(BROOM + "street16","west",0);
}
