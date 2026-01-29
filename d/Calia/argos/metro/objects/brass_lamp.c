/* ARGOS - Metro - A Brass Lamp
**
** Bought in Argos in the brass shop (rooms/brasswrk). Uses a vial of olive
** oil for fuel.
** Patched by Maniac, 16/10/95
**/
inherit "/std/torch";
 
#include <macros.h>
#include "defs.h"
 
void create_torch() {
    set_name("lamp");
   add_name(ARGOS_BRASS_LAMP);
    set_pname("lamps");
    set_adj("brass");
    set_short("brass lamp");
    set_pshort("brass lamps");
    set_long(
       "It is a brass lamp made in the shape of an oblong bowl with "+
       "a lid and pedestal. A handle extends from one end and a "+
       "stem with a wick on the other.\n");
    set_strength(2);
    set_time(1); /* Avoids division by zero */
    burned_out();  /* no oil when purchased */
}

string query_light_fail() {
    if (!query_time(1))
      return "There is no oil in the lamp. You can not light it.\n";
 
    if (find_call_out("burned_out") != -1)
        return "The brass lamp is already lit.\n";
 
    return 0;
}

