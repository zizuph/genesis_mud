// OBJECT:  breadstick

    /* Calia Domain

    HISTORY

    [1999-02-20] Created by Uhclem from [C:\CALIA\GELAN\BREADSTI.DOC].
    [2001-12-29] Uhclem added set_adj value.

    PURPOSE

    A newbie-sized food sold by the half-dozen in the Gelan bakery. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>

// OBJECT DEFINITION

void
create_food()

{

    /*
     *  DESCRIPTION    
     */

    string *flavors = ({"garlic-cheddar", "rye", "pumpernickel", "onion-dill",
        "onion", "garlic"});

    /*
     *  We'll only require the baker to make one flavor each day.   
     */

    string flavor = flavors[(object_time() / 3600) % sizeof(flavors)];

    set_name("breadstick");
    set_adj(flavor);

    set_long("This freshly-baked morsel appeals to the smaller" +
        " appetite. Its savory " + flavor + " aroma promises a taste" +
        " treat as well as good nutrition.\n");

    /*
     *  PROPERTIES    
     */

    set_amount(5);
    set_heap_size(6);

}
