/* Honey coded by Mylos   9-8-93
 * Cloned by hive
 */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("honey");
   add_name("_mylos_honey_");
    set_adj("brown");
    set_long("Beautiful dark rich honey, almost making your mouth water.\n");
    set_amount(35); /* 35 grams of food. */
    add_prop(OBJ_I_WEIGHT, 35); 
    add_prop(OBJ_I_VOLUME, 30);
}
