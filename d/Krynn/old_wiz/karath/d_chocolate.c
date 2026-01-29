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
    set_name("donut");
    add_name("doughnut");
    set_pname("donuts");
    add_pname("doughnuts");
    set_adj("chocolate");
    set_short("chocolate donut");
    set_pshort("chocolate donuts");
    set_long("A truely magnificent creation. This light and fluffy doughnut "+
	"has been doused with a thick layer of gooey chocolate icing on top. "+
	"It is still very soft and warm from the oven, and it's smell is "+
	"making you drool.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;
	this_player()->command("$drool");
    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", biting down lightly, reveling in the way the "+
	"icing sticks to the corner of your mouth.\nYou lick away the "+
	"extra icing and toss the rest of the donut in your mouth and "+
	"swallow it in one yummy bite.\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
      ", biting down lightly on it, reveling in the way the icing "+
	"sticks to the corners of "+ this_player()->query_possessive() +
	 " mouth.\n" +
	capitalize(this_player()->query_pronoun()) + " licks away the "+
	"extra icing and tosses the rest of the donut into " +
	this_player()->query_possessive() + " mouth and swallows it in "+
	"one yummy bite.\n");
	this_player()->command("$sigh content");
}
