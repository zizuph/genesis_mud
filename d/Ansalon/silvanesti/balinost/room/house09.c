
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
    set_short("An evacuated house");
    set_long("This is a typical house in Balinost.  It was shaped "+
      "from marble and looks like it would be quite comfortable if "+
      "it were furnished.  This house, like most others in the city "+
      "has been evacuated after the darkness came to Silvanesti.  "+
      "The rooms are all bare, but there is evidence of someone "+
      "having lived here as there are spots on the faded floor "+
      "where furniture blocked the sun.  Cobwebs have yet to form "+
      "but will soon unless the evil blanketing the city lifts.\n");

    add_exit(BROOM + "street30","south",0);
}
