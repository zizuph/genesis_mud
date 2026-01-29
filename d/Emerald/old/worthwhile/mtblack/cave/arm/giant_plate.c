/* A Giant torso plate - Tulix III, recoded 13/07/95 */
/* This armour is used by  */

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("plate");
    set_pname("plates");
    add_pname("armours");
    set_short("giant torso plate");
    set_pshort("giant torso plates");
    set_long(
        "It looks like Goblin 'craftsmen' made this. Despite this, " +
        "it still looks like a very good, if bulky, piece of armour. " +
        "This torso plate is very large, owing to the fact it was designed " +
        "especially for a giant. It is made out of steel, and is thus " +
        "rather heavy. It protects the torso from damage.\n");

    set_adj("giant");
    add_adj("torso");
    set_ac(41); /* would be 42 but is goblin made. */
    set_am(({ -1, 0, 1}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 20000); /* Heavy.......            */
    add_prop(OBJ_I_VOLUME, 10000); /* I guess its bulky, too. */
}
