// OBJECT:  cheese fuzzie

    /* Calia Domain

    HISTORY

    [96-03-15] Created by Uhclem from [D:\CALIA\UHCLEM\FUZZIE.DOC].

    [99-10-25] Modified for use in the great Halloween scavenger hunt and moved
        to [D:\CALIA\WEENWARE\FUZZIE.DOC] by Uhclem.

    PURPOSE

    A snack food served on Halloween in the Calia office in the Tower of
    Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>

// Function:  enter_env(inv, from)

/*

Purpose:  used here to trigger the deployment of the mouse from its hole;
called when this object enters an environment.

Arguments:  none

Returns:  nothing

*/

void
enter_env(object env, object from)

{

    object mouse_hole = present("mouse hole", env);

    ::enter_env(env, from);

    if (mouse_hole)

    {

        mouse_hole->deploy_mouse();

    }

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write(
        ({
        "It reveals the subtle fragrance of rodent" +
        " hairs and insect fragments.\n",
        "It smells as if someone had been hiding it in his armpit" +
        " for a long time.\n",
        "It smells like one hand clapping.\n",
        "One might characterize the aroma as a real rip-roarer.\n",
        "Nothing living smells like this, so you feel confident" +
        " that it's not some kind of monster in disguise.\n"
        })[random(5)]);

}

// OBJECT DEFINITION

void
create_food()

{

    /*
     *  DESCRIPTION    
     */

    set_name("fuzzie");
    add_name("cheese fuzzie");
    set_short("cheese fuzzie");

    set_long("This is a little bit of baked fluff that" +
        " smells vaguely of cheese. As you inspect it, you" +
        " detect the presence of processed purified" +
        " non-dairy cheese substitute product, locust bean" +
        " gum and other binders," +
        " non-nutritive sweetening agent, tallowate/beeswax" +
        " blend (for shine), pulverized acorn caps (to" +
        " eliminate excess shine), pork tripe essence" +
        " (for simulated cheese fragrance), and salt. According" +
        " to legend (or so you think you may have heard)," +
        " cheese fuzzies are baked by the ladies down at" +
        " Ersatz Brothers' Real Bakery and a tasty change of" +
        " pace from the meals served at the inns and" +
        " taverns of Genesis. Yum!\n");

    /*
     *  PROPERTIES    
     */

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 25);    /*  total fluff  */

}
