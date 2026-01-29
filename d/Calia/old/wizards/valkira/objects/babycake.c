// OBJECT:  baby cake

    /* Calia Domain

    HISTORY

    [97-03-12] Created by Uhclem from [C:\CALIA\UHCLEM\BABYCAKE.DOC].

    PURPOSE

    A snack food served in Uhclem's workroom. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>

// OBJECT DEFINITION

void
create_food()

    {

    /*  DESCRIPTION  */

    set_name("cake");
    add_name("babycake");
    set_adj("baby");
    set_short("babycake");

    set_long("This is a light fluffy cake with a thick" +
        " coating of sugary frosting. It's traditional fare served" +
        " by giants to their growing children, so just one is quite" +
        " a meal. The potent aromas of vanilla and cinnamon waft" +
        " to your nose, piquing your appetite and letting you" +
        " know that this treat was baked only minutes ago by the" +
        " ladies down at Ersatz Brothers' Real Bakery. Yum!\n");

    add_item(({"frosting", "sugary frosting", "coating"}),
        "The frosting is off-white and appears to be" +
        " buttercream.  The slight yellow-brown tint must" +
        " come from the addition of plenty of extra butter and" +
        " vanilla, and the frosting has been spread mighty" +
        " thick.  Eating one of these cakes should give" +
        " you plenty of energy!\n");

    /*  PROPERTIES  */

    set_amount(500);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 400);

    }
