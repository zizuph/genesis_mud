/* File:          /d/Khalakhor/ship/macdunn/sparkle/lime.c
 * Creator:       Teth
 * Date:          December 5, 1997
 * Modifications:
 * Purpose:       This is a lime, of which a few are placed in the
 *                box on this ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/ship/macdunn/sparkle/box.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"

public void
create_food()
{
    set_amount(10);
    set_name("lime");
    add_name(({"fruit","food"}));
    set_pname("limes");
    add_pname(({"fruits","food"}));
    set_adj("sour");
    add_adj(({"green","citrus"}));
    set_short("sour lime");
    set_pshort("sour limes");
    set_long("A citrus fruit, limes are quite sour in taste. They " +
      "are often used by sailors as a source of nutrients on long " +
      "voyages.\n");
}

/*
public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
      ", puckering your face in reaction to the bitterness!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
      ", puckering " + HIS(this_player()) + " face in reaction to the " +
      "bitterness!\n");
}
*/
