/* Rock candy for Kendermore, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("rock candy");
    add_name("candy");
    add_pname("rock candies");
    add_pname("candies");
    set_adj("long");
    add_adj("string");
    add_adj("candy");
    add_adj("rock");
    set_short("long string of rock candy");
    set_pshort("long strings of rock candy");
    set_long("Simply a long string with crystalized sugar clinging " + 
             "to it, but you know it will just melt in your mouth.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}
    
