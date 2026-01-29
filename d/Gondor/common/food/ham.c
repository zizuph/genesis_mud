inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("ham");
    set_pname("hams");
    set_adj("piece of");
    set_adj("large");
    set_short("piece of ham");
    set_pshort("pieces of ham");
    set_long("This large piece of ham looks delicious. The salty pork meat "
        + "would make a good, full meal.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(75);
    add_prop(OBJ_I_WEIGHT, 225);
    add_prop(OBJ_I_VOLUME, 200);
}

