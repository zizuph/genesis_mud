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

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

public int skitter(string str);

public void
create_food()
{
    set_amount(10);
    set_name( ({"mouse", "ginger-bread mouse"}) );
    set_pname( ({"mice", "ginger-bread mice"}) );
    set_adj("ginger-bread");
    set_short("ginger-bread mouse");
    set_pshort("ginger-bread mice");
    set_long("A yummy ginger-bread mouse with a smile and whiskers "+
	"of icing. His nose is a tiny little chocolate-chip, and "+
	"his eyes are little marshmallows, and his cute little "+
	"tail is made of licorice rope. He looks delicious, but "+
	"you might want to <play with> him first!\n");
}

init()
{
    add_action(skitter, "play");
    ::init();
}

public int
skitter(string str)
{
/*
    if(!sizeof(PARSE_THIS(str, " [with] [the] %o ")))
	return 0;
*/
object mouse1, mouse2;
if (!parse_command(str, environment(this_object()), "[with] [the] %o", mouse1)
	&&
    !parse_command(str, environment(this_player()), "[with] [the] %o", mouse2))
	return 0;

if (mouse1 != this_object() && mouse2 != this_object())
	return 0;
	

    switch (random(3))
      {
      case 0:
	{
	    write("You skitter your ginger-bread mouse across the floor, "+
		"letting it bounce against the wall.\nYou nimbly pounce "+
		"on it, keeping it from escaping.\n");
	    say(QCTNAME(this_player()) + " skitters " +
		this_player()->query_possessive() + " ginger-bread mouse "+
		"across the floor, letting it bounce against the wall.\n"+
		capitalize(this_player()->query_pronoun()) + " nimbly "+
		"pounces on it, keeping it from escaping.\n");
	    break;
	}
      case 1:
	{
	    write("You grab the tail of the mouse in between your teeth, "+
		"shaking your head wildly back and forth. You could swear "+
		"that you heard a frightened squeek come from the ginger-"+
		"bread creature!\n");
	    say(QCTNAME(this_player()) + " grabs the tail of the mouse "+
		"in between " + this_player()->query_possessive() + " teeth"+
		" shaking " + this_player()->query_possessive() + " head "+
		"wildly back and forth. You could swear that you heard "+
		"a frightened squeek come from the ginger-bread creature!\n");
	    break;
	}
      case 2:
	{
	    write("You roll over on your back, holding the tail of the "+
		"mouse between your feet while you bat it back and forth "+
		"with your hands ... er paws as the case may be.\n");
	    say(QCTNAME(this_player()) + " rolls over on " +
		this_player()->query_possessive() + " back, holding the "+
		"tail of the mouse between " +
		this_player()->query_possessive() + " feet while " +
		this_player()->query_pronoun() + " bats it back and forth "+
		"with " + this_player()->query_possessive() + " pawlike "+
		"hands.\n");
	    break;
	}
      }
    return 1;
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You mew hungrily and " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", chomping off the ears first, then the head, then tail, "+
	"finally eating his body in two big bites!\n");
    say(QCTNAME(this_player()) + " mews hungrily and " + vb + "s " + str +
	", chomping off the ears first, then the head, then tail, "+
	"finally eating his body in two big bites!\n");
}
