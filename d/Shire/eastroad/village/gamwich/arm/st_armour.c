
/* st_armour.c
 * Storytelling hobbit's armour
 * Gamwich Pub 
 * Created 26 February 1995 by Farlong
 */

inherit "/std/armour";

#include <stdproperties.h>

void
create_armour()
{
    set_name("tunic");
    set_adj("soiled");
    add_adj("hobbit");
    set_short("soiled hobbit tunic");
    set_long("This hobbit tunic looks to have had copious amounts "+
        "of alcohol spilt on it.  It's rather dirty.\n");

    set_default_armour();
    set_ac(10);
    set_at(2);

    add_prop(OBJ_I_VALUE,70);

}

