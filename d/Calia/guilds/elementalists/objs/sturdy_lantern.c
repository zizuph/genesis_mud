/*
 *    sturdy_lantern.c
 *
 *  A sturdy glass lantern with adjustable wick.
 *  Based on my lantern standard.
 *
 *  Baldacin@Genesis, Feb 2004.
 *
 */
inherit "/d/Calia/std/lantern";
#include <stdproperties.h>

void
create_lantern()
{
    set_adj("sturdy");
    add_adj("glass");    
    set_long("This is a sturdy glass lantern. It is "+
      "held together by thin pieces of wood and small "+
      "fragments of glass that has been inserted between "+
      "the wooden pieces, allowing for the light to "+
      "shine through. A thin wire handle has been "+
      "secured to the glass lamp so that it can be "+
      "carried or hung on something. It is also possible "+
      "to <adjust> the wick on this lantern, to alter the "+
      "amount of light it sheds.\n");
    
    set_strength(2);             // How many levels of light it gives
    set_oil_capacity(0);         // It's empty when we start.
    set_max_oil_capacity(1200);  // The maximum amout of oil it can hold.
    set_adjustable_wick(1);      // It is possible to adjust the wick, deciding
                                 // how bright it should light. Standard is 0,
	                             // wich means it run on max strength.
}