/* Clothing item for the chests in the Dunlending Camp
 *
 * Raymundo, April 2020
 */

#pragma strict_types

inherit "/std/armour";
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

#define NAME    "dress"
#define ADJ1    "simple"
#define ADJ2    "cotton"
void create_armour()
{
    set_name(NAME);
    add_adj(ADJ1);
    add_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + NAME);
    add_name("clothes");
     add_name("_dunlending_object");
    add_name("skirt");
    set_long("This " + query_short() + " looks simple and plain. "
        + "It has some flowers stiched into it for decoration. You also "
        + "notice some red spots near the neck.\n");
    set_default_armour(0, A_BODY);

    add_item( ({"spots", "red spots"}), "The red spots appear to be blood!\n");
    add_item( ({"flower", "flowers", "stich", "stiched", "embroidery"}),
        "The flowers are made of yellow stiching and look like daisies. "
       + "They're quite beautiful.\n");
}

