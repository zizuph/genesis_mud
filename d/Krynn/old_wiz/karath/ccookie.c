/* File:          /d/Khalakhor/ship/macdunn/ansalon/pickle.c
 * Creator:       Teth
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This is a pickle, of which many are placed in the
 *                barrel on the way to Khalakhor or Kalaman.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/ship/macdunn/ansalon/barrel.c
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
    set_amount(10);
    set_name("cookie");
    set_pname("cookies");
    set_adj("sugar");
    set_short("sugar cookie");
    set_pshort("sugar cookies");
    set_long("A yummy sugar cookie, lightly crusted with sugar and " +
      "pressed in a criss-cross with a fork.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
      ", licking your lips to get the delicious sugar crusted crumbs "+
	"that were left over from each bite!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
      ", licking " + this_player()->query_possessive() + " lips to "+
	"get the delicious sugar crusted crumbs that were leftover "+
	"from each bite!\n");
}
