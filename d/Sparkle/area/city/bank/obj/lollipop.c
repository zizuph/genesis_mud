/*
 * /w/aeg/sparkle/bank/obj/lollipop.c
 *
 * Edible candy that is given to patrons of the Gnomes
 * of Genesis Main Branch.
 *
 * Created March 2008, by Aeg (Matthew Morin)
 */
 
inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("lollipop");
    add_name( ({ "lollipop", "lolipop", "lolli", "candy" }) );
    add_adj( ({ "large", "circular" }) );
    set_long("This lollipop looks like a giant gold coin! "
        + "Gnomes are not known for their culinary expertise, "
        + "but a sugar filled treat might make them more money. "
        + "It looks like it may be butterscotch.\n");
        /* It is made of slug feces */
    
    set_short("large circular lollipop");
    set_pshort("large circular lollipops");
    set_amount(0);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    
} /* create_food */
