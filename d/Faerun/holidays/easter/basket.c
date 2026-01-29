inherit "/std/container";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <money.h>

void
create_container()
{
    setuid(); seteuid(getuid());

    set_name("basket");
    set_adj("large");
    set_adj("wooden");
    set_short("large wooden basket");
    set_long("This is a large wooden basket. It is made of braided, " +
        "flexible, strips of wood. The basket has a tall, rounded handle " +
        "and full of colored, shredded wood shavings.\n");

    add_item(({"shavings", "wood shavings", "colored wood shavings"}),
        "The wood shavings have been dyed bright, pastel colores. They are shades of yellow, green, pink, and blue.\n");
    add_item(({"handle", "tall handle", "tall rounded handle", "rounded handle"}),
        "The handle is thin and made from flexible strips of wood.\n");
    add_item(({"wood strips", "strips of wood", "flexible strips of wood", "wood"}),
        "The flexible strips of wood are thin and wide. They have been braided together and form the basket and the handle.\n");
    
    add_prop(CONT_I_WEIGHT,     1000); 	
    add_prop(CONT_I_VOLUME,     4000);
    add_prop(CONT_I_MAX_WEIGHT, 4500); 	
    add_prop(CONT_I_MAX_VOLUME, 8000);
    add_prop(OBJ_I_VALUE,        150);

}
