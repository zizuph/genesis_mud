/*
 *  /d/Gondor/clubs/nisse/obj/muffin.c
 *
 *  A bran muffin.
 *
 *  Deagol, April 2003
 */

inherit "/std/food";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Prototypes
 */
string	long_desc();

void
create_food()
{
    ::create_food();
    
    set_name("muffin");
    set_adj("bran");
    set_short("bran muffin");
    set_pshort("bran muffins");
    set_long(&long_desc());

    set_amount(150);

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}

string
long_desc()
{
    string nisse_text = "This bran muffin is Cerridwen's own recipe. " +
        "According to her, this is the perfect second breakfast for " +
        "anyone, especially hobbits. The muffin is rich, moist and " +
        "tastes wonderful.";

    string text = "This bran muffin is a secret Nisse recipe. " +
        "According to the cook, this is the perfect second breakfast for " +
        "anyone, especially hobbits. The muffin is rich, moist and " +
        "tastes wonderful.";
    
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
    write("You put " + short() + " into your mouth. It melts on your " +
        "tongue.\n");
}
