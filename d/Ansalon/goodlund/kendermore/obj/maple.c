/* Maple candy for Kendermore, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("maple");
    set_pname("maples");
    add_name("candy");
    add_pname("candies");
    set_adj("sweet");
    add_adj("sticky");
    set_long("This piece of maple candy is made from hardened maple syrup. " + 
             "It's very sweet with a delicious maple flavour that will " + 
             "melt in your mouth.\n");
    set_amount(10);
    add_prop(OBJ_I_VALUE, 20);
}
    
