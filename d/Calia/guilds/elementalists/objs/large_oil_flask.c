/*
 *    large_oil_flask.c
 *
 *  A large oil flask, used to fill lamps and
 *  lanterns. Based on my oil flask standard.
 *
 *  Baldacin@Genesis, Feb 2004.
 */
inherit "/d/Calia/std/oil_flask";
#include <stdproperties.h>

void
create_oil_flask()
{
    set_adj("large");
    add_adj("oil");    
    set_long("This is a cone-shaped bottle with a narrow "+
      "neck that widens at the top. It seems to be able to "+
      "hold a decent amount of lantern oil. Right now it "+
      "is @@query_amount_str@@\n");
    
    set_how_full(4000);  // It's full when we start.
    set_max_hold(4000);  // Set's the maximum amount of oil it holds.
}