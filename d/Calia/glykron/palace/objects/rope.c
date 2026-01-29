/* Some rope for the hardware store in Calia

    coder(s):   Maniac

    history:     31.1.94    created                         Maniac

    purpose:    players might find rope useful in some cases

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/rope";
#include <stdproperties.h>

void
create_rope()
{ 
    set_name("rope");
    set_pname("ropes");
    set_short("strong rope");
    set_pshort("lengths of strong rope"); 
    set_adj("strong");
    set_long("A length of strong looking rope.\n");

    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, 145);
  
    add_name("_calia_hardware_shop_");
}