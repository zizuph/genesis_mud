/* Brandy for Kendermore, Gwyneth, May 1999 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(200);
    set_alco_amount(30);
    set_name("brandy");
    add_name("snifter");
    set_pname("brandies");
    add_pname("snifters");
    set_adj("strong");
    add_adj("blackberry");
    set_short("snifter of brandy");
    set_pshort("snifters of brandy");
    set_long("With its sweet blackberry flavour, this is one of the " + 
             "tastier looking alcoholic drinks you've encountered. You " + 
             "know it will leave a warm feeling in your throat if you " + 
             "drink it. \n"); 
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    set_drink_msg("You feel a glowing warmth in your throat as you " + 
                  "swallow the blackberry brandy.\n");
}
