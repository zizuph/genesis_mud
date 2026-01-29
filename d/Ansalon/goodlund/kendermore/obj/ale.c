/* Kendermore ale, Gwyneth, May 1999 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(125);
    set_alco_amount(10);
    set_name("ale");
    add_name("mug");
    set_pname("ales");
    add_pname("mugs");
    set_adj("foamy");
    set_short("foamy mug of ale");
    set_pshort("foamy mugs of ale");
    set_long("This is a mug of golden ale, a favourite of kenders. It " + 
             "looks very refreshing, if a bit bitter. \n");
    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_I_VOLUME, 125);
}
    
