/* e-Wine for Shire Inns
 * Taveren, January 2001
 *
 * emotes and add_items added 
 * Raymundo, Jan 2020
 */

inherit "/std/drink";
#include "/d/Shire/defs.h"


void
message()
{
	if(TP->query_race_name() == "elf")
	{
		say(QCTNAME(TP) + " cries out in elvish: "
			+ "Hi miruvor na- -o orchel qualitui "
			+ "na firen miruvor! as " + HE_SHE(TP) + " drinks the "
			+ query_short() + ".\n");
		write("Without meaning to, you express how much you like "
			+ "the wine in Elvish!\n");
		return;
	}
}

void
create_drink()
{
	string adj1 = "elven";
 	string adj2 = "ice";
	string name = "wine";
	
      set_name(name);
      add_adj(adj1);
	  add_adj(adj2);
      set_short(adj1 + " " + adj2 + " " + name);
      
      set_long("This " + query_short() + 
		" is nearly clear in color, with only a faint hint "
		+ "of yellow. It smells of flowers and grass and butterscotch. It is "
		+ "commonly served cold and in a fluted glass so that you can "
		+ "appreciate its clarity.\n");
	
	add_item( ({"glass", "flute", "fluted glass"}), 
		"The flute has a short, extremely delicate stem which leads to "
		+ "a narrow cylinder of thin glass. If you were to hold the "
		+ "wine up to the light, you could appreciate its delicate "
		+ "color even more.\n");
	add_cmd_item( ({"wine", "glass", "flute", "fluted glass"}), 
		"smell", "You place your nose over the glass and inhale gently. "
		+ "First you smell flowers--daisies, mostly, but also wildflowers from "
		+ "mountain meadows--then grass, heavy with morning dew. Finally, "
		+ "you smell a hint of butterscotch, not much, but just enough "
		+ "sweetness to balance the acidity of the grapes. It's as if a "
		+ "very old elf spent his very long life doing nothing but making "
		+ "wine, and this is the product of his dedication.\n");
	add_cmd_item( ({"wine", "glass", "flute", "fluted glass"}),
		"feel", "You place your hand against the " + query_short() + 
		" and notice how cold it feels, not ice cold, but like the waters of "
		+ "a mountain river in the spring.\n");
      set_soft_amount(70);
      set_alco_amount(30);
	  
	  set_drink_msg(message());
}

void
init()
{
	::init();
	add_action("hold_glass", "hold");
	add_action("hold_glass", "lift");
}

int
hold_glass(string str)
{
	 if(!strlen(str))
        {
            notify_fail("Lift the glass up? to the light?");
            return 0;
        }
        if (parse_command(str, TO, " [the] [elven] 'wine' [up] [to] [the] 'light' "))
		{
			write("You lift the " + query_short() + " up to the light and notice how "
				+ "the pale yellow color becomes just a little more intense with "
				+ "the light behind it.\n");
			say(QCTNAME(TP) + " holds the " + query_short() + " up to the light "
				+ "and marvels at its exquisite color.\n");
			return 1;
		}
}
