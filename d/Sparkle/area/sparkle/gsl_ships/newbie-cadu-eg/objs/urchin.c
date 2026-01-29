/* File:          /d/Khalakhor/ship/macdunn/calia/urchin.c
 * Creator:       Teth
 * Date:          April 21, 1997
 * Modifications:
 * Purpose:       This is an urchin, of which a few are placed in
 *                the net on the way to Khalakhor or Kalaman.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/calia/
 *                /d/Khalakhor/ship/macdunn/calia/net.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

public void
create_food()
{
    set_amount(7);
    set_name("urchin");
    add_name(({"echinoderm","food"}));
    set_pname("urchins");
    add_pname(({"urchins","foods"}));
    set_adj("sea");
    set_short("sea urchin");
    set_pshort("sea urchins");
    set_long("The sea urchin is a small sea creature, purple or " +
      "red in colour. It has many calcareous spikes radiating " +
      "out from its spherical body. The roe is edible raw.\n");
}

/*
public void
consume_text(object *arr, string vb)
{
    string str;

    write("You crush open " + (str=COMPOSITE_DEAD(arr)) +
      ", and then " + vb + " a feast of roe!\n");
    say(QCTNAME(this_player()) + " crushes open " + str +
      ", and then " + vb + "s a feast of roe!\n");
}
*/
