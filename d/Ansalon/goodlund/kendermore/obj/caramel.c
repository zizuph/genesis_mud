/* Caramel candy for Kendermore, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("caramel");
    set_pname("caramels");
    add_name("candy");
    add_pname("candies");
    set_adj("chewy");
    set_short("chewy caramel");
    set_long("This piece of caramel is covered in a transparent " + 
             "wrapping. It tempts you with the chewy caramel flavour " + 
             "you know must lie beneath.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}
    
