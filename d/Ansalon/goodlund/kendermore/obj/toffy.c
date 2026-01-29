/* Toffy candy for Kendermore, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("toffy");
    add_name("candy");
    set_pname("toffies");
    add_pname("candies");
    set_adj("sweet");
    add_adj("brown");
    set_long("This piece of toffy is covered in foil, but you you can " + 
             "smell the chocolate that wraps around the crunchy toffy " + 
             "inside.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}
    
