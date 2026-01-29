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
    set_name( ({"man", "ginger-bread man"}) );
    set_pname( ({"men", "ginger-bread men"}) );
    set_adj("ginger-bread");
    set_short("ginger-bread man");
    set_pshort("ginger-bread men");
    set_long("A yummy ginger-bread man with a smile and clothing "+
	"of icing. His nose is a tiny little chocolate-chip, and "+
	"his eyes are little marshmallows. He looks delicious.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", chomping off the head first, then the arms, then legs, "+
	"finally eating his body in two big bites!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	", chomping off the head first, then the arms, then legs, "+
	"finally eating his body in two big bites!\n");
}
