inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("platter");
    set_adj("seafood");
    set_short("seafood platter");
    set_pshort("seafood platters");
    set_long("This is a platter of relatively fresh " +
      "seafood. The large quantity of it is rather cheap, " +
      "as the port of Sanction makes fishing easy for locals: " +
      "As the rivers of lava flow into the sea, marine life tend " +
      "to be boiled, floating to the surface for waiting fisherman.\n");
    set_amount(360);
}
