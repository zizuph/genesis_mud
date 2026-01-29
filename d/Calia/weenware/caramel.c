// OBJECT:  hallowe'en caramel

    /* Calia Domain

    HISTORY

    [99-10-26] Created by Sheytansha

    PURPOSE

    A nice treat for the players who are nice to the black cat */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>

// OBJECT DEFINITION

void
create_food()

    {

    /*  DESCRIPTION  */

    set_name("caramel");
    add_name("candy");
    set_adj("caramel");
    set_short("caramel candy");

    set_long("This is a hallowe'en treat much like the caramels" +
		 " you used to get when you went trick or treating." +
		 " It's a sweet, chewy caramel.\nHappy Hallowe'en!\n"); 

    /*  PROPERTIES  */

    set_amount(1);
    set_heap_size(1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 25);

    }
