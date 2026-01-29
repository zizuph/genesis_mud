/* 
 * Large apple for bree quest
 * Finwe, February 2020
 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("apple");
    add_name("honeycrisp apple");
    add_name("_honeycrisp_apple");
    set_short("large Westfarthing apple");
    set_pshort("large Westfarthing apples");
    set_adj(({"large", "Westfarthing"}));
    set_long("This is a large apple from Westfarthing with streaks of " +
        "yellow-orange in its red skin. The apple looks crisp and " +
        "smells sweet, like honey.\n");
    set_amount(340);
    add_prop(OBJ_I_WEIGHT, 340); // these are big apples
    add_prop(OBJ_I_VOLUME, 340);

}
