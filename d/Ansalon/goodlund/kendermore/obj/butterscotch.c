/* Butterscotch candy for Kendermore, Gwyneth, May 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("butterscotch");
    set_pname("butterscotches");
    add_name("candy");
    add_pname("candies");
    set_adj("sweet");
    add_adj("yellow");
    set_long("This piece of butterscotch is covered in crinkly yellow " + 
             "wrapping, and you can hardly wait to tear it open and pop " + 
             "it in your mouth.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}
    
