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
    set_name( ({"eclair", "cream-filled eclair"}) );
    set_adj("cream-filled");
    set_short("cream-filled eclair");
    set_long("This delicious eclair is covered in chocolate and has "+
	"just a little dab of cream leaking out of it's moist center.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", first licking off the chocolate from the outside, then "+
	"carefully sucking out the cream from the middle, then tossing "+
	"the empty, withered pastry aside!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	", first licking off the chocolate from the outside, "+
	"then carefully sucking out the cream from the middle, "+
	"then tossing the empty, withered pastry aside!\n");
}
