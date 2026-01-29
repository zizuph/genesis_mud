/* A recipe to something mysterious...
 *
 * Aridor 09/95
 *
 */
#include <macros.h>
#include "local.h"

inherit "/std/scroll";

int shake;
string scroll_text;

void
create_scroll()
{
    shake = random(6);

    set_name("paper");
    add_name("horn_recipe");
    set_adj("torn");
    set_long("This is a torn piece of paper, you can read it, but it " +
	     "seems some text is missing. The text itself has been scribbled " +
	     "down by hand and looks unorganized.\n");

    scroll_text = ("...use a mortar to mix these things in:\n" +
		   "(mind the order!)\n" +
		   "-feather from the Mishakalbird\n" +
		   "-what remains from a black dragon after death.\n" +
		   "pour the same number of drops into the mortar as the average muffin has raisins\n" +
		   "-ruby\n" +
		   "-magical powder (unnecessary if any of the above is magical)\n" +
		   (shake / 3 > 0 ? "Stir" : "Shake") +
		   (shake % 3 == 0 ? " carefully" :
		    (shake % 3 == 2 ? " violently" : "")) + " and ...\n");
}

void
read_it(string str)
{
    seteuid(getuid(this_object()));
    say(QCTNAME(this_player()) + " reads the " + QSHORT(this_object()) + ".\n");
    if (!scroll_text)
        write("There was nothing to read on that paper.\n");
    else
      {
	  write(scroll_text);
	  TP->add_prop(HORN_I_SHAKE,(shake < 4));
	  TP->add_prop(HORN_I_HOW,(shake % 3));
	  TP->add_prop(HORN_I_READ_RECIPE,1);
      }
}

int
query_shake()
{
    return shake < 4;
}

int
query_how()
{
    return shake % 3;
}
