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
    set_name("brownie");
    set_pname("brownies");
    set_adj("thick");
    set_short("thick brownie");
    set_pshort("thick brownies");
    set_long("A deliciously thick and chewy brownie. It appears to be "+
      "recently baked, and still is piping hot in your greedy little "+
	"hands.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
      ", getting little brownie crumbles on your clothing. You start to "+
	"brush them off, but instead you carefully grab the biggest pieces "+
	"and pop them into your mouth when you think noone is looking.\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
      ", getting little brownie crumbles on " + this_player()->query_possessive() +
	" clothing. " + capitalize(this_player()->query_pronoun()) +
	" starts to brush them off, but instead carefully pinches the biggest "+
	"pieces, and pops them into " + this_player()->query_possessive() +
	" mouth when " + this_player()->query_pronoun() + " thinks you "+
	"aren't looking!\n");
}
