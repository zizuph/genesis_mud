/*
 *  /d/Gondor/clubs/nisse/obj/scone.c
 *
 *  A potato scone.
 *
 *  Deagol, April 2003
 */

inherit "/std/food";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 *  Prototypes
 */
string	long_desc();

void
create_food()
{
    ::create_food();
    
    set_name("scone");
    set_adj("potato");
    set_short("potato scone");
    set_pshort("potato scones");
    set_long(&long_desc());

    set_amount(150);

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}

string
long_desc()
{
    string nisse_text = "Made from a recipe Brigid has given Cerridwen, " +
        "this potato scone is golden brown with a sprinkling of paprika " +
        "on top. The scone contains bits of soft boiled potatoes and is " +
        "quite filling.";

    string text = "Made from a recipe that has been passed down among the " +
        "Nisse for ages, this potato scone is golden brown with a " +
        "sprinkling of paprika on top. The scone contains bits of soft " +
        "boiled potatoes and is quite filling.";

    if (TP->query_nisse_level())
    {
        return nisse_text + "\n";
    }
    
    return text + "\n";
}

/*
 *  Function name: special_effect
 *  Description  : This routine is called when a player eats the cram.
 *  Arguments    : int amnt - amount of food
 */
public void
special_effect(int amnt)
{
    write("You munch " + short() + " quickly. It tastes great!\n");
}
