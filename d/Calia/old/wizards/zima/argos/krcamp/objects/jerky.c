/* Jerky carried by kretans */
inherit "/std/food";
#include <stdproperties.h>
 
create_food() {
    set_name("jerky");
    add_name(({"strip","strip of jerky"}));
   set_short("strip of jerky");
   set_pshort("strips of jerky");
    set_long(
       "It is a piece of jerky, a thick strip of dried and smoked mutton.\n");
    set_amount(75);
}
